from pathlib import Path
from typing import Tuple, Any
import errno
import os
import shlex
import subprocess as sp
import sys

from flatdict import FlatDict # type: ignore
import yaml # type: ignore

from utils.logger import log
from utils.file import delete_dir, get_file_list

# =============
# Utility types
# =============

# Stores paths to dependencies
# their include directories and libraries.
class DepDict(dict):
    def __init__(self, *arg, **kw):
        super().__init__(*arg, **kw)


    # Adds necessary switches to `include/` dir paths
    def add_inc_switch(self, includes: list) -> list:
        log.info('Processing include directories...')
        result = [f'-I{path}' for path in includes]

        return result


    def add_lib_switch(self, libs: list) -> list:
        log.info('Processing libraries...')
        result = [f'-L{path}' for path in libs]

        return result


    # Returns a list of library arguments for all dependencies
    # TODO: Check for the `enabled` flag
    def get_libargs(self) -> list:
        args = []
        log.info('Fetching libraries...')
        for key, val in self.items():
            if 'args' in key:
                for arg in val:
                    args.append(arg)

        return args


    # Resolves all dependency paths
    # TODO: Check for the `enabled` flag
    def resolve(self, dirs: dict):
        log.info('Resolving paths...')
        lib_dir = ''
        for key, val in self.items():
            # FlatDict represents a key like such
            # lv1:lv2:lv3 = val
            # We retrieve the topmost key
            # and use as the name of dependency
            name = key.split(':')[0]

            # We encountered the relevant key
            # that contains all path information
            if 'paths' in key:
                # Set the library directory
                if 'lib' in key:
                    lib_dir = val

                # Resolve and merge into our dict
                new_path = dirs['deps'] / name / val
                self[key] = new_path

            # Do the same for libraries
            if 'libs' in key:
                # Libraries are always stored in an array
                libs = []
                for lib in val:
                    # Get directory
                    lib_path = dirs['deps'] / name / lib_dir / lib
                    libs.append(lib_path)
                
                self[key] = libs


    def get_libs(self) -> list:
        log.info('Fetching library directories...')
        libraries = []
        for key, val in self.items():
            if 'paths' in key and 'lib' in key:
                libraries.append(f"\"{val}\"")

        return libraries


    # Returns a list of necessary include directories
    # for compiling.
    # TODO: Check for the `enabled` flag
    def get_includes(self, dirs: dict) -> list:
        log.info('Fetching include directories...')
        includes = []
        for key, val in self.items():
            if 'paths' in key and 'include' in key:
                includes.append(f"\"{val}\"")
                
        includes.append(f"\"{dirs['include']}\"")
        includes.append(f"\"{dirs['source']}\"")

        return includes


# ==============================
# Handles the configuration file
# ==============================
class Config(object):
    def __init__(self, path: Path):
        # Basic project setup
        # ===================
        self.config_path = path.resolve()
        (self.config, self.config_raw) = self.load_config(self.config_path)

        # Main project directory
        # extrapolated from the config path
        self.root = self.config_path.parent

        # Project configuration
        # =====================

        # Metadata
        self.name = self.config_get('project:name')
        self.authors = self.config_get('project:authors')
        self.version = self.config_get('project:version')
        self.language = self.config_get('project:language')

        # Project structure
        self.dirs = self.config_get('project:dirs')
        self.process_dirs()

        # List of directories necessary to be included during build
        self.includes = []

        # Project setup
        self.build_files = self.config_get('project:setup:files')
        self.build_type = self.config_get('project:setup:type')
        self.compiler = self.config_get('project:setup:compiler')
        self.profiles = self.config_get('project:setup:profiles')
        self.process_files()

        # Dependencies
        # ============
        self.raw_deps = self.config_get('project:dependencies')
        self.process_deps()

        # Adjusts target directories and add build flags
        # according to build profiles
        self.build_flags = self.profile_setup()

        # Clean-up directories
        self.cleanup_dirs = [self.dirs['build'], self.dirs['target']]


    # Resolve source and header files according to root directories
    def process_files(self):
        log.info('Resolving source and header files...')
        for key, path in self.build_files.items():
            temp_paths = []

            if key == 'sources':
                for p in path:
                    temp_paths.append(self.dirs['source'] / p)
            if key == 'include':
                for p in path:
                    temp_paths.append(self.dirs['include'] / p)

            # Put them back into the dictionary
            self.build_files[key] = temp_paths


    # Resolve all paths relative to project root
    def process_dirs(self):
        log.info('Resolving project directories...')
        for key, path in self.dirs.items():
            if isinstance(path, list):
                temp_paths = []
                for p in path:
                    temp_paths.append(self.root / p)
                
                self.dirs[key] = temp_paths
            else:
                self.dirs[key] = self.root / path


    # Using a utility types, resolve paths and add switches
    # to all of dependencies
    def process_deps(self):
        log.info('Resolving project dependencies...')
        self.deps = DepDict(self.raw_deps)
        self.deps.resolve(self.dirs)

        includes = self.deps.get_includes(self.dirs)
        self.includes = self.deps.add_inc_switch(includes)

        libraries = self.deps.get_libs()
        self.libraries = self.deps.add_lib_switch(libraries)

        self.libargs = self.deps.get_libargs()


    # Acquires a list of target directories
    # and build flags for specific profiles.
    def profile_setup(self):
        log.info('Setting up target directories and build flags...')

        target_dirs = []
        for profile in list(self.profiles):
            target_dirs.append(f"{self.dirs['target']}/{profile}")

        self.dirs['target'] = target_dirs

        # Resolve directories
        new_dirs = []
        for dir in self.dirs['target']:
            new_dirs.append(self.root / dir)

        self.dirs['target'] = new_dirs

        build_flags = dict()
        for k, v in self.profiles.items():
            build_flags[k] = v

        return build_flags


    # Load config as a raw yaml dump and a flat dictionary.
    def load_config(self, path: Path) -> Tuple[FlatDict, dict]:
        result = (FlatDict(), dict())

        log.info('Loading project configuration...')
        with open(path) as file:
            dump = yaml.load(file, Loader=yaml.FullLoader)
            result = (FlatDict(dump), dump)
        
        if result[0] is None or result[1] is None:
            log.error('Unable to parse configuration file')
            sys.exit(os.strerror(errno.BADF))

        return result


    def config_get(self, key: str) -> Any:
        value = self.config.get(key)

        if value is None:
            log.warning('Key not found in configuration file' , key=key)
            return
        else:
            return value


    # Traverses the yaml dump recursively and retrieves a value given a key.
    def config_find_val(self, key: str, src: Any) -> Any:
        for k, v in (src.items() if isinstance(src, dict) else enumerate(src) if isinstance(src, list) else []):
            if k == key:
                yield v
            elif isinstance(v, (dict, list)):
                for result in self.config_find_val(key, v):
                    yield result


    # Internally calls into `self.config_find_val` and performs a simple check.
    def config_get_raw(self, key: str) -> Any:
        for value in self.config_find_val(key, self.config_raw):
            if value is None:
                log.warning('Key not found in configuration file' , key=key)
                return
            else:
                return value


# ========================
# Does the actual building
# ========================
class Builder(Config):
    def __init__(self, path: Path):
        super().__init__(path)

    # Prepare intermediate and target build dirs
    def prepare_dirs(self):
        log.info('Checking if build and target dirs are present...')
        if not self.dirs['build'].exists():
            self.dirs['build'].mkdir()
        
        for path in self.dirs['target']:
            if not path.exists():
                path.mkdir(parents=True)


    def clean_up(self):
        for path in self.cleanup_dirs:
            delete_dir(path)


    # TODO: Check for the `enabled` flag
    # TODO: clean all this up
    def build(self):
        for source in self.build_files['sources']:
            input_file = source.name

            obj_file = self.dirs['build'] / f"{input_file.split('.')[0]}.o"
            
            # First compile object files.
            # TODO: support for profiles
            gcc_build_cmd = f"{self.compiler} -c -o \"{obj_file}\" {' '.join(self.includes)} \"{source}\" {' '.join(self.build_flags['debug'])}"

            # Split according to windows launch parameter rules
            gcc_build_cmd = shlex.split(gcc_build_cmd)

            # Run the command
            process = sp.run(gcc_build_cmd, capture_output=True)
            if process.returncode == 0:
                log.info('Build complete')

                if process.stderr:
                    log.info('Captured output: ')
                    log.info(process.stderr.decode('utf-8'))
            else:
                log.error('Build did not succeed')
                log.error(process.stderr.decode('utf-8'))

        # Glob all object files
        obj_files = get_file_list(self.dirs['build'], '*.o')
        obj_files = [f'\"{path}\"' for path in obj_files]

        # Change output type and arguments based on config
        # TODO: support for profiles and different args
        if self.build_type == 'lib':
            output_file = self.name + '.lib'
        elif self.build_type == 'exe':
            output_file = self.name + '.exe'
        else:
            log.error('Invalid project type: ', type=self.build_type)
            sys.exit(1)

        # TODO: support for changing profile type
        destination_path = f"\"{self.dirs['target'][0] / output_file}\""

        # Link all object files together
        gcc_build_cmd = f"{self.compiler} -o {destination_path} {' '.join(obj_files)} {' '.join(self.build_flags['debug'])} {' '.join(self.libraries)} {' '.join(self.libargs)}"
        gcc_build_cmd = shlex.split(gcc_build_cmd)

        process = sp.run(gcc_build_cmd, capture_output=True)
        if process.returncode == 0:
            log.info('Final build complete')

            if process.stderr:
                log.info('Captured output: ')
                log.info(process.stderr.decode('utf-8'))
        else:
            log.error('Final build did not succeed')
            log.error(process.stderr.decode('utf-8'))

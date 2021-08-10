from pathlib import Path
from typing import Tuple, Any
import errno
import os
import shlex
import subprocess as sp
import sys
import hashlib

from flatdict import FlatDict # type: ignore
import yaml # type: ignore

from utils.logger import log
from utils.file import delete_dir, get_file_list

# =============
# Utility types
# =============

# Manages dependency paths, collects and resolves them
# for use in building.
class DepDict(dict):
    def __init__(self, *arg, **kw):
        super().__init__(*arg, **kw)
    
    # Returns a list of all include directories
    def get_includes(self, dirs: dict) -> list:
        log.info('Fetching include directories...')
        includes = []
        for val in self.values():
            if val['enabled'] is True:
                include_dir = val['paths']['include']

                includes.append(f'\"{include_dir}\"')
                
        # Append main project source and include directories.
        includes.append(f"\"{dirs['include']}\"")
        includes.append(f"\"{dirs['source']}\"")

        return includes
    
    # Returns a list of all library directories
    def get_lib_paths(self) -> list:
        log.info('Fetching library directories...')
        libpaths = []
        for val in self.values():
            if val['enabled'] is True and val['header_only'] is False:
                lib_dir = val['paths']['lib']

                libpaths.append(f'\"{lib_dir}\"')

        return libpaths

    # Adds `-I` switch to include dirs
    def process_include_paths(self, includes: list) -> list:
        log.info('Adding switches to include directories...')
        result = [f'-I{path}' for path in includes]

        return result

    # Adds `-L` switch to lib dirs
    def process_lib_paths(self, libs: list) -> list:
        log.info('Adding switches to library directories...')
        result = [f'-L{path}' for path in libs]

        return result

    # Returns a list of library switches for all dependencies
    def get_lib_bins(self) -> list:
        log.info('Fetching libraries...')
        args = []
        for key, val in self.items():
            if val['enabled'] is True and val['header_only'] is False:
                for arg in val['args']:
                    args.append(arg)

        return args

    def resolve(self, dirs: dict):
        log.info('Resolving paths...')
        # Check for the enabled flag
        for key, val in self.items():
            if val['enabled'] is True:
                # Resolve include and lib directory for each dependency.
                # NOTE: key represents the name of the package here
                for path in val['paths'].values():
                    new_path = dirs['deps'] / key / path

                    self[key]['paths'][path] = new_path

                # Do the same for the libraries themselves
                # NOTE: only if they contain a library.
                if val['header_only'] is False:
                    new_libs = []
                    for path in val['libs']:
                        lib_path = val['paths']['lib']
                        new_path = dirs['deps'] / key / lib_path / path
                        
                        new_libs.append(new_path)
                    
                    self[key]['libs'] = new_libs
            else:
                continue


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
        self.raw_deps = self.config_get_raw('dependencies')
        self.process_deps()

        # Adjusts target directories and add build flags
        # according to build profiles
        self.build_flags = self.profile_setup()

        # Clean-up directories
        self.cleanup_dirs = [self.dirs['build'], self.dirs['target']]


    # Selects a specific target from the parsed configuration file
    # using the command-line arguments
    def set_target(self, target: str):
        if target in list(self.profiles):
            self.selected_target = target
        else:
            log.error('Target \"{target}\" not present in config')
            log.error('Defaulting to first target defined in the config file')
            self.selected_target = list(self.profiles)[0]

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
        self.includes = self.deps.process_include_paths(includes)

        libraries = self.deps.get_lib_paths()
        self.libraries = self.deps.process_lib_paths(libraries)

        self.libargs = self.deps.get_lib_bins()


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


    # Performs a simple clean up
    def clean_up(self):
        for path in self.cleanup_dirs:
            delete_dir(path)


    # Compiles all the source files into object files.
    def compile_sources(self):
        # Use the selected target from the commandline args
        target = self.selected_target
        log.info(f'Starting \"{target}\" build...')

        # Gather all the source files
        for source in self.build_files['sources']:
            src = source.name

            # Get hash of the file
            src_hash_raw = str(source).encode('utf-8')
            src_hash = hashlib.md5(src_hash_raw).hexdigest()[:8]

            # Get destination file path
            obj = self.dirs['build'] / f"{src.split('.')[0]}-{src_hash}.o"

            # Prepare vars for compiling
            includes = ' '.join(self.includes)
            build_flags = ' '.join(self.build_flags[target])

            # Build the command and split for compiler arguments
            cmd_build_obj = f"{self.compiler} -c -o \"{obj}\" \"{source}\" {includes} {build_flags}"
            cmd_build_obj = shlex.split(cmd_build_obj)

            # Run and capture output
            process = sp.run(cmd_build_obj, capture_output=True)
            if process.returncode == 0:
                log.info(f'\"{target}\" intermediate build complete')

                if process.stderr:
                    log.info('Captured output: ')
                    log.info(process.stderr.decode('utf-8'))
            else:
                log.error(f'\"{target}\" build did not succeed')
                log.error(process.stderr.decode('utf-8'))


    # Builds and links all object files together
    def build_objs(self):
        # Use the selected target from the commandline args
        target = self.selected_target
        log.info(f'Starting final \"{target}\" build...')

        # Collect all object files
        objs = get_file_list(self.dirs['build'], '*.o')
        objs = [f'\"{path}\"' for path in objs]

        # Ugly hack to use the selected target as the index for
        # the list of targets which are already stored as paths
        # TODO: Figure out a better way to do this
        tgt_path = self.root / 'target' / target
        tgt_idx = self.dirs['target'].index(tgt_path)
        
        # Change file extension based on target build type
        bin_name = self.dirs['target'][tgt_idx] / f'{self.name}.{self.build_type}'

        # Prepare vars for final build
        objs = ' '.join(objs)
        build_flags = ' '.join(self.build_flags[target])
        libs = ' '.join(self.libraries)
        args = ' '.join(self.libargs)

        # Build command and split
        cmd_build_bin = f"{self.compiler} -o \"{bin_name}\" {objs} {build_flags} {libs} {args}"
        cmd_build_bin = shlex.split(cmd_build_bin)

        # Run and capture output
        process = sp.run(cmd_build_bin, capture_output=True)
        if process.returncode == 0:
            log.info(f'Final \"{target}\" build complete')

            if process.stderr:
                log.info('Captured output: ')
                log.info(process.stderr.decode('utf-8'))
        else:
            log.error(f'Final \"{target}\" build did not succeed')
            log.error(process.stderr.decode('utf-8'))


    # Builds selected targets
    def build(self):
        self.compile_sources()
        self.build_objs()

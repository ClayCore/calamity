from flatdict import FlatDict # type: ignore
from pathlib import Path
from typing import Tuple, Any
from utils.logger import log
import errno
import os
import sys
import yaml # type: ignore

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

        # Project setup
        self.build_files = self.config_get('project:setup:files')
        self.build_type = self.config_get('project:setup:type')
        self.compiler = self.config_get('project:setup:compiler')
        self.profiles = self.config_get('project:setup:profiles')

        # Clean-up directories
        self.cleanup_dirs = [self.dirs['build'], self.dirs['target']]

        # Dependencies
        # ============
        self.deps = self.config_get('project:dependencies')

        # Adjusts target directories and add build flags
        # according to build profiles
        self.build_flags = self.profile_setup()

        # Resolves all directory and file paths
        self.resolve_paths()


    def resolve_paths(self):
        # All directories in `self.dirs` are relative to project root
        for k, path in self.dirs.items():
            if isinstance(path, list):
                # Do it to all paths
                temp_paths = []
                for p in path:
                    temp_paths.append(self.root / p)

                self.dirs[k] = temp_paths
            else:
                self.dirs[k] = self.root / path

        # Source and header files are relative to their own directories
        for k, v in self.build_files.items():
            temp_paths = []

            if k == 'sources':
                for path in v:
                    temp_paths.append(self.dirs['source'] / path)
            if k == 'include':
                for path in v:
                    temp_paths.append(self.dirs['include'] / path)

            # Put them back into the dictionary
            self.build_files[k] = temp_paths
        
        # Dependency paths are relative to their own directory
        for k, v in self.deps.items():
            # Split by colon and return only the first element.
            name = ''.join(k.split(':')[:1])

            # Resolve paths first
            if 'paths' in k:
                # Don't append the name of the package if the name of the package
                # is the same as the key used for the dir path
                if 'dep' in k:
                    new_path = self.dirs['deps'] / name
                else:
                    new_path = self.dirs['deps'] / name / v

                self.deps[k] = new_path

            # Resolve library files
            if 'libs' in k:
                libs = []
                for lib in v:
                    lib_path = self.dirs['deps'] / name / 'lib' / lib
                    libs.append(lib_path)
                
                self.deps[k] = libs

        for k, v in self.deps.items():
            log.debug(f'{k}: {v}')

    # Acquires a list of target directories
    # and build flags for specific profiles.
    def profile_setup(self):
        target_dirs = []
        for profile in list(self.profiles):
            target_dirs.append(f"{self.dirs['target']}/{profile}")

        self.dirs['target'] = target_dirs

        build_flags = dict()
        for k, v in self.profiles.items():
            build_flags[k] = v

        return build_flags

    # Load config as a raw yaml dump and a flat dictionary.
    def load_config(self, path: Path) -> Tuple[FlatDict, dict]:
        result = (FlatDict(), dict())

        log.info('Loading project configuration')
        with open(path) as file:
            dump = yaml.load(file, Loader=yaml.FullLoader)
            result = (FlatDict(dump), dump)
        
        if result[0] is None or result[1] is None:
            log.error('Unable to parse configuration file.')
            sys.exit(os.strerror(errno.BADF))

        return result

    def config_get(self, key: str) -> Any:
        value = self.config.get(key)

        if value is None:
            log.warning('Key not found in configuration file.' , key=key)
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
                log.warning('Key not found in configuration file.' , key=key)
                return
            else:
                return value

#!/usr/bin/env python3

'''py-build.py -- simple build system

Builds C/C++ projects based on YAML config.

Usage:
    py-build.py [--help]
    py-build.py clean <config> 
    py-build.py build <config> <profile>
    py-build.py run <config> <profile>

Options:
    --help              Shows this screen.

Input:
    <config>            Path to configuration file
    <profile>           What profile we're building
                        (as defined in the config)

Subcommands:
    clean               Cleans build and output directories.
    build               Builds the entire project.
    run                 Builds and runs the application.
'''

from pathlib import Path
import os
import sys

from docopt import docopt # type: ignore
import colorama # type: ignore

from utils.logger import log
from utils.types import Builder

def main():
    # Clear the screen
    if os.name == 'posix':
        os.system('clear')
    else:
        os.system('cls')

    # Initialize colorama for colored logging
    colorama.init()

    # Parsing launch parameters
    # =========================

    # Add `--help` if no arguments were supplied
    if len(sys.argv) == 1:
        sys.argv.append('--help')
        args = docopt(__doc__, version=None, options_first=True)
    else:
        args = docopt(__doc__, version=None, options_first=True)

        config_path = args['<config>']
        if config_path:
            log.debug('Found config path', path=config_path)

        # Turn the `str` path into `pathlib.Path`
        config_path = Path(config_path)

        # Initialize main `Builder` object
        builder = Builder(config_path)

        # Selected target profile
        target = args['<profile>']
        builder.set_target(target)

        # Entry point
        # =========================
        log.info('Initializing build system...')

        if args['clean'] == True:
            # Clean directories...
            log.info('Starting clean-up...')
            builder.clean_up()
        if args['build'] == True:
            # Build the project
            log.info('Starting build...')
            builder.prepare_dirs()
            builder.build()
        if args['run'] == True:
            # Build & run
            log.info('Starting build & run...')
            builder.prepare_dirs()
            builder.build()


if __name__ == '__main__':
    main()

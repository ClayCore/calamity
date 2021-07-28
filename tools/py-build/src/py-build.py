#!/usr/bin/env python3

'''py-build.py -- simple build system

Builds C/C++ projects based on YAML config.

Usage:
    py-build.py [--help]
    py-build.py clean <config>
    py-build.py build <config>
    py-build.py run <config>

Options:
    --help              Shows this screen.

Subcommands:
    clean               Cleans build and output directories.
    build               Builds the entire project.
    run                 Builds and runs the application.
'''

from docopt import docopt # type: ignore
from pathlib import Path
import colorama # type: ignore
import os
import sys

from utils.logger import log
from utils.config import Config

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

        # Entry point
        # =========================
        log.info('Initializing build system...')

        if args['clean'] == True:
            # Clean directories...
            log.info('Starting clean-up...')
            pass
        if args['build'] == True:
            # Build the project
            log.info('Starting build...')
            pass
        if args['run'] == True:
            # Build & run
            log.info('Starting build & run...')
            pass


if __name__ == '__main__':
    main()

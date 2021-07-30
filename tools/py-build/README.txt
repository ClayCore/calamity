py-build.py -- simple build system.

I made this tool just so I don't have to deal with CMake and linking shenanigans.
This isn't a production-ready tool for large projects. It's designed for building smaller projects
that don't rely on CMake.

Note that this project uses *poetry* which makes it easier
to deal with dependencies and virtual environments. 

Prerequisites:
    - poetry 1.1.5    (https://python-poetry.org/)
    - python 3.8.9    (https://www.python.org/)

Usage:
    - Invoke shell in the tools/py-build directory.

    - To see the usage and help menu run the following command:
        '$ poetry run python src/py-build.py --help'

    - Build project by specifying the config file and target profile using
        '$ poetry run python src/py-build.py [CONFIG] [TARGET]'

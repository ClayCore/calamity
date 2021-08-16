#!/bin/bash

pushd tools/py-build > /dev/null || exit

if [[ "$OSTYPE" =~ ^linux-gnu* ]]; then
    poetry run python src/py-build.py build ../../calamity/build.linux.yaml release
elif [[ "$OSTYPE" =~ ^msys* ]] || [[ "$OSTYPE" =~ ^cygwin* ]]; then
    poetry run python src/py-build.py build ../../calamity/build.win32.yaml release
else
    echo "Unrecognized operating system"
fi

popd > /dev/null || exit

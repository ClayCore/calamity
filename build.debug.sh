#!/bin/bash

pushd tools/py-build > /dev/null || exit

if [[ "$OSTYPE" =~ ^linux-gnu* ]]; then
    poetry run python src/py-build.py build ../../calamity/build.linux.yaml debug
elif [[ "$OSTYPE" =~ ^msys* ]] || [[ "$OSTYPE" =~ ^cygwin* ]]; then
    poetry run python src/py-build.py build ../../calamity/build.win32.yaml debug
else
    echo "Unrecognized operating system"
fi

popd > /dev/null || exit

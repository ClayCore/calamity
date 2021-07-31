#!/bin/bash

pushd tools/py-build > /dev/null

poetry run python src/py-build.py build ../../calamity/build.yaml release

popd > /dev/null

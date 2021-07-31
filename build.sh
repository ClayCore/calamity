#!/bin/bash

pushd tools/py-build

poetry run python src/py-build.py build ../../calamity/build.yaml debug

popd

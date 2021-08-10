# Calamity

## engine

-   [ ] Add game assets packing and unpacking.
-   [ ] ~~Add parsing of game assets by using [libyaml](https://github.com/yaml/libyaml) and binary formats.~~
        Parse game assets using a self-made parser.
-   [ ] Add a sane memory management system.
-   [ ] Add user options/configuration.
-   [ ] Add documentation specs for file formats used by game assets for modding.

## tools/py-build

-   [ ] Add support for sanitizers and static analysis tools like `cppcheck`.
-   [ ] Add a way to build all targets, instead of selecting just one.
-   [ ] Make the output of the tool neater.
-   [ ] Refactor into smaller types and functions and make it more readable.
-   [ ] Add support for building source files with the project (like `glad`) and not just static/shared libraries.
-   [x] Add hash of filename to prevent name collisions when building and linking object files.

## tools/map-editor

-   [ ] Load fonts as static files.
-   [ ] Add custom and maybe _self-made_ icons.

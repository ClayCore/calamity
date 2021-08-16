<!-- TODO: proper name -->

# Calamity

This project is all about developing a fully working game engine from scratch.
I'm trying to stay true to some previous work in the past done by ID Software.

## Getting started

Run [./configure](/configure) to install dependencies and submodules:
Note: you may have to enable exec permissions for all scripts in the root directory.

```
$ chmod +x ./configure
$ ./configure
```

Now you can build the project with the homebrew build system by using [./build.debug.sh](/build.debug.sh) or [./build.release.sh](/build.release.sh) depending on the profile you wish to build.

```
$ chmod +x ./build.debug.sh ./build.release.sh
$ ./build.debug.sh
```

## Contributing

See [CONTRIBUTING](CONTRIBUTING.md) for more details.

## License

This project is under the BSD 3-clause License. See [LICENSE](LICENSE) for details.

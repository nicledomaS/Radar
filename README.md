[![License][license-image]][license-url]

# Radar
The program for displaying objects detected by radar 

## Build project
`git submodule update --init --recursive`

`cmake -B build -DCMAKE_BUILD_TYPE=Debug -DFIND_MODULES=ON`

`cmake --build build/ -j4`

## Related project
[Cmake scripts for build c++ projects](https://github.com/nicledomaS/cmake/blob/master/README.md)

[license-image]: https://img.shields.io/badge/License-Apache%202.0-blue.svg
[license-url]: LICENSE

#!/bin/sh
#
# This is a simple script to auomate manual building of the project.
# This file is just an utility and it is not necessary to the project.
#

git clone https://github.com/microsoft/vcpkg
./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg install libjpeg-turbo

mkdir -p build
cd build
:
cmake -DCODE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug -j $(nproc)
ctest -j $(nproc) --output-on-failure

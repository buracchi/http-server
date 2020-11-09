#!/bin/sh
#
# This is a simple script to auomate manual building of the project.
# This file is just an utility and it is not necessary to the project.
#

./vcpkg/bootstrap-vcpkg.sh
mkdir build
cmake -S . -B build
cmake --build build -j $(nproc)

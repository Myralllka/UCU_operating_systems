#!/bin/bash -x

set -o errexit
set -o nounset
set -o pipefail

#mkdir -p build
#(
#    cd build
    cmake -B build .
    make --directory=build
#)
#rm -r build

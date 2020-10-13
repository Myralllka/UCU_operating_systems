#!/bin/bash -x

set -o errexit
set -o nounset
set -o pipefail

cmake -B build .
make --directory=build
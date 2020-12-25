#!/bin/bash -x

#set -o errexit
#set -o nounset
#set -o pipefail

debug=false
debug_build=false
optimize_build=false

while true; do
  case $1 in
  -D | --debug-build)
    debug_build=true
    shift
    ;;
  -O | --optimize-build)
    optimize_build=true
    shift
    ;;
  -h | --help)
    echo "Usage: ./start.sh [options]
  Options:
    -h      --help                  Show help message.
    -O      --optimize-build        Compile with optimization before executing.
    -D      --debug-build           Compile with debug options."
    exit 0
    ;;
  \?)
    echo "Invalid option: -$OPTARG" >&2
    exit 1
    ;;
  :)
    echo "Option -$OPTARG requires an numerical argument." >&2
    exit 1
    ;;
  *)
    break
    ;;
  esac
done

# different prepare staff


if [[ "$debug_build" == true ]]; then
  mkdir -p ./cmake-build-debug
  (
    pushd ./cmake-build-debug > /dev/null || exit 1
    echo Compiling...
    cmake -DCMAKE_BUILD_TYPE=Debug -G"Unix Makefiles" .. || exit 1
    make || exit 1
    popd
  )
fi

if [[ "$optimize_build" == true ]]; then
  mkdir -p ./cmake-build-release
  (
    pushd ./cmake-build-release >/dev/null || exit 1
    echo Compiling...
    cmake DCMAKE_BUILD_TYPE=Release -G"Unix Makefiles" .. || exit 1
    make || exit 1
    popd
  )
fi

if [[ "$debug_build" == true ]]; then
    mpirun -n 2 ./cmake-build-debug/exam || exit 1
  else
    mpirun -n 2 ./cmake-build-release/exam || exit 1
fi

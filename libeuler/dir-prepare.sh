#!/bin/bash
#
# This script creates some directories in order to prepare our source tree for builds.

cd "$(dirname "$0")"

if [[ ! -d "build" ]] ; then mkdir build ; fi
if [[ ! -d "build/release/lib" ]] ; then mkdir -p build/release/lib ; fi
if [[ ! -d "build/release/include/libeuler" ]] ; then mkdir -p build/release/include/libeuler; fi

exit 0

#!/bin/bash
#
# Script to copy our final, usable library to a proper location for our problems to access it.

cd "$(dirname "$0")"

# Make sure we have a built copy of libeuler.so.

if [[ ! -e "build/libeuler.so" ]] ; then
	echo "Couldn't find libeuler.so; did your build fail?"
	exit 1
fi

# Copy the shared library.

cp build/libeuler.so build/release/lib/ > /dev/null 2>&1

# Copy the header files.

cp -R src/* build/release/include/libeuler/ > /dev/null 2>&1
find build/release/include/libeuler/ -type f -iname "*.c" -or -iname "*.cpp" -exec rm -fr {} \;

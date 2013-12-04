#!/bin/bash
#
# Script to clean up & rebuild libeuler.
# This will build our library in RELEASE mode.

cd "$(dirname "$0")"

# Clean up our previous build, if any.

./clean.sh

if [[ $? -ne 0 ]];
then
	echo "FATAL: Couldn't execute clean.sh."
	exit 1
fi

# Make sure the directories we need exist.

./dir-prepare.sh

if [[ $? -ne 0 ]];
then
	echo "FATAL: Couldn't execute dir-prepare.sh."
	exit 1
fi

# Build the project.

cd build

cmake -DCMAKE_BUILD_TYPE=Release ..

if [[ $? -ne 0 ]] ; then
	echo "FATAL: Build failed!"
	exit 1
fi

make

if [[ $? -ne 0 ]] ; then
	echo "FATAL: Build failed!"
	exit 1
fi

cd ..

# Copy our release files.

./copy-release.sh

if [[ $? -ne 0 ]];
then
	echo "FATAL: Couldn't execute copy-release.sh."
	exit 1
fi

#!/usr/bin/env bash
#
# This script applies clang-format to the entire source tree.

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

find done/ new/ src/ test/ -type f -iname "*.h" -o -iname "*.hpp" -o -iname "*.cpp" | while read FILE
do
	clang-format -i "$FILE"
done

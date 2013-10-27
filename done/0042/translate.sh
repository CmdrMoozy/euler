#!/bin/bash
#
# This is a simple script to translate the input file for this problem into
# a format that is a bit more usable. The original file is in the format:
#
# "[A-Z]","[A-Z]",[...]
#
# What this script does is split every item onto a new line instead of being
# comma-separated (i.e., it replaces all commas with newlines), and then removes
# the extraneous double-quotation marks entirely.
#
# The syntax of this command is: translate.sh file.txt
# (Note that the input file is replaced by the output.)

TMP=$$.tmp

cat $1 | tr ',' '\n' > $TMP
mv $TMP $1
cat $1 | tr -d '"' > $TMP
mv $TMP $1

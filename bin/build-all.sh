#!/bin/bash
#
# This is a script to build all of our projects.

DIRS=`find . -mindepth 1 -maxdepth 1 -type d | sort`
for DIR in $DIRS ; do
	cd $DIR
	echo $DIR
	make
	echo -en "\n"
	cd ..
done


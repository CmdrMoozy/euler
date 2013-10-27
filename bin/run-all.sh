#!/bin/bash
#
# This is a script to execute all of our projects.

DIRS=`find . -mindepth 1 -maxdepth 1 -type d | sort`
for DIR in $DIRS ; do
        cd $DIR
        echo `pwd`
        time ./run
        echo -en "\n"
        cd ..
done

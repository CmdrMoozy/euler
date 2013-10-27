#!/bin/bash
#
# This is a script to list all of the libeuler dependencies of our projects.

DIRS=`find . -mindepth 1 -maxdepth 1 -type d | sort`
for DIR in $DIRS ; do
	cd $DIR

	FILES=`grep -l --include=*.{h,cpp} "#include \"libeuler/" *`
	if [ $? -eq 0 ] ; then
		echo -en "`basename $DIR`:\n"
		for FILE in $FILES ; do
			echo -en "  `basename $FILE`:\n"
			grep -nh "#include \"libeuler/" $FILE | sed -s 's/^/    /'
		done

		echo -en "\n"
	fi

	cd ..
done

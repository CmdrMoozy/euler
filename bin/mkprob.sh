#!/bin/bash
#
# This is a script to create a new ProjectEuler problem based on command-line arguments.

# This function prints out (optionally) an error message, and our script's usage syntax.
function usage {
	if [[ -n $1 ]] ; then
		echo -en "$1\n\n"
	fi
	
	echo "Usage: mkprob.sh [OPTIONS]"
	echo "    -n=[NUMBER] - The problem number, i.e. 0003 (REQUIRED)."
	echo "    -q          - Specify that this problem requires libeuler linkage."
	echo "    -g          - Specify that this problem requires GMP linkage."
}

# Setup initial variables.
declare NUMBER=
declare EULER=0
declare GMP=0

# Parse command-line arguments.
for i in $*
do
	case $i in
	-n=*) # Specify number.
		NUMBER=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
		;;
		
	-q) # Specify libeuler linkage.
		EULER=1
		;;
		
	-g) # Specify GMP linkage.
		GMP=1
		;;
		
	*) # Unknown option.
		usage "$i is an invalid option."
		exit 1
		;;
	esac
done

# Make sure the user specified a name and a number.
if [[ -z $NUMBER ]] ; then
	usage "You must specify a valid problem number."
	exit 1
fi

# Make sure the specified problem doesn't already exist.
if [[ -e $NUMBER ]] ; then
	echo "ERROR: The directory '$NUMBER' already exists!"
	exit 1
fi

###################################################
# We need to generate:                            #
#                                                 #
#     main.cpp                                    #
#     run.sh (if EULER)                           #
#     run symlink (depends on EULER)              #
#     Makefile (depends on EULER GMP)             #
###################################################

mkdir $NUMBER
cd $NUMBER

#############################
# Generate 'main.cpp'...    #
#############################

echo -en "#include <iostream>\n" > main.cpp
echo -en "#include <cassert>\n" >> main.cpp
echo -en "#include <cstdint>\n" >> main.cpp
echo -en "\n" >> main.cpp
echo -en "int main(void)\n" >> main.cpp
echo -en "{\n" >> main.cpp
echo -en "\t\n" >> main.cpp
echo -en "\t\n" >> main.cpp
echo -en "\treturn 0;\n" >> main.cpp
echo -en "}\n" >> main.cpp

#############################
# Generate 'run.sh'...      #
#############################

if [[ $EULER -eq 1 ]] ; then
	echo -en "#!/bin/bash\n" > run.sh
	echo -en "#\n" >> run.sh
	echo -en "# This is a script to execute our program.\n" >> run.sh
	echo -en "\n" >> run.sh
	echo -en "LD_LIBRARY_PATH=../../libeuler/build/release/lib ./Problem \$@\n" >> run.sh
	
	chmod +x run.sh
fi

#############################
# Generate 'run' symlink... #
#############################

if [[ $EULER -eq 1 ]] ; then
	ln -s run.sh ./run
else
	ln -s Problem ./run
fi

#############################
# Generate 'Makefile'...    #
#############################

echo -en "CFLAGS = -pipe -fomit-frame-pointer -Wall -W -O2 -std=c++0x\n" > Makefile

if [[ $EULER -eq 1 || $GMP -eq 1 ]] ; then
	echo -en "LDFLAGS = " >> Makefile
	
	if [[ $EULER -eq 1 ]] ; then
		echo -en "-leuler -lgmp -lgmpxx -lmpfr -lrt -lm" >> Makefile
	elif [[ $GMP -eq 1 ]] ; then
		echo -en "-lgmp -lgmpxx" >> Makefile
	fi
	
	echo -en "\n" >> Makefile
fi

if [[ $QUADRA -eq 1 ]] ; then
	echo -en "INCPATH = ../../libeuler/build/release/include\n" >> Makefile
	echo -en "LIBPATH = ../../libeuler/build/release/lib\n" >> Makefile
fi

echo -en "CC = g++\n" >> Makefile
echo -en "\n" >> Makefile
echo -en "PROG = Problem\n" >> Makefile
echo -en "\n" >> Makefile
echo -en "all: \$(PROG)\n" >> Makefile
echo -en "\n" >> Makefile
echo -en "\$(PROG): main.cpp\n" >> Makefile

echo -en "\t\$(CC) \$(CFLAGS) " >> Makefile
if [[ $EULER -eq 1 || $GMP -eq 1 ]] ; then
	echo -en "\$(LDFLAGS) " >> Makefile
fi
if [[ $EULER -eq 1 ]] ; then
	echo -en "-I\$(INCPATH) -L\$(LIBPATH) " >> Makefile
fi
echo -en "main.cpp -o \$(PROG)\n" >> Makefile

echo -en "\n" >> Makefile
echo -en "clean:\n" >> Makefile
echo -en "\t@rm -fr \$(PROG)\n" >> Makefile

cd ..
exit 0

#!/usr/bin/python

import os
import argparse
import traceback
import sys

sys.path.append('{0}/bin/modules'.format(os.path.dirname(
	os.path.dirname(os.path.realpath(__file__)))))

import euler

# Define our build options.

CFLAGS = [
	'-Wall',
	'-Wextra',
	'-ansi',
	'-pedantic',
	'-Wshadow',
	'-Wpointer-arith',
	'-Wcast-qual',
	'-pipe',
	'-fomit-frame-pointer',
	'-Wall',
	'-W',
	'-O2',
	'-std=c++0x'
]

DEBUG_CFLAGS = [
	'-Wall',
	'-Wextra',
	'-ansi',
	'-pedantic',
	'-Wshadow',
	'-Wpointer-arith',
	'-Wcast-qual',
	'-pipe',
	'-Wall',
	'-W',
	'-O0',
	'-g',
	'-std=c++0x'
]

LDFLAGS = [
	'-leuler',
	'-lpthread',
	'-lgmp',
	'-lgmpxx',
	'-lmpfr',
	'-lrt',
	'-lm'
]

INCPATH = [
	'{0}/libeuler/build/release/include'.format(euler.get_euler_root())
]

LIBPATH = [
	'{0}/libeuler/build/release/lib'.format(euler.get_euler_root())
]

CC = 'g++'

# This is a function which formulates the correct arguments to, and calls, the build_problem()
# function in our Euler Python module.
#
# \param number The number of the problem to build.
# \param debug Whether or not to build in debug mode.
# \param verbose Whether or not to enable verbose output.
def build_problem(number, debug, verbose):
	if debug:
		euler.build_problem(number, verbose, CC, DEBUG_CFLAGS, LDFLAGS, INCPATH, LIBPATH)
	else:
		euler.build_problem(number, verbose, CC, CFLAGS, LDFLAGS, INCPATH, LIBPATH)

# Get our command-line arguments.

parser = argparse.ArgumentParser(description='Compile one or all ProjectEuler problems.')

parser.add_argument('-n', help='particular problem number to build, instead of all', type=int)
parser.add_argument('-g', help='build in debug mode (default is release mode)', action='store_true')
parser.add_argument('-v', help='enable verbose build output', action='store_true')

args = parser.parse_args()

# Based on these arguments, build some code!

try:
	if args.n is not None:
		build_problem(args.n, args.g is True, args.v is True)
	else:
		for number in euler.get_done_list():
			build_problem(number, args.g is True, args.v is True)
	
except SystemExit as e:
	if e.code != 0:
		sys.stderr.write('Build failed!\n')
	pass
	
except KeyboardInterrupt:
	sys.stderr.write('Aborting by user request!\n')
	pass
	
except:
	sys.stderr.write('Unexpected error: %s\n' % traceback.format_exc())
	sys.exit(1)

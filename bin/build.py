#!/usr/bin/python

#
# euler - A collection of ProjectEuler solutions, and supporting libraries and tools.
# Copyright (C) 2013 Axel Rasmussen
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

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

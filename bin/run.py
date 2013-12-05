#!/usr/bin/python

import os
import argparse
import traceback
import sys

sys.path.append('{0}/bin/modules'.format(os.path.dirname(
	os.path.dirname(os.path.realpath(__file__)))))

import euler

LD_LIBRARY_PATH = '{0}/libeuler/build/release/lib'.format(euler.get_euler_root())

# Get our command-line arguments.

parser = argparse.ArgumentParser(description='Run one or all ProjectEuler problems.')

parser.add_argument('-n', help='particular problem number to run, instead of all', type=int)

args = parser.parse_args()

# Based on these arguments, run some problems!

try:
	if args.n is not None:
		euler.run_problem(args.n, LD_LIBRARY_PATH)
	else:
		for number in euler.get_done_list():
			euler.run_problem(number, LD_LIBRARY_PATH)
	
except SystemExit as e:
	if e.code != 0:
		sys.stderr.write('Running problem failed!\n')
	pass
	
except KeyboardInterrupt:
	sys.stderr.write('Aborting by user request!\n')
	pass
	
except:
	sys.stderr.write('Unexpected error: %s\n' % traceback.format_exc())
	sys.exit(1)

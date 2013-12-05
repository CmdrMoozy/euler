#!/usr/bin/python

import os
import argparse
import traceback
import sys

sys.path.append('{0}/bin/modules'.format(os.path.dirname(
	os.path.dirname(os.path.realpath(__file__)))))

import euler

# Get our command-line arguments.

parser = argparse.ArgumentParser(description='Create a new ProjectEuler problem.')

parser.add_argument('-n', help='the number of the problem to create', type=int, required=True)

args = parser.parse_args()

# Based on these arguments, create the new problem!

try:
	euler.create_problem(args.n)
	
except SystemExit as e:
	if e.code != 0:
		sys.stderr.write('Creating problem failed!\n')
	pass
	
except KeyboardInterrupt:
	sys.stderr.write('Aborting by user request!\n')
	pass
	
except:
	sys.stderr.write('Unexpected error: %s\n' % traceback.format_exc())
	sys.exit(1)

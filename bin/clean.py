#!/usr/bin/python

import os
import traceback
import sys

sys.path.append('{0}/bin/modules'.format(os.path.dirname(
	os.path.dirname(os.path.realpath(__file__)))))

import euler

# Clean all of our problems.

try:
	for number in euler.get_new_list():
		euler.clean_problem(number)
	
	for number in euler.get_done_list():
		euler.clean_problem(number)
	
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

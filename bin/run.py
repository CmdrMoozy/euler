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
		runtimes = []
		
		for number in euler.get_done_list():
			runtimes.append(euler.run_problem(number, LD_LIBRARY_PATH))
		
		if runtimes:
			sum = 0
			mint = runtimes[0]
			maxt = runtimes[0]
			
			for time in runtimes:
				sum += time
				mint = min(mint, time)
				maxt = max(maxt, time)
			
			avg = sum / len(runtimes)
			sum = sum / 1000
			
			print('Total run time:   %.2f s' % sum)
			print('Average run time: %.2f ms' % avg)
			print('Min run time:     %d ms' % mint)
			print('Max run time:     %d ms' % maxt)
	
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

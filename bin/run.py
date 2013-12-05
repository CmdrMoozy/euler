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

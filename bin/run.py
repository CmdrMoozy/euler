#!/usr/bin/env python3

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

parser = argparse.ArgumentParser(
	description='Run one or all ProjectEuler problems.')
parser.add_argument('-n',
	help='particular problem number to run, instead of all', type=int)
parser.add_argument('-b', help='path to build directory')

args = parser.parse_args()

try:
	# Locate the build directory.

	build_directory = '{0}/build'.format(os.path.dirname(
		os.path.dirname(os.path.realpath(__file__))))

	if args.b:
		build_directory = args.b

	if not os.path.exists(os.path.join(build_directory, 'CMakeCache.txt')):
		print('ERROR: Invalid build directory.')
		sys.exit(1)

	# Compute the directory containing the Euler library.

	ldpath = os.path.join(build_directory, 'libeuler')

	# Run the specified problem(s).

	if args.n is not None:
		euler.run_problem(args.n, ldpath, build_directory)
	else:
		runtimes = []

		for number in euler.get_done_list():
			runtimes.append(euler.run_problem(number, ldpath, build_directory))

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

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

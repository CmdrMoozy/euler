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

import traceback
import sys
import subprocess
import os
import re
import time
import errno

# This function returns the full path to the root of our ProjectEuler directory.
#
# \return The path to the ProjectEuler root directory.
def get_euler_root():
	return os.path.dirname(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))

# This function returns whether or not the file denoted by the given path is a valid executable.
#
# \return True if the path can be executed, or false otherwise.
def is_exe(path):
	return os.path.isfile(path) and os.access(path, os.X_OK)

# This function attempts to create all of the directories in the given path. Ancestors are created
# as well, if they don't already exist.
#
# \param path The path to create.
def mkpath(path):
	try:
		os.makedirs(path)
	except OSError as exc:
		if exc.errno == errno.EEXIST and os.path.isdir(path):
			pass
		else:
			raise

# This function attempts to find the directory containing the sources of the given problem number.
# If the problem can't be found, this function returns None instead.
#
# \param number The number of the problem to find, as an integer.
# \return The path to the problem's directory.
def find_problem(number):
	number = str(number).zfill(4)
	
	path = '{0}/new/{1}'.format(get_euler_root(), number)
	
	if os.path.isdir(path):
		return path
	
	path = '{0}/done/{1}'.format(get_euler_root(), number)
	
	if os.path.isdir(path):
		return path
	
	return None

# This function returns a list of all problems that are done.
#
# \return A list of done problems.
def get_done_list():
	problems = []
	
	for item in os.listdir('{0}/done/'.format(get_euler_root())):
		path = '{0}/done/{1}'.format(get_euler_root(), item)
		if os.path.isdir(path):
			name = os.path.basename(path)
			match = re.match(r'^\d{4}$', name)
			
			if match is not None:
				try:
					number = int(name)
					problems.append(number)
				except:
					continue
	
	return sorted(problems)

# This function returns a list of all problems that are "new".
#
# \return A list of new problems.
def get_new_list():
	problems = []
	
	for item in os.listdir('{0}/new/'.format(get_euler_root())):
		path = '{0}/new/{1}'.format(get_euler_root(), item)
		if os.path.isdir(path):
			name = os.path.basename(path)
			match = re.match(r'^\d{4}$', name)
			
			if match is not None:
				try:
					number = int(name)
					problems.append(number)
				except:
					continue
	
	return sorted(problems)

# This function creates a default "main.cpp" for a ProjectEuler problem with the given number. This
# new problem will be created inside the new/ directory.
#
# If the problem already exists, we will print an error and do nothing.
#
# \param number The number of the problem to create.
def create_problem(number):
	try:
		# See if the problem already exists.
		
		path = find_problem(number)
		
		if path is not None:
			sys.stderr.write('FATAL: Problem {0} already exists at: {1}!\n'
				.format(number, path))
			return
		
		# Looks like we're good; create the new problem!
		
		path = '{0}/new/{1}'.format(get_euler_root(), str(number).zfill(4))
		mkpath(path)
		
		with open('{0}/main.cpp'.format(path), 'w') as f:
			f.write('/*\n')
			f.write(' * euler - A collection of ProjectEuler solutions, and supporting libraries and tools.\n')
			f.write(' * Copyright (C) 2013 Axel Rasmussen\n')
			f.write(' *\n')
			f.write(' * This program is free software: you can redistribute it and/or modify\n')
			f.write(' * it under the terms of the GNU General Public License as published by\n')
			f.write(' * the Free Software Foundation, either version 3 of the License, or\n')
			f.write(' * (at your option) any later version.\n')
			f.write(' *\n')
			f.write(' * This program is distributed in the hope that it will be useful,\n')
			f.write(' * but WITHOUT ANY WARRANTY; without even the implied warranty of\n')
			f.write(' * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n')
			f.write(' * GNU General Public License for more details.\n')
			f.write(' *\n')
			f.write(' * You should have received a copy of the GNU General Public License\n')
			f.write(' * along with this program.  If not, see <http://www.gnu.org/licenses/>.\n')
			f.write(' */\n')
			f.write('\n')
			f.write('#include <iostream>\n')
			f.write('#include <cassert>\n')
			f.write('#include <cstdint>\n')
			f.write('\n')
			f.write('int main(void)\n')
			f.write('{\n')
			f.write('\t\n')
			f.write('\t\n')
			f.write('\treturn 0;\n')
			f.write('}\n')
			
			f.flush()
	
	except KeyboardInterrupt:
		raise
	
	except:
		sys.stderr.write('FATAL: Creating problem {0} failed!\n'.format(number))
		sys.stderr.write('{0}\n'.format(traceback.format_exc()))

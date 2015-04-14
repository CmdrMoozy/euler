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

# This function returns a list of executables inside the given directory. If
# no executables were found, an empty list is returned instead.
#
# \param path The path to look for executables in.
# \return A list of the executables in the given path.
def find_exes(path):
	if os.path.isdir(path):
		exes = []
		for file in os.listdir(path):
			exe = os.path.join(path, file)
			if is_exe(exe):
				exes.append(exe)

		return exes

	return []

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

	path = os.path.join(get_euler_root(), 'done', number)
	if os.path.isdir(path):
		return path

	path = os.path.join(get_euler_root(), 'new', number)
	if os.path.isdir(path):
		return path

	return None

# This function attempts to find the executable for the given problem in the
# given build directory. If the executable can't be found, this function
# returns None instead.
#
# \param build_directory The directory containing built executables.
# \param number The number of the problem to find, as an integer.
# \return The full path to the problem's executable.
def find_problem_executable(build_directory, number):
	number = str(number).zfill(4)

	path = os.path.join(build_directory, 'done', number)
	exes = find_exes(path)
	if len(exes) > 0:
		return exes

	path = os.path.join(build_directory, 'new', number)
	exes = find_exes(path)
	if len(exes) > 0:
		return exes

	return []

# This function returns a list of all problems that are done.
#
# \return A list of done problems.
def get_done_list():
	problems = []

	for item in os.listdir(os.path.join(get_euler_root(), 'done')):
		path = os.path.join(get_euler_root(), 'done', item)
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

	for item in os.listdir(os.path.join(get_euler_root(), 'new')):
		path = os.path.join(get_euler_root(), 'new', item)
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
			f.write('#include <cassert>\n')
			f.write('#include <cstdint>\n')
			f.write('#include <iostream>\n')
			f.write('\n')
			f.write('int main(void)\n')
			f.write('{\n')
			f.write('\t\n')
			f.write('\t\n')
			f.write('\treturn 0;\n')
			f.write('}\n')

			f.flush()

		with open('{0}/CMakeLists.txt'.format(path), 'w') as f:
			f.write('eulerAddProblem()\n')

			f.flush()

	except KeyboardInterrupt:
		raise

	except:
		sys.stderr.write('FATAL: Creating problem {0} failed!\n'.format(number))
		sys.stderr.write('{0}\n'.format(traceback.format_exc()))

def run_problem(number, ldpath, build_directory):
	elapsed = -1

	try:
		# Find the problem we're going to run.

		exe = find_problem_executable(build_directory, number)
		if len(exe) != 1:
			sys.stderr.write('FATAL: Couldn\'t find problem {0}!\n'.format(number))
			return
		path = os.path.dirname(exe[0])

		# Run the problem.

		stime = int(round(time.time() * 1000))

		sys.stdout.write('Problem {0}:\n'.format(number))

		cmd = [exe[0]]

		env = os.environ.copy()
		env['LD_LIBRARY_PATH'] = ldpath

		out = []

		with subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, cwd=path, env=env) as p:
			out = p.stdout.readlines()
			retval = p.wait()

			if retval != 0:
				sys.stderr.write('FATAL: Problem returned error code {0}.\n'.format(retval))

			for line in out:
				sys.stdout.write('{0}'.format(line.decode('utf-8')))

			sys.stdout.flush()

		etime = int(round(time.time() * 1000))
		elapsed = etime - stime

		sys.stdout.write('{0} ms\n'.format(elapsed))

	except KeyboardInterrupt:
		raise

	except:
		sys.stderr.write('FATAL: Running problem {0} failed!\n'.format(number))
		sys.stderr.write('{0}\n'.format(traceback.format_exc()))

	sys.stdout.write('\n')

	return elapsed

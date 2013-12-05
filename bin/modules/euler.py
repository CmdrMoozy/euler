#!/usr/bin/python

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

# This function builds a particular problem.
#
# \param number The number of the problem to build.
# \param verbose Whether or not to enable verbose build output.
# \param cc The compiler command to use.
# \param cflags A list of compile flags to pass to the compiler.
# \param ldflags A list of link flags to pass to the compiler.
# \param incpath A list of paths to tell the compiler to include.
# \param libpath A list of paths to tell the compiler to look for libraries in.
def build_problem(number, verbose, cc, cflags, ldflags, incpath, libpath):
	try:
		print('{0}: Building...'.format(str(number).zfill(4)))
		
		# Find the problem directory.
		
		path = find_problem(number)
		
		if path is None:
			sys.stderr.write('FATAL: Couldn\'t find problem {0}!\n'.format(number))
			return
		
		# If the problem has already been compiled, remove it.
		
		if is_exe('{0}/Problem'.format(path)):
			os.remove('{0}/Problem'.format(path))
		
		# Formulate the command used to build the problem.
		
		cmd = [cc]
		cmd.extend(cflags)
		cmd.extend(ldflags)
		
		for ipath in incpath:
			cmd.append('-I{0}'.format(ipath))
		
		for lpath in libpath:
			cmd.append('-L{0}'.format(lpath))
		
		cmd.append('{0}/main.cpp'.format(path))
		
		cmd.extend(['-o', '{0}/Problem'.format(path)])
		
		# Execute the build command.
		
		if verbose:
			sys.stdout.write('\t{0}\n'.format(' '.join(cmd)))
		
		with subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT) as p:
			out = p.stdout.readlines()
			retval = p.wait()
			
			if retval != 0:
				sys.stderr.write('FATAL: {0} returned error code {1}.\n'
					.format(cc, retval))
			
			for line in out:
				sys.stdout.write('{0}\n'.format(line.decode('utf-8')))
			
			sys.stdout.flush()
	
	except KeyboardInterrupt:
		raise
	
	except:
		sys.stderr.write('FATAL: Building problem {0} failed!\n'.format(number))
		sys.stderr.write('{0}\n'.format(traceback.format_exc()))
	
	sys.stdout.write('\n')

# This function attempts to clean a problem, by removing its compiled output.
#
# \param number The number of the problem to clean.
def clean_problem(number):
	try:
		# Find the problem, and remove its compiled output (if it's found).
		
		path = find_problem(number)
		
		if path is not None:
			
			os.remove('{0}/Problem'.format(path))
	
	except KeyboardInterrupt:
		raise
	
	except IOError as exc:
		if exc.errno == errno.ENOENT:
			pass
		else:
			sys.stderr.write('FATAL: Cleaning problem {0} failed!\n'.format(number))
			sys.stderr.write('{0}\n'.format(traceback.format_exc()))

# This function attempts to run the problem with the given number.
#
# \param number The number of the problem to run.
# \param ldpath The LD_LIBRARY_PATH to use when executing the problem.
def run_problem(number, ldpath):
	try:
		# Find the problem we're going to run.
		
		path = find_problem(number)
		
		if path is None:
			sys.stderr.write('FATAL: Couldn\'t find problem {0}!\n'.format(number))
			return
		
		exe = '{0}/Problem'.format(path)
		
		if not is_exe(exe):
			sys.stderr.write('FATAL: Problem {0} hasn\'t been built!\n'.format(number))
			return
		
		# Run the problem.
		
		stime = int(round(time.time() * 1000))
		
		sys.stdout.write('Problem {0}:\n'.format(number))
		
		cmd = [exe]
		
		env = os.environ.copy()
		env['LD_LIBRARY_PATH'] = ldpath
		
		out = []
		
		with subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, cwd=path, env=env) as p:
			out = p.stdout.readlines()
			retval = p.wait()
			
			if retval != 0:
				sys.stderr.write('FATAL: Problem returned error code {0}.\n'
					.format(retval))
			
			for line in out:
				sys.stdout.write('{0}'.format(line.decode('utf-8')))
			
			sys.stdout.flush()
		
		etime = int(round(time.time() * 1000))
		
		sys.stdout.write('{0} ms\n'.format(etime - stime))
	
	except KeyboardInterrupt:
		raise
	
	except:
		sys.stderr.write('FATAL: Running problem {0} failed!\n'.format(number))
		sys.stderr.write('{0}\n'.format(traceback.format_exc()))
		
	sys.stdout.write('\n')

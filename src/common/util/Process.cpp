/*
 * euler - A collection of ProjectEuler libraries, tools, and solutions.
 * Copyright (C) 2013 Axel Rasmussen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Process.hpp"

#include <cerrno>
#include <cstddef>
#include <sstream>

#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#include "common/util/Error.hpp"

namespace
{
constexpr std::size_t READ_BUFFER_SIZE = 256;

template <typename T>
std::vector<T> concatenate(std::vector<T> const &a, std::vector<T> const &b)
{
	std::vector<T> result;
	result.reserve(a.size() + b.size());
	result.insert(result.end(), a.begin(), a.end());
	result.insert(result.end(), b.begin(), b.end());
	return result;
}

std::vector<char const *>
toCStringVector(std::vector<std::string> const &strings)
{
	std::vector<char const *> cstrings(strings.size());
	for(std::size_t i = 0; i < strings.size(); ++i)
		cstrings[i] = strings[i].c_str();
	return cstrings;
}

std::string readAll(int fd)
{
	std::vector<char> buffer(READ_BUFFER_SIZE);
	std::ostringstream oss;
	ssize_t count;
	while((count = read(fd, buffer.data(), buffer.size())) != 0)
	{
		if(count == -1)
			euler::util::error::throwErrnoError();
		oss << std::string(buffer.data(),
		                   static_cast<std::size_t>(count));
	}
	return oss.str();
}
}

namespace euler
{
namespace util
{
namespace process
{
void registerProblemSignalHandlers()
{
	// Ignore SIGCHLD, in order to portably reap child processes.
	signal(SIGCHLD, SIG_IGN);
}

ProcessArguments::ProcessArguments(std::string const &p,
                                   std::vector<std::string> const &a)
        : path(p),
          arguments(a),
          file(path.c_str()),
          argv(concatenate(concatenate({file}, toCStringVector(arguments)),
                           {"\0"}))
{
}

Process::Process(std::string const &p, std::vector<std::string> const &a)
        : args(p, a), parent(getpid()), child(-1)
{
	// Open a pipe, so we can get error messages from our child.

	int pipes[2];
	if(pipe(pipes) != 0)
		error::throwErrnoError();

	int existingFlags = fcntl(pipes[1], F_GETFD);
	if(existingFlags == -1)
		error::throwErrnoError();

	if(fcntl(pipes[1], F_SETFD, existingFlags | FD_CLOEXEC) != 0)
		error::throwErrnoError();

	// Fork a new process.

	pid_t pid = fork();
	if(pid == -1)
		error::throwErrnoError();

	if(pid == 0)
	{
		// In the child process. Try to exec the binary.

		close(pipes[0]);

		try
		{
			// The POSIX standard guarantees that argv will not be
			// modified, so this const cast is safe.
			if(execvp(args.file, const_cast<char *const *>(
			                             args.argv.data())) == -1)
				error::throwErrnoError();
		}
		catch(std::runtime_error const &e)
		{
			std::string message = e.what();
			write(pipes[1], message.c_str(), message.length());
		}
		catch(...)
		{
			std::string message = "Unknown error.";
			write(pipes[1], message.c_str(), message.length());
		}
		_exit(EXIT_FAILURE);
	}
	else
	{
		// Still in the parent process. Check for errors.

		child = pid;
		close(pipes[1]);
		std::string error = readAll(pipes[0]);
		close(pipes[0]);
		if(!error.empty())
			throw std::runtime_error(error);
	}
}

Process::~Process()
{
	if(child == -1)
		return;

	int status;
	while(waitpid(child, &status, 0) == -1)
	{
		if(errno != EINTR)
			error::throwErrnoError();
	}
}
}
}
}

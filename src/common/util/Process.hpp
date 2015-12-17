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

#ifndef common_util_Process_HPP
#define common_util_Process_HPP

#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include <sys/types.h>

#include "common/util/Profiler.hpp"
#include "common/util/Terminal.hpp"

namespace euler
{
namespace util
{
namespace process
{
namespace detail
{
struct Pipe
{
	int read;
	int write;

	explicit Pipe(int flags = 0);

	Pipe(Pipe const &) = default;
	Pipe(Pipe &&) = default;
	Pipe &operator=(Pipe const &) = default;
	Pipe &operator=(Pipe &&) = default;

	~Pipe() = default;
};
}

void registerProblemSignalHandlers();

struct ProcessArguments
{
public:
	using ArgvSmartPointer =
	        std::unique_ptr<char, std::function<void(char *)>>;
	using ArgvContainer = std::vector<ArgvSmartPointer>;

	const std::string path;
	const std::vector<std::string> arguments;

private:
	const ArgvContainer argvContainer;
	const std::vector<char *> argvPointers;

public:
	char const *file;
	char *const *argv;

	ProcessArguments(std::string const &p,
	                 std::vector<std::string> const &a);
};

class Process
{
public:
	Process(std::string const &p, std::vector<std::string> const &a = {});

	Process(Process const &) = delete;
	Process(Process &&) = default;
	Process &operator=(Process const &) = delete;
	Process &operator=(Process &&) = default;

	~Process();

	int getPipe(terminal::StdStream stream) const;

	int wait();

private:
	ProcessArguments args;
	pid_t parent;
	pid_t child;
	std::map<terminal::StdStream, detail::Pipe> pipes;
};

template <typename R> struct ProblemResult
{
	using result_type = typename std::decay<R>::type;

	result_type actual;
	const result_type expected;

	bool isCorrect() const;
};

template <typename R> bool ProblemResult<R>::isCorrect() const
{
	return actual == expected;
}

template <typename R>
std::ostream &operator<<(std::ostream &o, ProblemResult<R> const &r)
{
	o << "Actual result: " << r.actual
	  << " / Expected result: " << r.expected;
	return o;
}

template <typename R>
int problemMain(std::function<ProblemResult<R>()> const &problem, int /*argc*/,
                char const *const * /*argv*/)
{
	euler::util::Profiler profiler(
	        terminal::isInteractiveTerminal(terminal::StdStream::Out));

	try
	{
		ProblemResult<R> result = problem();
		if(terminal::isInteractiveTerminal(terminal::StdStream::Out))
			std::cout << result << "\n";
		return result.isCorrect() ? EXIT_SUCCESS : EXIT_FAILURE;
	}
	catch(std::exception const &e)
	{
		if(terminal::isInteractiveTerminal(terminal::StdStream::Err))
			std::cerr << "Caught exception: " << e.what() << "\n";
	}
	catch(...)
	{
		if(terminal::isInteractiveTerminal(terminal::StdStream::Err))
			std::cerr << "Caught unknown exception.\n";
	}

	return EXIT_FAILURE;
}
}
}
}

#define EULER_PROBLEM_ENTRYPOINT                                               \
	int main(int argc, char const *const *argv)                            \
	{                                                                      \
		::euler::util::process::registerProblemSignalHandlers();       \
		return ::euler::util::process::problemMain<decltype(           \
		        problem())::result_type>(problem, argc, argv);         \
	}

#endif

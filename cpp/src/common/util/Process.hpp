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
#include <type_traits>

#include <bdrck/process/Pipe.hpp>

namespace euler
{
namespace util
{
namespace process
{
void registerProblemSignalHandlers();

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
	bool isInteractiveOut = bdrck::process::pipe::isInteractiveTerminal(
	        bdrck::process::pipe::getStreamPipe(
	                bdrck::process::StdStream::STDOUT));
	bool isInteractiveErr = bdrck::process::pipe::isInteractiveTerminal(
	        bdrck::process::pipe::getStreamPipe(
	                bdrck::process::StdStream::STDERR));

	try
	{
		ProblemResult<R> result = problem();
		if(isInteractiveOut)
			std::cout << result << "\n";
		return result.isCorrect() ? EXIT_SUCCESS : EXIT_FAILURE;
	}
	catch(std::exception const &e)
	{
		if(isInteractiveErr)
			std::cerr << "Caught exception: " << e.what() << "\n";
	}
	catch(...)
	{
		if(isInteractiveErr)
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

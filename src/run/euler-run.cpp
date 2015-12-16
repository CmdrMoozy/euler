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

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "common/fs/Path.hpp"
#include "common/math/Math.hpp"
#include "common/util/Process.hpp"
#include "common/util/Profiler.hpp"
#include "common/util/Terminal.hpp"

int main(int, char const *const *)
{
	std::string pattern = euler::fs::path::join(
	        {EULER_BINARY_DIR, "src", "done", "????", "????"});
	std::vector<std::string> binaries = euler::fs::path::glob(pattern);

	std::vector<double> timings;
	std::size_t successes = 0;
	for(auto const &binary : binaries)
	{
		euler::util::Profiler profiler;
		euler::util::process::Process process(binary);
		int ret = process.wait();
		timings.push_back(profiler.getElapsed());

		if(ret == EXIT_SUCCESS)
		{
			++successes;
		}
		else if(euler::util::terminal::isInteractiveTerminal(
		                euler::util::terminal::StdStream::Out))
		{
			std::cout << "FAILED: " << binary << "\n";
		}
	}

	double avgTiming = euler::math::average(timings.begin(), timings.end());
	double minTiming = *std::min_element(timings.begin(), timings.end());
	double maxTiming = *std::max_element(timings.begin(), timings.end());

	assert(successes <= binaries.size());

	if(euler::util::terminal::isInteractiveTerminal(
	           euler::util::terminal::StdStream::Out))
	{
		std::cout << "Executed " << binaries.size() << " problems ("
		          << successes << " successes, "
		          << (binaries.size() - successes) << " failures).\n";
		std::printf("Execution time: average %0.9fs, min %0.9fs, max "
		            "%0.9fs\n",
		            avgTiming, minTiming, maxTiming);
	}

	return successes == binaries.size() ? EXIT_SUCCESS : EXIT_FAILURE;
}

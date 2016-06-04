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
#include <map>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include <bdrck/fs/Util.hpp>
#include <bdrck/process/Process.hpp>
#include <bdrck/process/Terminal.hpp>

#include "common/math/Math.hpp"
#include "common/util/Profiler.hpp"

namespace
{
struct ExecutionResult
{
	std::string problem;
	double time;
	bool success;
};

std::vector<ExecutionResult> executeProblems()
{
	std::string pattern = bdrck::fs::combinePaths(
	        {EULER_BINARY_DIR, "src", "done", "????", "????"});
	std::vector<std::string> binaries = bdrck::fs::glob(pattern);

	std::vector<ExecutionResult> results;
	for(auto const &binary : binaries)
	{
		euler::util::Profiler profiler;
		bdrck::process::Process process(binary);
		int ret = process.wait();
		double time = profiler.getElapsed();

		if(ret != EXIT_SUCCESS)
			std::cout << "FAILED: " << binary << "\n";

		results.push_back({bdrck::fs::basename(binary), time,
		                   ret == EXIT_SUCCESS});
	}
	return results;
}

constexpr unsigned int PERCENTILES[] = {50, 75, 85, 95, 99};

std::map<unsigned int, std::vector<double>::const_iterator>
computePercentiles(std::vector<double> const &times)
{
	std::map<unsigned int, std::vector<double>::const_iterator> percentiles;
	for(auto const &p : PERCENTILES)
	{
		percentiles.insert(std::make_pair(
		        p, euler::math::percentileValue(p, times.begin(),
		                                        times.end())));
	}
	return percentiles;
}

struct Timings
{
	std::vector<double> times;
	std::size_t successes;

	double average;
	double minimum;
	double maximum;
	double stddev;
	double total;

	std::map<unsigned int, std::vector<double>::const_iterator> percentiles;

	Timings(std::vector<ExecutionResult> const &results)
	        : times(),
	          successes(0),
	          average(),
	          minimum(),
	          maximum(),
	          stddev(),
	          total(),
	          percentiles()
	{
		for(auto const &result : results)
		{
			times.emplace_back(result.time);
			if(result.success)
				++successes;
		}

		std::sort(times.begin(), times.end());

		average = euler::math::average(times.begin(), times.end());
		minimum = *times.begin();
		maximum = *times.rbegin();
		stddev = euler::math::stddevPopulation(times.begin(),
		                                       times.end());
		total = std::accumulate(times.begin(), times.end(), double(0));

		percentiles = computePercentiles(times);
	}
};
}

int main(int, char const *const *)
{
#ifdef EULER_DEBUG
	if(bdrck::process::terminal::isInteractiveTerminal(
	           bdrck::process::terminal::StdStream::Out))
	{
		std::cout << "WARNING: Problems were built in debug mode. "
		             "Timings may not be useful.\n";
	}
#endif

	std::vector<ExecutionResult> results = executeProblems();
	std::sort(
	        results.begin(), results.end(),
	        [](ExecutionResult const &a, ExecutionResult const &b) -> bool {
		        return a.time < b.time;
		});

	Timings timings(results);

	if(bdrck::process::terminal::isInteractiveTerminal(
	           bdrck::process::terminal::StdStream::Out))
	{
		std::cout << "Executed " << results.size() << " problems ("
		          << timings.successes << " successes, "
		          << (results.size() - timings.successes)
		          << " failures).\n";

		std::printf("Execution time: average %0.9fs, min %0.9fs, max "
		            "%0.9fs, stddev %0.9fs, total %0.9fs\n",
		            timings.average, timings.minimum, timings.maximum,
		            timings.stddev, timings.total);

		std::cout << "Time percentiles: ";
		for(auto const &percentile : timings.percentiles)
		{
			std::printf("%u:%0.9fs ", percentile.first,
			            *percentile.second);
		}
		std::cout << "\n";

		std::size_t topSlowest =
		        std::min<std::size_t>(10, results.size());
		std::cout << "Top " << topSlowest
		          << " slowest problems, descending order: ";
		for(std::size_t i = 0; i < topSlowest; ++i)
		{
			std::cout << results[results.size() - 1 - i].problem
			          << " ";
		}
		std::cout << "\n";
	}

	return timings.successes == results.size() ? EXIT_SUCCESS
	                                           : EXIT_FAILURE;
}

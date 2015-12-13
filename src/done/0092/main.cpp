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

#include <cstdint>
#include <array>

#include "common/util/Process.hpp"

/*
 * A number chain is created by continuously adding the square of the digits in
 * a number to form a new number until it has been seen before.
 *
 * For example,
 *
 *     44 -> 32 -> 13 -> 10 -> 1 -> 1
 *     85 -> 89 -> 145 -> 42 -> 20 -> 4 -> 16 -> 37 -> 58 -> 89
 *
 * Therefore any chain that arrives at 1 or 89 will become stuck in an endless
 * loop. What is most amazing is that EVERY starting number will eventually
 * arrive at 1 or 89.
 *
 * How many starting numbers below ten million will arrive at 89?
 */

namespace
{
constexpr uint64_t EXPECTED_RESULT = 8581146;

euler::util::process::ProblemResult<uint64_t> problem()
{
	bool *stop = new bool[10000001]; // Cache which numbers end at 89 to
	                                 // prevent recalculation.
	uint64_t count = 0, x, sum;

	// Fill cache with false's to start.

	for(int i = 0; i < 10000001; ++i)
		stop[i] = false;

	// Start at 2, since 1 has already arrived at 1...

	for(uint64_t n = 2; n < 10000000; ++n)
	{
		x = n;

		do
		{
			sum = 0;

			while(x > 0)
			{
				sum += (x % 10) * (x % 10);
				x /= 10;
			}

			x = sum;
			if((x <= 10000000) && (stop[x]))
				x = 89;

		} while((x != 89) && (x != 1));

		if(x == 89)
		{
			stop[n] = true;
			++count;
		}
	}

	delete[] stop;
	return {count, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

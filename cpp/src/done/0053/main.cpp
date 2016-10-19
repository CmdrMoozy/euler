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

#include "common/math/EMath.h"
#include "common/util/Process.hpp"

/*
 * There are exactly ten ways of selecting three from five, 12345:
 *
 *     123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
 *
 * In combinatorics, we use the notation, 5C3 = 10.
 *
 * In general,
 *
 * nCr = n! / (r! * (n-r)!), where r <= n, n! = n * (n-1 * ... * 3 * 2 * 1,
 * and 0! = 1.
 *
 * It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.
 *
 * How many, not necessarily distinct, values of nCr, for 1 <= n <= 100, are
 * greater than one-million?
 */

namespace
{
constexpr uint32_t EXPECTED_RESULT = 4075;

euler::util::process::ProblemResult<uint32_t> problem()
{
	uint64_t v;
	uint32_t n, r, c;

	c = 0;
	for(n = 1; n <= 100; n++)
	{
		for(r = 1; r <= n; r++)
		{
			v = EMath::combinations(static_cast<int>(n),
			                        static_cast<int>(r));

			if(v > 1000000)
				c++;
		}
	}

	return {c, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

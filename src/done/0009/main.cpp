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
 * A Pythagorean triplet is a set of three natural numbers, a < b < c, for
 * which,
 *
 *     a^2 + b^2 = c^2
 *
 * For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2
 *
 * There exists a Pythagorean triplet for which a + b + c = 1000. Find the
 * product abc.
 */

namespace
{
constexpr uint64_t EXPECTED_RESULT = 31875000;

struct Solution
{
	bool valid;
	uint64_t product;
};

Solution checkSolution(uint32_t i, uint32_t j, uint32_t k)
{
	uint64_t a = EMath::getPythagoreanTripleA(i, j, k);
	uint64_t b = EMath::getPythagoreanTripleB(i, j, k);
	uint64_t c = EMath::getPythagoreanTripleC(i, j, k);
	return {(a + b + c) == 1000, a * b * c};
}

euler::util::process::ProblemResult<uint64_t> problem()
{
	for(uint32_t rangeMax = 5;; rangeMax += 5)
	{
		for(uint32_t i = 1; i <= rangeMax; ++i)
		{
			for(uint32_t j = 1; j <= rangeMax; ++j)
			{
				for(uint32_t k = 1; k <= rangeMax; ++k)
				{
					if(i <= j)
						continue;
					Solution s = checkSolution(i, j, k);
					if(s.valid)
					{
						return {s.product,
						        EXPECTED_RESULT};
					}
				}
			}
		}
	}
}
}

EULER_PROBLEM_ENTRYPOINT

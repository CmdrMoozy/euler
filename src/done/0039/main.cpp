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

#include <cmath>
#include <cstdint>
#include <set>
#include <vector>

#include "common/types/ERightTriangle.h"
#include "common/util/Process.hpp"

/*
 * If p is the perimeter of a right angle triangle with integral length sides,
 * {a,b,c}, there are exactly three solutions for p = 120.
 *
 * {20,48,52}, {24,45,51}, {30,40,50}
 *
 * For which value of p <= 1000, is the number of solutions maximised?
 */

namespace
{
constexpr std::size_t PERIMETER_MAX = 1000;
constexpr double DOUBLE_COMPARE_EPSILON = 0.0000000001;

constexpr std::size_t EXPECTED_RESULT = 840;

euler::util::process::ProblemResult<std::size_t> problem()
{
	std::vector<std::set<ERightTriangle>> count(PERIMETER_MAX + 1);
	for(uint32_t a = 1; a <= 998; ++a)
	{
		for(uint32_t b = 1; b <= 998; ++b)
		{
			double c = std::sqrt(static_cast<double>(a * a) +
			                     static_cast<double>(b * b));
			uint32_t ic = static_cast<uint32_t>(std::floor(c));

			if(std::abs(static_cast<double>(ic) - c) >=
			   DOUBLE_COMPARE_EPSILON)
			{
				continue;
			}

			if((a + b + ic) > PERIMETER_MAX)
				continue;

			count[a + b + ic].insert(ERightTriangle(a, b, ic));
		}
	}

	std::size_t mp = 0;
	std::size_t mv = 0;
	for(std::size_t a = 0; a < (PERIMETER_MAX + 1); ++a)
	{
		if(count[a].size() > mv)
		{
			mp = a;
			mv = count[a].size();
		}
	}

	return {mp, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

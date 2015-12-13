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
 * Starting in the top left corner of a 2x2 grid, there are 6 routes (without
 * backtracking) to the bottom right corner.
 *
 *     [...]
 *
 * How many routes are there through a 20x20 grid?
 */

namespace
{
constexpr uint64_t EXPECTED_RESULT = 137846528820;

euler::util::process::ProblemResult<uint64_t> problem()
{
	/*
	 * It is well-defined that the number of paths (without backtracking)
	 * through an m by n grid is: (m + n) combinations of n.
	 */
	return {EMath::combinations(40, 20), EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

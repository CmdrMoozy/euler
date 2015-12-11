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
#include "common/math/EPrimeSieve.h"
#include "common/util/Process.hpp"

/*
 * The prime factors of 13195 are 5, 7, 13 and 29.
 *
 * What is the largest prime factor of the number 600851475143?
 */

namespace
{
constexpr uint64_t VALUE_TO_FACTOR = 600851475143;
constexpr uint32_t EXPECTED_RESULT = 6857;

euler::util::process::ProblemResult<uint32_t> problem()
{
	uint64_t root = EMath::isqrt(VALUE_TO_FACTOR);
	EPrimeSieve s;
	s.setLimit(static_cast<uint32_t>(root));

	for(auto it = s.rbegin(); it != s.rend(); ++it)
	{
		if((VALUE_TO_FACTOR % *it) == 0)
			return {*it, EXPECTED_RESULT};
	}

	return {0, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

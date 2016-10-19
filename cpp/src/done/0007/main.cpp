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

#include "common/math/EPrimeSieve.h"
#include "common/util/Process.hpp"

/*
 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see
 * that the 6th prime is 13.
 *
 * What is the 10001st prime number?
 */

namespace
{
constexpr uint32_t TARGET_PRIME = 10001;
constexpr uint32_t INITIAL_SIEVE_LIMIT = 100000;
constexpr uint32_t SIEVE_SCALING_FACTOR = 2;
constexpr uint32_t EXPECTED_RESULT = 104743;

euler::util::process::ProblemResult<uint32_t> problem()
{
	EPrimeSieve s;
	s.setLimit(INITIAL_SIEVE_LIMIT);
	uint32_t primeCount = 1;
	auto it = s.begin();
	while(true)
	{
		++it;
		++primeCount;

		// If we have reached the target prime, break out of the loop.
		if(primeCount == TARGET_PRIME)
			return {*it, EXPECTED_RESULT};

		// If we have reached the end of the sieve, increase its size
		// and reset the iterator.
		if(it == s.end())
		{
			uint32_t number = *(--it);
			s.setLimit(s.getLimit() * SIEVE_SCALING_FACTOR);
			it = s.find(number);
			++it;
		}
	}
}
}

EULER_PROBLEM_ENTRYPOINT

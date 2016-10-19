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
#include "common/types/EBigInteger.h"
#include "common/util/Process.hpp"

/*
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
 *
 * Find the sum of all the primes below two million.
 */

namespace
{
constexpr uint32_t PRIME_VALUE_MAX = 2000000;
constexpr char EXPECTED_VALUE[] = "142913828922";

euler::util::process::ProblemResult<EBigInteger> problem()
{
	EPrimeSieve s;
	s.setLimit(PRIME_VALUE_MAX - 1);

	EBigInteger total(static_cast<int64_t>(0));
	for(auto it = s.begin(); it != s.end(); ++it)
		total += EBigInteger(static_cast<uint64_t>(*it));

	return {total, EBigInteger(std::string(EXPECTED_VALUE))};
}
}

EULER_PROBLEM_ENTRYPOINT

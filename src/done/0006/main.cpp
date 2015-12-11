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

#include <gmp.h>
#include <gmpxx.h>

#include "common/util/Process.hpp"

/*
 * The sum of the squares of the first ten natural numbers is,
 *
 *     1^2 + 2^2 + ... + 10^2 = 385
 *
 * The square of the sum of the first ten natural numbers is,
 *
 *     (1 + 2 + ... + 10)^2 = 55^2 = 3025
 *
 * Hence the difference between the sum of the squares of the first ten natural
 * numbers and the square of the sum is 3025 - 385 = 2640.
 *
 * Find the difference between the sum of the squares of the first one hundred
 * natural numbers and the square of the sum.
 */

namespace
{
constexpr uint64_t START_NUMBER = 1;
constexpr uint64_t END_NUMBER = 100;
constexpr uint64_t EXPECTED_RESULT = 25164150;

euler::util::process::ProblemResult<uint64_t> problem()
{
	mpz_class result = 0;

	for(uint64_t i = START_NUMBER; i <= END_NUMBER; ++i)
		result += i;
	result = (result * result);

	mpz_class sumOfSquares = 0;
	for(uint64_t i = START_NUMBER; i <= END_NUMBER; ++i)
		sumOfSquares += (i * i);
	result -= sumOfSquares;

	return {result.get_ui(), EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

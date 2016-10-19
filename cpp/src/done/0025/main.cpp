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

#include <cstddef>
#include <cstdint>

#include <gmp.h>
#include <gmpxx.h>

#include "common/math/EMath.h"
#include "common/util/Process.hpp"

/*
 * The Fibonacci sequence is defiend by the recurrence relation:
 *
 *     F(n) = F(n-1) + F(n-2), where F(1) = 1 and F(2) = 1.
 *
 * Hence the first 12 terms will be:
 *
 *     F(1) = 1
 *     F(2) = 1
 *     F(3) = 2
 *     F(4) = 3
 *     F(5) = 5
 *     F(6) = 8
 *     F(7) = 13
 *     F(8) = 21
 *     F(9) = 34
 *     F(10) = 55
 *     F(11) = 89
 *     F(12) = 144
 *
 * The 12th term, F(12), is the first term to contain three digits.
 *
 * What is the first term in the Fibonacci sequence to contain 1000 digits?
 */

namespace
{
constexpr uint64_t EXPECTED_RESULT = 4782;

euler::util::process::ProblemResult<uint64_t> problem()
{
	mpz_class target;

	// The limit we are searching for is 10^999.
	target = 10;
	mpz_pow_ui(target.get_mpz_t(), target.get_mpz_t(), 999);

	return {EMath::fibonacciSearch(1000, target), EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

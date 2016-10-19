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
#include "common/types/EDigitInteger.h"
#include "common/util/Process.hpp"

/*
 * We shall say than an n-digit number is pandigital if it makes use of all the
 * digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is
 * also prime.
 *
 * What is the largest n-digit pandigital prime that exists?
 */

namespace
{
constexpr int PRIME_PRECISION = 100;
constexpr uint64_t EXPECTED_RESULT = 7652413;

euler::util::process::ProblemResult<uint64_t> problem()
{
	uint32_t digits[] = {987654321, 87654321, 7654321, 654321, 54321,
	                     4321,      321,      21,      1};
	uint64_t result = 0, i, j;
	EDigitInteger d;

	for(i = 0; i < 9; i++)
	{
		d = digits[i];
		do
		{
			j = d.toInteger();

			if(j > result)
				if(EMath::isPrime_UI(j, PRIME_PRECISION))
					result = j;

		} while(d.permutateDigits());

		if(result != 0)
			break;
	}

	return {result, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

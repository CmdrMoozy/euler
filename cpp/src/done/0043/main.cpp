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

#include "common/util/EArrayUtilities.h"
#include "common/util/Process.hpp"

/*
 * The number, 1406357289, is a 0 to 9 pandigital number because it is made up
 * of each of the digits 0 to 9 in some order, but it also has a rather
 * interesting sub-string divisibility property.
 *
 * Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note
 * the following:
 *
 *     - d2d3d4  = 406 is divisible by 2
 *     - d3d4d5  = 063 is divisible by 3
 *     - d4d5d6  = 635 is divisible by 5
 *     - d5d6d7  = 357 is divisible by 7
 *     - d6d7d8  = 572 is divisible by 11
 *     - d7d8d9  = 728 is divisible by 13
 *     - d8d9d10 = 289 is divisible by 17
 *
 * Find the sum of all 0 to 9 pandigital numbers with this property.
 */

namespace
{
constexpr uint64_t EXPECTED_RESULT = 16695334890;

euler::util::process::ProblemResult<uint64_t> problem()
{
	uint64_t sum = 0, n;
	uint64_t test;

	/*
	 * We start with the number 1023456789 because numbers with leading
	 * zeros are actually NOT 0-9 pandigital,
	 * and this is the smallest number which doesn't have a leading zero.
	 */
	uint64_t digits[10] = {1, 0, 2, 3, 4, 5, 6, 7, 8, 9};

	// Loop through all 0-9 pandigitals.

	do
	{
		// Test for the divisibilities we are looking for.

		test = (digits[7] * 100) + (digits[8] * 10) + digits[9];
		if((test % 17) != 0)
			continue;

		test = (test / 10) + (digits[6] * 100);
		if((test % 13) != 0)
			continue;

		test = (test / 10) + (digits[5] * 100);
		if((test % 11) != 0)
			continue;

		test = (test / 10) + (digits[4] * 100);
		if((test % 7) != 0)
			continue;

		test = (test / 10) + (digits[3] * 100);
		if((test % 5) != 0)
			continue;

		test = (test / 10) + (digits[2] * 100);
		if((test % 3) != 0)
			continue;

		test = (test / 10) + (digits[1] * 100);
		if((test % 2) != 0)
			continue;

		// The number must have passed! Add it to the total.

		n = digits[0];
		n = (n * 10) + digits[1];
		n = (n * 10) + digits[2];
		n = (n * 10) + digits[3];
		n = (n * 10) + digits[4];
		n = (n * 10) + digits[5];
		n = (n * 10) + digits[6];
		n = (n * 10) + digits[7];
		n = (n * 10) + digits[8];
		n = (n * 10) + digits[9];
		sum += n;

	} while(EArrayUtilities::permutate<uint64_t>(digits, 10));

	return {sum, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

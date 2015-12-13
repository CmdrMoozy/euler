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

#include <climits>
#include <cstdint>

#include "common/types/EDigitInteger.h"
#include "common/util/EBitwise.h"
#include "common/util/Process.hpp"

/*
 * The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.
 *
 * Find the sum of all numbers, less than one million, which are palindromic in
 * base 10 and base 2.
 *
 * (Please note that the palindromic number, in either base, may not include
 * leading zeros.)
 */

namespace
{
constexpr uint32_t EXPECTED_RESULT = 872187;

euler::util::process::ProblemResult<uint32_t> problem()
{
	uint32_t i, result;
	EDigitInteger d;

	result = 0;
	for(i = 1; i < 1000000; i++)
	{
		// If our number is palindromic in base 2...
		if(EBitwise::isPalindromic(i))
		{
			// If it is also palindromic in base 10...
			d = i;
			if(d.isPalindrome())
			{
				// Add it to our results list!
				result += i;
			}
		}
	}

	return {result, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

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
#include <set>

#include "common/types/EDigitInteger.h"
#include "common/util/Process.hpp"

/*
 * A paldinromic number reads the same both ways. The largest palindrome made
 * from the product of two 2-digit numbers is 9009 = 91 x 99.
 *
 * Find the largest palindrome made from the product of two 3-digit numbers.
 */

namespace
{
constexpr uint32_t EXPECTED_RESULT = 906609;

euler::util::process::ProblemResult<uint32_t> problem()
{
	EDigitInteger eda;

	// Formulate a list of all of the products of two three-digit numbers.
	std::set<uint32_t> products;
	for(uint32_t a = 100; a < 1000; a++)
	{
		// a is our upper bound, so we don't re-insert b*a and a*b.
		for(uint32_t b = 100; b <= a; b++)
			products.insert(a * b);
	}

	// Start with the largest number and work backwards until we find a
	// palindrome.
	for(auto rit = products.rbegin(); rit != products.rend(); rit++)
	{
		eda = *rit;
		if(eda.isPalindrome())
			return {*rit, EXPECTED_RESULT};
	}

	return {0, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

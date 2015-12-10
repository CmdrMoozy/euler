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

#include <iostream>
#include <cassert>
#include <cstdint>
#include <set>
#include <algorithm>
#include <cmath>

#include "common/math/EMath.h"
#include "common/math/Math.h"
#include "common/types/EDigitInteger.h"

/*
 * Take the number 192 and multiply it by each of 1, 2, and 3:
 *
 *     192 x 1 = 192
 *     192 x 2 = 384
 *     192 x 3 = 576
 *
 * By concatenating each product we get the 1 to 9 pandigital, 192384576. We
 *will call 192384576
 * the concatenated product of 192 and (1,2,3)
 *
 * The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4,
 *and 5, giving the
 * pandigital, 918273645, which is the concatenated product of 9 and
 *(1,2,3,4,5).
 *
 * What is the largest 1 to 9 pandigital 9-digit number that can be formed as
 *the concatenated product
 * of an integer with (1,2, ... ,n) where n > 1?
 */

inline void concatenate(uint64_t &d, uint64_t o)
{
	d *= euler::math::ipow(10,
	                       static_cast<uint8_t>(EMath::logBaseTen(o) + 1));
	d += o;
}

int main(void)
{
	std::set<uint64_t> numbers;
	std::set<uint64_t>::reverse_iterator it;
	EDigitInteger ptest;

	uint64_t concat, lbound, ubound;

	/*
	 * Test every number of multiples from [2, 9], since 9 is the largest
	 * number of multiples we
	 * can take that can still possibly produce a 9-digit number (assuming
	 * the base is one).
	 */

	for(uint64_t n = 2; n <= 9; ++n)
	{ // The largest number we will multiply the base by.

		/*
		 * We calculate lower and upper bounds for the base number based
		 *on the fact that the end number needs
		 * to be nine digits in length. Thus, we generate the largest
		 *number which would produce a result of less
		 * than nine digits:
		 *
		 *     10^(floor(9/n) - 1)
		 *
		 * And the smallest number which would produce a result of more
		 *than nine digits:
		 *
		 *     10^(floor(9/n))
		 *
		 * For instance, when n = 3, our bounds are going to be: (99,
		 *1000), which would result in us testing numbers
		 * in the inclusive range [100, 999].
		 */

		lbound = euler::math::ipow(
		        10, static_cast<uint8_t>(
		                    floor(9.0 / static_cast<double>(n))) -
		                    1);
		ubound = euler::math::ipow(
		        10, static_cast<uint8_t>(
		                    floor(9.0 / static_cast<double>(n))));

		for(uint64_t base = lbound; base < ubound; ++base)
		{ // The base number we are taking multiples of.

			/*
			 * The problem description gives that the pandigital
			 * 918273645 exists, which means that the greatest
			 * pandigital must be greater than or equal to the given
			 * one. Thus, the first digit of our base must
			 * be a nine.
			 */

			if(base / (euler::math::ipow(
			                  10,
			                  static_cast<uint8_t>(
			                          EMath::logBaseTen(base)))) !=
			   9)
				continue;

			// Formulate the number.

			concat = 0;
			for(uint64_t i = 1; i <= n; ++i)
			{
				// Add this product to the end of our number.

				concatenate(concat, base * i);

				// If our number is too large, just quit now.

				if(EMath::logBaseTen(concat) > 8)
				{
					concat = 0;
					break;
				}
			}

			// If the number isn't exactly 9 digits, it cannot be
			// 9-digit pandigital.

			if(EMath::logBaseTen(concat) != 8)
				continue;

			// If the number is pandigital, add it to the list.

			ptest = concat;
			if(ptest.isPandigital())
				numbers.insert(concat);
		}
	}

	// Print out the largest number we got.

	it = numbers.rbegin();
	if(it != numbers.rend())
	{
		std::cout << "The largest pandigital is: " << (*it) << "\n";
		assert((*it) == 932718654);
	}
	else
	{
		std::cout << "No pandigital numbers found.\n";
		assert(false);
	}

	return 0;
}

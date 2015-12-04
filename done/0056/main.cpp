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

#include <cassert>
#include <cstddef>
#include <iostream>

#include <gmp.h>
#include <gmpxx.h>

#include "libeuler/types/EDigitInteger.h"

/*
 * A googol (10^100) is a massive number: one followed by one-hundred zeros;
 *100^100 is almost
 * unimaginably large: one followed by two-hundred zeros. Despite their size,
 *the sum of the
 * digits in each number is only 1.
 *
 * Considering natural numbers of the form, a^b, where a, b < 100, what is the
 *maximum digital
 * sum?
 */

int main(void)
{
	EDigitInteger d;
	uint32_t a, b, s, result;
	mpz_class number;

	result = 0;
	for(a = 99; a >= 1; --a)
	{
		// Skip any powers of 10, since they will always have a sum of
		// just 1.
		if((a % 10) == 0)
			continue;

		for(b = 99; b >= 1; --b)
		{
			mpz_ui_pow_ui(number.get_mpz_t(), a, b);
			d = number;

			s = static_cast<uint32_t>(d.sumOfDigits());
			if(s > result)
				result = s;
		}
	}

	std::cout << "The maximum digital sum in our range is: " << result
	          << "\n";

	assert(result == 972);
	return 0;
}

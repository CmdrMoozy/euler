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

#include "libeuler/math/EMath.h"

/*
 * An irrational decimal fraction is created by concatenating the positive integers:
 *
 *     0.12345678910_1_112131415161718192021...
 *
 * It can be seen that the 12th digit of the fractional part is 1.
 *
 * If dn represents the nth digit of the fractional part, find the value of the following
 * expression.
 *
 *     d1 x d10 x d100 x d1000 x d10000 x d100000 x d1000000
 */

int main(void)
{
	uint32_t i, j, on, n, result, log;
	short *digits;
	digits = new short[1000000];

	// Populate our digits list.
	i = 0;
	on = 1;
	while(i < 1000000)
	{
		n = on;
		log = EMath::logBaseTen(on);

		j = i + log;
		while(n > 0)
		{
			if(j < 1000000)
				digits[j] = n % 10;
			--j;
			n /= 10;
		}
		i += log + 1;

		on++;
	}

	// Get our result.

	result = digits[0] * digits[9] * digits[99] * digits[999] *
		digits[9999] * digits[99999] * digits[999999];

	delete[] digits;

	std::cout << "The product of the specified digits is: " << result << "\n";

	assert(result == 210);
	return 0;
}

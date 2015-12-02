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

#include "libeuler/types/EDigitInteger.h"
#include "libeuler/math/EMath.h"
#include "libeuler/math/Math.h"

/*
 * It can be seen that the number, 125874, and its double, 251748, contain
 *exactly the same
 * digits, but in a different order.
 *
 * Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x,
 *contain the same
 * digits.
 */

int main(void)
{
	uint32_t x, a, b, c;
	EDigitInteger dx, db;

	// For each positive integer...
	for(x = 2;; x++)
	{
		// If our multiples are getting too large, move on to the next
		// multiple of 10.
		c = EMath::logBaseTen(x);
		if(EMath::logBaseTen(6 * x) > EMath::logBaseTen(x))
		{
			x = euler::math::ipow(10, (c + 1)) - 1;
			continue;
		}

		a = (x + x);
		dx = a; // 2x
		b = (a + x);
		db = b; // 3x

		dx.sortDigitsAscending();
		db.sortDigitsAscending();

		if(dx == db)
		{
			b = (a + x); // 4x
			db = b;

			db.sortDigitsAscending();

			if(dx == db)
			{
				b += x; // 5x
				db = b;

				db.sortDigitsAscending();

				if(dx == db)
				{
					b += x; // 6x
					db = b;

					db.sortDigitsAscending();

					if(dx == db)
					{
						break;
					}
				}
			}
		}
	}

	std::cout << "The smallest positive integer such that its multiples "
	             "contain the same digits is: "
	          << x << "\n";

	assert(x == 142857);
	return 0;
}

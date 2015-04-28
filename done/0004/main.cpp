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
#include <set>
#include <cassert>

#include "libeuler/types/EDigitInteger.h"

/*
 * A paldinromic number reads the same both ways. The largest palindrome made
 *from the
 * product of two 2-digit numbers is 9009 = 91 x 99.
 *
 * Find the largest palindrome made from the product of two 3-digit numbers.
 */

int main(void)
{
	EDigitInteger eda;
	std::set<uint32_t> products;
	std::set<uint32_t>::reverse_iterator rit;
	uint32_t a, b;

	// Formulate a list of all of the products of two three-digit numbers.
	for(a = 100; a < 1000; a++)
		for(b = 100; b <= a; b++) // a is our upper bound, so we don't
			                  // re-insert b*a and a*b.
			products.insert(a * b);

	// Start with the largest number and work backwards until we find a
	// palindrome.
	for(rit = products.rbegin(); rit != products.rend(); rit++)
	{
		eda = (*rit);
		if(eda.isPalindrome())
		{
			std::cout << "The largest palindrome that is a product "
			             "of two 3-digit numbers is: " << (*rit)
			          << "\n";

			assert((*rit) == 906609);
			return 0;
		}
	}

	return 0;
}

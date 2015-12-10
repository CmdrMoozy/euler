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
#include <set>

#include <gmp.h>
#include <gmpxx.h>

#include "common/math/EPrimeSieve.h"

/*
 * The prime factors of 13195 are 5, 7, 13 and 29.
 *
 * What is the largest prime factor of the number 600851475143?
 */

#define VALUE_TO_FACTOR 600851475143

int main(void)
{
	EPrimeSieve s;
	std::set<uint32_t>::iterator it;
	mpz_class value, root;

	value = VALUE_TO_FACTOR;
	mpz_sqrt(root.get_mpz_t(), value.get_mpz_t());

	s.setLimit(static_cast<uint32_t>(root.get_ui()));

	it = s.end();
	it--;
	do
	{
		if((value % (*it)) == 0)
		{
			std::cout << "The largest prime factor of " << value
			          << " is: " << (*it) << "\n";

			assert((*it) == 6857);
			return 0;
		}

		if(it == s.begin())
			break;

		it--;
	} while(true);

	return 0;
}

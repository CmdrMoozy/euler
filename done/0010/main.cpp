/*
 * euler - A collection of ProjectEuler solutions, and supporting libraries and tools.
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

#include "libeuler/math/EPrimeSieve.h"

/*
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
 *
 * Find the sum of all the primes below two million.
 */

#define PRIME_VALUE_MAX 2000000
#define PRIME_PRECISION 100

int main(void)
{
	mpz_class total;
	EPrimeSieve s;
	std::set<uint32_t>::iterator it;

	s.setLimit(PRIME_VALUE_MAX - 1);

	total = 0;
	for(it = s.begin(); it != s.end(); it++)
		total += (*it);

	std::cout << "The sum of all primes less than 2,000,000 is: " << total << "\n";

	assert(total == 142913828922);
	return 0;
}

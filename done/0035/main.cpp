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

#include <iostream>
#include <map>
#include <cassert>

#include <gmp.h>
#include <gmpxx.h>

#include "libeuler/euler/ECircularPrimeSieve.h"

#define PRIME_LIMIT 1000000

/*
 * The number, 197, is called a circular prime because all rotations of the digits:
 * 197, 971, and 719, are themselves prime.
 *
 * There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73,
 * 79, and 97.
 *
 * How many circular primes are there below one million?
 */

int main(void)
{
	int count;
	ECircularPrimeSieve s;
	
	s.setLimit(PRIME_LIMIT);
	
	count = s.getSize();
	std::cout << "The number of circular primes under " << PRIME_LIMIT << " is: " << count << "\n";
	
	assert(count == 55);
	return 0;
}

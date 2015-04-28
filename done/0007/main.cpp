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
#include <cstdint>
#include <cassert>
#include <set>

#include "libeuler/math/EPrimeSieve.h"

/*
 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th
 * prime is 13.
 *
 * What is the 10001st prime number?
 */

#define TARGET_PRIME 10001
#define INITIAL_SIEVE_LIMIT 100000

int main(void)
{
	EPrimeSieve s;
	int primeCount;
	uint32_t number;
	std::set<uint32_t>::iterator it;
	
	// Define some arbitrary sieve limit to start.
	s.setLimit(INITIAL_SIEVE_LIMIT);
	
	primeCount = 1;
	it = s.begin();
	while(true)
	{
		// Move to the next prime.
		it++;
		primeCount++;
		
		// If we are at the target prime, break out of the loop.
		if(primeCount == TARGET_PRIME)
			break;
		
		// If we have reached the end of the sieve, increase its size by a factor of 2 & reset the iterator.
		if(it == s.end())
		{
			number = (* (--it));
			s.setLimit(s.getLimit() * 2);
			it = s.find(number);
			it++;
		}
	}
	
	std::cout << "The 10,001st prime is: " << (*it) << "\n";
	
	assert((*it) == 104743);
	return 0;
}

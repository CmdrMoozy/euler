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
#include <cassert>

#include "libeuler/math/EPrimeSieve.h"
#include "libeuler/types/EDigitInteger.h"

#define INITIAL_SIEVE_LIMIT 1000000
#define SIEVE_STEPPING 2
#define TARGET_COUNT 11

/*
 * The number 3797 has an interesting property. Being prime itself, it is possible to
 * continuously remove digits from left to right, and remain prime at each stage: 3797,
 * 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
 *
 * Find the sum of the only eleven primes that are both truncatable from left to right and
 * right to left.
 *
 * NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
 */

int main(void)
{
	EPrimeSieve sieve;
	std::set<uint32_t>::iterator it;
	uint32_t h, sum = 0;
	int count = 0, i;
	
	EDigitInteger number;
	bool trunc;
	
	sieve.setLimit(INITIAL_SIEVE_LIMIT);
	
	// Skip past the single-digit primes excluded by the problem description.
	it = sieve.begin();
	while( ((*it) < 10) && (it != sieve.end()) )
		it++;
	
	// Keep going until we hit our target count of primes.
	while(count < TARGET_COUNT)
	{
		// Set our number.
		number = (*it);
		
		// Test if our number is truncatable from left to right.
		trunc = true;
		for(i = 1; i < number.digitCount(); i++)
		{
			h = number.rangeToInteger(i, number.digitCount() - 1);
			if(sieve.find(h) == sieve.end())
			{
				trunc = false;
				break;
			}
		}
		
		// If it hasn't already found to NOT be truncatable, test if our number is from right to left.
		if(trunc)
		{
			for(i = 1; i < number.digitCount(); i++)
			{
				h = number.rangeToInteger(0, (number.digitCount() - 1) - i);
				if(sieve.find(h) == sieve.end())
				{
					trunc = false;
					break;
				}
			}
		}
		
		// If we've found a truncatable prime, increment our count.
		if(trunc)
		{
			count++;
			sum += (*it);
		}
		
		// Increment our iterator.
		h = (*it);
		it++;
		if(it == sieve.end())
		{
			// If we've reached the end of our current sieve, resize it and reset our iterator.
			sieve.setLimit(sieve.getLimit() * SIEVE_STEPPING);
			it = sieve.find(h);
			it++;
			
			// If we are still at the end of the sieve (for some reason), break.
			if(it == sieve.end())
				break;
		}
	}
	
	std::cout << "The sum of the only eleven truncatable primes is: " << sum << "\n";
	
	assert(sum == 748317);
	return 0;
}

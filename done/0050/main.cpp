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
#include <vector>

#include "libeuler/math/EPrimeSieve.h"

/*
 * The prime 41, can be written as the sum of six consecutive primes:
 *
 *     41 = 2 + 3 + 5 + 7 + 11 + 13
 *
 * This is the longest sum of consecutive primes that adds to a prime below one-hundred.
 *
 * The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and
 * is equal to 953.
 *
 * Which prime, below one-million, can be written as the sum of the most consecutive primes?
 */

int main(void)
{
	/*
	 * It can be determined by adding the first n primes that the largest possible set of consecutive
	 * primes added together to form a number less than 1,000,000 is 546. Thus, this is our starting
	 * upper limit.
	 */
	
	EPrimeSieve sieve(1000000);
	std::vector<uint32_t> primes(sieve.begin(), sieve.end());
	uint32_t start, end;
	
	for(uint32_t length = 546; length > 0; --length)
	{
		/*
		 * For each possible length, we try to see if the sum of that number of any consecutive primes
		 * produces a prime.
		 */
		
		start = 0;
		end = start + length;
		
		while(end <= sieve.getSize())
		{
			uint32_t result = 0;
			
			for(uint32_t i = start; i < end; ++i)
			{
				result += primes[i];
				
				// Stop checking if our sum has grown too large.
				if(result >= 1000000)
				{
					result = 0;
					break;
				}
			}
			
			// If the resulting number is prime, we've found the one we wanted!
			if(sieve.contains(result))
			{
				std::cout << "The prime < 1,000,000 which is the sum of the most consecutive primes (" << length <<
					") is: " << result << "\n";
				assert(result == 997651);
				
				return 0;
			}
			
			// Increment the range we are working with.
			++start;
			++end;
		}
	}
}

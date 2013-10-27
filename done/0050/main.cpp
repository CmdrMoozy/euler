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

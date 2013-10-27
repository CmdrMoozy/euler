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

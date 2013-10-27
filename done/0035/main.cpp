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

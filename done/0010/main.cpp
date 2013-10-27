#include <iostream>
#include <cassert>
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

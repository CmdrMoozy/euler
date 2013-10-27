#include <iostream>
#include <cassert>
#include <set>

#include <gmp.h>
#include <gmpxx.h>

#include "libeuler/math/EPrimeSieve.h"

/*
 * The prime factors of 13195 are 5, 7, 13 and 29.
 *
 * What is the largest prime factor of the number 600851475143?
 */

#define VALUE_TO_FACTOR 600851475143
#define PRIME_PRECISION 10

int main(void)
{
	EPrimeSieve s;
	std::set<uint32_t>::iterator it;
	mpz_class value, root;
	
	value = VALUE_TO_FACTOR;
	mpz_sqrt(root.get_mpz_t(), value.get_mpz_t());
	
	s.setLimit( static_cast<uint32_t>(root.get_ui()) );
	
	it = s.end();
	it--;
	do
	{
		if((value % (*it)) == 0)
		{
			std::cout << "The largest prime factor of " << value << " is: " << (*it) << "\n";
			
			assert((*it) == 6857);
			return 0;
		}
		
		if(it == s.begin())
			break;
		
		it--;
	} while(true);
	
	return 0;
}

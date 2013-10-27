#include <iostream>
#include <cassert>
#include <set>
#include <cstdint>

#include "libeuler/math/EMath.h"
#include "libeuler/math/EPrimeSieve.h"

/*
 * The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways:
 * (i) each of the three terms are prime, and, (ii) each of the 4-digit numbers are permutations of one another.
 *
 * There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there
 * is one other 4-digit increasing sequence.
 *
 * What 12-digit number do you form by concatenating the three terms in this sequence?
 */

int main(void)
{
	EPrimeSieve sieve(10000);
	std::set<uint32_t>::iterator ita, itb, itc;
	
	for(ita = sieve.lowerBound(1000); ita != sieve.end(); ita++)
	{ // For each four-digit prime...
		
		// For each arithmetic increase that would make sense...
		for(uint32_t add = 1; ((*ita) + (add << 1)) < 10000; ++add)
		{
			// See if the second number is prime.
			itb = sieve.find((*ita) + add);
			if(itb != sieve.end())
			{
				// See if the third number is prime.
				itc = sieve.find((*ita) + (add << 1));
				if(itc != sieve.end())
				{
					// See if they are permutations of one another.
					if(EMath::isPermutationOf((*ita), (*itb)) && EMath::isPermutationOf((*ita), (*itc)))
					{
						// See if the sequence we've found isn't just the given one.
						if( ((*ita) != 1487) && ((*itb) != 4817) && ((*itc) != 8147) )
						{
							std::cout << "Found arithmetic sequence: " << (*ita) <<
								(*itb) << (*itc) << "\n";
							
							assert( ((*ita) == 2969) && ((*itb) == 6299) &&
								((*itc) == 9629) );
							
							return 0;
						}
					}
				}
			}
		}
		
	}
	
	std::cout << "No arithmetic sequence found!\n";
	assert(false);
	return 1;
}

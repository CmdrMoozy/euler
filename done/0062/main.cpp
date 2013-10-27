#include <iostream>
#include <cassert>
#include <cstdint>
#include <vector>

#include "libeuler/math/EMath.h"

/*
 * The cube, 41063625 (345^3), can be permutated to produce two other cubes: 56623104 (384^3) and
 * 66430125 (405^3). In fact, 41063625 is the smallest cube which has exactly three permutations of
 * its digits which are also cube.
 *
 * Find the smallest cube for which exactly five permutations of its digits are cube.
 */

// "Find the smallest cube for which exactly CUBIC_PERMS_TARGET permutations of its digits are cube."
#define CUBIC_PERMS_TARGET 5

int main(void)
{
	uint64_t bresult = 0;
	
	// We can start with 8-digit cubes, since we're given that 41063625 is the smallest 3-permutation.
	int digits = 8;
	
	while(true)
	{
		// Build the range of numbers we'll be testing for this digit count.
		
		std::vector<uint64_t> bases;
		uint64_t min = EMath::icbrt(EMath::integerPow(10, digits - 1)) + 1;
		uint64_t max = EMath::icbrt(EMath::integerPow(10, digits));
		
		for(uint64_t i = min; i <= max; ++i)
			bases.push_back(i);
		
		/*
		 * For each base in this range, compute its cube root. For each other value in this
		 * range, if it's a permutation of the current value, we count it.
		 *
		 * If this value has exactly CUBIC_PERMS_TARGET permutations which are cubes in the same
		 * range, we're done. Otherwise, we can remove ALL permutations of this value from our
		 * list, since they have already been checked by proxy.
		 */
		
		for(std::vector<uint64_t>::iterator it = bases.begin(); it != bases.end(); ++it)
		{
			// If this base has already been checked, skip it.
			
			if((*it) == 0)
				continue;
			
			uint64_t value = (*it) * (*it) * (*it);
			
			// For each other value, test if it's a permutation of this value.
			
			std::vector< std::vector<uint64_t>::iterator > perms;
			
			for(std::vector<uint64_t>::iterator oit = it + 1; oit != bases.end(); ++oit)
			{
				uint64_t ov = (*oit) * (*oit) * (*oit);
				
				// If this other value is a permutation, add it to the list and carry on.
				
				if(EMath::isPermutationOf(value, ov))
					perms.push_back(oit);
			}
			
			// If we found enough other permutations, we're done. Otherwise, skip those others.
			
			if(perms.size() == (CUBIC_PERMS_TARGET - 1))
			{
				// Set our result, and stop looping - we're done!
				
				bresult = (*it);
				break;
			}
			else
			{
				// This value isn't the answer - clear it and all of its permutations.
				
				(*it) = 0;
				
				for(std::vector< std::vector<uint64_t>::iterator >::iterator cit = perms.begin();
					cit != perms.end(); ++cit)
				{
					(**cit) = 0;
				}
			}
		}
		
		// If we found our result, then just stop here.
		
		if(bresult != 0)
			break;
		
		// Increment our digit count.
		
		++digits;
	}
	
	// Print out our result and bail!
	
	std::cout << "The smallest cube with exactly " << (CUBIC_PERMS_TARGET -1) <<
		" other cubic permutations is: " << (bresult * bresult * bresult) << "\n";
	assert(bresult == 5027);
	
	return 0;
}

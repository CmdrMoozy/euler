#include <iostream>
#include <cassert>

#include <gmp.h>
#include <gmpxx.h>

#include "libeuler/types/EDigitInteger.h"

/*
 * A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost
 * unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the
 * digits in each number is only 1.
 *
 * Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital
 * sum?
 */

int main(void)
{
	EDigitInteger d;
	uint32_t a, b, s, result;
	mpz_class number;
	
	result = 0;
	for(a = 99; a >= 1; --a)
	{
		// Skip any powers of 10, since they will always have a sum of just 1.
		if((a % 10) == 0)
			continue;
		
		for(b = 99; b >= 1; --b)
		{
			mpz_ui_pow_ui(number.get_mpz_t(), a, b);
			d = number;
			
			s = d.sumOfDigits();
			if(s > result)
				result = s;
		}
	}
	
	std::cout << "The maximum digital sum in our range is: " << result << "\n";
	
	assert(result == 972);
	return 0;
}

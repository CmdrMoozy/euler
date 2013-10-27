#include <iostream>
#include <climits>
#include <cassert>

#include "libeuler/types/EDigitInteger.h"
#include "libeuler/util/EBitwise.h"

/*
 * The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.
 *
 * Find the sum of all numbers, less than one million, which are palindromic in base 10 and
 * base 2.
 *
 * (Please note that the palindromic number, in either base, may not include leading zeros.)
 */

int main(void)
{
	uint32_t i, result;
	EDigitInteger d;
	
	result = 0;
	for(i = 1; i < 1000000; i++)
	{
		// If our number is palindromic in base 2...
		if(EBitwise::isPalindromic(i))
		{
			// If it is also palindromic in base 10...
			d = i;
			if(d.isPalindrome())
			{
				// Add it to our results list!
				result += i;
			}
		}
	}
	
	std::cout << "The sum of the numbers below 1,000,000 that are palindromic in base 10 and 2 is: " << result << "\n";
	
	assert(result == 872187);
	return 0;
}

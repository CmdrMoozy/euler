#include <iostream>
#include <set>
#include <cassert>

#include "libeuler/types/EDigitInteger.h"

/*
 * A paldinromic number reads the same both ways. The largest palindrome made from the
 * product of two 2-digit numbers is 9009 = 91 x 99.
 *
 * Find the largest palindrome made from the product of two 3-digit numbers.
 */

int main(void)
{
	EDigitInteger eda;
	std::set<uint32_t> products;
	std::set<uint32_t>::reverse_iterator rit;
	uint32_t a, b;
	
	// Formulate a list of all of the products of two three-digit numbers.
	for(a = 100; a < 1000; a++)
		for(b = 100; b <= a; b++) // a is our upper bound, so we don't re-insert b*a and a*b.
			products.insert(a*b);
	
	// Start with the largest number and work backwards until we find a palindrome.
	for(rit = products.rbegin(); rit != products.rend(); rit++)
	{
		eda = (*rit);
		if(eda.isPalindrome())
		{
			std::cout << "The largest palindrome that is a product of two 3-digit numbers is: " << (*rit) << "\n";
			
			assert((*rit) == 906609);
			return 0;
		}
	}
	
	return 0;
}

#include <iostream>
#include <cassert>

#include <gmp.h>

#include "libeuler/types/EDigitInteger.h"

/*
 * 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
 *
 * What is the sum of the digits of the number 2^1000?
 */

int main(void)
{
	EDigitInteger eda;
	mpz_class number;
	int sum;
	
	number = 2;
	mpz_pow_ui(number.get_mpz_t(), number.get_mpz_t(), 1000);
	
	eda = number;
	sum = eda.sumOfDigits();
	std::cout << "The sum of the digits in 2^1000 is: " << sum << "\n";
	
	assert(sum == 1366);
	return 0;
}

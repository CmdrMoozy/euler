#include <iostream>
#include <cassert>

#include <gmp.h>
#include <gmpxx.h>

#include "libeuler/types/EDigitInteger.h"

/*
 * n! means n x  (n - 1) x ... x 3 x 2 x 1
 *
 * Find the sum of the digits in the number 100!
 */

int main(void)
{
	EDigitInteger eda;
	mpz_class number, sum;
	int result;
	
	mpz_fac_ui(number.get_mpz_t(), 100);
	
	eda = number;
	result = eda.sumOfDigits();
	std::cout << "The sum of the digits in 100! is: " << result << "\n";
	
	assert(result == 648);
	return 0;
}

#include <iostream>
#include <cassert>

#include <gmp.h>
#include <gmpxx.h>

#include "libeuler/math/EMath.h"

/*
 * The Fibonacci sequence is defiend by the recurrence relation:
 *
 *     F(n) = F(n-1) + F(n-2), where F(1) = 1 and F(2) = 1.
 *
 * Hence the first 12 terms will be:
 *
 *     F(1) = 1
 *     F(2) = 1
 *     F(3) = 2
 *     F(4) = 3
 *     F(5) = 5
 *     F(6) = 8
 *     F(7) = 13
 *     F(8) = 21
 *     F(9) = 34
 *     F(10) = 55
 *     F(11) = 89
 *     F(12) = 144
 *
 * The 12th term, F(12), is the first term to contain three digits.
 *
 * What is the first term in the Fibonacci sequence to contain 1000 digits?
 */

int main(void)
{
	mpz_class target;
	uint32_t result;
	
	// The limit we are searching for is 10^999.
	target = 10;
	mpz_pow_ui(target.get_mpz_t(), target.get_mpz_t(), 999);
	
	result = EMath::fibonacciSearch(1000, target);
	std::cout << "The " << result << "th number is the first to have >= 1,000 digits.\n";
	
	assert(result == 4782);
	return 0;
}

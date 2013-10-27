#include <iostream>
#include <cassert>
#include <cstdint>
#include <sstream>

#include <gmp.h>
#include <gmpxx.h>

/*
 * It is possible to show that the square root of two can be expressed as an infinite continued fraction.
 *
 *     sqrt(2) = 1 + 1/(2 + 1/(2 + 1/(2 + ... ))) = 1414213...
 *
 * By expanding this for the first four iterations, we get:
 *
 *     1 + 1/2 = 3/2 = 1.5
 *     1 + 1/(2 + 1/2) = 7/5 = 1.4
 *     1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...
 *     1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...
 *
 * The next three expansions are 99/70, 239/169, and 577/408, but the eighth expansion, 1393/985, is the
 * first example where the number of digits in the numerator exceeds the number of digits in the denominator.
 *
 * In the first one-thousand expansions, how many fractions contain a numerator with more digits than denominator?
 */

int main(void)
{
	mpz_class n = 1, d = 1, nn, nd, gcd;
	int total = 0;
	
	// Compute the first one thousand expansions.
	
	for(int i = 0; i < 1000; ++i)
	{
		// If this expansion's numerator has more digits than the denominator, add it to the total.
		
		std::stringstream num(std::stringstream::out), den(std::stringstream::out);
		num << n;
		den << d;
		
		if(num.str().length() > den.str().length())
			++total;
		
		// Calculate the next expansion.
		
		n = n + d + d;
		d = n - d;
		mpz_gcd(gcd.get_mpz_t(), n.get_mpz_t(), d.get_mpz_t());
		mpz_divexact(n.get_mpz_t(), n.get_mpz_t(), gcd.get_mpz_t());
		mpz_divexact(d.get_mpz_t(), d.get_mpz_t(), gcd.get_mpz_t());
	}
	
	std::cout << "The number of expansions where log10(numerator) > log10(denominator) is: " << total << "\n";
	assert(total == 153);
	
	return 0;
}

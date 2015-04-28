/*
 * euler - A collection of ProjectEuler libraries, tools, and solutions.
 * Copyright (C) 2013 Axel Rasmussen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <cassert>

#include "libeuler/math/EPrimeSieve.h"
#include "libeuler/math/EMath.h"

/*
 * Euler published the remarkable quadratic formula:
 *
 *     n^2 + n + 41
 *
 * it turns out that the formula will produce 40 primes for the consecutive values
 * n=0 to 39. However, when n=40, 40^2 + 40 + 41 = 40(40+1) + 41 is divisible by 41,
 * and certainly when n=41, 41^2 + 41 + 41 is clearly divisible by 41.
 *
 * Using computers, the incredible formula n^2 - 79n + 1601 was discovered, which
 * produces 80 primes for the consecutive values n=0 to 79. The product of the coefficients,
 * -79 and 1601, is -126479.
 *
 * Considering quadratics of the form:
 *
 *     n^2 + an + b, where |a| < 1000 and |b| < 1000
 *
 * Find the product of the coefficients, a and b, for the quadratic expression that
 * produces the longest maximum number of primes for consecutive values of n, starting
 * with n=0.
 */

#define SIEVE_LIMIT 1000000
#define PRIME_PRECISION 200

/*
 * This function returns the result of our polynomial with the given value of n, and the given
 * coefficients.
 */
inline int polynomial(int n, int a, int b)
{
	return ( (n*n) + (a*n) + b );
}

int main(void)
{
	EPrimeSieve sieve;
	int i, j, v;
	int a = 0, b = 0, n, cc, mc = -1;
	
	sieve.setLimit(SIEVE_LIMIT);
	
	// Test each possible polynomial.
	for(i = -999; i < 1000; i++)
	{
		for(j = -999; j < 1000; j++)
		{
			// Test each possible n value in this polynomial.
			cc=0;
			for(n = 0; ; n++)
			{
				v = polynomial(n, i, j);
				
				// Negative numbers are not prime.
				if(v < 0)
					break;
				
				if(v < SIEVE_LIMIT)
				{ // If our value is inside our sieve limit, test it for primality that way.
					if(sieve.find(v) != sieve.end())
						cc++;
					else
						break;
				}
				else
				{ // Otherwise, do a probabalistic test.
					if(EMath::isPrime_UI(v, PRIME_PRECISION))
						cc++;
					else
						break;
				}
			}
			
			// If this sequence is the longest we've found, update our results.
			if(cc > mc)
			{
				a=i;
				b=j;
				mc=cc;
			}
		}
	}
	
	std::cout << "The product of the coefficients on the longest prime-generating polynomial is: " << (a*b) << "\n";
	
	assert((a*b) == -59231);
	return 0;
}

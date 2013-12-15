/*
 * euler - A collection of ProjectEuler solutions, and supporting libraries and tools.
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
#include <cstdint>

#include <gmp.h>
#include <gmpxx.h>

/* 
 * The square root of 2 can be written as an infinite continued fraction.
 *
 * sqrt(2) = 1 +      1
 *               -----------
 *               2 +    1
 *                   -------
 *                   2 + ...
 *
 * The infinite continued fraction can be written, sqrt(2) = [1;(2)], (2) indicates that 2 repeats
 * ad infinitum. In a similar way, sqrt(23) = [4;(1,3,1,8)].
 *
 * It turns out that the sequence of partial values of continued fractions for square roots provide the best
 * rational approximations. Let us consider the convergents for sqrt(2):
 *
 *     3/2
 *     7/5
 *     17/12
 *     41/29
 *
 * Hence the sequence of the first ten convergents for sqrt(2) are:
 *
 *     1, 3/2, 7/5, 17/12, 41/29, 99/70, 239/169, 577/408, 1393/985, 3363/2378, ...
 *
 * What is most surprising is that the important mathematical constant,
 *
 *     e = [2; 1, 2, 1, 1, 4, 1, 1, 6, 1, ... , 1, 2k, 1, ...].
 *
 * The first ten terms in the sequence of convergents for e are:
 *
 *     2, 3, 8/3, 11/4, 19/7, 87/32, 106/39, 193/71, 1264/465, 1457/536, ...
 *
 * The sum of the digits in the numerator of the 10th convergent is 1+4+5+7=17.
 *
 * Find the sum of the digits in the numerator of the 100th convergent of the continued fraction for e.
 */

/*
 * This function returns the nth continued fraction denominator for the continued fraction representation
 * of e, elsewhere referred to as b(n).
 *
 * We are using the continued fraction: [ 2; (1, 2k, 1) ] for this calculation.
 */
uint64_t getDenominator(uint32_t n)
{
	if(n > 0)
	{
		if( (n % 3) == 2 )
			return 2 * ((n+1)/3);
		else
			return 1;
	}
	else
	{
		return 2;
	}
}

int main(void)
{
	/*
	 * By the Fundamental Recurrence formulas (http://en.wikipedia.org/wiki/Fundamental_recurrence_formulas),
	 * we are given the following:
	 *
	 * The nth convergent, x(n), = A(n) / B(n).
	 *
	 * Let A(n) and B(n) be defined by the recurrence relation:
	 *
	 *       A(0) = b(0)
	 *       A(1) = b(1)b(0) + a(1)
	 *     A(n+1) = b(n+1)A(n) + a(n+1)A(n-1)
	 *
	 *       B(0) = 1
	 *       B(1) = b(1)
	 *     B(n+1) = b(n+1)B(n) + a(n+1)B(n-1)
	 *
	 * Where a(n) and b(n) represent the nth numerator and denominator of the continued fraction, respectively.
	 * It can be seen that for the continued fraction representation [...], where S(n) is the nth term of the
	 * representation starting at S(0), that:
	 *
	 *     b(n) = S(n)
	 *     a(n) = 1
	 *
	 * It should also be noted that, by the way continued fraction representations are constructed, we know that
	 * the the convergent x(n) for all n in Z is automatically written in lowest terms (i.e., gcd(A(n), B(n)) = 1
	 * for all valid n).
	 */
	
	// The first two convergent numerators are 2(/1) and 3(/2).
	
	mpz_class Am1 = 2, A = 3, hold;
	uint64_t sum;
	
	// We want the numerator of the 100th convergent, so calculate the next A 99 times.
	
	for(uint32_t n = 1; n < 99; ++n)
	{
		// A(n+1) = b(n+1)A(n) + a(n+1)A(n-1)
		
		hold = (getDenominator(n + 1) * A) + Am1;
		Am1 = A;
		A = hold;
	}
	
	// A now contains the numerator of the 100th convergent. Add its digits to get our answer.
	
	sum = 0;
	while(A > 0)
	{
		hold = A % 10;
		sum += hold.get_ui();
		A /= 10;
	}
	
	std::cout << "The sum of the digits in the 100th numerator is: " << sum << "\n";
	assert(sum == 272);
	
	return 0;
}

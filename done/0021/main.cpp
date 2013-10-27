#include <iostream>
#include <set>
#include <cstdint>
#include <cassert>

#include "libeuler/math/EMath.h"

/*
 * Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
 * If d(a) = b and d(b) = a, where a != b, then a and b are an amicable pair and each of a and b are called
 * amicable numbers.
 *
 * For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(22) = 284.
 * The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
 *
 * Evaluate the sum of all the amicable numbers under 10000.
 */

#define LIMIT 10000

int main(void)
{
	std::set<uint32_t> bset;
	uint32_t a, b;
	uint32_t sum;
	
	for(sum = 0, a = 0; a <= LIMIT; a++)
	{
		if(bset.find(a) != bset.end())
			continue;
		
		b = EMath::aliquotSumProperDivisors(a);
		
		if(a == b)
			continue;
		
		if(EMath::aliquotSumProperDivisors(b) == a)
		{
			sum += a;
			sum += b;
			bset.insert(b);
		}
	}
	
	std::cout << "The sum of all amicable numbers below 10,000 is: " << sum << "\n";
	
	assert(sum == 31626);
	return 0;
}

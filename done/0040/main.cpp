#include <iostream>
#include <cassert>
#include <cstdint>

#include "libeuler/math/EMath.h"

/*
 * An irrational decimal fraction is created by concatenating the positive integers:
 *
 *     0.12345678910_1_112131415161718192021...
 *
 * It can be seen that the 12th digit of the fractional part is 1.
 *
 * If dn represents the nth digit of the fractional part, find the value of the following
 * expression.
 *
 *     d1 x d10 x d100 x d1000 x d10000 x d100000 x d1000000
 */

int main(void)
{
	uint32_t i, j, on, n, result, log;
	short *digits;
	digits = new short[1000000];
	
	// Populate our digits list.
	i = 0;
	on = 1;
	while(i < 1000000)
	{
		n = on;
		log = EMath::logBaseTen(on);
		
		j = i + log;
		while(n > 0)
		{
			digits[j--] = n % 10;
			n /= 10;
		}
		i += log + 1;
		
		on++;
	}
	
	// Get our result.
	
	result = digits[0] * digits[9] * digits[99] * digits[999] *
		digits[9999] * digits[99999] * digits[999999];
	
	delete[] digits;
	
	std::cout << "The product of the specified digits is: " << result << "\n";
	
	assert(result == 210);
	return 0;
}

#include <iostream>
#include <cassert>

#include "libeuler/types/EDigitInteger.h"
#include "libeuler/math/EMath.h"

#define PRIME_PRECISION 100

/*
 * We shall say than an n-digit number is pandigital if it makes use of all the digits
 * 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.
 *
 * What is the largest n-digit pandigital prime that exists?
 */

int main(int argc, char *argv[])
{
	uint32_t digits[] = {
		987654321,
		87654321,
		7654321,
		654321,
		54321,
		4321,
		321,
		21,
		1
	};
	uint32_t result = 0, i, j;
	EDigitInteger d;
	
	for(i = 0; i < 9; i++)
	{
		d = digits[i];
		do
		{
			
			j = d.toInteger();
			
			if(j > result)
				if(EMath::isPrime_UI(j, PRIME_PRECISION))
					result = j;
			
		} while(d.permutateDigits());
		
		if(result != 0)
			break;
	}
	
	std::cout << "The largest pandigital prime is: " << result << "\n";
	
	assert(result == 7652413);
	return 0;
}

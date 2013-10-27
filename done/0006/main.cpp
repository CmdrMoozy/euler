#include <iostream>
#include <cassert>

#include <gmp.h>
#include <gmpxx.h>

/*
 * The sum of the squares of the first ten natural numbers is,
 *
 *     1^2 + 2^2 + ... + 10^2 = 385
 *
 * The square of the sum of the first ten natural numbers is,
 *
 *     (1 + 2 + ... + 10)^2 = 55^2 = 3025
 *
 * Hence the difference between the sum of the squares of the first ten natural numbers
 * and the square of the sum is 3025 - 385 = 2640.
 *
 * Find the difference between the sum of the squares of the first one hundred natural numbers
 * and the square of the sum.
 */

#define START_NUMBER 1
#define END_NUMBER 100

int main(void)
{
	mpz_class result, a, b;
	int i;
	
	result = 0;
	a = 0;
	
	for(i = START_NUMBER; i <= END_NUMBER; i++)
		result += i;
	
	result = (result * result);
	
	for(i = START_NUMBER; i <= END_NUMBER; i++)
	{
		b = (i * i);
		a += b;
	}
	
	result -= a;
	
	std::cout << "The square of the sum of the first 100 natural numbers, minus the sum of the squares " <<
		"of the first 100 natural numbers is: " << result << "\n";
	
	assert(result == 25164150);
	return 0;
}

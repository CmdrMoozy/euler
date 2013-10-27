#include <iostream>
#include <cassert>

/*
 * 2520 is the smallest number that can be divided by each of the numbers from 1 to 10
 * without any remainder.
 *
 * What is the smallest positive number that is evenly divisible by all of the numbers
 * from 1 to 20?
 */

int main(void)
{
	uint64_t number = 0;
	bool success = false;
	
	while(!success)
	{
		number += 20;
		
		success = !(number % 11) &&
			!(number % 12) &&
			!(number % 13) &&
			!(number % 14) &&
			!(number % 15) &&
			!(number % 16) &&
			!(number % 17) &&
			!(number % 18) &&
			!(number % 19) &&
			!(number % 20);
	}
	
	std::cout << number << " is the smallest positive integer divisible by every number from [1, 20].\n";
	
	assert(number == 232792560);
	return 0;
}

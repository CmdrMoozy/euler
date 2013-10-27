#include <iostream>
#include <cassert>
#include <cstdint>
#include <array>

/*
 * A number chain is created by continuously adding the square of the digits in a number to form a new number until
 * it has been seen before.
 *
 * For example,
 *
 *     44 -> 32 -> 13 -> 10 -> 1 -> 1
 *     85 -> 89 -> 145 -> 42 -> 20 -> 4 -> 16 -> 37 -> 58 -> 89
 *
 * Therefore any chain that arrives at 1 or 89 will become stuck in an endless loop. What is most amazing is that EVERY
 * starting number will eventually arrive at 1 or 89.
 *
 * How many starting numbers below ten million will arrive at 89?
 */

int main(void)
{
	bool *stop = new bool[10000001]; // Cache which numbers end at 89 to prevent recalculation.
	uint64_t count = 0, x, sum;
	
	// Fill cache with false's to start.
	
	for(int i = 0; i < 10000001; ++i)
		stop[i] = false;
	
	// Start at 2, since 1 has already arrived at 1...
	
	for(uint64_t n = 2; n < 10000000; ++n)
	{
		x = n;
		
		do
		{
			
			sum = 0;
			
			while(x > 0)
			{
				sum += (x % 10) * (x % 10);
				x /= 10;
			}
			
			x = sum;
			if( (x <= 10000000) && (stop[x]) )
				x = 89;
			
		} while( (x != 89) && (x != 1) );
		
		if(x == 89)
		{
			stop[n] = true;
			++count;
		}
	}
	
	std::cout << count << " numbers below ten million arrive at 89.\n";
	assert(count == 8581146);
	
	delete[] stop;
	return 0;
}

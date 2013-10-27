#include <iostream>
#include <cassert>
#include <cstdlib>

#define STARTING_UPPER_LIMIT 200000
#define UPPER_LIMIT_MULTIPLIER 2

/*
 * The first two consecutive numbers to have two distinct prime factors are:
 *
 *     14 = 2 x 7
 *     15 = 3 x 5
 *
 * The first three consecutive numbers to have three distinct prime factors are:
 *
 *     644 = 2^2 x 7 x 23
 *     645 = 3 x 5 x 43
 *     646 = 2 x 17 x 19
 *
 * Find the first four consecutive integers to have four distinct prime factors. What is
 * the first of these numbers?
 */

void sieve(uint32_t *li, uint32_t le)
{
	uint32_t i, j;
	
	for(i = 0; i < le; ++i)
		li[i] = 0;
	
	for(i = 2; i < le; ++i)
	{
		if(li[i] > 0)
			continue;
		
		for(j = i; j < le; j += i)
			li[j]++;
	}
}

int main(void)
{
	uint32_t *list = NULL;
	uint32_t upperBound = STARTING_UPPER_LIMIT;
	uint32_t result, i;
	
	result = 0;
	do
	{
		if(list != NULL)
			delete[] list;
		
		list = new uint32_t[upperBound];
		sieve(list, upperBound);
		
		i = 0;
		while((i+3) < upperBound)
		{
			if(list[i] == 4)
			{
				if(list[i+3] == 4)
				{
					if(list[i+1] == 4)
					{
						if(list[i+2] == 4)
						{
							result = i;
							break;
						}
						else
						{
							i += 3;
						}
					}
					else
					{
						i += 3;
					}
				}
				else
				{
					i += 4;
				}
			}
			else
			{
				++i;
			}
		}
		
		upperBound *= UPPER_LIMIT_MULTIPLIER;
	} while(result == 0);
	
	if(list != NULL)
		delete[] list;
	
	std::cout << "The first of four consecutive integers to have four distinct prime factors is: " << result << "\n";
	
	assert(result == 134043);
	return 0;
}

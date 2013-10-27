#include <iostream>
#include <cassert>
#include <cstdint>

#include "libeuler/math/EMath.h"

/*
 * A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
 *
 *     a^2 + b^2 = c^2
 *
 * For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2
 *
 * There exists a Pythagorean triplet for which a + b + c = 1000. Find the product abc.
 */
 
int main(void)
{
	uint32_t rangeMax;
	uint32_t i, j, k;
	uint32_t a, b, c;
	
	rangeMax = 5;
	while(1)
	{
		for(i = 1; i <= rangeMax; i++)
		{
			for(j = 1; j <= rangeMax; j++)
			{
				for(k = 1; k <= rangeMax; k++)
				{
					if(i > j)
					{
						a = EMath::getPythagoreanTripleA(i, j, k);
						b = EMath::getPythagoreanTripleB(i, j, k);
						c = EMath::getPythagoreanTripleC(i, j, k);
						
						if((a+b+c) == 1000)
						{
							std::cout << "The product of the desired pythagorean triple is: " << (a*b*c) << "\n";
							
							assert((a*b*c) == 31875000);
							return 0;
						}
					}
				}
			}
		}
		
		rangeMax += 5;
	}
	
	return 0;
}

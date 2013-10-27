#include <iostream>
#include <cassert>
#include <cstdint>

#include "libeuler/euler/ESpiral.h"

/*
 * Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5
 * spiral is formed as follows:
 *
 *    21 22 23 24 25
 *    20  7  8  9 10
 *    19  6  1  2 11
 *    18  5  4  3 12
 *    17 16 15 14 13
 *
 * It can be verified that the sum of the numbers on the diagonals is 101.
 *
 * What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the
 * same way?
 */

int main(void)
{
	ESpiral s;
	uint32_t result = 1;
	uint32_t i;
	
	i = 1;
	while(s.getSizeFor(i) <= 1001)
	{
		result += s.diagonalValueAt(i, ESpiral::I);
		result += s.diagonalValueAt(i, ESpiral::II);
		result += s.diagonalValueAt(i, ESpiral::III);
		result += s.diagonalValueAt(i, ESpiral::IV);
		
		i++;
	}
	
	std::cout << "The sum of the numbers on the diagonals is: " << result << "\n";
	
	assert(result == 669171001);
	return 0;
}

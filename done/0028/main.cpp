/*
 * euler - A collection of ProjectEuler libraries, tools, and solutions.
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

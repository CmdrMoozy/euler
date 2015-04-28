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
#include <vector>

#include "libeuler/util/EBitwise.h"

#define MIN_NUMBER 2
#define MAX_NUMBER 1000000

/*
 * The following iterative sequence is defined for the set of positive integers:
 *
 *   n -> n/2 (n is even)
 *   n -> 3n + 1 (n is odd)
 *
 * Using the rule above and starting with 13, we generate the following sequence:
 *
 *   13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
 *
 * It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms.
 * Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers
 * finish at 1.
 *
 * Which starting number, under one million, produces the longest chain?
 *
 * NOTE: Once the chain starts the terms are allowed to go above one million.
 */

int main(void)
{
	uint32_t *lenlist;
	uint64_t n, p;
	uint32_t l, length, number;
	
	lenlist = new uint32_t[ MAX_NUMBER + 1 ];
	
	length = number = 0;
	
	// For each number...
	for(n = MIN_NUMBER; n <= MAX_NUMBER; ++n)
	{
		// Optimize powers of two and odd starting numbers.
		if( (n&1) == 0)
		{
			if(EBitwise::isPowTwo(n))
			{
				l = lenlist[n] = EBitwise::lg32(n);
				
				// If this sequence is longer than our previous one, replace it.
				if(l > length)
				{
					number = n;
					length = l;
				}
				
				continue;
			}
			
			p = n;
			l = 1;
		}
		else
		{
			p = (n+n+n+1);
			l = 2;
		}
		
		// While our number doesn't reach a number we have already calculated...
		while(p >= n)
		{
			if( (p&1) != 0 )
			{
				p = (p+p+p+1);
				++l;
			}
			
			p /= 2;
			++l;
		}
		
		// Retrieve the already-calculated length and add this one to the list.
		l += lenlist[p];
		lenlist[n] = l;
		
		// If this sequence is longer than our previous one, replace it.
		if(l > length)
		{
			number = n;
			length = l;
		}
	}
	
	delete[] lenlist;
	
	std::cout << "The number that produces the longest chain is " << number << " (" << length << " elements).\n";
	
	assert(number == 837799);
	return 0;
}

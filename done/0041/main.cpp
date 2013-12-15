/*
 * euler - A collection of ProjectEuler solutions, and supporting libraries and tools.
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

#include "libeuler/types/EDigitInteger.h"
#include "libeuler/math/EMath.h"

#define PRIME_PRECISION 100

/*
 * We shall say than an n-digit number is pandigital if it makes use of all the digits
 * 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.
 *
 * What is the largest n-digit pandigital prime that exists?
 */

int main(void)
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

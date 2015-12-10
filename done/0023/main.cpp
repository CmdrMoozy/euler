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

#include <cassert>
#include <cstring>
#include <iostream>
#include <set>

#include "common/math/EMath.h"

/*
 * A perfect number is a number for which the sum of its proper divisors is
 *exactly
 * equal to the number. For example, the sum of the proper divisors of 28 would
 *be
 * 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
 *
 * A number n is called deficient if the sum of its proper divisors is less than
 *n
 * and it is called abundant if this sum exceeds n.
 *
 * As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest
 *number
 * that can be written as the sum of two abundant numbers is 24. By mathematical
 * analysis, it can be shown that all integers greater than 28123 can be written
 *as
 * the sum of two abundant numbers. However, this upper limit cannot be reduced
 *by
 * analysis even though it is known that the greatest number that cannot be
 *expressed
 * as the sum of two abundant numbers is less than this limit.
 *
 * Find the sum of all the positive integers which cannot be written as the sum
 *of
 * two abundant numbers.
 */

// We reduce the upper limit as per:
// http://en.wikipedia.org/wiki/Abundant_number
#define LIMIT 20161

int main(void)
{
	uint64_t *abundantNumbers;
	uint64_t i, j, k;
	uint32_t total;
	bool sum;

	abundantNumbers = new uint64_t[LIMIT + 1];
	memset(abundantNumbers, 0, sizeof(uint64_t) * (LIMIT + 1));

	// Formulate a list of all of the abundant numbers.
	for(i = 12; i <= LIMIT;
	    i++) // 12 is the smallest abundant number, so start there.
	{
		// If we already have this number in our list, continue.
		if(abundantNumbers[i] == i)
			continue;

		j = EMath::aliquotSumProperDivisors(i);
		if(j > i)
		{ // If this number is abundant...
			// Add all of its multiples to the list.
			j = 1;
			do
			{
				k = i * (j++);

				if(k > LIMIT)
					break;

				abundantNumbers[k] = k;
			} while(true);
		}
	}

	// For each number in range, see if it can be written as a sum of
	// abundant numbers.
	total = 0;
	for(i = 1; i <= LIMIT; i++)
	{
		sum = false;

		for(j = 0; j <= LIMIT; j++)
		{
			if(abundantNumbers[j] == 0)
				continue;

			if(abundantNumbers[j] >= i)
				break;

			k = i - abundantNumbers[j];
			if(k <= LIMIT)
			{
				if(abundantNumbers[k] == k)
				{
					sum = true;
					break;
				}
			}
		}

		if(!sum)
			total += i;
	}

	delete[] abundantNumbers;

	std::cout << "The sum of the numbers that CANNOT be written as the sum "
	             "of two abundant numbers is: "
	          << total << "\n";

	assert(total == 4179871);
	return 0;
}

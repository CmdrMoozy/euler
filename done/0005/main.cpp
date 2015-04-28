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

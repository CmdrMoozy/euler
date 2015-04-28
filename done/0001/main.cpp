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
 * If we list all the natural numbers below 10 that are multiples of 3 or 5, we
 *get
 * 3, 5, 6 and 9. The sum of these multiples is 23.
 *
 * Find the sum of all the multiples of 3 or 5 below 1000.
 */

int main(void)
{
	int total = 0, i;

	for(i = 1; i < 1000; i++)
		if(((i % 5) == 0) || ((i % 3) == 0))
			total += i;

	std::cout << "The sum of all the multiples of 3 or 5 below 1000 is: "
	          << total << "\n";

	assert(total == 233168);
	return 0;
}

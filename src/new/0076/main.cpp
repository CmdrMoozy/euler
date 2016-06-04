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
#include <cstdint>
#include <iostream>

/*
 * It is possible to write five as a sum in exactly six different ways:
 *
 *     4 + 1
 *     3 + 2
 *     3 + 1 + 1
 *     2 + 2 + 1
 *     2 + 1 + 1 + 1
 *     1 + 1 + 1 + 1 + 1
 *
 * How many different ways can one hundred be written as a sum of at least two
 *positive
 * integers?
 */

#define MAX_VALUE 100

int main(void)
{
	uint64_t *counts = new uint64_t[MAX_VALUE + 1];

	// Set some initial counts for the recurrence relation.

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 1;

	// For each next value, count using previous values.

	for(uint64_t v = 3; v <= MAX_VALUE; ++v)
	{
		for(uint64_t sub = 1; sub < v; ++sub)
		{
		}
	}

	// Done! Print the answer.

	delete[] counts;

	return 0;
}

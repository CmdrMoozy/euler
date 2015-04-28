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

#include "libeuler/util/EArray.h"

/*
 * A permutation is an ordered arrangement of objects. For example, 3124 is one
 *possible
 * permutation of the digits 1, 2, 3 and 4. If all of the permutations are
 *listed numerically
 * or alphabetically, we call it lexicographic order. The lexicographic
 *permutations of 0, 1
 * and 2 are:
 *
 * 012 021 102 120 201 210
 *
 * What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4,
 *5, 6, 7, 8 and 9?
 */

int main(void)
{
	/*
	 * We just use the implementation found of Knuth's Algorithm L found in
	 * EulerArray
	 * to permutate the given starting string 1,000,000 times.
	 */

	int c;
	char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	EArray<char> permutator(10, digits);
	char solution[10] = {'2', '7', '8', '3', '9', '1', '5', '4', '6', '0'};

	// Make positive we have the first permutation.
	permutator.sortAscending();

	// Permutate until we are at the 1,000,000th permutation.
	for(c = 1; c < 1000000; c++)
		permutator.permutate();

	// Print out the results!

	std::cout << "The 1,000,000th permutation of '0123456789' is: ";

	for(c = 0; c < 10; c++)
		std::cout << permutator.at(c);

	std::cout << "\n";

	for(c = 0; c < 10; c++)
		assert(permutator.at(c) == solution[c]);

	return 0;
}

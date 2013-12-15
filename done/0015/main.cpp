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

#include "libeuler/math/EMath.h"

/*
 * Starting in the top left corner of a 2x2 grid, there are 6 routes (without backtracking) to
 * the bottom right corner.
 *
 *     [...]
 *
 * How many routes are there through a 20x20 grid?
 */

int main(void)
{
	unsigned long int r;
	/*
	 * It is well-defined that the number of paths (without backtracking) through an m by n grid is:
	 * (m + n) combinations of n.
	 */
	
	r = EMath::combinations(40, 20);
	std::cout << "The number of paths through a 20x20 grid is: " << r << "\n";
	
	assert(r == 137846528820);
	return 0;
}

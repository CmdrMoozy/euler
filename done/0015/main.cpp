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

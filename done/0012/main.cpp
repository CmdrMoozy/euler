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
#include <cstdint>
#include <cassert>

#include "libeuler/math/EMath.h"

/*
 * This is the smallest number that has exactly 500 factors -- we use this as
 * our lower-bound.
 * The theory behind how this number was calculated is described here:
 *     http://www.primepuzzles.net/problems/prob_019.htm
 */
#define MINIMUM_NUMBER 62370000

/*
 * The sequence of triangle numbers is generated by adding the natural numbers.
 *So the 7th triangle
 * number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten terms would be:
 *
 *  1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
 *
 * Let us list the factors of the first seven triangle numbers:
 *    1: 1
 *    3: 1,3
 *    6: 1,2,3,6
 *   10: 1,2,5,10
 *   15: 1,3,5,15
 *   21: 1,3,7,21
 *   28: 1,2,4,7,14,28
 *
 * We can see that 28 is the first trangle number to have over five divisors.
 * What is the value of the first triangle number to have over five hundred
 *divisors?
 */

int main(void)
{
	uint32_t i = 0, n = 0;

	while(n < MINIMUM_NUMBER)
		n = EMath::getTriangleNumberN(++i);

	while(EMath::aliquotNumberDivisors(n) <= 500)
		n = EMath::getTriangleNumberN(++i);

	std::cout << "The first triangle number with over 500 factors is: " << n
	          << "\n";

	assert(n == 76576500);
	return 0;
}

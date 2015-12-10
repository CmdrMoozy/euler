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
#include <cstdint>

#include "common/math/EMath.h"

/*
 * A Pythagorean triplet is a set of three natural numbers, a < b < c, for
 *which,
 *
 *     a^2 + b^2 = c^2
 *
 * For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2
 *
 * There exists a Pythagorean triplet for which a + b + c = 1000. Find the
 *product abc.
 */

int main(void)
{
	uint32_t rangeMax;
	uint32_t i, j, k;
	uint64_t a, b, c;

	rangeMax = 5;
	while(1)
	{
		for(i = 1; i <= rangeMax; i++)
		{
			for(j = 1; j <= rangeMax; j++)
			{
				for(k = 1; k <= rangeMax; k++)
				{
					if(i > j)
					{
						a = EMath::
						        getPythagoreanTripleA(
						                i, j, k);
						b = EMath::
						        getPythagoreanTripleB(
						                i, j, k);
						c = EMath::
						        getPythagoreanTripleC(
						                i, j, k);

						if((a + b + c) == 1000)
						{
							std::cout
							        << "The "
							           "product of "
							           "the "
							           "desired "
							           "pythagorean"
							           " triple "
							           "is: "
							        << (a * b * c)
							        << "\n";

							assert((a * b * c) ==
							       31875000);
							return 0;
						}
					}
				}
			}
		}

		rangeMax += 5;
	}
}

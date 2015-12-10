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
#include <set>

#include "common/math/EMath.h"
#include "common/types/EFraction.h"

/*
 * Consider the fraction, n/d, where n and d are positive integers. If n<d and
 *HCF(n,d)=1, it is
 * called a reduced proper fraction.
 *
 * If we list the set of reduced proper fractions for d <= 8 in ascending order
 *of size, we get:
 *
 *     1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8,
 *2/3, 5/7, 3/4, 4/5,
 *     5/6, 6/7, 7/8
 *
 * It can be seen that there are 21 elements in this set.
 *
 * How many elements would be contained in the set of reduced proper fractions
 *for d <= 1,000,000?
 */

#define DENOMINATOR_LIMIT 1000000

int main(void)
{
	std::set<EFraction> fractions;
	uint64_t n;

	for(n = 1; n < DENOMINATOR_LIMIT; ++n)
	{
		EFraction f(n, DENOMINATOR_LIMIT);
		f.reduce();

		fractions.insert(f);
	}

	std::cout << "The set contains " << fractions.size() << " fractions.\n";

	return 0;
}

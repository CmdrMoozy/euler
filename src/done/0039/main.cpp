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
#include <cmath>
#include <set>

#include "common/types/ERightTriangle.h"

/*
 * If p is the perimeter of a right angle triangle with integral length sides,
 *{a,b,c},
 * there are exactly three solutions for p = 120.
 *
 * {20,48,52}, {24,45,51}, {30,40,50}
 *
 * For which value of p <= 1000, is the number of solutions maximised?
 */

#define PERIMETER_MAX 1000

namespace
{
constexpr double DOUBLE_COMPARE_EPSILON = 0.000001;
}

int main(void)
{
	std::set<ERightTriangle> *count;
	uint32_t a, b, ic, mp;
	std::size_t mv;
	double c;

	count = new std::set<ERightTriangle>[PERIMETER_MAX + 1];

	for(a = 1; a <= 998; a++)
	{
		for(b = 1; b <= 998; b++)
		{
			c = sqrt(static_cast<double>(a * a) +
			         static_cast<double>(b * b));
			ic = static_cast<uint32_t>(floor(c));

			if(std::abs(static_cast<double>(ic) - c) <
			   DOUBLE_COMPARE_EPSILON)
			{
				continue;
			}

			if((a + b + ic) > PERIMETER_MAX)
				continue;

			count[a + b + ic].insert(ERightTriangle(a, b, ic));
		}
	}

	mv = mp = 0;
	for(a = 0; a < (PERIMETER_MAX + 1); a++)
	{
		if(count[a].size() > mv)
		{
			mp = a;
			mv = count[a].size();
		}
	}

	std::cout << "The perimeter with the most solutions is " << mp << " ("
	          << mv << " solutions).\n";

	delete[] count;
	assert(mp == 840);
	return 0;
}

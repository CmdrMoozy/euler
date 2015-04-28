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

#include "MathTest.h"

#include <cmath>

#include "libeuler/math/Math.h"

namespace
{
void ipowTest()
{
	for(int i = 0; i <= 10; ++i)
	{
		for(int j = 0; j <= 10; ++j)
		{
			uint64_t exp = static_cast<uint64_t>(std::pow(i, j));
			uint64_t act = euler::math::ipow(i, j);
			vrfy::assert::assertEquals(exp, act);
		}
	}
}

void ipowmodTest()
{
	for(int i = 1; i <= 5; ++i)
	{
		for(int j = 1; j <= 5; ++j)
		{
			uint64_t exp = static_cast<uint64_t>(std::pow(i, j)) % 5;
			uint64_t act = euler::math::ipowmod(i, j, 5);
			vrfy::assert::assertEquals(exp, act);
		}
	}
}
}

namespace euler
{
namespace test
{
void MathTest::test()
{
	ipowTest();
	ipowmodTest();
}
}
}

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

#include <catch/catch.hpp>

#include <cstdint>
#include <cstdlib>

#include "libeuler/types/EFraction.h"

TEST_CASE("Test fraction reducing", "[EFraction]")
{
	constexpr double DOUBLE_COMPARE_EPSILON = 0.00001;

	for(uint64_t m = 3; m <= 5; ++m)
	{
		for(uint64_t n = 0; n <= 10; ++n)
		{
			for(uint64_t d = 1; d <= 10; ++d)
			{
				EFraction f;
				f.setNumerator(n * m);
				f.setDenominator(d * m);
				CHECK(f.getNumerator() == (n * m));
				CHECK(f.getDenominator() == (d * m));

				double v = f.toDouble();
				f.reduce();
				CHECK(std::abs(f.toDouble() - v) <
				      DOUBLE_COMPARE_EPSILON);
			}
		}
	}
}

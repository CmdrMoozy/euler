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

#include "libeuler/types/EDigitInteger.h"

TEST_CASE("Test getting a range of digits as an integer", "[EDigitInteger]")
{
	uint64_t value = 12345678910ULL;
	EDigitInteger i(value);

	CHECK(i.rangeToInteger(0, 5) == 678910);
	CHECK(i.rangeToInteger(6, 9) == 2345);
	CHECK(i.rangeToInteger(0, 0) == 0);
	CHECK(i.rangeToInteger(10, 10) == 1);
	CHECK(i.rangeToInteger(0, 10) == 12345678910ULL);
}

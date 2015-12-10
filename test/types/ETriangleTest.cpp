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

#include "libeuler/types/ETriangle.h"

TEST_CASE("Test triangle constructors and equality operator", "[ETriangle]")
{
	ETriangle t(1, 2, 3);
	CHECK(t.getA() == 1);
	CHECK(t.getB() == 2);
	CHECK(t.getC() == 3);

	ETriangle u(t);
	CHECK(t == u);

	ETriangle v;
	CHECK(v.getA() == 0);
	CHECK(v.getB() == 0);
	CHECK(v.getC() == 0);
}

TEST_CASE("Test triangle get/set functions", "[ETriangle]")
{
	ETriangle t;

	t.setA(3);
	t.setB(2);
	t.setC(1);
	CHECK(t.getA() == 3);
	CHECK(t.getB() == 2);
	CHECK(t.getC() == 1);
}

TEST_CASE("Test isValidTriangle", "[ETriangle]")
{
	ETriangle t(1, 1, 2);
	CHECK(!t.isValidTriangle());

	ETriangle u(3, 4, 5);
	CHECK(u.isValidTriangle());
}

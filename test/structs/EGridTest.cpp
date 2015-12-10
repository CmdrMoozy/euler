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

#include "common/structs/EGrid.h"

TEST_CASE("Test grid construction", "[EGrid]")
{
	EGrid<int> g(10);
	CHECK(g.getSize() == 10);
}

TEST_CASE("Test setting grid points", "[EGrid]")
{
	EGrid<int> g(10);

	g.set(0, 0, 10);
	g.set(3, 4, 1230);
	g.set(1, 9, 5665);
	g.set(0, 3, 176);
	g.set(6, 1, 123);

	CHECK(g.at(0, 0) == 10);
	CHECK(g.at(3, 4) == 1230);
	CHECK(g.at(1, 9) == 5665);
	CHECK(g.at(0, 3) == 176);
	CHECK(g.at(6, 1) == 123);
}

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

#include "common/euler/ETriangleStructure.h"

TEST_CASE("Test ETriangleStructure path finding", "[ETriangleStructure]")
{
	// The largest path through the given triangle has been precomputed and
	// is 1074, so verify that our structure gives the right answer.

	constexpr std::size_t TRIANGLE_SIZE = 15;
	constexpr int EXPECTED_RESULT = 1074;

	constexpr int TEST_DATA[][TRIANGLE_SIZE] = {
	        {75},
	        {95, 64},
	        {17, 47, 82},
	        {18, 35, 87, 10},
	        {20, 4, 82, 47, 65},
	        {19, 1, 23, 75, 3, 34},
	        {88, 2, 77, 73, 7, 63, 67},
	        {99, 65, 4, 28, 6, 16, 70, 92},
	        {41, 41, 26, 56, 83, 40, 80, 70, 33},
	        {41, 48, 72, 33, 47, 32, 37, 16, 94, 29},
	        {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14},
	        {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57},
	        {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48},
	        {63, 66, 4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31},
	        {4, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23}};

	ETriangleStructure t(TRIANGLE_SIZE);
	for(std::size_t i = 0; i < TRIANGLE_SIZE; ++i)
		t.setRowAt(i, TEST_DATA[i]);

	CHECK(t.getHeight() == TRIANGLE_SIZE);
	CHECK(t.getLargestPathSum() == EXPECTED_RESULT);
}

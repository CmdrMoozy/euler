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
#include <vector>

#include "common/types/ERightTriangle.h"

TEST_CASE("Test triangle normalization", "[ERightTriangle]")
{
	ERightTriangle t;
	t.set(5, 3, 4);

	CHECK(t.getA() < t.getB());
	CHECK(t.getB() < t.getC());
}

TEST_CASE("Test valid right triangle detection", "[ERightTriangle]")
{
	using TestCase = struct
	{
		uint32_t a;
		uint32_t b;
		uint32_t c;
		bool valid;
	};

	static const std::vector<TestCase> TEST_CASES{
	        {3, 4, 5, true},    {5, 12, 13, true},  {7, 24, 25, true},
	        {8, 15, 17, true},  {9, 40, 41, true},  {11, 60, 61, true},
	        {12, 35, 37, true}, {13, 84, 85, true}, {16, 63, 65, true},
	        {20, 21, 29, true}, {28, 45, 53, true}, {33, 56, 65, true},
	        {36, 77, 85, true}, {39, 80, 89, true}, {48, 55, 73, true},
	        {65, 72, 97, true}, {3, 4, 6, false},   {5, 11, 13, false},
	        {8, 24, 25, false}, {8, 15, 18, false}, {9, 33, 41, false}};

	for(auto const &testCase : TEST_CASES)
	{
		ERightTriangle t;
		t.set(testCase.a, testCase.b, testCase.c);
		CHECK(t.isValidTriangle() == testCase.valid);
	}
}

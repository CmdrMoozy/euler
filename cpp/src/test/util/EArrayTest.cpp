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

#include <array>
#include <cstddef>

#include "common/util/EArray.h"

namespace
{
constexpr std::array<int, 5> TEST_DATA{{32, 12, 237, 98, 10}};

constexpr std::array<int, 10> NONUNIQUE_TEST_DATA{
        {-168, 2345, 112, 234, 8539, 90123, 234, 467, 168, 19233}};

constexpr std::array<int, 3> PERMUTATION_TEST_DATA{{3, 1, 2}};
}

TEST_CASE("Test constructors, operators, and comparisons", "[EArray]")
{
	EArray<int> a(TEST_DATA.size(), TEST_DATA.data());
	EArray<int> b(a);

	for(std::size_t i = 0; i < TEST_DATA.size(); ++i)
	{
		CHECK(a.at(i) == TEST_DATA[i]);
		CHECK(b.at(i) == TEST_DATA[i]);
	}

	CHECK(a == b);
	CHECK(a.isEqualTo(b));

	b.sortAscending();

	CHECK(!a.isEqualTo(b));
	CHECK(a.isEqualToUnsorted(b));

	b = a;

	CHECK(a.isEqualTo(b));
}

TEST_CASE("Test getSize and setSize", "[EArray]")
{
	EArray<int> a(TEST_DATA.size(), TEST_DATA.data());
	EArray<int> b(TEST_DATA.size(), TEST_DATA.data());

	a.setSize(10, true);
	b.setSize(0);

	for(std::size_t i = 0; i < 10; ++i)
	{
		if(i < TEST_DATA.size())
			CHECK(a.at(i) == TEST_DATA[i]);
		else
			CHECK(a.at(i) == 0);
	}

	CHECK(a.getSize() == 10);
	CHECK(b.getSize() == 0);
}

TEST_CASE("Test at and set", "[EArray]")
{
	EArray<int> a(TEST_DATA.size(), TEST_DATA.data());

	CHECK(a.at(1) != 123);
	a.set(1, 123);
	CHECK(a.at(1) == 123);

	CHECK(a.at(3) != 456);
	a.at(3) = 456;
	CHECK(a.at(3) == 456);
}

TEST_CASE("Test search and binarySearch", "[EArray]")
{
	EArray<int> a(TEST_DATA.size(), TEST_DATA.data());
	a.at(2) = 278327;
	CHECK(a.search(278327) == 2);

	a.sortAscending();
	CHECK(a.search(278327) == a.binarySearch(278327));

	CHECK(a.search(-10) == -1);
	CHECK(a.binarySearch(-10) == -1);
}

TEST_CASE("Test sortAscending, sortDescending, and reverse", "[EArray]")
{
	EArray<int> a(TEST_DATA.size(), TEST_DATA.data());
	EArray<int> b(TEST_DATA.size(), TEST_DATA.data());

	a.sortAscending();
	CHECK(a != b);

	b.sortDescending();
	CHECK(a != b);

	b.reverse();
	CHECK(a == b);
}

TEST_CASE("Test isUnique and makeUnique", "[EArray]")
{
	EArray<int> a(NONUNIQUE_TEST_DATA.size(), NONUNIQUE_TEST_DATA.data());

	CHECK(!a.isUnique());
	a.makeUnique();
	CHECK(a.isUnique());
	CHECK(a.getSize() == 9);
}

TEST_CASE("Test permutate and reversePermutate", "[EArray]")
{
	EArray<int> a(PERMUTATION_TEST_DATA.size(),
	              PERMUTATION_TEST_DATA.data());
	a.sortAscending();
	EArray<int> b(a);

	b.permutate();
	CHECK(b != a);
	b.reversePermutate();
	CHECK(b == a);

	a.permutate();
	CHECK(a.getSize() == 3);
	CHECK(a.at(0) == 1);
	CHECK(a.at(1) == 3);
	CHECK(a.at(2) == 2);
}

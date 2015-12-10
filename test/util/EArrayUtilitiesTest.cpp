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

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <memory>
#include <random>
#include <set>
#include <vector>

#include "common/util/EArrayUtilities.h"
#include "common/util/ScopeExit.h"

namespace
{
using ArrayPointer = std::unique_ptr<int, std::function<void(int *)>>;

void arrayDeleter(int *p)
{
	delete[] p;
}
}

TEST_CASE("Test getPowerSet", "[EArrayUtilities]")
{
	std::set<int> originalSet{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::set<std::set<int>> powerSet =
	        EArrayUtilities::getPowerSet<int>(originalSet);
	CHECK(powerSet.size() ==
	      static_cast<std::size_t>(
	              std::pow(2.0, static_cast<double>(originalSet.size()))));
}

TEST_CASE("Test copy, equal, and equalUnsorted", "[EArrayUtilities]")
{
	std::vector<int> a{34,    2345, 112, 123, 8539,
	                   90123, 234,  467, 168, 19233};
	ArrayPointer b(EArrayUtilities::copy<int>(a.data(), a.size()),
	               arrayDeleter);

	CHECK(std::equal(a.data(), a.data() + a.size(), b.get()));
	CHECK(EArrayUtilities::equal<int>(a.data(), b.get(), a.size()));

	std::random_device rd;
	std::mt19937 engine(rd());
	std::shuffle(a.data(), a.data() + a.size(), engine);
	std::shuffle(b.get(), b.get() + a.size(), engine);
	CHECK(EArrayUtilities::equalUnsorted<int>(a.data(), b.get(), a.size()));
}

TEST_CASE("Test array utilities resize", "[EArrayUtilities]")
{
	static const std::vector<int> TEST_DATA{34, 2345, 112, 123, 8539};
	static const std::vector<int> RESIZED_TEST_DATA{
	        34, 2345, 112, 123, 8539, 0, 0, 0, 0, 0};

	int *a = nullptr;
	euler::util::ScopeExit<std::function<void()>> cleanup(
	        [&a]()
	        {
		        if(a != nullptr)
			        delete[] a;
		});
	a = new int[TEST_DATA.size()];
	std::copy(TEST_DATA.begin(), TEST_DATA.end(), a);

	EArrayUtilities::resize<int>(a, TEST_DATA.size(),
	                             RESIZED_TEST_DATA.size(), true);
	CHECK(std::equal(RESIZED_TEST_DATA.begin(), RESIZED_TEST_DATA.end(),
	                 a));

	EArrayUtilities::resize<int>(a, RESIZED_TEST_DATA.size(),
	                             TEST_DATA.size(), false);
	for(std::size_t i = 0; i < TEST_DATA.size(); ++i)
		CHECK(a[i] == 0);
}

TEST_CASE("Test array utilities sortAscending, sortDescending, and reverse",
          "[EArrayUtilities]")
{
	static const std::vector<int> TEST_DATA{34,    2345, 112, 123, 8539,
	                                        90123, 234,  467, 168, 19233};

	ArrayPointer a(new int[TEST_DATA.size()], arrayDeleter);
	std::copy(TEST_DATA.begin(), TEST_DATA.end(), a.get());

	EArrayUtilities::sortAscending<int>(a.get(), TEST_DATA.size());
	for(std::size_t i = 0; i < (TEST_DATA.size() - 1); ++i)
		CHECK(a.get()[i] <= a.get()[i + 1]);

	ArrayPointer b(EArrayUtilities::copy<int>(a.get(), TEST_DATA.size()),
	               arrayDeleter);
	EArrayUtilities::sortDescending<int>(b.get(), TEST_DATA.size());
	for(std::size_t i = 0; i < (TEST_DATA.size() - 1); ++i)
		CHECK(b.get()[i] >= b.get()[i + 1]);

	EArrayUtilities::reverse<int>(b.get(), 0, TEST_DATA.size() - 1);
	CHECK(std::equal(a.get(), a.get() + TEST_DATA.size(), b.get()));
}

TEST_CASE("Test array utilities search and binarySearch", "[EArrayUtilities]")
{
	static const std::vector<int> TEST_DATA{34,    2345, 112, 123, 8539,
	                                        90123, 234,  467, 168, 19233};

	ArrayPointer a(new int[TEST_DATA.size()], arrayDeleter);
	std::copy(TEST_DATA.begin(), TEST_DATA.end(), a.get());
	ArrayPointer b(EArrayUtilities::copy<int>(a.get(), TEST_DATA.size()),
	               arrayDeleter);
	EArrayUtilities::sortAscending<int>(b.get(), TEST_DATA.size());

	for(std::size_t i = 0; i < (TEST_DATA.size() - 1); ++i)
	{
		int aIdx = EArrayUtilities::search<int>(
		        a.get(), TEST_DATA.size(), a.get()[i]);
		int bIdx = EArrayUtilities::binarySearch<int>(
		        b.get(), 0, static_cast<int>(TEST_DATA.size() - 1),
		        b.get()[i]);
		CHECK(aIdx == static_cast<int>(i));
		CHECK(bIdx == static_cast<int>(i));

		aIdx = EArrayUtilities::search<int>(a.get(), TEST_DATA.size(),
		                                    static_cast<int>(i));
		bIdx = EArrayUtilities::binarySearch<int>(
		        b.get(), 0, static_cast<int>(TEST_DATA.size() - 1),
		        static_cast<int>(i));
		CHECK(aIdx == -1);
		CHECK(bIdx == -1);
	}
}

TEST_CASE("Test array utilities isUnique and makeUnique", "[EArrayUtilities]")
{
	static const std::vector<int> TEST_DATA{-168,  2345, 112, 234, 8539,
	                                        90123, 234,  467, 168, 19233};
	constexpr std::size_t UNIQUE_DATA_SIZE = 9;

	int *a = nullptr;
	euler::util::ScopeExit<std::function<void()>> cleanup(
	        [&a]()
	        {
		        if(a != nullptr)
			        delete[] a;
		});
	a = new int[TEST_DATA.size()];
	std::copy(TEST_DATA.begin(), TEST_DATA.end(), a);

	CHECK(!EArrayUtilities::isUnique<int>(a, TEST_DATA.size()));

	CHECK(EArrayUtilities::makeUnique<int>(a, TEST_DATA.size()) ==
	      UNIQUE_DATA_SIZE);
	CHECK(EArrayUtilities::isUnique<int>(a, UNIQUE_DATA_SIZE));
}

TEST_CASE("Test array utilities permutate and reversePermutate",
          "[EArrayUtilities]")
{
	static const std::vector<int> TEST_DATA{3, 1, 2};
	static const std::vector<int> FIRST_PERMUTATION{1, 3, 2};

	ArrayPointer a(new int[TEST_DATA.size()], arrayDeleter);
	std::copy(TEST_DATA.begin(), TEST_DATA.end(), a.get());
	EArrayUtilities::sortAscending<int>(a.get(), TEST_DATA.size());

	ArrayPointer b(EArrayUtilities::copy<int>(a.get(), TEST_DATA.size()),
	               arrayDeleter);

	EArrayUtilities::permutate<int>(b.get(), TEST_DATA.size());
	EArrayUtilities::reversePermutate<int>(b.get(), TEST_DATA.size());
	CHECK(EArrayUtilities::equal<int>(a.get(), b.get(), TEST_DATA.size()));

	EArrayUtilities::permutate<int>(a.get(), TEST_DATA.size());
	CHECK(std::equal(FIRST_PERMUTATION.begin(), FIRST_PERMUTATION.end(),
	                 a.get()));
}

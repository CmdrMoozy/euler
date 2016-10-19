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

#include <string>
#include <utility>
#include <vector>

#include "common/euler/EPoker.h"

TEST_CASE("Test EPoker parsing and comparison", "[EPoker]")
{
	static const std::vector<std::pair<std::string, std::string>>
	        TEST_CASES{{"TH 8H 5C QS TC", "9H 4D JC KS JS"},
	                   {"7C 5H 8D TD KS", "5C AD 5D AC 9C"},
	                   {"QH TD JC 2D 8S", "3H 7H 6S KC JS"},
	                   {"TH 8H 5C QS TC", "9H 4D JC KS JS"},
	                   {"2S 8D 8C 4C TS", "9S 9D 9C AC 3D"}};

	for(auto const &testCase : TEST_CASES)
	{
		EPoker a;
		EPoker b;
		a.parse(testCase.first);
		b.parse(testCase.second);

		CHECK(a < b);
		CHECK(b > a);
	}
}

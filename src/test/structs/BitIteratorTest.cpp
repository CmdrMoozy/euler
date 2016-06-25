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
#include <cstdint>
#include <iterator>
#include <utility>
#include <vector>

#include "common/structs/BitIterator.hpp"

TEST_CASE("Test forward iteration", "[BitIterator]")
{
	static const std::vector<std::pair<uint8_t, std::vector<bool>>>
	        TEST_CASES{
	                {0x00U,
	                 {false, false, false, false, false, false, false,
	                  false}},
	                {0xFFU,
	                 {true, true, true, true, true, true, true, true}},
	                {0xAAU,
	                 {false, true, false, true, false, true, false, true}},
	                {0x55U,
	                 {true, false, true, false, true, false, true, false}}};

	for(auto const &testCase : TEST_CASES)
	{
		euler::structs::BitIterator<uint8_t> it(testCase.first);
		euler::structs::BitIterator<uint8_t> end;
		std::vector<bool> output;
		std::copy(it, end, std::back_inserter(output));
		CHECK(output == testCase.second);
	}
}

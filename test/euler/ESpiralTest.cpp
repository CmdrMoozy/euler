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

#include <cstddef>
#include <cstdint>

#include "libeuler/euler/ESpiral.h"

TEST_CASE("Test ESpiral", "[ESpiral]")
{
	// We have precomputed that the sum of the numbers on the diagonals
	// (the ones our spiral class generates) in a spiral grid of
	// 1001 x 1001 elements is 669171001. Verify that we get this answer
	// to test our class.

	constexpr uint64_t EXPECTED_RESULT = 669171001;
	constexpr std::size_t TEST_SPIRAL_SIZE = 1001;

	ESpiral s;
	uint64_t result = 1;
	for(uint32_t i = 1; s.getSizeFor(i) <= TEST_SPIRAL_SIZE; ++i)
	{
		result += s.diagonalValueAt(i, ESpiral::I);
		result += s.diagonalValueAt(i, ESpiral::II);
		result += s.diagonalValueAt(i, ESpiral::III);
		result += s.diagonalValueAt(i, ESpiral::IV);
	}

	CHECK(result == EXPECTED_RESULT);
}

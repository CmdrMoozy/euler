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

#include "common/structs/BitArray.hpp"

TEST_CASE("Test default construction and bit size", "[BitArray]")
{
	euler::structs::BitArray a(80, euler::structs::BitArrayFillPolicy::SET);
	CHECK(a.size() == 80);
	CHECK(a.byteSize() == a.size() / 8);
	CHECK(a.all());
}

TEST_CASE("Test resize", "[BitArray]")
{
	euler::structs::BitArray a(80, euler::structs::BitArrayFillPolicy::SET);
	a.resize(40, euler::structs::BitArrayFillPolicy::CLEAR);
	CHECK(a.size() == 40);
	CHECK(a.byteSize() == a.size() / 8);
	CHECK(a.none());
}

TEST_CASE("Test set and reset", "[BitArray]")
{
	euler::structs::BitArray a(80,
	                           euler::structs::BitArrayFillPolicy::CLEAR);
	CHECK(a.none());
	a.set();
	CHECK(a.all());
	a.reset();
	CHECK(a.none());
}

TEST_CASE("Test flip", "[BitArray]")
{
	euler::structs::BitArray a(80,
	                           euler::structs::BitArrayFillPolicy::CLEAR);
	a.flip();
	CHECK(a.all());
	a.flip();
	CHECK(a.none());
}

TEST_CASE("Test at, set, and flip", "[BitArray]")
{
	euler::structs::BitArray a(80,
	                           euler::structs::BitArrayFillPolicy::CLEAR);
	for(std::size_t i = 0; i < a.size(); ++i)
	{
		if(i & 1)
			a.set(i, true);
		CHECK(a.at(i) == (i & 1));
	}

	a.flip();
	for(std::size_t i = 0; i < a.size(); ++i)
		CHECK(a.at(i) == !(i & 1));
}

TEST_CASE("Test <<= and >>=", "[BitArray]")
{
	euler::structs::BitArray a(8, euler::structs::BitArrayFillPolicy::SET);
	// Resize the array to make room for the shifts we'll do for testing.
	a.resize(20, euler::structs::BitArrayFillPolicy::PRESERVE_CLEAR);

	CHECK(a.to_ulong() == 0xFFUL);
	a <<= 8;
	CHECK(a.to_ulong() == 0xFF00UL);
	a <<= 4;
	CHECK(a.to_ulong() == 0xFF000UL);
	a >>= 4;
	CHECK(a.to_ulong() == 0xFF00UL);
	a >>= 8;
	CHECK(a.to_ulong() == 0xFFUL);
	a >>= 8;
	CHECK(a.to_ulong() == 0UL);
}

TEST_CASE("Test leftRotate and rightRotate", "[BitArray]")
{
	euler::structs::BitArray a(64,
	                           euler::structs::BitArrayFillPolicy::CLEAR);
	for(std::size_t offFromEnd = 0; offFromEnd < 8; ++offFromEnd)
		a.set(a.size() - 1 - offFromEnd);

	a.leftRotate(8);
	CHECK(a.size() == 64);
	CHECK(a.to_ulong() == 0xFFUL);

	a.reset();
	a.set(0, true);
	a.set(1, false);
	a.set(2, true);
	a.set(3, false);
	a.set(4, false);
	a.set(5, true);
	a.set(6, false);
	a.set(7, true);
	a.rightRotate(4);
	CHECK(a.to_ulong() == 0x500000000000000AUL);
}

TEST_CASE("Test bitwiseAnd", "[BitArray]")
{
	euler::structs::BitArray a =
	        euler::structs::BitArray::fromValue<uint32_t>(0x9AFCCC7B);
	euler::structs::BitArray b =
	        euler::structs::BitArray::fromValue<uint32_t>(0xF880DF73);
	CHECK(a.to_ulong() == 0x9AFCCC7B);
	CHECK(b.to_ulong() == 0xF880DF73);
	a &= b;
	CHECK(a.to_ulong() == 0x9880CC73);
}

TEST_CASE("Test bitwiseOr", "[BitArray]")
{
	euler::structs::BitArray a =
	        euler::structs::BitArray::fromValue<uint32_t>(0x9AFCCC7B);
	euler::structs::BitArray b =
	        euler::structs::BitArray::fromValue<uint32_t>(0xF880DF73);
	CHECK(a.to_ulong() == 0x9AFCCC7B);
	CHECK(b.to_ulong() == 0xF880DF73);
	a |= b;
	CHECK(a.to_ulong() == 0xFAFCDF7B);
}

TEST_CASE("Test bitwiseXor", "[BitArray]")
{
	euler::structs::BitArray a =
	        euler::structs::BitArray::fromValue<uint32_t>(0x9AFCCC7B);
	euler::structs::BitArray b =
	        euler::structs::BitArray::fromValue<uint32_t>(0xF880DF73);
	CHECK(a.to_ulong() == 0x9AFCCC7B);
	CHECK(b.to_ulong() == 0xF880DF73);
	a ^= b;
	CHECK(a.to_ulong() == 0x627C1308);
}

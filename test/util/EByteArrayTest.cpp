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

#include "common/util/EByteArray.h"

TEST_CASE("Test getMinimumByteLength", "[EByteArray]")
{
	CHECK(EByteArray::getMinimumByteLength(0) == 1);
	CHECK(EByteArray::getMinimumByteLength(31) == 4);
	CHECK(EByteArray::getMinimumByteLength(32) == 4);
	CHECK(EByteArray::getMinimumByteLength(33) == 5);
}

TEST_CASE("Test default construction and bit size", "[EByteArray]")
{
	EByteArray a(10, EByteArray::Set);
	CHECK(a.getSize() == 10);
	CHECK(a.bitSize() == (a.getSize() * 8));

	for(std::size_t i = 0; i < a.getSize(); ++i)
		CHECK(a.at(i) == 0xFF);
}

TEST_CASE("Test resize", "[EByteArray]")
{
	EByteArray a(10, EByteArray::Set);
	a.resize(5, EByteArray::Clear);

	CHECK(a.getSize() == 5);
	CHECK(a.bitSize() == (a.getSize() * 8));

	for(std::size_t i = 0; i < a.getSize(); ++i)
		CHECK(a.at(i) == 0);
}

TEST_CASE("Test clearBits and setBits", "[EByteArray]")
{
	EByteArray a(10, EByteArray::Clear);
	for(std::size_t i = 0; i < a.getSize(); ++i)
		CHECK(a.at(i) == 0);

	a.setBits();
	for(std::size_t i = 0; i < a.getSize(); ++i)
		CHECK(a.at(i) == 0xFF);

	a.clearBits();
	for(std::size_t i = 0; i < a.getSize(); ++i)
		CHECK(a.at(i) == 0);
}

TEST_CASE("Test flipBitAt", "[EByteArray]")
{
	EByteArray a(10, EByteArray::Clear);
	for(std::size_t i = 0; i < a.bitSize(); ++i)
		a.flipBitAt(i);
	for(std::size_t i = 0; i < a.getSize(); ++i)
		CHECK(a.at(i) == 0xFF);

	for(std::size_t i = 0; i < a.bitSize(); ++i)
		a.flipBitAt(i);
	for(std::size_t i = 0; i < a.getSize(); ++i)
		CHECK(a.at(i) == 0);
}

TEST_CASE("Test bitAt, setBitAt, and bitwiseComplement", "[EByteArray]")
{
	EByteArray a(10, EByteArray::Clear);
	for(std::size_t i = 0; i < a.bitSize(); ++i)
	{
		if(i & 1)
			a.setBitAt(i, true);

		CHECK(a.bitAt(i) == (i & 1));
	}
	for(std::size_t i = 0; i < a.getSize(); ++i)
		CHECK(a.at(i) == 0xAA);

	a.bitwiseComplement();
	for(std::size_t i = 0; i < a.bitSize(); ++i)
		CHECK(a.bitAt(i) != (i & 1));
	for(std::size_t i = 0; i < a.getSize(); ++i)
		CHECK(a.at(i) == 0x55);
}

TEST_CASE("Test leftShift and rightShift", "[EByteArray]")
{
	EByteArray a(10, EByteArray::Clear);
	a.at(0) = 0xFF;

	a.leftShift(8);
	CHECK(a.at(1) == 0xFF);
	CHECK(a.at(0) == 0x00);

	a.leftShift(4);
	CHECK(a.at(2) == 0x0F);
	CHECK(a.at(1) == 0xF0);

	a.rightShift(4);
	CHECK(a.at(1) == 0xFF);
	CHECK(a.at(2) == 0x00);

	a.rightShift(8);
	CHECK(a.at(0) == 0xFF);
	CHECK(a.at(1) == 0x00);
}

TEST_CASE("Test leftRotate and rightRotate", "[EByteArray]")
{
	EByteArray a(10, EByteArray::Clear);
	a.at(a.getSize() - 1) = 0xFF;

	a.leftRotate(8);
	CHECK(a.at(a.getSize() - 1) == 0x00);
	CHECK(a.at(0) == 0xFF);

	a.clearBits();
	a.at(0) = 0xA5;

	a.rightRotate(4);
	CHECK(a.at(0) == 0x0A);
	CHECK(a.at(a.getSize() - 1) == 0x50);
}

TEST_CASE("Test bitwiseAnd", "[EByteArray]")
{
	EByteArray a(4, EByteArray::Clear);
	a.at(3) = 0x9A;
	a.at(2) = 0xFC;
	a.at(1) = 0xCC;
	a.at(0) = 0x7B;
	EByteArray b(a);

	EByteArray andBytes(4, EByteArray::Clear);
	andBytes.at(3) = 0xF8;
	andBytes.at(2) = 0x80;
	andBytes.at(1) = 0xDF;
	andBytes.at(0) = 0x73;
	uint32_t andNumber = 0xF880DF73;

	a.bitwiseAnd(andBytes);
	b.bitwiseAnd(andNumber);

	CHECK(a.at(0) == 0x73);
	CHECK(a.at(1) == 0xCC);
	CHECK(a.at(2) == 0x80);
	CHECK(a.at(3) == 0x98);

	CHECK(a.getSize() == b.getSize());
	for(std::size_t i = 0; i < a.getSize(); ++i)
		CHECK(a.at(i) == b.at(i));
}

TEST_CASE("Test bitwiseOr", "[EByteArray]")
{
	EByteArray a(4, EByteArray::Clear);
	a.at(3) = 0x9A;
	a.at(2) = 0xFC;
	a.at(1) = 0xCC;
	a.at(0) = 0x7B;
	EByteArray b(a);

	EByteArray orBytes(4, EByteArray::Clear);
	orBytes.at(3) = 0xF8;
	orBytes.at(2) = 0x80;
	orBytes.at(1) = 0xDF;
	orBytes.at(0) = 0x73;
	uint32_t orNumber = 0xF880DF73;

	a.bitwiseOr(orBytes);
	b.bitwiseOr(orNumber);

	CHECK(a.at(0) == 0x7B);
	CHECK(a.at(1) == 0xDF);
	CHECK(a.at(2) == 0xFC);
	CHECK(a.at(3) == 0xFA);

	CHECK(a.getSize() == b.getSize());
	for(std::size_t i = 0; i < a.getSize(); ++i)
		CHECK(a.at(i) == b.at(i));
}

TEST_CASE("Test bitwiseXor", "[EByteArray]")
{
	EByteArray a(4, EByteArray::Clear);
	a.at(3) = 0x9A;
	a.at(2) = 0xFC;
	a.at(1) = 0xCC;
	a.at(0) = 0x7B;
	EByteArray b(a);

	EByteArray xorBytes(4, EByteArray::Clear);
	xorBytes.at(3) = 0xF8;
	xorBytes.at(2) = 0x80;
	xorBytes.at(1) = 0xDF;
	xorBytes.at(0) = 0x73;
	uint32_t xorNumber = 0xF880DF73;

	a.bitwiseXor(xorBytes);
	b.bitwiseXor(xorNumber);

	CHECK(a.at(0) == 0x08);
	CHECK(a.at(1) == 0x13);
	CHECK(a.at(2) == 0x7C);
	CHECK(a.at(3) == 0x62);

	CHECK(a.getSize() == b.getSize());
	for(std::size_t i = 0; i < a.getSize(); ++i)
		CHECK(a.at(i) == b.at(i));
}

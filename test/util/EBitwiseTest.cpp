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

#include "common/util/EBitwise.h"

TEST_CASE("Test isPowerOfTwo", "[EBitwise]")
{
	CHECK(EBitwise::isPowTwo(1));
	CHECK(EBitwise::isPowTwo(2));
	CHECK(EBitwise::isPowTwo(4));
	CHECK(EBitwise::isPowTwo(32));
	CHECK(EBitwise::isPowTwo(8192));
	CHECK(EBitwise::isPowTwo(32768));
	CHECK(EBitwise::isPowTwo(131072));

	CHECK(!EBitwise::isPowTwo(31));
	CHECK(!EBitwise::isPowTwo(0));
	CHECK(!EBitwise::isPowTwo(27834));
	CHECK(!EBitwise::isPowTwo(2892));
	CHECK(!EBitwise::isPowTwo(3226880));
	CHECK(!EBitwise::isPowTwo(1234));
	CHECK(!EBitwise::isPowTwo(1023));
}

TEST_CASE("Test reverseBits and reverseAllBits", "[EBitwise]")
{
	CHECK(EBitwise::reverseAllBits(0xFFFF0000) == 0x0000FFFF);
	CHECK(EBitwise::reverseAllBits(0x0000FFFF) == 0xFFFF0000);
	CHECK(EBitwise::reverseAllBits(0xFA37A0B1) == 0x8D05EC5F);

	CHECK(EBitwise::reverseBits(0x0000FFFF) == 0x0000FFFF);
	CHECK(EBitwise::reverseBits(0x000000AA) == 0x00000055);
	CHECK(EBitwise::reverseAllBits(0xFA37A0B1) ==
	      EBitwise::reverseBits(0xFA37A0B1));
}

TEST_CASE("Test isPalindromic", "[EBitwise]")
{
	CHECK(EBitwise::isPalindromic(0x909909));
	CHECK(!EBitwise::isPalindromic(0xA0AA0A));
}

TEST_CASE("Test left and right rotations", "[EBitwise]")
{
	uint32_t i = 0xFA7D9017;
	i = EBitwise::rotl32(i, 7);
	CHECK(i == 0x3EC80BFD);
	i = EBitwise::rotr32(i, 7);
	CHECK(i == 0xFA7D9017);
}

TEST_CASE("Test modPowTwo", "[EBitwise]")
{
	for(uint64_t n = 10000; n < 100000; n += (n % 983))
	{
		for(uint64_t s = 1; s < 32; ++s)
		{
			uint64_t d = (1 << s);
			uint64_t m = EBitwise::modPowTwo(
			        n, static_cast<unsigned int>(s));
			CHECK(m == (n % d));
		}
	}
}

TEST_CASE("Test modPowTwoLessOne", "[EBitwise]")
{
	for(uint64_t n = 10000; n < 100000; n += (n % 937))
	{
		for(uint64_t s = 1; s < 32; ++s)
		{
			uint64_t d = (static_cast<uint64_t>(1) << s) - 1;
			uint64_t m = EBitwise::modPowTwoLessOne(
			        n, static_cast<unsigned int>(s));

			CHECK(m == (n % d));
		}
	}
}

TEST_CASE("Test opop", "[EBitwise]")
{
	CHECK(EBitwise::opop(0x6a6840affaf15391) == 32);
	CHECK(EBitwise::opop(0x7530df0870018e15) == 26);
	CHECK(EBitwise::opop(0x337efa4696ff2544) == 36);
	CHECK(EBitwise::opop(0x65d16922488e5f15) == 29);
	CHECK(EBitwise::opop(0x76ab67fded75d5cc) == 42);
	CHECK(EBitwise::opop(0x89d6b9d1737a0d09) == 32);
	CHECK(EBitwise::opop(0x057bb30f7f18ccfd) == 37);
	CHECK(EBitwise::opop(0xd68db35a8ed86582) == 32);
	CHECK(EBitwise::opop(0x37a1830037ba525d) == 29);
	CHECK(EBitwise::opop(0x831e2a44a317a1ca) == 27);
	CHECK(EBitwise::opop(0x46b3dd9234c70018) == 27);
	CHECK(EBitwise::opop(0xabf75b932d01c853) == 33);
	CHECK(EBitwise::opop(0x1724cc1f953e671b) == 33);
	CHECK(EBitwise::opop(0x63f5f72f31e3a24e) == 37);
	CHECK(EBitwise::opop(0x6a28ecb167e3043f) == 32);
	CHECK(EBitwise::opop(0x773459da787256be) == 36);
	CHECK(EBitwise::opop(0x4bce68e474dc57c0) == 32);
	CHECK(EBitwise::opop(0xae379f0b7018de7a) == 35);
	CHECK(EBitwise::opop(0x38397e32ef15ea50) == 33);
	CHECK(EBitwise::opop(0xb1c84171e7a27ddd) == 34);
	CHECK(EBitwise::opop(0x58ba3a0e7ad2a1ff) == 35);
	CHECK(EBitwise::opop(0xb354839b34209fdb) == 32);
	CHECK(EBitwise::opop(0x70f300372460d770) == 27);
	CHECK(EBitwise::opop(0xdb429b79d2202490) == 27);
	CHECK(EBitwise::opop(0xef557b1deeec95c3) == 40);
}

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
#include <cmath>

#include "common/math/Math.h"

TEST_CASE("Test ipow function", "[Math]")
{
	for(unsigned int b = 0; b <= 10; ++b)
	{
		for(uint8_t e = 0; e <= 10; ++e)
		{
			uint64_t exp = static_cast<uint64_t>(std::pow(b, e));
			uint64_t act = euler::math::ipow(b, e);
			CHECK(exp == act);
		}
	}
}

TEST_CASE("Test ipowmod function", "[Math]")
{
	constexpr unsigned int MODULUS = 5;
	for(unsigned int b = 1; b <= 5; ++b)
	{
		for(unsigned int e = 1; e <= 5; ++e)
		{
			uint64_t exp =
			        static_cast<uint64_t>(std::pow(b, e)) % MODULUS;
			uint64_t act = euler::math::ipowmod(b, e, MODULUS);
			CHECK(exp == act);
		}
	}
}

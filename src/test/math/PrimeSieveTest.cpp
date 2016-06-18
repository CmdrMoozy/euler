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

#include "common/math/EMath.h"
#include "common/math/PrimeSieve.hpp"

TEST_CASE("Verify new prime number sieve functionality", "[PrimeSieve]")
{
	constexpr uint64_t SIEVE_LIMIT = 10000;
	constexpr int PRIME_TEST_PRECISION = 50;

	euler::math::PrimeSieve sieve(SIEVE_LIMIT);
	for(uint64_t i = 0; i <= SIEVE_LIMIT; ++i)
	{
		CHECK(sieve.contains(i) ==
		      EMath::isPrime_UI(i, PRIME_TEST_PRECISION));
	}
}

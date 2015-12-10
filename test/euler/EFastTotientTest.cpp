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

#include "libeuler/euler/EFastTotient.h"
#include "libeuler/math/EMath.h"
#include "libeuler/math/EPrimeSieve.h"

TEST_CASE("Test fast totient computation", "[EFastTotient]")
{
	constexpr uint32_t TEST_LIMIT = 1000;

	EPrimeSieve s;
	EFastTotient t(&s, TEST_LIMIT);

	for(uint32_t i = 0; i <= TEST_LIMIT; ++i)
		CHECK(EMath::totient(i) == t.totient(i));
}

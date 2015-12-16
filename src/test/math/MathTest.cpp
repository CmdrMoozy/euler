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

#include <cmath>
#include <cstdint>
#include <vector>

#include "common/math/floatCompare.hpp"
#include "common/math/Math.hpp"

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

TEST_CASE("Test average function", "[Math]")
{
	using TestCase = struct
	{
		std::vector<double> values;
		double expected;
	};

	static const std::vector<TestCase> TEST_CASES{
	        {{0.0, 0.0, 0.0}, 0.0},
	        {{1.0, 1.0, 1.0}, 1.0},
	        {{-97.047790049926, 2.2699590208147, 87.702374647301,
	          -82.952833961549, -30.853109530753, 77.352712625263,
	          -27.762678970164, -78.276824490749, 11.014111208521,
	          85.738191989333, 76.382296597373, 57.000249288384,
	          -38.178431785339, 79.10107093935, 2.2370599400008,
	          4.7434514388933, 47.573826787054, 39.190955050969,
	          39.666378628033, -74.557951729133},
	         9.0171508821838400}};

	for(auto const &testCase : TEST_CASES)
	{
		double avg = euler::math::average(testCase.values.begin(),
		                                  testCase.values.end());
		CHECK(euler::math::floatCompare(avg, testCase.expected) == 0);
	}
}

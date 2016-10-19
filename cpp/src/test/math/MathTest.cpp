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

#include <bdrck/util/floatCompare.hpp>

#include "common/math/Math.hpp"

TEST_CASE("Test signed division", "[Math]")
{
	using TestCase = struct
	{
		int32_t dividend;
		int32_t divisor;
		int32_t quotient;
		int32_t remainder;
	};

	static const std::vector<TestCase> TEST_CASES{
	        {0, 100, 0, 0},     {0, -100, 0, 0},   {100, 1, 100, 0},
	        {-100, 1, -100, 0}, {100, 3, 33, 1},   {100, -3, -33, 1},
	        {-100, 3, -33, -1}, {-100, -3, 33, -1}};

	for(auto const &testCase : TEST_CASES)
	{
		auto resultA = euler::math::divide<int32_t>(testCase.dividend,
		                                            testCase.divisor);
		CHECK(resultA.first == testCase.quotient);
		CHECK(resultA.second == testCase.remainder);

		auto resultB = euler::math::divide<int64_t>(testCase.dividend,
		                                            testCase.divisor);
		CHECK(resultB.first == testCase.quotient);
		CHECK(resultB.second == testCase.remainder);
	}
}

TEST_CASE("Test unsigned division", "[Math]")
{
	using TestCase = struct
	{
		uint32_t dividend;
		uint32_t divisor;
		uint32_t quotient;
		uint32_t remainder;
	};

	static const std::vector<TestCase> TEST_CASES{
	        {0, 100, 0, 0}, {100, 1, 100, 0}, {100, 3, 33, 1}};

	for(auto const &testCase : TEST_CASES)
	{
		auto resultA = euler::math::divide<uint32_t>(testCase.dividend,
		                                             testCase.divisor);
		CHECK(resultA.first == testCase.quotient);
		CHECK(resultA.second == testCase.remainder);

		auto resultB = euler::math::divide<uint64_t>(testCase.dividend,
		                                             testCase.divisor);
		CHECK(resultB.first == testCase.quotient);
		CHECK(resultB.second == testCase.remainder);
	}
}

TEST_CASE("Test greatestCommonDivisor", "[Math]")
{
	using TestCase = struct
	{
		uint64_t u;
		uint64_t v;
		uint64_t result;
	};

	static const std::vector<TestCase> TEST_CASES{
	        {900, 736, 4}, {951, 474, 3},  {377, 540, 1},   {210, 818, 2},
	        {832, 17, 1},  {986, 799, 17}, {855, 469, 1},   {990, 604, 2},
	        {138, 827, 1}, {424, 203, 1},  {522, 813, 3},   {251, 26, 1},
	        {329, 191, 1}, {965, 435, 5},  {759, 400, 1},   {53, 549, 1},
	        {218, 678, 2}, {453, 767, 1},  {396, 594, 198}, {821, 615, 1},
	        {104, 410, 2}, {725, 153, 1},  {744, 764, 4},   {765, 436, 1},
	        {666, 86, 2}};

	for(auto const &testCase : TEST_CASES)
	{
		CHECK(euler::math::gcd(testCase.u, testCase.v) ==
		      testCase.result);
	}
}

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
	        {{-97.047790049926, 2.2699590208147,  87.702374647301,
	          -82.952833961549, -30.853109530753, 77.352712625263,
	          -27.762678970164, -78.276824490749, 11.014111208521,
	          85.738191989333,  76.382296597373,  57.000249288384,
	          -38.178431785339, 79.10107093935,   2.2370599400008,
	          4.7434514388933,  47.573826787054,  39.190955050969,
	          39.666378628033,  -74.557951729133},
	         9.0171508821838400}};

	for(auto const &testCase : TEST_CASES)
	{
		double avg = euler::math::average(testCase.values.begin(),
		                                  testCase.values.end());
		CHECK(bdrck::util::floatCompare(avg, testCase.expected) == 0);
	}
}

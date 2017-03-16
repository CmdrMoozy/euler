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
#include <set>
#include <utility>
#include <vector>

#include <gmp.h>
#include <gmpxx.h>

#include "common/math/EMath.cpp"
#include "common/math/Math.hpp"

TEST_CASE("Test isPrime_UI and isPrime", "[EMath]")
{
	static const std::set<uint64_t> KNOWN_PRIMES{
	        2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,  41,
	        43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97,  101,
	        103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
	        173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
	        241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313,
	        317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
	        401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467,
	        479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569,
	        571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643,
	        647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
	        739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823,
	        827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911,
	        919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997,
	};

	constexpr int PRIME_TEST_PRECISION = 10;

	for(uint64_t i = 1; i <= 1000; ++i)
	{
		CHECK(EMath::isPrime_UI(i, PRIME_TEST_PRECISION) ==
		      (KNOWN_PRIMES.count(i) > 0));
	}
}

TEST_CASE("Test areCoprime", "[EMath]")
{
	for(uint32_t i = 1; i < 100; ++i)
	{
		for(uint32_t j = 1; j < 100; ++j)
		{
			CHECK(EMath::areCoprime(i, j) ==
			      (euler::math::gcd(i, j) == 1));
		}
	}
}

TEST_CASE("Test totient", "[EMath]")
{
	static const std::vector<std::pair<uint32_t, uint32_t>> TEST_CASES{
	        {1, 1},   {2, 1},   {3, 2},   {4, 2},   {5, 4},   {6, 2},
	        {7, 6},   {8, 4},   {9, 6},   {10, 4},  {11, 10}, {12, 4},
	        {13, 12}, {14, 6},  {15, 8},  {16, 8},  {17, 16}, {18, 6},
	        {19, 18}, {20, 8},  {21, 12}, {22, 10}, {23, 22}, {24, 8},
	        {25, 20}, {26, 12}, {27, 18}, {28, 12}, {29, 28}, {30, 8},
	        {31, 30}, {32, 16}, {33, 20}, {34, 16}, {35, 24}, {36, 12},
	        {37, 36}, {38, 18}, {39, 24}, {40, 16}, {41, 40}, {42, 12},
	        {43, 42}, {44, 20}, {45, 24}, {46, 22}, {47, 46}, {48, 16},
	        {49, 42}, {50, 20}, {51, 32}, {52, 24}, {53, 52}, {54, 18},
	        {55, 40}, {56, 24}, {57, 36}, {58, 28}, {59, 58}, {60, 16},
	        {61, 60}, {62, 30}, {63, 36}, {64, 32}, {65, 48}, {66, 20},
	        {67, 66}, {68, 32}, {69, 44}, {70, 24}, {71, 70}, {72, 24},
	        {73, 72}, {74, 36}, {75, 40}, {76, 36}, {77, 60}, {78, 24},
	        {79, 78}, {80, 32}, {81, 54}, {82, 40}, {83, 82}, {84, 24},
	        {85, 64}, {86, 42}, {87, 56}, {88, 40}, {89, 88}, {90, 24},
	        {91, 72}, {92, 44}, {93, 60}, {94, 46}, {95, 72}, {96, 32},
	        {97, 96}, {98, 42}, {99, 60}};

	for(auto const &testCase : TEST_CASES)
	{
		CHECK(EMath::totient(testCase.first) == testCase.second);
	}
}

TEST_CASE("Test leastCommonMultiple", "[EMath]")
{
	using TestCase = struct
	{
		uint64_t a;
		uint64_t b;
		uint64_t result;
	};

	static const std::vector<TestCase> TEST_CASES{
	        {900, 736, 165600}, {951, 474, 150258}, {377, 540, 203580},
	        {210, 818, 85890},  {832, 17, 14144},   {986, 799, 46342},
	        {855, 469, 400995}, {990, 604, 298980}, {138, 827, 114126},
	        {424, 203, 86072},  {522, 813, 141462}, {251, 26, 6526},
	        {329, 191, 62839},  {965, 435, 83955},  {759, 400, 303600},
	        {53, 549, 29097},   {218, 678, 73902},  {453, 767, 347451},
	        {396, 594, 1188},   {821, 615, 504915}, {104, 410, 21320},
	        {725, 153, 110925}, {744, 764, 142104}, {765, 436, 333540},
	        {666, 86, 28638}};

	for(auto const &testCase : TEST_CASES)
	{
		CHECK(EMath::leastCommonMultiple(testCase.a, testCase.b) ==
		      testCase.result);
	}
}

TEST_CASE("Test isSquare", "[EMath]")
{
	constexpr double TEST_CASE_EPSILON = 0.000001;

	for(uint32_t i = 1; i <= 10000; ++i)
	{
		double d = std::sqrt(static_cast<double>(i));
		CHECK(EMath::isSquare(i) ==
		      (std::abs(d - floor(d)) < TEST_CASE_EPSILON));
	}
}

TEST_CASE("Test permutations", "[EMath]")
{
	using TestCase = struct
	{
		int n;
		int r;
		uint64_t result;
	};

	static const std::vector<TestCase> TEST_CASES{
	        {5, 4, 120}, {4, 1, 4}, {5, 2, 20}, {4, 2, 12}, {5, 3, 60},
	        {3, 2, 6},   {5, 1, 5}, {4, 4, 24}, {1, 1, 1},  {5, 5, 120}};

	for(auto const &testCase : TEST_CASES)
	{
		CHECK(EMath::permutations(testCase.n, testCase.r) ==
		      testCase.result);
	}
}

TEST_CASE("Test getPythagoreanTriple{A,B,C}", "[EMath]")
{
	for(uint64_t i = 1; i <= 5; ++i)
	{
		for(uint64_t j = 1; j <= 5; ++j)
		{
			for(uint64_t k = 1; k <= 5; ++k)
			{
				uint64_t a =
				        EMath::getPythagoreanTripleA(i, j, k);
				uint64_t b =
				        EMath::getPythagoreanTripleB(i, j, k);
				uint64_t c =
				        EMath::getPythagoreanTripleC(i, j, k);

				CHECK(euler::math::ipow(a, 2) +
				              euler::math::ipow(b, 2) ==
				      euler::math::ipow(c, 2));
			}
		}
	}
}

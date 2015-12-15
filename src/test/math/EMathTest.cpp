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

#include "common/math/EFactorization.h"
#include "common/math/EMath.cpp"
#include "common/math/Math.hpp"

TEST_CASE("Test getTriangleNumberN", "[EMath]")
{
	static const std::vector<std::pair<uint64_t, uint64_t>> TEST_CASES{
	        {0, 0},     {1, 1},     {2, 3},     {3, 6},     {4, 10},
	        {5, 15},    {6, 21},    {7, 28},    {8, 36},    {9, 45},
	        {10, 55},   {11, 66},   {12, 78},   {13, 91},   {14, 105},
	        {15, 120},  {16, 136},  {17, 153},  {18, 171},  {19, 190},
	        {20, 210},  {21, 231},  {22, 253},  {23, 276},  {24, 300},
	        {25, 325},  {26, 351},  {27, 378},  {28, 406},  {29, 435},
	        {30, 465},  {31, 496},  {32, 528},  {33, 561},  {34, 595},
	        {35, 630},  {36, 666},  {37, 703},  {38, 741},  {39, 780},
	        {40, 820},  {41, 861},  {42, 903},  {43, 946},  {44, 990},
	        {45, 1035}, {46, 1081}, {47, 1128}, {48, 1176}, {49, 1225},
	        {50, 1275}, {51, 1326}, {52, 1378}, {53, 1431}};

	for(auto const &testCase : TEST_CASES)
	{
		CHECK(EMath::getTriangleNumberN(testCase.first) ==
		      testCase.second);
	}
}

TEST_CASE("Test getPentagonalNumberN", "[EMath]")
{
	static const std::vector<std::pair<uint64_t, uint64_t>> TEST_CASES{
	        {0, 0},     {1, 1},     {2, 5},     {3, 12},    {4, 22},
	        {5, 35},    {6, 51},    {7, 70},    {8, 92},    {9, 117},
	        {10, 145},  {11, 176},  {12, 210},  {13, 247},  {14, 287},
	        {15, 330},  {16, 376},  {17, 425},  {18, 477},  {19, 532},
	        {20, 590},  {21, 651},  {22, 715},  {23, 782},  {24, 852},
	        {25, 925},  {26, 1001}, {27, 1080}, {28, 1162}, {29, 1247},
	        {30, 1335}, {31, 1426}, {32, 1520}, {33, 1617}, {34, 1717},
	        {35, 1820}, {36, 1926}, {37, 2035}, {38, 2147}, {39, 2262},
	        {40, 2380}, {41, 2501}, {42, 2625}, {43, 2752}, {44, 2882},
	        {45, 3015}, {46, 3151}};

	for(auto const &testCase : TEST_CASES)
	{
		CHECK(EMath::getPentagonalNumberN(testCase.first) ==
		      testCase.second);
	}
}

TEST_CASE("Test getHexagonalNumberN", "[EMath]")
{
	static const std::vector<std::pair<uint64_t, uint64_t>> TEST_CASES{
	        {0, 0},     {1, 1},     {2, 6},     {3, 15},    {4, 28},
	        {5, 45},    {6, 66},    {7, 91},    {8, 120},   {9, 153},
	        {10, 190},  {11, 231},  {12, 276},  {13, 325},  {14, 378},
	        {15, 435},  {16, 496},  {17, 561},  {18, 630},  {19, 703},
	        {20, 780},  {21, 861},  {22, 946},  {23, 1035}, {24, 1128},
	        {25, 1225}, {26, 1326}, {27, 1431}, {28, 1540}, {29, 1653},
	        {30, 1770}, {31, 1891}, {32, 2016}, {33, 2145}, {34, 2278},
	        {35, 2415}, {36, 2556}, {37, 2701}, {38, 2850}, {39, 3003},
	        {40, 3160}, {41, 3321}, {42, 3486}, {43, 3655}, {44, 3828},
	        {45, 4005}, {46, 4186}, {47, 4371}, {48, 4560}};

	for(auto const &testCase : TEST_CASES)
	{
		CHECK(EMath::getHexagonalNumberN(testCase.first) ==
		      testCase.second);
	}
}

TEST_CASE("Test getFibonacciNumberN_UI", "[EMath]")
{
	static const std::vector<std::pair<uint32_t, uint64_t>> TEST_CASES{
	        {0, 0},         {1, 1},         {2, 1},        {3, 2},
	        {4, 3},         {5, 5},         {6, 8},        {7, 13},
	        {8, 21},        {9, 34},        {10, 55},      {11, 89},
	        {12, 144},      {13, 233},      {14, 377},     {15, 610},
	        {16, 987},      {17, 1597},     {18, 2584},    {19, 4181},
	        {20, 6765},     {21, 10946},    {22, 17711},   {23, 28657},
	        {24, 46368},    {25, 75025},    {26, 121393},  {27, 196418},
	        {28, 317811},   {29, 514229},   {30, 832040},  {31, 1346269},
	        {32, 2178309},  {33, 3524578},  {34, 5702887}, {35, 9227465},
	        {36, 14930352}, {37, 24157817}, {38, 39088169}};

	for(auto const &testCase : TEST_CASES)
	{
		CHECK(EMath::getFibonacciNumberN_UI(testCase.first) ==
		      testCase.second);
	}
}

TEST_CASE("Test fibonacciSearch", "[EMath]")
{
	/*
	 * From one of our ProjectEuler problems, we know that the first
	 * Fibonacci number to be larger than 10^999 is fibonacci(4782).
	 */
	mpz_class fibsTarget = 10;
	mpz_pow_ui(fibsTarget.get_mpz_t(), fibsTarget.get_mpz_t(), 999);
	CHECK(EMath::fibonacciSearch(1000, fibsTarget) == 4782);
}

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
			      (EMath::greatestCommonDivisor(i, j) == 1));
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

TEST_CASE("Test repetendLength", "[EMath]")
{
	static const std::vector<std::pair<uint32_t, uint32_t>> TEST_CASES{
	        {2, 0}, {3, 1}, {4, 0}, {5, 0}, {6, 1},
	        {7, 6}, {8, 0}, {9, 1}, {10, 0}};

	EFactorization fac;

	for(auto const &testCase : TEST_CASES)
	{
		CHECK(EMath::repetendLength(testCase.first, fac) ==
		      testCase.second);
	}
}

TEST_CASE("Test greatestCommonDivisor", "[EMath]")
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
		CHECK(EMath::greatestCommonDivisor(testCase.u, testCase.v) ==
		      testCase.result);
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

TEST_CASE("Test aliquotNumberDivisors", "[EMath]")
{
	EFactorization fac;

	for(uint32_t i = 0; i < 1000; ++i)
	{
		fac.setNumber(i);
		CHECK(fac.getAllFactorsCount() ==
		      EMath::aliquotNumberDivisors(i));
	}
}

TEST_CASE("Test aliquotSumDivisors and aliquotSumProperDivisors", "[EMath]")
{
	static const std::vector<std::pair<uint64_t, uint64_t>> TEST_CASES{
	        {1, 0},   {2, 1},   {3, 1},   {4, 3},   {5, 1},   {6, 6},
	        {7, 1},   {8, 7},   {9, 4},   {10, 8},  {11, 1},  {12, 16},
	        {13, 1},  {14, 10}, {15, 9},  {16, 15}, {17, 1},  {18, 21},
	        {19, 1},  {20, 22}, {21, 11}, {22, 14}, {23, 1},  {24, 36},
	        {25, 6},  {26, 16}, {27, 13}, {28, 28}, {29, 1},  {30, 42},
	        {31, 1},  {32, 31}, {33, 15}, {34, 20}, {35, 13}, {36, 55},
	        {37, 1},  {38, 22}, {39, 17}, {40, 50}, {41, 1},  {42, 54},
	        {43, 1},  {44, 40}, {45, 33}, {46, 26}, {47, 1},  {48, 76},
	        {49, 8},  {50, 43}, {51, 21}, {52, 46}, {53, 1},  {54, 66},
	        {55, 17}, {56, 64}, {57, 23}, {58, 32}, {59, 1},  {60, 108},
	        {61, 1},  {62, 34}, {63, 41}, {64, 63}, {65, 19}, {66, 78},
	        {67, 1},  {68, 58}, {69, 27}, {70, 74}, {71, 1},  {72, 123},
	        {73, 1},  {74, 40}, {75, 49}, {76, 64}, {77, 19}, {78, 90},
	        {79, 1},  {80, 106}};

	for(auto const &testCase : TEST_CASES)
	{
		uint64_t result =
		        EMath::aliquotSumProperDivisors(testCase.first);
		CHECK(result == testCase.second);
		CHECK(result + testCase.first ==
		      EMath::aliquotSumDivisors(testCase.first));
	}
}

TEST_CASE("Test logBaseTen", "[EMath]")
{
	for(uint32_t i = 1; i < 10000; ++i)
	{
		CHECK(EMath::logBaseTen(i) ==
		      static_cast<uint32_t>(
		              std::floor(std::log10(static_cast<double>(i)))));
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

TEST_CASE("Test combinations", "[EMath]")
{
	using TestCase = struct
	{
		int n;
		int r;
		uint64_t result;
	};

	static const std::vector<TestCase> TEST_CASES{
	        {10, 8, 45},  {9, 3, 84},  {4, 1, 4},  {1, 1, 1},  {6, 1, 6},
	        {10, 6, 210}, {9, 5, 126}, {7, 2, 21}, {9, 7, 36}, {4, 3, 4}};

	for(auto const &testCase : TEST_CASES)
	{
		CHECK(EMath::combinations(testCase.n, testCase.r) ==
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

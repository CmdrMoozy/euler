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
#include <cstdint>
#include <random>

#include <gmp.h>
#include <gmpxx.h>

#include "common/types/EDigitInteger.h"

TEST_CASE("Test construction and assignment", "[EDigitInteger]")
{
	EDigitInteger a;
	CHECK(a.toInteger() == 0);
	CHECK(a.isPositive());

	a = "+123456789";
	CHECK(a.isPositive());
	CHECK(a.toInteger() == 123456789);
	CHECK(a.toBigInteger() == 123456789);
	CHECK(a.toString() == "123456789");

	a = "-12345";
	CHECK(!a.isPositive());
	CHECK(a.toInteger() == 12345);
	CHECK(a.toBigInteger() == 12345);
	CHECK(a.toString() == "-12345");

	a = "12345678910";
	CHECK(a.isPositive());
	CHECK(a.toInteger() == 12345678910);
	CHECK(a.toBigInteger() == 12345678910);
	CHECK(a.toString() == "12345678910");
}

TEST_CASE("Test copy construction and assignment", "[EDigitInteger]")
{
	EDigitInteger a;
	a = "654321";
	EDigitInteger b(a);

	CHECK(a == b);
	CHECK(a.toInteger() == b.toInteger());

	a = "123456";
	b = a;
	CHECK(a == b);
	CHECK(a.toInteger() == b.toInteger());
}

TEST_CASE("Test big integer assignment", "[EDigitInteger]")
{
	mpz_class bigint = 1278483892;
	EDigitInteger a;
	a = bigint;
	CHECK(a.toBigInteger() == bigint);
}

TEST_CASE("Test getting a range of digits as an integer", "[EDigitInteger]")
{
	EDigitInteger a(12345678910);
	CHECK(a.rangeToInteger(0, 5) == 678910);
	CHECK(a.rangeToInteger(6, 9) == 2345);
	CHECK(a.rangeToInteger(0, 0) == 0);
	CHECK(a.rangeToInteger(10, 10) == 1);
	CHECK(a.rangeToInteger(0, 10) == 12345678910);

	EDigitInteger b(3797);
	CHECK(b.rangeToInteger(0, 3) == 3797);
	CHECK(b.rangeToInteger(0, 2) == 797);

	EDigitInteger c;
	c = "-12345";
	CHECK(c.rangeToInteger(0, 3) == 2345);
}

TEST_CASE("Test unary negation", "[EDigitInteger]")
{
	EDigitInteger a(12345);
	EDigitInteger b = -a;
	CHECK(b != a);
	a.setPositive(false);
	CHECK(b == a);

	EDigitInteger c;
	c = "-12345";
	EDigitInteger d = -c;
	CHECK(d != c);
	c.setPositive(true);
	CHECK(d == c);
}

TEST_CASE("Test increment and decrement operators", "[EDigitInteger]")
{
	uint64_t i;
	EDigitInteger a;

	for(i = 0, a = 0; i < 1000; ++i, ++a)
		CHECK(a.toInteger() == i);

	for(i = 0, a = 0; i < 1000; ++i, a++)
		CHECK(a.toInteger() == i);

	for(i = 1000, a = 1000; i > 0; --i, --a)
		CHECK(a.toInteger() == i);

	for(i = 1000, a = 1000; i > 0; --i, a--)
		CHECK(a.toInteger() == i);
}

TEST_CASE("Test addition operator", "[EDigitInteger]")
{
	EDigitInteger a, b;

	a = 123456;
	a += EDigitInteger(123456);
	CHECK(a.toInteger() == 246912);
	CHECK(a.isPositive());

	a = 1000;
	a.setPositive(false);
	a += EDigitInteger(1000000);
	CHECK(a.toInteger() == 999000);
	CHECK(a.isPositive());

	a = 999;
	b = 1999;
	b.setPositive(false);
	a += b;
	CHECK(a.toInteger() == 1000);
	CHECK(!a.isPositive());

	a = 100;
	a.setPositive(false);
	a += EDigitInteger(1000);
	CHECK(a.toInteger() == 900);
	CHECK(a.isPositive());
}

TEST_CASE("Test subtraction operator", "[EDigitInteger]")
{
	EDigitInteger a, b;

	a = 12345;
	a -= EDigitInteger(2345);
	CHECK(a.toInteger() == 10000);
	CHECK(a.isPositive());

	a = 100;
	a -= EDigitInteger(1000);
	CHECK(a.toInteger() == 900);
	CHECK(!a.isPositive());

	a = 100;
	b = 900;
	b.setPositive(false);
	a -= b;
	CHECK(a.toInteger() == 1000);
	CHECK(a.isPositive());
}

TEST_CASE("Test multiplication operator", "[EDigitInteger]")
{
	EDigitInteger a, b;

	a = 123;
	a *= EDigitInteger(456);
	CHECK(a.toInteger() == 56088);
	CHECK(a.isPositive());

	a = 999;
	a.setPositive(false);
	a *= EDigitInteger(0);
	CHECK(a.toInteger() == 0);
	CHECK(a.isPositive());

	a = 983243;
	a.setPositive(false);
	a *= EDigitInteger(5);
	CHECK(a.toInteger() == 4916215);
	CHECK(!a.isPositive());

	a = 321;
	a.setPositive(false);
	b = 987;
	b.setPositive(false);
	a *= b;
	CHECK(a.toInteger() == 316827);
	CHECK(a.isPositive());
}

TEST_CASE("Test rightDigitalShift", "[EDigitInteger]")
{
	EDigitInteger a(726398567);
	a.rightDigitalShift(3);
	CHECK(a.toInteger() == 726398);
	CHECK(a.digitCount() == 6);
	a.rightDigitalShift(1);
	CHECK(a.toInteger() == 72639);
	CHECK(a.digitCount() == 5);
	a.rightDigitalShift(-2);
	CHECK(a.toInteger() == 7263900);
	CHECK(a.digitCount() == 7);
	a.rightDigitalShift(0);
	CHECK(a.toInteger() == 7263900);
	CHECK(a.digitCount() == 7);
	a.rightDigitalShift(10);
	CHECK(a.toInteger() == 0);
	CHECK(a.digitCount() == 1);
}

TEST_CASE("Test rightDigitalRotate", "[EDigitInteger]")
{
	EDigitInteger a(12437070894);
	a.rightDigitalRotate(11);
	CHECK(a.toInteger() == 12437070894);
	CHECK(a.digitCount() == 11);
	a.rightDigitalRotate(0);
	CHECK(a.toInteger() == 12437070894);
	CHECK(a.digitCount() == 11);
	a.rightDigitalRotate(-3);
	CHECK(a.toInteger() == 37070894124);
	CHECK(a.digitCount() == 11);
	a.rightDigitalRotate(5);
	CHECK(a.toInteger() == 94124370708);
	CHECK(a.digitCount() == 11);
	a.rightDigitalRotate(1);
	CHECK(a.toInteger() == 89412437070);
	CHECK(a.digitCount() == 11);
	a.rightDigitalRotate(1);
	CHECK(a.toInteger() == 8941243707);
	CHECK(a.digitCount() == 10);
}

TEST_CASE("Test leftDigitalShift", "[EDigitInteger]")
{
	EDigitInteger a(82736);
	a.leftDigitalShift(3);
	CHECK(a.toInteger() == 82736000);
	CHECK(a.digitCount() == 8);
	a.leftDigitalShift(-3);
	CHECK(a.toInteger() == 82736);
	CHECK(a.digitCount() == 5);
	a.leftDigitalShift(1);
	CHECK(a.toInteger() == 827360);
	CHECK(a.digitCount() == 6);
	a.leftDigitalShift(0);
	CHECK(a.toInteger() == 827360);
	CHECK(a.digitCount() == 6);
	a.leftDigitalShift(5);
	CHECK(a.toInteger() == 82736000000);
	CHECK(a.digitCount() == 11);
}

TEST_CASE("Test leftDigitalRotate", "[EDigitInteger]")
{
	EDigitInteger a(17892372809);
	a.leftDigitalRotate(-5);
	CHECK(a.toInteger() == 72809178923);
	CHECK(a.digitCount() == 11);
	a.leftDigitalRotate(11);
	CHECK(a.toInteger() == 72809178923);
	CHECK(a.digitCount() == 11);
	a.leftDigitalRotate(1);
	CHECK(a.toInteger() == 28091789237);
	CHECK(a.digitCount() == 11);
	a.leftDigitalRotate(0);
	CHECK(a.toInteger() == 28091789237);
	CHECK(a.digitCount() == 11);
	a.leftDigitalRotate(5);
	CHECK(a.toInteger() == 78923728091);
	CHECK(a.digitCount() == 11);
	a.leftDigitalRotate(8);
	CHECK(a.toInteger() == 9178923728);
	CHECK(a.digitCount() == 10);
}

TEST_CASE("Test division operator", "[EDigitInteger]")
{
	EDigitInteger a, b;

	a = 1234;
	a /= EDigitInteger(123);
	CHECK(a.toInteger() == 10);
	CHECK(a.isPositive());

	a = 9999;
	a /= EDigitInteger(1);
	CHECK(a.toInteger() == 9999);
	CHECK(a.isPositive());

	a = 182374;
	b = 2829;
	b.setPositive(false);
	a /= b;
	CHECK(a.toInteger() == 64);
	CHECK(!a.isPositive());

	a = 321;
	a.setPositive(false);
	b = 123;
	b.setPositive(false);
	a /= b;
	CHECK(a.toInteger() == 2);
	CHECK(a.isPositive());

	a = 100;
	CHECK_THROWS_AS(a /= EDigitInteger(0), EDivideByZeroException);

	a = 31278;
	a.setPositive(false);
	b = 27;
	b.setPositive(false);
	a /= b;
	CHECK(a.toInteger() == 1158);
	CHECK(a.isPositive());
}

TEST_CASE("Test modulus operator", "[EDigitInteger]")
{
	EDigitInteger a, b;

	a = 18937237;
	b = 23;
	a %= b;
	CHECK(a.toInteger() == 3);
	CHECK(a.isPositive());

	a = 18937237;
	a.setPositive(false);
	b = 1;
	a %= b;
	CHECK(a.toInteger() == 0);
	CHECK(a.isPositive());

	a = 2787;
	b = 0;
	CHECK_THROWS_AS(a %= b, EDivideByZeroException);

	a = 27823;
	b = 378;
	b.setPositive(false);
	a %= b;
	CHECK(a.toInteger() == 229);
	CHECK(a.isPositive());

	a = 31278;
	a.setPositive(false);
	b = 27;
	b.setPositive(false);
	a %= b;
	CHECK(a.toInteger() == 12);
	CHECK(!a.isPositive());
}

TEST_CASE("Test sumOfDigits", "[EDigitInteger]")
{
	EDigitInteger a;

	a = 2378274987;
	CHECK(a.sumOfDigits() == 57);

	a = 2378274987;
	a.setPositive(false);
	CHECK(a.sumOfDigits() == 57);

	a = 2378274000;
	CHECK(a.sumOfDigits() == 33);
}

TEST_CASE("Test isPalindrome", "[EDigitInteger]")
{
	EDigitInteger a;

	a = 237824782;
	CHECK(!a.isPalindrome());

	a = 112232211;
	CHECK(a.isPalindrome());

	a = 112232211;
	a.setPositive(false);
	CHECK(a.isPalindrome());
}

TEST_CASE("Test isPandigital", "[EDigitInteger]")
{
	EDigitInteger a;

	a = 12345;
	a.setPositive(false);
	CHECK(a.isPandigital());

	a = 1;
	CHECK(a.isPandigital());

	a = 123456789;
	CHECK(a.isPandigital());

	a = 1234567891;
	CHECK(!a.isPandigital());

	a = 5;
	CHECK(!a.isPandigital());
}

TEST_CASE("Test isDigitallyEquivalent", "[EDigitInteger]")
{
	EDigitInteger a, b;

	a = 12345;
	b = 54312;
	CHECK(a.isDigitallyEquivalent(b));

	a = 11;
	b = 1;
	CHECK(!a.isDigitallyEquivalent(b));

	a = 27837;
	b = 37287;
	a.setPositive(false);
	CHECK(a.isDigitallyEquivalent(b));
}

TEST_CASE("Test reverseDigits", "[EDigitInteger]")
{
	EDigitInteger a;

	a = 2173843782;
	a.reverseDigits();
	CHECK(a.toInteger() == 2873483712);

	a = 10;
	a.reverseDigits();
	CHECK(a.toInteger() == 1);

	a = 2003;
	a.setPositive(false);
	a.reverseDigits();
	CHECK(a.toInteger() == 3002);
	CHECK(!a.isPositive());

	a = 123456789;
	a.reverseDigits(1, 7);
	CHECK(a.toInteger() == 187654329);
}

TEST_CASE("Test digit sorting", "[EDigitInteger]")
{
	EDigitInteger a;

	// Ascending

	a = 219287365939;
	a.sortDigitsAscending();

	for(std::size_t i = 0; i < (a.digitCount() - 1); ++i)
		EASSERT(a.get(i) <= a.get(i + 1))

	// Descending

	a = 219287365939;
	a.sortDigitsDescending();

	for(std::size_t i = 0; i < (a.digitCount() - 1); ++i)
		EASSERT(a.get(i) >= a.get(i + 1))
}

TEST_CASE("Test comparison operators", "[EDigitInteger]")
{
	std::random_device rd;
	std::mt19937 engine(rd());

	auto generate = [&]() {
		auto v = engine();
		EDigitInteger i;
		i = v;
		i.setPositive(v & 1);
		int64_t sv = static_cast<int64_t>(v);
		sv *= i.isPositive() ? 1 : -1;
		return std::make_pair(sv, i);
	};

	for(std::size_t i = 0; i < 1000; ++i)
	{
		auto a = generate();
		auto b = generate();

		CHECK((a.first == b.first) == (a.second == b.second));
		CHECK((a.first != b.first) == (a.second != b.second));
		CHECK((a.first < b.first) == (a.second < b.second));
		CHECK((a.first > b.first) == (a.second > b.second));
		CHECK((a.first <= b.first) == (a.second <= b.second));
		CHECK((a.first >= b.first) == (a.second >= b.second));
	}
}

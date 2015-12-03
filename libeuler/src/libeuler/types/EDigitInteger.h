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

#ifndef INCLUDE_LIBEULER_TYPES_DIGIT_INTEGER_H
#define INCLUDE_LIBEULER_TYPES_DIGIT_INTEGER_H

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>

#ifdef _WIN32
// Disable all warnings for gmp.h and gmpxx.h on win32, since they generate
// warnings.
#pragma warning(push, 0)
#endif

#include <gmp.h>
#include <gmpxx.h>

#ifdef _WIN32
// Be sure to enable warnings again.
#pragma warning(pop)
#endif

#include "libeuler/EExceptions.h"

#ifdef LIBEULER_DEBUG
#include <ctime>
#endif

// Forward declarations.
class EDigitInteger;
std::ostream &operator<<(std::ostream &out, const EDigitInteger &i);

/*!
 * \brief This class stores integers of arbitrary size as a series of digits.
 *
 * This allows for non-standard checks that involve individual digits, such as
 * whether or not the number is a palindrome.
 *
 * It should be noted that, although this class provides some rudimentary
 * mathematical functions (mostly +, -, *, / and %) they are going to be MUCH
 * slower than the same operations on primitive types (or even the same
 * operation on GMP types). As such, if you are going to be performing lots of
 * math, you should do it with some other type and then initialize a new
 * EDigitInteger using that value.
 */
class EDigitInteger
{
public:
#ifdef LIBEULER_DEBUG
	static void doTestSuite();
#endif

	EDigitInteger();
	EDigitInteger(EDigitInteger const &) = default;
	EDigitInteger(EDigitInteger &&) = default;
	explicit EDigitInteger(uint64_t v);
	explicit EDigitInteger(const mpz_class &v);
	~EDigitInteger() = default;

	EDigitInteger &operator=(EDigitInteger const &) = default;
	EDigitInteger &operator=(EDigitInteger &&) = default;
	EDigitInteger &operator=(const std::string &v);
	EDigitInteger &operator=(uint64_t v);
	EDigitInteger &operator=(const mpz_class &v);

	bool operator==(const EDigitInteger &o) const;
	bool operator!=(const EDigitInteger &o) const;
	bool operator<(const EDigitInteger &o) const;
	bool operator>(const EDigitInteger &o) const;
	bool operator<=(const EDigitInteger &o) const;
	bool operator>=(const EDigitInteger &o) const;

	EDigitInteger operator-() const;

	EDigitInteger &operator+=(const EDigitInteger &o);
	EDigitInteger &operator-=(const EDigitInteger &o);
	EDigitInteger &operator*=(const EDigitInteger &o);
	EDigitInteger &operator/=(const EDigitInteger &o);
	EDigitInteger &operator%=(const EDigitInteger &o);

	EDigitInteger operator+(const EDigitInteger &o) const;
	EDigitInteger operator-(const EDigitInteger &o) const;
	EDigitInteger operator*(const EDigitInteger &o) const;
	EDigitInteger operator/(const EDigitInteger &o) const;
	EDigitInteger operator%(const EDigitInteger &o) const;

	EDigitInteger &operator++();
	EDigitInteger operator++(int i);
	EDigitInteger &operator--();
	EDigitInteger operator--(int i);

	bool isPositive() const;
	void setPositive(bool p);
	std::size_t digitCount() const;

	bool hasNthDigit(std::size_t i) const;
	int get(std::size_t i) const;

	int sumOfDigits() const;

	bool isPalindrome() const;
	bool isPandigital() const;

	bool isDigitallyEquivalent(const EDigitInteger &o) const;

	bool put(std::size_t i, int v);
	bool erase(std::size_t i);

	void rightDigitalShift(int p);
	bool rightDigitalRotate(int p);
	void leftDigitalShift(int p);
	bool leftDigitalRotate(int p);

	void sortDigitsAscending();
	bool sortDigitsDescending();
	bool permutateDigits();
	bool reversePermutateDigits();

	bool
	reverseDigits(std::size_t l = 0,
	              std::size_t r = std::numeric_limits<std::size_t>::max());

	uint64_t rangeToInteger(std::size_t l, std::size_t r) const;
	uint64_t toInteger() const;
	mpz_class rangeToBigInteger(std::size_t l, std::size_t r) const;
	mpz_class toBigInteger() const;
	std::string rangeToString(std::size_t l, std::size_t r) const;
	std::string toString() const;

private:
	std::unordered_map<std::size_t, int> digits;
	bool positive;

	bool volatileSetDigitAt(std::size_t i, int v);
	bool removeLeadingZeros();

	void carry();
	void borrow();

	void setZero();

	bool unsignedEqualTo(const EDigitInteger &o) const;
	bool unsignedNotEqualTo(const EDigitInteger &o) const;
	bool unsignedLessThan(const EDigitInteger &o) const;
	bool unsignedGreaterThan(const EDigitInteger &o) const;
	bool unsignedLessThanEqualTo(const EDigitInteger &o) const;
	bool unsignedGreaterThanEqualTo(const EDigitInteger &o) const;

	void unsignedAdd(const EDigitInteger &i);
	void unsignedSubtract(const EDigitInteger &i);
	void unsignedMultiply(const EDigitInteger &i);
	void unsignedDivide(const EDigitInteger &i, bool m = false);
};

#endif

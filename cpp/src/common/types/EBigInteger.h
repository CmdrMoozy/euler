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

#ifndef INCLUDE_LIBEULER_TYPES_BIG_INTEGER_H
#define INCLUDE_LIBEULER_TYPES_BIG_INTEGER_H

#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <string>

#include <gmp.h>
#include <gmpxx.h>

// Forward declarations.
class EBigInteger;
std::ostream &operator<<(std::ostream &o, const EBigInteger &i);

/*!
 * \brief This class implements an arbitrary-precision integer using GMP.
 *
 * It provides some functionality that GMP's mpz_class type either doesn't
 * provide, or doesn't make easy to use syntactically.
 */
class EBigInteger
{
public:
	EBigInteger();
	explicit EBigInteger(mpz_class const &v);
	explicit EBigInteger(std::string const &v);
	EBigInteger(int64_t v);
	explicit EBigInteger(uint64_t v);

	EBigInteger(EBigInteger const &) = default;
	EBigInteger &operator=(EBigInteger const &) = default;

	virtual ~EBigInteger();

	bool operator==(const EBigInteger &o) const;
	bool operator!=(const EBigInteger &o) const;
	bool operator<(const EBigInteger &o) const;
	bool operator<=(const EBigInteger &o) const;
	bool operator>(const EBigInteger &o) const;
	bool operator>=(const EBigInteger &o) const;

	EBigInteger operator-() const;

	EBigInteger operator+(const EBigInteger &o) const;
	EBigInteger operator-(const EBigInteger &o) const;
	EBigInteger operator*(const EBigInteger &o) const;
	EBigInteger operator/(const EBigInteger &o) const;
	EBigInteger operator%(const EBigInteger &o) const;

	EBigInteger &operator+=(const EBigInteger &o);
	EBigInteger &operator-=(const EBigInteger &o);
	EBigInteger &operator*=(const EBigInteger &o);
	EBigInteger &operator/=(const EBigInteger &o);
	EBigInteger &operator%=(const EBigInteger &o);

	EBigInteger &operator++();
	EBigInteger operator++(int);
	EBigInteger &operator--();
	EBigInteger operator--(int);

	EBigInteger operator~() const;
	EBigInteger operator&(const EBigInteger &o) const;
	EBigInteger operator|(const EBigInteger &o) const;
	EBigInteger operator^(const EBigInteger &o) const;
	EBigInteger operator<<(const EBigInteger &o) const;
	EBigInteger operator>>(const EBigInteger &o) const;

	EBigInteger &operator&=(const EBigInteger &o);
	EBigInteger &operator|=(const EBigInteger &o);
	EBigInteger &operator^=(const EBigInteger &o);
	EBigInteger &operator<<=(const EBigInteger &o);
	EBigInteger &operator>>=(const EBigInteger &o);

	EBigInteger abs() const;
	int sgn() const;

	EBigInteger pow(const EBigInteger &e) const;
	EBigInteger powMod(const EBigInteger &e, const EBigInteger &m) const;
	EBigInteger lcm(const EBigInteger &o) const;

	void nextPrime();

	std::string toString() const;
	int64_t toInt() const;
	uint64_t toUInt() const;
	mpz_class &toMPZ();

private:
	mpz_class value;
};

#endif

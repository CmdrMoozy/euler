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

#include "EBigInteger.h"

#include <climits>
#include <cstdlib>
#include <iostream>
#include <memory>

#if(defined _WIN32 || defined __APPLE__)
#include "common/math/EMath.h"
#endif

/*
 * This is our default constructor, which initializes our integer's value to 0.
 */
EBigInteger::EBigInteger() : value(0)
{
}

EBigInteger::EBigInteger(const mpz_class &v) : value(v)
{
}

EBigInteger::EBigInteger(std::string const &v) : value(v, 10)
{
}

EBigInteger::EBigInteger(int64_t v)
{
	int64_t s = ((-(v >> 63)) | ((-v) >> 63));
	uint64_t a = static_cast<uint64_t>(v * s);

	(*this) = EBigInteger(a);

	if(s == -1)
		(*this) = -(*this);
}

EBigInteger::EBigInteger(uint64_t v)
{
#if(defined _WIN32 || defined __APPLE__)
	value = EMath::int64ToBigInteger(v);
#else
	value = v;
#endif
}

EBigInteger::~EBigInteger()
{
}

bool EBigInteger::operator==(const EBigInteger &o) const
{
	return value == o.value;
}

bool EBigInteger::operator!=(const EBigInteger &o) const
{
	return value != o.value;
}

bool EBigInteger::operator<(const EBigInteger &o) const
{
	return value < o.value;
}

bool EBigInteger::operator<=(const EBigInteger &o) const
{
	return value <= o.value;
}

bool EBigInteger::operator>(const EBigInteger &o) const
{
	return value > o.value;
}

bool EBigInteger::operator>=(const EBigInteger &o) const
{
	return value >= o.value;
}

EBigInteger EBigInteger::operator-() const
{
	EBigInteger r((*this));
	r *= EBigInteger(static_cast<int64_t>(-1));
	return r;
}

EBigInteger EBigInteger::operator+(const EBigInteger &o) const
{
	EBigInteger r((*this));
	r.value += o.value;
	return r;
}

EBigInteger EBigInteger::operator-(const EBigInteger &o) const
{
	EBigInteger r((*this));
	r.value -= o.value;
	return r;
}

EBigInteger EBigInteger::operator*(const EBigInteger &o) const
{
	EBigInteger r((*this));
	r.value *= o.value;
	return r;
}

EBigInteger EBigInteger::operator/(const EBigInteger &o) const
{
	EBigInteger r((*this));
	r.value /= o.value;
	return r;
}

EBigInteger EBigInteger::operator%(const EBigInteger &o) const
{
	EBigInteger r((*this));
	r.value %= o.value;
	return r;
}

EBigInteger &EBigInteger::operator+=(const EBigInteger &o)
{
	value += o.value;
	return (*this);
}

EBigInteger &EBigInteger::operator-=(const EBigInteger &o)
{
	value -= o.value;
	return (*this);
}

EBigInteger &EBigInteger::operator*=(const EBigInteger &o)
{
	value *= o.value;
	return (*this);
}

EBigInteger &EBigInteger::operator/=(const EBigInteger &o)
{
	value /= o.value;
	return (*this);
}

EBigInteger &EBigInteger::operator%=(const EBigInteger &o)
{
	value %= o.value;
	return (*this);
}

// Prefix increment.
EBigInteger &EBigInteger::operator++()
{
	(*this) += 1;
	return (*this);
}

// Postfix increment.
EBigInteger EBigInteger::operator++(int)
{
	return (*this) + 1;
}

// Prefix increment.
EBigInteger &EBigInteger::operator--()
{
	(*this) -= 1;
	return (*this);
}

// Postfix increment.
EBigInteger EBigInteger::operator--(int)
{
	return (*this) - 1;
}

EBigInteger EBigInteger::operator~() const
{
	EBigInteger r((*this));
	mpz_com(r.value.get_mpz_t(), r.value.get_mpz_t());
	return r;
}

EBigInteger EBigInteger::operator&(const EBigInteger &o) const
{
	EBigInteger r((*this));
	r &= o;
	return r;
}

EBigInteger EBigInteger::operator|(const EBigInteger &o) const
{
	EBigInteger r((*this));
	r |= o;
	return r;
}

EBigInteger EBigInteger::operator^(const EBigInteger &o) const
{
	EBigInteger r((*this));
	r ^= o;
	return r;
}

EBigInteger EBigInteger::operator<<(const EBigInteger &o) const
{
	EBigInteger r((*this));
	r <<= o;
	return r;
}

EBigInteger EBigInteger::operator>>(const EBigInteger &o) const
{
	EBigInteger r((*this));
	r >>= o;
	return r;
}

EBigInteger &EBigInteger::operator&=(const EBigInteger &o)
{
	mpz_and(value.get_mpz_t(), value.get_mpz_t(), o.value.get_mpz_t());
	return (*this);
}

EBigInteger &EBigInteger::operator|=(const EBigInteger &o)
{
	mpz_ior(value.get_mpz_t(), value.get_mpz_t(), o.value.get_mpz_t());
	return (*this);
}

EBigInteger &EBigInteger::operator^=(const EBigInteger &o)
{
	mpz_xor(value.get_mpz_t(), value.get_mpz_t(), o.value.get_mpz_t());
	return (*this);
}

/*
 * This function does a left bit shift by the given number of bits. Note that
 * the actual number of bits
 * shifted is, per the GMP API, specified as an 'unsigned long', so it is up to
 * the caller to ensure that
 * o fits in that type.
 */
EBigInteger &EBigInteger::operator<<=(const EBigInteger &o)
{
	mpz_mul_2exp(value.get_mpz_t(), value.get_mpz_t(),
	             static_cast<mp_bitcnt_t>(mpz_get_ui(o.value.get_mpz_t())));

	return (*this);
}

/*
 * This function does a right bit shift by the given number of bits. If our
 * value is positive, this is an
 * unsigned shift, whereas if it is negative, then an arithmetic shift is
 * performed instead (see the GMP docs
 * for mpz_tdiv_q_2exp). Also note that the actual number of bits shifted is,
 * per the GMP API, specified
 * as an 'unsigned long', so it is up to the caller to ensure that o fits in
 * that type.
 */
EBigInteger &EBigInteger::operator>>=(const EBigInteger &o)
{
	mpz_tdiv_q_2exp(
	        value.get_mpz_t(), value.get_mpz_t(),
	        static_cast<mp_bitcnt_t>(mpz_get_ui(o.value.get_mpz_t())));

	return (*this);
}

EBigInteger EBigInteger::abs() const
{
	EBigInteger r;
	mpz_abs(r.value.get_mpz_t(), value.get_mpz_t());
	return r;
}

int EBigInteger::sgn() const
{
	return mpz_sgn(value.get_mpz_t());
}

/*!
 * This function returns a EBigInteger whose value is this ^ e. Note that e
 * needs to fit in an unsigned long,
 * which should always be the case (see:
 * http://gmplib.org/list-archives/gmp-discuss/2008-October/003421.html).
 */
EBigInteger EBigInteger::pow(const EBigInteger &e) const
{
	EBigInteger r;
	mpz_pow_ui(r.value.get_mpz_t(), value.get_mpz_t(),
	           mpz_get_ui(e.value.get_mpz_t()));
	return r;
}

EBigInteger EBigInteger::powMod(const EBigInteger &e,
                                const EBigInteger &m) const
{
	EBigInteger r;
	mpz_powm(r.value.get_mpz_t(), value.get_mpz_t(), e.value.get_mpz_t(),
	         m.value.get_mpz_t());
	return r;
}

EBigInteger EBigInteger::lcm(const EBigInteger &o) const
{
	EBigInteger r;
	mpz_lcm(r.value.get_mpz_t(), value.get_mpz_t(), o.value.get_mpz_t());
	return r;
}

void EBigInteger::nextPrime()
{
	mpz_nextprime(value.get_mpz_t(), value.get_mpz_t());
}

std::string EBigInteger::toString() const
{
	auto deleter = [](char *p) {
		if(p != nullptr)
			std::free(p);
	};
	std::unique_ptr<char, std::function<void(char *)>> s(
	        mpz_get_str(nullptr, 10, value.get_mpz_t()), deleter);
	return std::string(s.get());
}

/*
 * This function returns our value as a 64-bit signed integer. If the value is
 * too small or too large to fit
 * in the resulting data type, INT64_MIN or INT64_MAX are returned,
 * respectively.
 */
int64_t EBigInteger::toInt() const
{
#if(defined _WIN32 || defined __APPLE__)
	if(value < QMath::int64ToBigInteger(INT64_MIN))
	{
		return INT64_MIN;
	}
	else if(value > QMath::int64ToBigInteger(INT64_MAX))
	{
		return INT64_MAX;
	}
	else
	{
		// Get our value using toUInt() instead.
		uint64_t r = toUInt();
		r %= sgn() < 0 ? INT64_MIN : INT64_MAX;
		r *= sgn();
		return r;
	}
#else
	if(value < INT64_MIN)
	{
		return INT64_MIN;
	}
	else if(value > INT64_MAX)
	{
		return INT64_MAX;
	}
	else
	{
		// Get our value using toUInt() instead.
		uint64_t r = toUInt();
		int s = sgn();
		if((s < 0) && (r >= static_cast<uint64_t>(INT64_MAX) + 1))
		{
			return INT64_MIN;
		}
		else if((s > 0) && (r >= static_cast<uint64_t>(INT64_MAX)))
		{
			return INT64_MAX;
		}
		else
		{
			return s * static_cast<int64_t>(r);
		}
	}
#endif
}

/*
 * This function returns our value as a 64-bit unsigned integer. If the value is
 * too large to fit in the resulting
 * data type, UINT64_MAX is returned instead. The value returned is the
 * /absolute value/ of our number.
 */
uint64_t EBigInteger::toUInt() const
{
	if(sgn() < 0)
	{
		return abs().toUInt();
	}
#if(defined _WIN32 || defined __APPLE__)
	else if(value > QMath::int64ToBigInteger(UINT64_MAX))
#else
	else if(value > UINT64_MAX)
#endif
	{
		return UINT64_MAX;
	}
	else
	{
		/*
		 * If "unsigned long int" is 64-bits long on our platform, we
		 * can just use GMP's conversion functions
		 * directly. Otherwise, convert from a string in order to
		 * preserve precision(something which might
		 * not be guaranteed if, e.g., we converted to double first).
		 */

		if((CHAR_BIT * sizeof(unsigned long int)) == 64)
		{
			return static_cast<uint64_t>(
			        mpz_get_ui(value.get_mpz_t()));
		}
		else
		{
			/*
			 * Since we don't particularly need to target machines
			 * that aren't either 32- or 64-bit, we'll
			 * just assume that "unsigned long int" is 32 bits, for
			 * the purposes of this conversion.
			 */

			uint64_t r = 0;
			mpz_class v;

			// Get the low bits.

			mpz_mod_ui(v.get_mpz_t(), value.get_mpz_t(),
			           UINT32_MAX);
			r += mpz_get_ui(v.get_mpz_t());

			// Get the high bits.

			mpz_tdiv_q_2exp(v.get_mpz_t(), value.get_mpz_t(), 32);
			mpz_mod_ui(v.get_mpz_t(), v.get_mpz_t(), UINT32_MAX);
			r += static_cast<uint64_t>(mpz_get_ui(v.get_mpz_t()))
			     << 32;

			return r;
		}
	}
}

/*
 * This function returns a reference to our internal mpz_class object, e.g. so
 * one can use it to perform GMP
 * operations that aren't strictly supported by this container class.
 */
mpz_class &EBigInteger::toMPZ()
{
	return value;
}

std::ostream &operator<<(std::ostream &o, const EBigInteger &i)
{
	o << i.toString();
	return o;
}
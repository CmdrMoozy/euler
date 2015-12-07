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

#include "EBitwise.h"

#include <climits>

/*!
 * This function tests if the given value is a power of two or not.
 *
 * \param v The value to test.
 * \return True if v is a power of two, or false otherwise.
 */
bool EBitwise::isPowerOfTwo(uint32_t v)
{
	return EBitwise::isPowTwo(v);
}

/*!
 * This function is similar to lg() in that it calculates the base-2 logarithm
 *of the given value,
 * except that it is designed to work only on values that are guaranteed to be
 *powers of 2.
 *
 * Note that this function is slightly faster than lg(), and as such should be
 *used where possible.
 *
 * \param v The value to take the lg() of.
 * \return The log2(v).
 */
uint32_t EBitwise::lgPowerOfTwo(uint32_t v)
{
	return EBitwise::lg32(v);
}

/*!
 * This function returns the base-2 logarithm of the given value.
 *
 * \param v The value to take the lg() of.
 * \return The log2(v).
 */
uint32_t EBitwise::lg(uint32_t v)
{
	return EBitwise::lg32(v);
}

uint32_t EBitwise::lg32(uint32_t v)
{
	return 31 - static_cast<uint32_t>(EBitwise::nlz32(v));
}

uint32_t EBitwise::lg64(uint64_t v)
{
	return 63 - static_cast<uint32_t>(EBitwise::nlz64(v));
}

/*!
 * This function reverses the order of ALL of the bits in v (including leading
 *0's).
 *
 * \param v The value to reverse.
 * \return A value which is bit-reversed v.
 */
uint32_t EBitwise::reverseAllBits(uint32_t v)
{
	uint32_t r = v;
	int s = sizeof(v) * CHAR_BIT - 1;

	for(v >>= 1; v; v >>= 1)
	{
		r <<= 1;
		r |= v & 1;
		s--;
	}
	r <<= s;

	return r;
}

/*!
 * This function reverses the order of the bits in v, excluding any leading
 *zeros.
 *
 * \param v The value to reverse.
 * \return A value which is bit-reversed v.
 */
uint32_t EBitwise::reverseBits(uint32_t v)
{
	return (EBitwise::reverseAllBits(v) >> (31 - EBitwise::lg32(v)));
}

/*!
 * This is a convenience function, which tests if v is palindromic in base 2.
 *This test
 * just compares if v is equal to reverseBits(v).
 *
 * \param v The value to test.
 * \return True if v is a palindrome, or false otherwise.
 */
bool EBitwise::isPalindromic(uint32_t v)
{
	return (v == EBitwise::reverseBits(v));
}

/*!
 * This function does a circular shift (a rotation) of the 32-bit unsigned
 *integer n by
 * p places to the left.
 *
 * \param n The value to operate on.
 * \param p The number of places to left-rotate n.
 * \return The result of n <<< p.
 */
uint32_t EBitwise::rotateLeft(uint32_t n, int p)
{
	return EBitwise::rotl32(n, p);
}

/*!
 * This function does a circular shift (a rotation) of the 32-bit unsigned
 *integer n by
 * p places to the right.
 *
 * \param n The value to operate on.
 * \param p The number of places to right-rotate n.
 * \return The result of n >>> p.
 */
uint32_t EBitwise::rotateRight(uint32_t n, int p)
{
	return EBitwise::rotr32(n, p);
}

/*!
 * This function does a circular shift (a rotation) of the 32-bit unsigned
 *integer n by
 * p places to the left.
 *
 * \param n The value to operate on.
 * \param p The number of places to left-rotate n.
 * \return The result of n <<< p.
 */
uint32_t EBitwise::rotl32(uint32_t n, int p)
{
	return (n << (p % 32)) | (n >> (32 - (p % 32)));
}

/*!
 * This function does a circular shift (a rotation) of the 32-bit unsigned
 *integer n by
 * p places to the right.
 *
 * \param n The value to operate on.
 * \param p The number of places to right-rotate n.
 * \return The result of n >>> p.
 */
uint32_t EBitwise::rotr32(uint32_t n, int p)
{
	return (n >> (p % 32)) | (n << (32 - (p % 32)));
}

/*!
 * This function does a circular shift (a rotation) of the 64-bit unsigned
 *integer n by
 * p places to the left.
 *
 * \param n The value to operate on.
 * \param p The number of places to left-rotate n.
 * \return The result of n <<< p.
 */
uint64_t EBitwise::rotl64(uint64_t n, int p)
{
	return (n << (p % 64)) | (n >> (64 - (p % 64)));
}

/*!
 * This function does a circular shift (a rotation) of the 64-bit unsigned
 *integer n by
 * p places to the right.
 *
 * \param n The value to operate on.
 * \param p The number of places to right-rotate n.
 * \return The result of n >>> p.
 */
uint64_t EBitwise::rotr64(uint64_t n, int p)
{
	return (n >> (p % 64)) | (n << (64 - (p % 64)));
}

/*!
 * This function returns the result of a modulus division of a numerator, n, by
 *some power of two
 * 2^s.
 *
 * \param n Our numerator.
 * \param s Our divisor will be 2^s.
 * \return n % (2^s)
 */
uint64_t EBitwise::modPowTwo(uint64_t n, unsigned int s)
{
	uint64_t ret = static_cast<uint64_t>(1) << s;
	ret -= 1;
	return n & ret;
}

/*!
 * This function returns the result of a modulus division of a numerator, n, by
 *one less than some
 * power of two (2^s)-1.
 *
 * \param n Our numerator.
 * \param s Our divisor will be (2^s)-1.
 * \return n % ((2^s)-1)
 */
uint64_t EBitwise::modPowTwoLessOne(uint64_t n, unsigned int s)
{
	uint64_t d = (static_cast<uint64_t>(1) << s) - 1;
	uint64_t m = 0;

	for(m = n; n > d; n = m)
		for(m = 0; n; n >>= s)
			m += n & d;

	return ((m == d) ? 0 : m);
}

/*!
 * This function returns the input value with the right-most one bit turned off.
 *
 * \param x Our input value.
 * \return Our input with the right-most one turned off.
 */
uint64_t EBitwise::rmoOff(uint64_t x)
{
	return (x & (x - 1));
}

/*!
 * This function returns the input value with the right-most zero bit turned on.
 *
 * \param x Our input value.
 * \return Our input value with the right-most zero turned on.
 */
uint64_t EBitwise::rmzOn(uint64_t x)
{
	return (x | (x + 1));
}

/*!
 * This function tests whether or not the input value is a power of two.
 *
 * \param n The number to test.
 * \return True if x is a power of two, or false otherwise.
 */
bool EBitwise::isPowTwo(uint64_t n)
{
	return (n && !EBitwise::rmoOff(n));
}

/*!
 * This function tests whether or not the input value is of the form 2^e - 1.
 *
 * \param n The number to test.
 * \return True if n is one less than a power of two, or false otherwise.
 */
bool EBitwise::isPowTwoLessOne(uint64_t n)
{
	return (n && !(n & (n + 1)));
}

/*!
 * This function isolates the right-most one bit in the given input value. For
 *instance:
 *     rmoIsolate( 0101 1000 ) = 0000 1000
 *
 * \param x Our input value.
 * \return A value with the right-most one bit isolated.
 */
uint64_t EBitwise::rmoIsolate(uint64_t x)
{
	return (x & (-x));
}

/*!
 * This function isolates the right-most zero bit in the given input value. For
 *instance:
 *     rmzIsolate( 0101 0111 ) = 0000 1000
 *
 * \param x Our input value.
 * \return A value with the right-most zero bit isolated.
 */
uint64_t EBitwise::rmzIsolate(uint64_t x)
{
	return (~x | (x - 1));
}

/*!
 * This function returns a mask for the trailing zero bits in the given input
 *value. For instance:
 *     trailZMask( 1100 1000 ) = 0000 0111
 *
 * \param x Our input value.
 * \return A mask for the trailing zeros in x.
 */
uint64_t EBitwise::trailZMask(uint64_t x)
{
	return (~x & (x - 1));
}

/*!
 * This function returns a mask for the trailing one bits in the given input
 *value. For instance:
 *     trailOMask( 1100 0111 ) = 0000 0111
 *
 * \param x Our input value.
 * \return A mask for the trailing ones in x.
 */
uint64_t EBitwise::trailOMask(uint64_t x)
{
	return (~x | (x + 1));
}

/*!
 * This function returns a mask for the right-most one bit and the trailing
 *zeros after it. For instance:
 *     trailRMOZMask( 0101 0000 ) = 0001 1111
 *
 * \param x Our input value.
 * \return A mask for the right-most one and trailing zeros in x.
 */
uint64_t EBitwise::trailRMOZMask(uint64_t x)
{
	return (x ^ (x - 1));
}

/*!
 * This function returns a mask for the right-most zero bit and the trailing
 *ones after it. For instance:
 *     trailRMZOMask( 1110 1111 ) = 0001 1111
 *
 * \param x Our input value.
 * \return A mask for the right-most zero and the trailing ones in x.
 */
uint64_t EBitwise::trailRMZOMask(uint64_t x)
{
	return (x ^ (x + 1));
}

/*!
 * This function propagates the right-most one bit to the right. For instance:
 *     rmoPropR( 1010 0000 ) = 1011 1111
 *
 * \param x Our input value.
 * \return A new value with the right-most one in x propagated to the right.
 */
uint64_t EBitwise::rmoPropR(uint64_t x)
{
	return (x | (x - 1));
}

/*!
 * This function propagates the right-most zero bit to the right. For instance:
 *     rmzPropR( 1010 1111 ) = 1010 0000
 *
 * \param x Our input value.
 * \return A new value with the right-most zero in x propagated to the right.
 */
uint64_t EBitwise::rmzPropR(uint64_t x)
{
	return (x & (x + 1));
}

/*!
 * This function turns the right-most string of ones off. For instance:
 *     rmosOff( 1010 0111 ) = 1010 0000
 *
 * \param x Our input value.
 * \return A new value with the right-most string of ones in x turned off.
 */
uint64_t EBitwise::rmosOff(uint64_t x)
{
	return (((x | (x - 1)) + 1) & x);
}

/*!
 * This function turns the right-most string of zeros on. For instance:
 *     rmzsOn( 1010 1000 ) = 1010 1111
 *
 * \param x Our input value.
 * \return A new value with the right-most string of zeros in x turned off.
 */
uint64_t EBitwise::rmzsOn(uint64_t x)
{
	return (((x & (x + 1)) - 1) | x);
}

/*!
 * This function returns the number of one bits set in the given input value, or
 *it's "population count".
 *
 * Note that if you are just going to test if the number of one bits is exactly
 *one, it is somewhat faster
 * to call isPowTwo() instead.
 *
 * \param x Our input value.
 * \return The number of one bits in x.
 */
int EBitwise::opop(uint64_t x)
{
	x = (x & 0x5555555555555555) + ((x >> 1) & 0x5555555555555555);
	x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
	x = (x & 0x0F0F0F0F0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F0F0F0F0F);
	x = (x & 0x00FF00FF00FF00FF) + ((x >> 8) & 0x00FF00FF00FF00FF);
	x = (x & 0x0000FFFF0000FFFF) + ((x >> 16) & 0x0000FFFF0000FFFF);
	x = (x & 0x00000000FFFFFFFF) + ((x >> 32) & 0x00000000FFFFFFFF);
	return static_cast<int>(x);
}

/*!
 * This function returns the number of leading zeros for the given number.
 *
 * \param x The value to inspect.
 * \return The number of leading zeros in the given value.
 */
int EBitwise::nlz32(uint32_t x)
{
	uint32_t y;
	int n, c;

	n = 32;
	c = 16;
	do
	{
		y = x >> c;
		if(y != 0)
		{
			n = n - c;
			x = y;
		}

		c >>= 1;
	} while(c != 0);

	return n - static_cast<int>(x);
}

/*!
 * This function returns the number of leading zeros for the given number.
 *
 * \param x The value to inspect.
 * \return The number of leading zeros in the given value.
 */
int EBitwise::nlz64(uint64_t x)
{
	uint64_t y;
	int n, c;

	n = 64;
	c = 32;
	do
	{
		y = x >> c;
		if(y != 0)
		{
			n = n - c;
			x = y;
		}

		c >>= 1;
	} while(c != 0);

	return n - static_cast<int>(x);
}

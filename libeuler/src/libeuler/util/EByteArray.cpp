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

#include "EByteArray.h"

#include "libeuler/EDefines.h"
#include "libeuler/util/EBitwise.h"

#ifdef LIBEULER_DEBUG
#include <iostream>
#endif

#ifdef LIBEULER_DEBUG
/*!
 * This function implements our test suite for this class. It uses
 * non-abort()'ing
 * assertions, and merely prints the result to stdout.
 */
void EByteArray::doTestSuite()
{
	bool success;
	std::size_t i;

	std::cout << "\tTesting 'EByteArray'...\t\t\t";
	try
	{
		success = true;

		// getMinimumByteLength

		for(i = 0; i < 1000; ++i)
		{
			EASSERT(EByteArray::getMinimumByteLength(i) ==
			        ((i - (i % 8)) / 8) + 1)
		}

		// Default Constructor + bitSize

		EByteArray a(10, EByteArray::Set);

		EASSERT(a.getSize() == 10)
		EASSERT(a.bitSize() == 80)

		for(i = 0; i < a.getSize(); ++i)
			EASSERT(a.at(i) == 0xFF)

		// resize

		a.resize(4, EByteArray::Clear);

		EASSERT(a.getSize() == 4)
		EASSERT(a.bitSize() == 32)

		// clearBits + setBits

		a.setBits();
		for(i = 0; i < a.getSize(); ++i)
			EASSERT(a.at(i) == 0xFF)

		a.clearBits();
		for(i = 0; i < a.getSize(); ++i)
			EASSERT(a.at(i) == 0x00)

		// flipBitAt

		for(i = 0; i < a.bitSize(); ++i)
			a.flipBitAt(i);

		for(i = 0; i < a.getSize(); ++i)
			EASSERT(a.at(i) == 0xFF)

		for(i = 0; i < a.bitSize(); ++i)
			a.flipBitAt(i);

		for(i = 0; i < a.getSize(); ++i)
			EASSERT(a.at(i) == 0x00)

		// bitAt + setBitAt + bitwiseComplement

		for(i = 0; i < a.bitSize(); ++i)
			if(i & 1)
				a.setBitAt(i, true);

		for(i = 0; i < a.bitSize(); ++i)
			EASSERT(a.bitAt(i) == (i & 1))

		for(i = 0; i < a.getSize(); ++i)
			EASSERT(a.at(i) == 0xAA)

		a.bitwiseComplement();

		for(i = 0; i < a.getSize(); ++i)
			EASSERT(a.at(i) == 0x55)

		// leftShift + rightShift

		a.clearBits();

		a.at(0) = 0xFF;

		a.leftShift(8);
		EASSERT(a.at(1) == 0xFF)
		EASSERT(a.at(0) == 0x00)

		a.leftShift(4);
		EASSERT(a.at(2) == 0x0F)
		EASSERT(a.at(1) == 0xF0)

		a.rightShift(4);
		EASSERT(a.at(1) == 0xFF)
		EASSERT(a.at(2) == 0x00)

		a.rightShift(8);
		EASSERT(a.at(0) == 0xFF)
		EASSERT(a.at(1) == 0x00)

		// leftRotate + rightRotate

		a.at(a.getSize() - 1) = 0xFF;
		a.leftRotate(8);

		EASSERT(a.at(a.getSize() - 1) == 0x00)
		EASSERT(a.at(0) == 0xFF)

		a.clearBits();
		a.at(0) = 0xA5;

		a.rightRotate(4);
		EASSERT(a.at(0) == 0x0A)
		EASSERT(a.at(a.getSize() - 1) == 0x50)

		uint32_t number;
		EByteArray b(4, EByteArray::Clear);
		// bitwiseAnd

		a.at(3) = 0x9A;
		a.at(2) = 0xFC;
		a.at(1) = 0xCC;
		a.at(0) = 0x7B;

		b.at(3) = 0xF8;
		b.at(2) = 0x80;
		b.at(1) = 0xDF;
		b.at(0) = 0x73;

		number = 0xF880DF73;

		a.bitwiseAnd(b);
		EASSERT(a.at(0) == 0x73)
		EASSERT(a.at(1) == 0xCC)
		EASSERT(a.at(2) == 0x80)
		EASSERT(a.at(3) == 0x98)

		a.at(3) = 0x9A;
		a.at(2) = 0xFC;
		a.at(1) = 0xCC;
		a.at(0) = 0x7B;

		a.bitwiseAnd(number);
		EASSERT(a.at(0) == 0x73)
		EASSERT(a.at(1) == 0xCC)
		EASSERT(a.at(2) == 0x80)
		EASSERT(a.at(3) == 0x98)

		// bitwiseOr

		a.at(3) = 0x9A;
		a.at(2) = 0xFC;
		a.at(1) = 0xCC;
		a.at(0) = 0x7B;

		b.at(3) = 0xF8;
		b.at(2) = 0x80;
		b.at(1) = 0xDF;
		b.at(0) = 0x73;

		number = 0xF880DF73;

		a.bitwiseOr(b);
		EASSERT(a.at(0) == 0x7B)
		EASSERT(a.at(1) == 0xDF)
		EASSERT(a.at(2) == 0xFC)
		EASSERT(a.at(3) == 0xFA)

		a.at(3) = 0x9A;
		a.at(2) = 0xFC;
		a.at(1) = 0xCC;
		a.at(0) = 0x7B;

		a.bitwiseOr(number);
		EASSERT(a.at(0) == 0x7B)
		EASSERT(a.at(1) == 0xDF)
		EASSERT(a.at(2) == 0xFC)
		EASSERT(a.at(3) == 0xFA)

		// bitwiseXor

		a.at(3) = 0x9A;
		a.at(2) = 0xFC;
		a.at(1) = 0xCC;
		a.at(0) = 0x7B;

		b.at(3) = 0xF8;
		b.at(2) = 0x80;
		b.at(1) = 0xDF;
		b.at(0) = 0x73;

		number = 0xF880DF73;

		a.bitwiseXor(b);
		EASSERT(a.at(0) == 0x08)
		EASSERT(a.at(1) == 0x13)
		EASSERT(a.at(2) == 0x7C)
		EASSERT(a.at(3) == 0x62)

		a.at(3) = 0x9A;
		a.at(2) = 0xFC;
		a.at(1) = 0xCC;
		a.at(0) = 0x7B;

		a.bitwiseXor(number);

		EASSERT(a.at(0) == 0x08)
		EASSERT(a.at(1) == 0x13)
		EASSERT(a.at(2) == 0x7C)
		EASSERT(a.at(3) == 0x62)
	}
	catch(EAssertionException &)
	{
		success = false;
	}
	catch(EOutOfBoundsException &e)
	{
		EDIE_LOGIC(e)
	}

	// Print out our results.
	if(success)
		std::cout << "[ OK ]\n";
	else
		std::cout << "[FAIL]\n";
}
#endif

/*!
 * This is a utility function, which returns the minimum length of a bitstring
 *in BYTES in order to
 * accomadate the given number of BITS.
 *
 * \param b The number of bits we need to accomadate.
 * \return The number of bytes required.
 */
std::size_t EByteArray::getMinimumByteLength(std::size_t b)
{
	return ((b + (8 - (b % 8))) / 8);
}

/*!
 * This is our default constructor, which initializes a new QByteArray object of
 *the given length
 * (in BYTES), using the given fill policy to determine its initial value. Note
 *that fill policies
 * including preserve are treated the same as their non-preserve counterparts,
 *since it doesn't make
 * since to preserve old data when initializing a new object.
 *
 * \param l The length of our new bitstring, in BYTES.
 * \param p The policy to use while populating the new bitstring.
 */
EByteArray::EByteArray(std::size_t l, EByteArray::FillPolicy p)
{
	// Initialize our data list depending on the FillPolicy we were given.
	switch(p)
	{
	case EByteArray::Set:
	case EByteArray::PreserveSet:
		setSize(l);
		setBits();
		break;

	case EByteArray::Clear:
	case EByteArray::PreserveClear:
		setSize(l);
		clearBits();
		break;
	};
}

/*!
 * This is our default destructor, which cleans up & destroys our object.
 */
EByteArray::~EByteArray()
{
}

/*!
 * This function tests if our value is equal to that of the given other byte
 *array.
 *
 * \param o The array to compare ourself to.
 * \return True if we are equal to o, or false otherwise.
 */
bool EByteArray::operator==(const EByteArray &o) const
{
	return (compare(o) == 0);
}

/*!
 * This function tests if our value is less than that of the given other byte
 *array.
 *
 * \param o The array to compare ourself to.
 * \return True if we are less than o, or false otherwise.
 */
bool EByteArray::operator<(const EByteArray &o) const
{
	return (compare(o) < 0);
}

/*!
 * This function tests if our value is less than or equal to that of the given
 *other byte array.
 *
 * \param o The array to compare ourself to.
 * \return True if we are less than or equal to o, or false otherwise.
 */
bool EByteArray::operator<=(const EByteArray &o) const
{
	return (compare(o) <= 0);
}

/*!
 * This function tests if our value is greater than that of the given other byte
 *array.
 *
 * \param o The array to compare ourself to.
 * \return True if we are greater than o, or false otherwise.
 */
bool EByteArray::operator>(const EByteArray &o) const
{
	return (compare(o) > 0);
}

/*!
 * This function tests if our value is greater than or equal to that of the
 *given other byte array.
 *
 * \param o The array to compare ourself to.
 * \return True if we are greater than or equal to o, or false otherwise.
 */
bool EByteArray::operator>=(const EByteArray &o) const
{
	return (compare(o) >= 0);
}

/*!
 * This is a convenience function which returns the size of our bitstring in
 *BITS. It is equivalent
 * to multiplying the return value of size() by 8.
 *
 * \return The size of our bitstring in bits.
 */
std::size_t EByteArray::bitSize() const
{
	return (getSize() * 8);
}

/*!
 * This function resizes our bitstring to the given length (in BYTES), filling
 *in the new space according to a
 * specified fill policy. Note that policies of "Clear" and "Set" will OVERRIDE
 *existing data with all 0's or all
 * 1's, repsectively, whereas the Preserve policies will maintain existing data,
 *only filling in the new space.
 *
 * Note that setSize() will achieve more or less the same thing, but this
 *function provides more granularity with
 * the new bits/bytes via our FillPolicy parameter.
 *
 * \param n The new length of our bitstring.
 * \param p The policy to use while populating new space.
 */
void EByteArray::resize(std::size_t n, EByteArray::FillPolicy p)
{
	EByteArray a(*this);

	try
	{
		setSize(n);

		if(p == EByteArray::Set)
		{
			setBits();
			return;
		}
		else if(p == EByteArray::Clear)
		{
			clearBits();
			return;
		}
		else
		{
			for(std::size_t i = 0; i < n; i++)
			{
				if(i < a.getSize())
					set(i, a.at(i));
				else
				{
					if(p == EByteArray::PreserveSet)
						set(i, 0xFF);
					else
						set(i, 0x00);
				}
			}
		}
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This function returns whether or not the bit at the given BIT OFFSET is set
 *or not.
 *
 * \param i The offset of the desired bit.
 * \return True if the specified bit is set, or false otherwise.
 */
bool EByteArray::bitAt(std::size_t i) const
{
	byte mask = 1;
	mask <<= relativeBitOffset(i);

	return ((at(byteOffset(i)) & mask) > 0);
}

/*!
 * This function sets whether or not the bit at the given BIT OFFSET is set.
 *
 * \param i The offset of the desired bit.
 * \param v Whether or not the specified bit should be set to "1" or not.
 */
void EByteArray::setBitAt(std::size_t i, bool v)
{
	byte mask = 1;
	mask <<= relativeBitOffset(i);

	if(v)
		at(byteOffset(i)) |= mask;
	else
		at(byteOffset(i)) &= (~mask);
}

/*!
 * This function flips the state of the bit at the given BIT OFFSET in our
 *bitstring. That is,
 * a "1" bit will become "0," and a "0" bit will become "1."
 *
 * \param i The offset of the desired bit.
 */
void EByteArray::flipBitAt(std::size_t i)
{
	byte mask = 1;
	mask <<= relativeBitOffset(i);

	at(byteOffset(i)) ^= mask;
}

/*!
 * This is a convenience function that clears all of the bits in our bitstring
 * (i.e., it
 * sets all bits to 0).
 */
void EByteArray::clearBits()
{
	try
	{
		for(std::size_t i = 0; i < getSize(); ++i)
			at(i) = 0;
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This is a convenience function that sets all of the bits in our bitstring
 * (i.e., it
 * sets all bits to 1).
 */
void EByteArray::setBits()
{
	try
	{
		for(std::size_t i = 0; i < getSize(); i++)
			at(i) = 0xFF;
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This function returns the total number of "1" bits in our byte array - i.e.,
 *its population.
 *
 * \return The number of "1" bits.
 */
std::size_t EByteArray::population() const
{
	std::size_t pop = 0;

	try
	{
		for(std::size_t i = 0; i < getSize(); ++i)
			pop += static_cast<std::size_t>(EBitwise::opop(at(i)));
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}

	return pop;
}

/*!
 * This function does a logical left-shift of our bitstring by a specified
 * number of places. Note that, just like the left shift operator on primitive
 * types, new bits shifted in on the right will be set to 0.
 *
 * \param n The number of places to left-shift our bitstring.
 */
void EByteArray::leftShift(std::size_t n)
{
	bool hA = false, hB;

	try
	{
		// If our bitstring is empty, just return.
		if(getSize() == 0)
			return;

		// If we're shifting the whole thing, just clear.
		if(n >= bitSize())
		{
			clearBits();
			return;
		}

		// Shift whole bytes first, if we can.
		while(n >= 8)
		{
			for(std::size_t i = (getSize() - 1); i > 0; i--)
				at(i) = at(i - 1);

			at(0) = 0;

			n -= 8;
		}

		// Shift the remaining distance.
		for(std::size_t i = 0; i < n; i++)
		{
			for(std::size_t j = 0; j < getSize(); j++)
			{
				hB = (at(j) & (1 << 7)) > 0;
				at(j) <<= 1;

				if(j > 0)
					at(j) |= static_cast<byte>(hA);

				hA = hB;
			}
		}
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This function does a logical left rotation of our bitstring by a specified
 * number of places. This is similar to a logical left shift, except bits that
 * are ejected off the left side of the bitstring are then carried back to the
 * front (at the right).
 *
 * \param n The number of places to left-rotate our bitstring.
 */
void EByteArray::leftRotate(std::size_t n)
{
	// v <<< n = (v << n) | (v >> (bits - n))

	EByteArray b(*this);

	n %= bitSize();

	leftShift(n);
	b.rightShift(bitSize() - n);
	bitwiseOr(b);
}

/*!
 * This function does a logical right shift of our bitstring by a specified
 * number of places. Note that, just like the right shift operator on primitive
 * types, new bits shifted in on the left will be set to 0.
 *
 * \param n The number of places to right-shift our bitstring.
 */
void EByteArray::rightShift(std::size_t n)
{
	bool hA = false, hB;

	try
	{
		// If our bitstring is empty, just return.
		if(getSize() == 0)
			return;

		// If we're shifting the whole thing, just clear.
		if(n >= bitSize())
		{
			clearBits();
			return;
		}

		// Shift whole bytes first, if we can.
		while(n >= 8)
		{
			for(std::size_t i = 0; i < (getSize() - 1); i++)
				at(i) = at(i + 1);

			at(getSize() - 1) = 0;

			n -= 8;
		}

		// Shift the remaining distance.
		for(std::size_t i = 0; i < n; i++)
		{
			for(std::size_t j = getSize() - 1;; j--)
			{
				hB = (at(j) & 1) > 0;
				at(j) >>= 1;

				if(j < (getSize() - 1))
					at(j) |= (static_cast<byte>(hA) << 7);

				hA = hB;

				if(j == 0)
					break;
			}
		}
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This function does a logical left rotation of our bitstring by a specified
 *number of places. This is similar
 * to a logical left shift, except bits that are ejected off the left side of
 *the bitstring are then carried back
 * to the front (at the right).
 *
 * \param n The number of places to left-rotate our bitstring.
 */
void EByteArray::rightRotate(std::size_t n)
{
	// v >>> n = (v >> n) | (v << (bits - n))

	EByteArray b(*this);

	n %= bitSize();

	rightShift(n);
	b.leftShift(bitSize() - n);
	bitwiseOr(b);
}

/*!
 * This function sets our object's value to its logical logical complement. That
 * is, all "1" bits are flipped to
 * "0," and all "0" bits are flipped to "1."
 */
void EByteArray::bitwiseComplement()
{
	try
	{
		for(std::size_t i = 0; i < getSize(); ++i)
			at(i) = ~at(i);
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This function sets our value to the logical AND of our current value, and the
 *value of the given other object. This
 * operation is done byte-by-byte. If the other object is SMALLER than our
 *object by n bytes, then the n high bytes in
 * our object are not modified, and, similarly, if the other object is LARGER
 *than our object by n bytes, then the n high
 * bytes in the other object are simply ignored.
 *
 * \param o The other bitstring with which we will perform a logical AND.
 */
void EByteArray::bitwiseAnd(const EByteArray &o)
{
	try
	{
		std::size_t mSize =
		        o.getSize() > getSize() ? getSize() : o.getSize();
		for(std::size_t i = 0; i < mSize; ++i)
			at(i) &= o.at(i);
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This function sets our value to the logical OR of our current value, and the
 *value of the given other object. This
 * operation is done byte-by-byte. If the other object is SMALLER than our
 *object by n bytes, then the n high bytes
 * in our object are not modified, and, similarly, if the other object is LARGER
 *than our object by n bytes, then the
 * n high bytes in the other object are simply ignored.
 *
 * \param o The other bitstring with which we will perform a logical OR.
 */
void EByteArray::bitwiseOr(const EByteArray &o)
{
	try
	{
		std::size_t mSize =
		        o.getSize() > getSize() ? getSize() : o.getSize();
		for(std::size_t i = 0; i < mSize; ++i)
			at(i) |= o.at(i);
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This function sets our value to the logical XOR (eXclusive OR) of our current
 *value, and the value of the given other
 * object. This operation is done byte-by-byte. If the other object is SMALLER
 *than our object by n bytes, then the n
 * high bytes in our object are not modified and, similarly, if the other object
 *is LARGER than our object by n bytes,
 * then the n high bytes in the other object are simply ignored.
 *
 * \param o The other bitstring with which we will perform a logical XOR.
 */
void EByteArray::bitwiseXor(const EByteArray &o)
{
	try
	{
		std::size_t mSize =
		        o.getSize() > getSize() ? getSize() : o.getSize();
		for(std::size_t i = 0; i < mSize; ++i)
			at(i) ^= o.at(i);
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This function is similar to the other implementation of bitwiseAnd(), except
 * it takes a 32-bit unsigned integer instead of a second bitstring. It does
 * the same byte-by-byte logical AND operation, starting with the byte at the
 * given left-shift offset.
 *
 * \param v The integer with which we will perform a logical AND.
 * \param lS The number of BYTES to left-shift the value before and'ing.
 */
void EByteArray::bitwiseAnd(uint32_t v, std::size_t lS)
{
	try
	{
		for(std::size_t i = 0; i < 4; i++)
		{
			at(lS++) &= static_cast<byte>(v);
			v >>= 8;
		}
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This function is similar to the other implementation of bitwiseOr(), except
 * it takes a 32-bit unsigned integer instead of a second bitstring. It does
 * the same byte-by-byte logical OR operation, starting with the byte at the
 * given left-shift offset.
 *
 * \param v The integer with which we will perform a logical OR.
 * \param lS The number of BYTES to left-shift the value before or'ing.
 */
void EByteArray::bitwiseOr(uint32_t v, std::size_t lS)
{
	try
	{
		for(std::size_t i = 0; i < 4; i++)
		{
			at(lS++) |= static_cast<byte>(v);
			v >>= 8;
		}
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This function is similar to the other implementation of bitwiseXor(), except
 * that it takes a 32-bit unsigned integer instead of a second bitstring. It
 * does the same byte-by-byte logical XOR operation, starting with the byte at
 * the given left-shift offset.
 *
 * \param v The integer with which we will perform a logical XOR.
 * \param lS The number of BYTES to left-shift the value before xor'ing.
 */
void EByteArray::bitwiseXor(uint32_t v, std::size_t lS)
{
	try
	{
		for(std::size_t i = 0; i < 4; i++)
		{
			at(lS++) ^= static_cast<byte>(v);
			v >>= 8;
		}
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This function provides our class with a three-way-compare function against
 * another byte array. This function returns -1 if this < o, 0 if this == o,
 * and 1 if this > o.
 *
 * \param o The byte array to compare ourself to.
 * \return The comparison between this array and the other.
 */
int EByteArray::compare(const EByteArray &o) const
{
	try
	{
		for(std::size_t i = 0; i < getSize(); ++i)
		{
			if(at(i) < o.at(i))
				return -1;
			else if(at(i) > o.at(i))
				return 1;
		}
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}

	return 0;
}

/*!
 * This is a utility function, which returns the ABOLUTE BIT offset version of
 *the given
 * byte / relative bit offset.
 *
 * \param by The byte offset of the desired bit.
 * \param bi The bit offset of the desired bit, relative to the byte.
 * \return The absolute bit offset of the given byte/bit offset.
 */
std::size_t EByteArray::bitOffset(std::size_t by, std::size_t bi) const
{
	return ((by * 8) + bi);
}

/*!
 * This is a utility function, which returns the BYTE offset the given BIT
 * OFFSET lies in.
 *
 * \param i The offset of a BIT.
 * \return The offset of the BYTE the specified BIT is in.
 */
std::size_t EByteArray::byteOffset(std::size_t i) const
{
	return (i / 8);
}

/*!
 * This is a utility function, which returns the RELATIVE bit offset of the
 * given ABSOLUTE bit offset.
 *
 * \param i The ABSOLUTE offset of a bit.
 * \return The offset of the bit relative to the beginning of the byte it is in.
 */
std::size_t EByteArray::relativeBitOffset(std::size_t i) const
{
	return (i % 8);
}

/*!
 * This is a utility function, which checks whether our bitstring has AT LEAST
 * one "1" bit in it.
 *
 * \return True if we have at least one bit set, or false otherwise.
 */
bool EByteArray::hasBitsSet() const
{
	try
	{
		for(std::size_t i = 0; i < getSize(); i++)
			if(at(i) > 0)
				return true;
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}

	return false;
}

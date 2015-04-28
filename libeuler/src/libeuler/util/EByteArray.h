/*
 * euler - A collection of ProjectEuler solutions, and supporting libraries and
 *tools.
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

#ifndef INCLUDE_LIBEULER_UTIL_BYTE_ARRAY_H
#define INCLUDE_LIBEULER_UTIL_BYTE_ARRAY_H

#include <cstdint>

#include "libeuler/util/EArray.h"
#include "libeuler/EExceptions.h"

// Typedef 'byte' for EByteArray.
typedef uint8_t byte;

/*!
 * \brief This class represents a string of bits.
 *
 * It can be operated on just like any smaller container like an int or a long,
 *but it can be
 * an arbitrary amount of bytes in length.
 */
class EByteArray : public EArray<byte>
{
public:
	/*!
	 * This enum defines the policy that would be used when filling-in new
	 *space in a
	 * bitstring object, for instance, while resizing or while initializing
	 *a new object.
	 *
	 * "Preserve" means that old data (e.g., while resizing) will be
	 *preserved, "Set"
	 * means that bits will be set to "1" and "Clear" means bits will be set
	 *to "0."
	 */
	enum FillPolicy
	{
		Set,
		Clear,
		PreserveSet,
		PreserveClear
	};

#ifdef LIBEULER_DEBUG
	static void doTestSuite();
#endif

	static int getMinimumByteLength(int b);

	EByteArray(int l = 0, EByteArray::FillPolicy p = EByteArray::Clear);
	virtual ~EByteArray();

	bool operator==(const EByteArray &o) const;
	bool operator<(const EByteArray &o) const;
	bool operator<=(const EByteArray &o) const;
	bool operator>(const EByteArray &o) const;
	bool operator>=(const EByteArray &o) const;

	int bitSize() const;
	void resize(int n, EByteArray::FillPolicy p);

	bool bitAt(int i) const throw(EOutOfBoundsException &);
	void setBitAt(int i, bool v) throw(EOutOfBoundsException &);

	void flipBitAt(int i) throw(EOutOfBoundsException &);

	void clearBits();
	void setBits();
	int population() const;

	void leftShift(int n);
	void leftRotate(int n);
	void rightShift(int n);
	void rightRotate(int n);

	void bitwiseComplement();

	void bitwiseAnd(const EByteArray &o);
	void bitwiseOr(const EByteArray &o);
	void bitwiseXor(const EByteArray &o);

	void bitwiseAnd(uint32_t v, int lS = 0);
	void bitwiseOr(uint32_t v, int lS = 0);
	void bitwiseXor(uint32_t v, int lS = 0);

private:
	int compare(const EByteArray &o) const;

	int bitOffset(int by, int bi) const;
	int byteOffset(int i) const;
	int relativeBitOffset(int i) const;

	bool hasBitsSet() const;
};

#endif

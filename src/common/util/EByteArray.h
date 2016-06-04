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

#ifndef INCLUDE_LIBEULER_UTIL_BYTE_ARRAY_H
#define INCLUDE_LIBEULER_UTIL_BYTE_ARRAY_H

#include <cstddef>
#include <cstdint>

#include "common/EExceptions.h"
#include "common/util/EArray.h"

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

	static std::size_t getMinimumByteLength(std::size_t b);

	EByteArray(std::size_t l = 0,
	           EByteArray::FillPolicy p = EByteArray::Clear);

	EByteArray(EByteArray const &) = default;
	EByteArray(EByteArray &&) = default;

	virtual ~EByteArray();

	EByteArray &operator=(EByteArray const &) = default;
	EByteArray &operator=(EByteArray &&) = default;

	bool operator==(const EByteArray &o) const;
	bool operator<(const EByteArray &o) const;
	bool operator<=(const EByteArray &o) const;
	bool operator>(const EByteArray &o) const;
	bool operator>=(const EByteArray &o) const;

	std::size_t bitSize() const;
	void resize(std::size_t n, EByteArray::FillPolicy p);

	bool bitAt(std::size_t i) const;
	void setBitAt(std::size_t i, bool v);

	void flipBitAt(std::size_t i);

	void clearBits();
	void setBits();
	std::size_t population() const;

	void leftShift(std::size_t n);
	void leftRotate(std::size_t n);
	void rightShift(std::size_t n);
	void rightRotate(std::size_t n);

	void bitwiseComplement();

	void bitwiseAnd(const EByteArray &o);
	void bitwiseOr(const EByteArray &o);
	void bitwiseXor(const EByteArray &o);

	void bitwiseAnd(uint32_t v, std::size_t lS = 0);
	void bitwiseOr(uint32_t v, std::size_t lS = 0);
	void bitwiseXor(uint32_t v, std::size_t lS = 0);

private:
	int compare(const EByteArray &o) const;

	std::size_t bitOffset(std::size_t by, std::size_t bi) const;
	std::size_t byteOffset(std::size_t i) const;
	std::size_t relativeBitOffset(std::size_t i) const;

	bool hasBitsSet() const;
};

#endif

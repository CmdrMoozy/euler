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

#ifndef common_structs_BitArray_HPP
#define common_structs_BitArray_HPP

#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <ostream>
#include <type_traits>

#include <boost/optional/optional.hpp>

namespace euler
{
namespace structs
{
enum class BitArrayFillPolicy
{
	SET,
	CLEAR,
	PRESERVE_SET,
	PRESERVE_CLEAR
};

class BitArray
{
public:
	template <typename T> static BitArray fromValue(T value);

	typedef uint64_t chunk_type;
	static constexpr std::size_t CHUNK_BIT = sizeof(chunk_type) * CHAR_BIT;

	BitArray(std::size_t s = 0,
	         BitArrayFillPolicy p = BitArrayFillPolicy::CLEAR);

	BitArray(BitArray const &o);
	BitArray &operator=(BitArray const &o);

	BitArray(BitArray &&) = default;
	BitArray &operator=(BitArray &&) = default;

	~BitArray() = default;

	int compare(BitArray const &o) const;

	bool operator==(BitArray const &o) const;
	bool operator!=(BitArray const &o) const;
	bool operator<(BitArray const &o) const;
	bool operator<=(BitArray const &o) const;
	bool operator>(BitArray const &o) const;
	bool operator>=(BitArray const &o) const;

	std::size_t size() const;
	std::size_t byteSize() const;
	void resize(std::size_t s, BitArrayFillPolicy p);
	std::size_t capacity() const;
	std::size_t byteCapacity() const;

	/*!
	 * Returns the chunk at the given position, along with a mask
	 * indicating which bits in the chunk are actually members of this
	 * bit array.
	 *
	 * If the given position is out of bounds, an undefined value is
	 * returned with a zero mask (indicating that it should be ignored).
	 *
	 * \param p The position of the chunk to retrieve.
	 * \return A pair containing the chunk and its mask.
	 */
	std::pair<chunk_type, chunk_type> chunkAt(std::size_t p) const;

	/*!
	 * Access the bit at the given position, and return its value. Unlike
	 * test() or at(), this function has no bounds-checking, so passing a
	 * position that is out of bounds results in undefined behavior.
	 *
	 * Note that, unlike other standard containers, this function returns
	 * a copy instead of a reference. Set() must be used instead to modify
	 * bits.
	 *
	 * \param p The position of the bit to access.
	 * \return True if the bit was set, or false otherwise.
	 */
	bool operator[](std::size_t p) const;

	/*!
	 * Access the bit at the given position, and return its value. If the
	 * given position is out of bounds, return the given default value. If
	 * not default value is specified, throw an exception instead.
	 *
	 * \param p The position of the bit to access.
	 * \param defaultValue The default value if p is out of bounds.
	 * \return True if the bit was set, or false otherwise.
	 */
	bool test(std::size_t p,
	          boost::optional<bool> defaultValue = boost::none) const;

	/*!
	 * A synonym for test().
	 *
	 * \param p The position of the bit to access.
	 * \param defaultValue The default value if p is out of bounds.
	 * \return True if the bit was set, or false otherwise.
	 */
	bool at(std::size_t p,
	        boost::optional<bool> defaultValue = boost::none) const;

	bool all() const;
	bool any() const;
	bool none() const;
	std::size_t count() const;

	BitArray &set();
	BitArray &set(std::size_t p, bool v = true);
	BitArray &reset();
	BitArray &reset(std::size_t p);
	BitArray &flip();
	BitArray &flip(std::size_t p);

	BitArray operator<<(std::size_t n) const;
	BitArray &operator<<=(std::size_t n);
	BitArray operator>>(std::size_t n) const;
	BitArray &operator>>=(std::size_t n);

	BitArray &leftRotate(std::size_t n);
	BitArray &rightRotate(std::size_t n);

	BitArray operator&(BitArray const &o) const;
	BitArray &operator&=(BitArray const &o);
	BitArray operator|(BitArray const &o) const;
	BitArray &operator|=(BitArray const &o);
	BitArray operator^(BitArray const &o) const;
	BitArray &operator^=(BitArray const &o);
	BitArray operator~() const;

	std::string to_string() const;
	unsigned long to_ulong() const;
	unsigned long long to_ullong() const;
	uintmax_t to_uintmax() const;

private:
	std::size_t bitSize;
	std::size_t chunkSize;
	std::unique_ptr<chunk_type, std::function<void(chunk_type *)>> data;
};

template <typename T> BitArray BitArray::fromValue(T value)
{
	using value_type = typename std::decay<T>::type;
	BitArray a(sizeof(value_type) * CHAR_BIT);
	uint8_t const *srcFirst = reinterpret_cast<uint8_t const *>(&value);
	uint8_t const *srcLast = srcFirst + sizeof(value_type);
	std::copy(srcFirst, srcLast, reinterpret_cast<uint8_t *>(a.data.get()));
	return a;
}

std::ostream &operator<<(std::ostream &os, BitArray const &ba);
}
}

#endif

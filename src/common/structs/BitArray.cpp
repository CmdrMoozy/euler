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

#include "BitArray.hpp"

#include <cassert>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <utility>

#include <bdrck/algorithm/String.hpp>

#include "common/math/Math.hpp"
#include "common/util/Bitwise.hpp"

namespace
{
void arrayDeleter(uint64_t *a)
{
	if(a != nullptr)
		delete[] a;
}

std::pair<std::size_t, std::size_t> bitToChunkIndex(std::size_t p)
{
	return euler::math::divide(p, euler::structs::BitArray::CHUNK_BIT);
}

std::size_t getMinimumChunkSize(std::size_t s)
{
	if(s == 0)
		return 0;
	return bitToChunkIndex(s - 1).first + 1;
}

bool getRaw(euler::structs::BitArray::chunk_type const *data, std::size_t p)
{
	auto index = bitToChunkIndex(p);
	auto mask = euler::structs::BitArray::chunk_type(1) << index.second;
	return data[index.first] & mask;
}

void setRaw(euler::structs::BitArray::chunk_type *data, std::size_t p, bool v)
{
	auto index = bitToChunkIndex(p);
	auto mask = euler::structs::BitArray::chunk_type(1) << index.second;
	if(v)
		data[index.first] |= mask;
	else
		data[index.first] &= ~mask;
}

/*!
 * Shift the chunks in the given chunk array left by n places. Fill in n
 * chunks with 0's at the bottom of the chunk array.
 *
 * \param data The chunk array to shift.
 * \param l The length of the chunk array.
 * \param n The number of places (chunks) to shift left.
 */
void shiftChunksLeft(euler::structs::BitArray::chunk_type *data, std::size_t l,
                     std::size_t n)
{
	n = std::min(n, l);
	// Compute the number of chunks that will be shifted off the left end.
	std::size_t shiftedOff = n + n - std::min(l, n + n);
	// Setup the pointers to where the chunk copies will occur.
	auto const *srcFirst = data;
	auto const *srcLast = data + n - shiftedOff;
	auto *dstLast = data + std::min(l, n + n);
	// Copy chunks starting from the end of the chunk array.
	std::copy_backward(srcFirst, srcLast, dstLast);
	// Fill in the bottom n chunks with 0's.
	std::fill(data, data + n, 0);
}

/*!
 * Shift the chunks in the given chunk array right by n places. Fill in n
 * chunks with 0's at the top of the chunk array.
 *
 * \param data The chunk array to shift.
 * \param l The length of the chunk array.
 * \param n The number of places (chunks) to shift right.
 */
void shiftChunksRight(euler::structs::BitArray::chunk_type *data, std::size_t l,
                      std::size_t n)
{
	n = std::min(n, l);
	// Compute the number of chunks that will be shifted off the right end.
	std::size_t shiftedOff = n + n - std::min(l, n + n);
	// Setup the pointers to where the chunk copies will occur.
	auto const *srcFirst = data + l - n + shiftedOff;
	auto const *srcLast = data + l;
	auto *dstFirst = data;
	// Copy chunks starting from the front of the chunk array.
	std::copy(srcFirst, srcLast, dstFirst);
	// Fill in the top n chunks with 0's.
	std::fill(data + l - n, data + l, 0);
}
}

namespace euler
{
namespace structs
{
BitArray::BitArray(std::size_t s, BitArrayFillPolicy p)
        : bitSize(0), chunkSize(0), data(nullptr, arrayDeleter)
{
	resize(s, p);
}

BitArray::BitArray(BitArray const &o)
        : bitSize(0), chunkSize(0), data(nullptr, arrayDeleter)
{
	*this = o;
}

BitArray &BitArray::operator=(BitArray const &o)
{
	if(this == &o)
		return *this;
	bitSize = o.bitSize;
	chunkSize = o.chunkSize;
	data.reset(new chunk_type[chunkSize]);
	std::copy(o.data.get(), o.data.get() + o.chunkSize, data.get());
	return *this;
}

int BitArray::compare(BitArray const &o) const
{
	std::size_t maxSize = std::max(size(), o.size());
	for(std::size_t offFromEnd = 0; offFromEnd < maxSize; ++offFromEnd)
	{
		std::size_t p = maxSize - 1 - offFromEnd;
		if(test(p, false) && !o.test(p, false))
			return 1;
		else if(!test(p, false) && o.test(p, false))
			return -1;
	}
	return 0;
}

bool BitArray::operator==(BitArray const &o) const
{
	return compare(o) == 0;
}

bool BitArray::operator!=(BitArray const &o) const
{
	return !(*this == o);
}

bool BitArray::operator<(BitArray const &o) const
{
	return compare(o) < 0;
}

bool BitArray::operator<=(BitArray const &o) const
{
	return compare(o) <= 0;
}

bool BitArray::operator>(BitArray const &o) const
{
	return compare(o) > 0;
}

bool BitArray::operator>=(BitArray const &o) const
{
	return compare(o) >= 0;
}

std::size_t BitArray::size() const
{
	return bitSize;
}

std::size_t BitArray::byteSize() const
{
	assert(bitSize % 8 == 0);
	return bitSize / 8;
}

void BitArray::resize(std::size_t s, BitArrayFillPolicy p)
{
	if(s == 0)
	{
		bitSize = 0;
		chunkSize = 0;
		data.reset();
		return;
	}

	auto newChunkSize = getMinimumChunkSize(s);
	decltype(data) newData(new chunk_type[newChunkSize], arrayDeleter);

	chunk_type fill(0);
	if(p == BitArrayFillPolicy::SET ||
	   p == BitArrayFillPolicy::PRESERVE_SET)
	{
		fill = ~fill;
	}

	for(std::size_t i = 0; i < newChunkSize; ++i)
	{
		chunk_type v = fill;
		if(p == BitArrayFillPolicy::PRESERVE_SET ||
		   p == BitArrayFillPolicy::PRESERVE_CLEAR)
		{
			auto chunk = chunkAt(i);
			v = (chunk.first & chunk.second) |
			    (fill & ~chunk.second);
		}
		newData.get()[i] = v;
	}

	bitSize = s;
	chunkSize = newChunkSize;
	data = std::move(newData);
}

std::size_t BitArray::capacity() const
{
	return chunkSize * CHUNK_BIT;
}

std::size_t BitArray::byteCapacity() const
{
	return capacity() / 8;
}

std::pair<BitArray::chunk_type, BitArray::chunk_type>
BitArray::chunkAt(std::size_t p) const
{
	if(p >= chunkSize)
		return std::make_pair<chunk_type, chunk_type>(0, 0);

	chunk_type chunk = data.get()[p];
	chunk_type mask = ~chunk_type(0);

	// If this is the last chunk, compute a mask.
	if(p == chunkSize - 1)
	{
		std::size_t lastChunkBits = bitSize % CHUNK_BIT;
		if(lastChunkBits == 0)
			lastChunkBits = CHUNK_BIT;
		mask = mask << (CHUNK_BIT - lastChunkBits) >>
		       (CHUNK_BIT - lastChunkBits);
	}

	return std::make_pair(chunk, mask);
}

bool BitArray::operator[](std::size_t p) const
{
	return getRaw(data.get(), p);
}

bool BitArray::test(std::size_t p, boost::optional<bool> defaultValue) const
{
	if(p >= bitSize)
	{
		if(!!defaultValue)
		{
			return *defaultValue;
		}
		else
		{
			throw std::runtime_error(
			        "BitArray index is out of bounds.");
		}
	}
	return (*this)[p];
}

bool BitArray::at(std::size_t p, boost::optional<bool> defaultValue) const
{
	return test(p, defaultValue);
}

bool BitArray::all() const
{
	constexpr chunk_type ALL_CHUNK = ~chunk_type(0);
	for(std::size_t i = 0; i < chunkSize; ++i)
	{
		auto chunk = chunkAt(i);
		if((chunk.first & chunk.second) != (ALL_CHUNK & chunk.second))
			return false;
	}
	return true;
}

bool BitArray::any() const
{
	return !none();
}

bool BitArray::none() const
{
	for(std::size_t i = 0; i < chunkSize; ++i)
	{
		auto chunk = chunkAt(i);
		if((chunk.first & chunk.second) != chunk_type(0))
			return false;
	}
	return true;
}

std::size_t BitArray::count() const
{
	std::size_t c = 0;
	for(std::size_t i = 0; i < chunkSize; ++i)
		c += euler::util::bitwise::opop(data.get()[i]);
	return c;
}

BitArray &BitArray::set()
{
	for(std::size_t i = 0; i < chunkSize; ++i)
		data.get()[i] = ~chunk_type(0);
	return *this;
}

BitArray &BitArray::set(std::size_t p, bool v)
{
	setRaw(data.get(), p, v);
	return *this;
}

BitArray &BitArray::reset()
{
	for(std::size_t i = 0; i < chunkSize; ++i)
		data.get()[i] = chunk_type(0);
	return *this;
}

BitArray &BitArray::reset(std::size_t p)
{
	return set(p, false);
}

BitArray &BitArray::flip()
{
	std::transform(data.get(), data.get() + chunkSize, data.get(),
	               [](chunk_type c) -> chunk_type { return ~c; });
	return *this;
}

BitArray &BitArray::flip(std::size_t p)
{
	auto index = bitToChunkIndex(p);
	chunk_type mask = chunk_type(1) << index.second;
	if(data.get()[index.first] & mask)
		data.get()[index.first] &= ~mask;
	else
		data.get()[index.first] |= mask;
	return *this;
}

BitArray BitArray::operator<<(std::size_t n) const
{
	BitArray a(*this);
	a <<= n;
	return a;
}

BitArray &BitArray::operator<<=(std::size_t n)
{
	// If this array is empty, just return.
	if(size() == 0)
		return *this;

	// If we're shifting the whole thing, just clear.
	if(n >= size())
	{
		reset();
		return *this;
	}

	// Shift as many full chunks as possible first.
	shiftChunksLeft(data.get(), chunkSize, n / CHUNK_BIT);

	// Shift the remaining number of bits left in each chunk.
	std::size_t bitShift = n % CHUNK_BIT;
	for(std::size_t idx = chunkSize - 1; idx > 0; --idx)
	{
		data.get()[idx] <<= bitShift;
		data.get()[idx] |=
		        data.get()[idx - 1] >> (CHUNK_BIT - bitShift);
	}
	data.get()[0] <<= bitShift;

	return *this;
}

BitArray BitArray::operator>>(std::size_t n) const
{
	BitArray a(*this);
	a >>= n;
	return a;
}

BitArray &BitArray::operator>>=(std::size_t n)
{
	// If this array is empty, just return.
	if(size() == 0)
		return *this;

	// If we're shifting the whole thing, just clear.
	if(n >= size())
	{
		reset();
		return *this;
	}

	// Shift as many full chunks as possible first.
	shiftChunksRight(data.get(), chunkSize, n / CHUNK_BIT);

	// Shift the remaining number of bits right in each chunk.
	std::size_t bitShift = n % CHUNK_BIT;
	for(std::size_t idx = 0; idx < (chunkSize - 1); ++idx)
	{
		data.get()[idx] >>= bitShift;
		data.get()[idx] |= data.get()[idx + 1]
		                   << (CHUNK_BIT - bitShift);
	}
	data.get()[chunkSize - 1] >>= bitShift;

	return *this;
}

BitArray &BitArray::leftRotate(std::size_t n)
{
	// v <<< n = (v << n) | (v >> (bits - n))

	BitArray b(*this);
	// Remove any whole multiples of our size (full rotations) from n.
	n %= size();
	*this <<= n;
	b >>= size() - n;
	*this |= b;
	return *this;
}

BitArray &BitArray::rightRotate(std::size_t n)
{
	// v >>> n = (v >> n) | (v << (bits - n))

	BitArray b(*this);
	// Remove any whole multiples of our size (full rotations) from n.
	n %= size();
	*this >>= n;
	b <<= size() - n;
	*this |= b;
	return *this;
}

BitArray BitArray::operator&(BitArray const &o) const
{
	BitArray a(*this);
	a &= o;
	return a;
}

BitArray &BitArray::operator&=(BitArray const &o)
{
	for(std::size_t i = 0; i < chunkSize; ++i)
	{
		data.get()[i] &=
		        i < o.chunkSize ? o.data.get()[i] : chunk_type(0);
	}
	return *this;
}

BitArray BitArray::operator|(BitArray const &o) const
{
	BitArray a(*this);
	a |= o;
	return a;
}

BitArray &BitArray::operator|=(BitArray const &o)
{
	for(std::size_t i = 0; i < chunkSize; ++i)
	{
		data.get()[i] |=
		        i < o.chunkSize ? o.data.get()[i] : chunk_type(0);
	}
	return *this;
}

BitArray BitArray::operator^(BitArray const &o) const
{
	BitArray a(*this);
	a ^= o;
	return a;
}

BitArray &BitArray::operator^=(BitArray const &o)
{
	for(std::size_t i = 0; i < chunkSize; ++i)
	{
		data.get()[i] ^=
		        i < o.chunkSize ? o.data.get()[i] : chunk_type(0);
	}
	return *this;
}

BitArray BitArray::operator~() const
{
	return BitArray(*this).flip();
}

std::string BitArray::to_string() const
{
	std::ostringstream oss;
	for(std::size_t idx = 0; idx < size(); ++idx)
		oss << ((*this)[idx] ? '1' : '0');
	return oss.str();
}

unsigned long BitArray::to_ulong() const
{
	return static_cast<unsigned long>(to_uintmax());
}

unsigned long long BitArray::to_ullong() const
{
	return static_cast<unsigned long long>(to_uintmax());
}

uintmax_t BitArray::to_uintmax() const
{
	uintmax_t value(0);

	// Build a vector of chunk values which will make up the uintmax_t.
	constexpr std::size_t floorChunks =
	        sizeof(uintmax_t) / sizeof(chunk_type);
	constexpr std::size_t byteRemainder =
	        sizeof(uintmax_t) % sizeof(chunk_type);
	constexpr std::size_t totalChunkCount =
	        floorChunks + (byteRemainder > 0 ? 1 : 0);
	std::size_t chunkCount = std::min(totalChunkCount, chunkSize);
	std::vector<chunk_type> chunks(chunkCount, 0);
	for(std::size_t i = 0; i < chunkCount; ++i)
	{
		auto chunk = chunkAt(i);
		chunks[i] = chunk.first & chunk.second;
	}

	// Copy the chunk data from this vector to the uintmax_t.
	uint8_t const *srcFirst =
	        reinterpret_cast<uint8_t const *>(chunks.data());
	std::size_t byteLength =
	        std::min(sizeof(uintmax_t), chunkSize * sizeof(chunk_type));
	uint8_t const *srcLast = srcFirst + byteLength;
	uint8_t *dstFirst = reinterpret_cast<uint8_t *>(&value);
	std::copy(srcFirst, srcLast, dstFirst);

	return value;
}

std::ostream &operator<<(std::ostream &os, BitArray const &ba)
{
	os << ba.to_string();
	return os;
}
}
}

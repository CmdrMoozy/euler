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

#include "Hash.h"

#include <cmath>
#include <cstring>
#include <random>
#include <stdexcept>
#include <type_traits>

#include "libeuler/util/EBitwise.h"

namespace
{
uint32_t getHashSeed()
{
	std::mt19937 mtEngine;
	std::uniform_int_distribution<uint32_t> distribution;
	return distribution(mtEngine);
}

static_assert(std::is_same<uintmax_t, euler::Hash::result_type>::value,
              "This code must be updated if euler::Hash::result_type changes.");

struct SignedIntegralHashImpl
{
	euler::Hash::result_type operator()(const intmax_t &value) const
	{
		return static_cast<euler::Hash::result_type>(value);
	}
};

struct UnsignedIntegralHashImpl
{
	euler::Hash::result_type operator()(const uintmax_t &value) const
	{
		return value;
	}
};

struct FloatingPointHashImpl
{
	euler::Hash::result_type operator()(const long double &value) const
	{
		static_assert(sizeof(euler::Hash::result_type) >=
		                      sizeof(double),
		              "double must fit inside result type.");

		if(!std::isnormal(value))
			throw std::runtime_error("Invalid hash input value.");

		euler::Hash::result_type ret = 0;
		std::memcpy(&ret, &value, sizeof(long double));
		return ret;
	}
};

template <typename T> struct HashImplFunctorWrapper
{
	typedef typename std::conditional<
	        std::is_integral<T>::value,
	        typename std::conditional<std::is_signed<T>::value,
	                                  SignedIntegralHashImpl,
	                                  UnsignedIntegralHashImpl>::type,
	        FloatingPointHashImpl>::type type;
};

template <typename T> euler::Hash::result_type hashImpl(const T &value)
{
	typename HashImplFunctorWrapper<T>::type functor;
	return functor(value);
}

uint64_t murmurMix(uint64_t k)
{
	k ^= k >> 33;
	k *= 0xff51afd7ed558ccdULL;
	k ^= k >> 33;
	k *= 0xc4ceb9fe1a85ec53ULL;
	k ^= k >> 33;
	return k;
}

template <typename Result>
Result murmurHash(const void *data, std::size_t length, uint32_t seed)
{
	unsigned __int128 result;
	void *resultPointer = &result;

	Result ret;
	void *retPointer = &ret;

	const uint8_t *dataBytes = static_cast<const uint8_t *>(data);
	const std::size_t nblocks = length / 16;

	uint64_t h1 = seed;
	uint64_t h2 = seed;

	const uint64_t c1 = 0x87c37b91114253d5ULL;
	const uint64_t c2 = 0x4cf5ad432745937fULL;

	const uint64_t *blocks = static_cast<const uint64_t *>(data);

	for(std::size_t i = 0; i < nblocks; ++i)
	{
		uint64_t k1 = blocks[i * 2 + 0];
		uint64_t k2 = blocks[i * 2 + 1];

		k1 *= c1;
		k1 = EBitwise::rotl64(k1, 31);
		k1 *= c2;
		h1 ^= k1;

		h1 = EBitwise::rotl64(h1, 27);
		h1 += h2;
		h1 = h1 * 5 + 0x52dce729;

		k2 *= c2;
		k2 = EBitwise::rotl64(k2, 33);
		k2 *= c1;
		h2 ^= k2;

		h2 = EBitwise::rotl64(h2, 31);
		h2 += h1;
		h2 = h2 * 5 + 0x38495ab5;
	}

	const uint8_t *tail =
	        static_cast<const uint8_t *>(dataBytes + nblocks * 16);

	uint64_t k1 = 0;
	uint64_t k2 = 0;

	switch(length & 15)
	{
	case 15:
		k2 ^= static_cast<uint64_t>(tail[14]) << 48;
	case 14:
		k2 ^= static_cast<uint64_t>(tail[13]) << 40;
	case 13:
		k2 ^= static_cast<uint64_t>(tail[12]) << 32;
	case 12:
		k2 ^= static_cast<uint64_t>(tail[11]) << 24;
	case 11:
		k2 ^= static_cast<uint64_t>(tail[10]) << 16;
	case 10:
		k2 ^= static_cast<uint64_t>(tail[9]) << 8;
	case 9:
		k2 ^= static_cast<uint64_t>(tail[8]) << 0;
		k2 *= c2;
		k2 = EBitwise::rotl64(k2, 33);
		k2 *= c1;
		h2 ^= k2;

	case 8:
		k1 ^= static_cast<uint64_t>(tail[7]) << 56;
	case 7:
		k1 ^= static_cast<uint64_t>(tail[6]) << 48;
	case 6:
		k1 ^= static_cast<uint64_t>(tail[5]) << 40;
	case 5:
		k1 ^= static_cast<uint64_t>(tail[4]) << 32;
	case 4:
		k1 ^= static_cast<uint64_t>(tail[3]) << 24;
	case 3:
		k1 ^= static_cast<uint64_t>(tail[2]) << 16;
	case 2:
		k1 ^= static_cast<uint64_t>(tail[1]) << 8;
	case 1:
		k1 ^= static_cast<uint64_t>(tail[0]) << 0;
		k1 *= c1;
		k1 = EBitwise::rotl64(k1, 31);
		k1 *= c2;
		h1 ^= k1;
	};

	h1 ^= length;
	h2 ^= length;

	h1 += h2;
	h2 += h1;

	h1 = murmurMix(h1);
	h2 = murmurMix(h2);

	h1 += h2;
	h2 += h1;

	static_cast<uint64_t *>(resultPointer)[0] = h1;
	static_cast<uint64_t *>(resultPointer)[1] = h2;

	const uint8_t *resultBytes =
	        static_cast<const uint8_t *>(resultPointer);
	uint8_t *retBytes = static_cast<uint8_t *>(retPointer);

	for(std::size_t idx = 0; idx < sizeof(Result); ++idx)
		retBytes[idx] = resultBytes[idx % sizeof(unsigned __int128)];

	return ret;
}
}

namespace euler
{
Hash::Hash() : seed(getHashSeed())
{
}

template <> Hash::result_type Hash::operator()(const bool &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const char &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const signed char &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const unsigned char &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const char16_t &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const char32_t &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const wchar_t &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const short &value) const
{
	return hashImpl(value);
}

template <>
Hash::result_type Hash::operator()(const unsigned short &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const int &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const unsigned int &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const long &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const unsigned long &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const long long &value) const
{
	return hashImpl(value);
}

template <>
Hash::result_type Hash::operator()(const unsigned long long &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const float &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const double &value) const
{
	return hashImpl(value);
}

template <> Hash::result_type Hash::operator()(const std::string &value) const
{
	return hashImpl(murmurHash<Hash::result_type>(value.data(),
	                                              value.length(), seed));
}
}

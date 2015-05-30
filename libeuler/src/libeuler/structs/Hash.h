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

#ifndef INCLUDE_LIBEULER_STRUCTS_HASH_H
#define INCLUDE_LIBEULER_STRUCTS_HASH_H

#include <cstdint>
#include <string>

namespace euler
{
struct Hash
{
	typedef uintmax_t result_type;

	const uint32_t seed;

	Hash();

	template <typename T> result_type operator()(const T &value) const;

	template <typename T> result_type operator()(const T *&value) const
	{
		return (*this)(static_cast<uintmax_t>(value));
	}
};

template <> Hash::result_type Hash::operator()(const bool &value) const;

template <> Hash::result_type Hash::operator()(const char &value) const;

template <> Hash::result_type Hash::operator()(const signed char &value) const;

template <>
Hash::result_type Hash::operator()(const unsigned char &value) const;

template <> Hash::result_type Hash::operator()(const char16_t &value) const;

template <> Hash::result_type Hash::operator()(const char32_t &value) const;

template <> Hash::result_type Hash::operator()(const wchar_t &value) const;

template <> Hash::result_type Hash::operator()(const short &value) const;

template <>
Hash::result_type Hash::operator()(const unsigned short &value) const;

template <> Hash::result_type Hash::operator()(const int &value) const;

template <> Hash::result_type Hash::operator()(const unsigned int &value) const;

template <> Hash::result_type Hash::operator()(const long &value) const;

template <>
Hash::result_type Hash::operator()(const unsigned long &value) const;

template <> Hash::result_type Hash::operator()(const long long &value) const;

template <>
Hash::result_type Hash::operator()(const unsigned long long &value) const;

template <> Hash::result_type Hash::operator()(const float &value) const;

template <> Hash::result_type Hash::operator()(const double &value) const;

template <> Hash::result_type Hash::operator()(const std::string &value) const;
}

#endif

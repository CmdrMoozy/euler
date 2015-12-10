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

#ifndef INCLUDE_LIBEULER_UTIL_ABSOLUTE_VALUE_H
#define INCLUDE_LIBEULER_UTIL_ABSOLUTE_VALUE_H

#include <cinttypes>
#include <cmath>
#include <type_traits>

namespace euler
{
namespace absolute_impl
{
struct IntegralAbs
{
	template <typename T> T operator()(const T &v)
	{
		static_assert(std::is_integral<T>::value,
		              "Type must be integral.");
		return static_cast<T>(std::imaxabs(v));
	}
};

struct FloatingPointAbs
{
	template <typename T> T operator()(const T &v)
	{
		static_assert(std::is_floating_point<T>::value,
		              "Type must be floating point.");
		return std::fabs(v);
	}
};

template <typename T> struct AbsSignedFunctorWrapper
{
	typedef typename std::conditional<std::is_integral<T>::value,
	                                  IntegralAbs, FloatingPointAbs> type;
};

struct UnsignedAbs
{
	template <typename T> T operator()(const T &v)
	{
		return v;
	}
};

template <typename T> struct AbsFunctorWrapper
{
	typedef typename std::conditional<
	        std::is_signed<T>::value,
	        typename AbsSignedFunctorWrapper<T>::type,
	        UnsignedAbs>::type type;
};
}

/*!
 * \param v The value to compute an absolute value of.
 * \return The absolute value of v.
 */
template <typename T> T absolute(const T &v)
{
	static_assert(std::is_arithmetic<T>::value,
	              "Cannot take absolute value of non-arithmetic type.");
	typename absolute_impl::AbsFunctorWrapper<T>::type functor;
	return functor(v);
}
}

#endif

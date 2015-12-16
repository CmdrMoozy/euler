/*
 * euler - a collection of projecteuler libraries, tools, and solutions.
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

#ifndef common_math_floatCompare_HPP
#define common_math_floatCompare_HPP

#include <algorithm>
#include <cassert>
#include <cfloat>
#include <cmath>
#include <type_traits>

namespace euler
{
namespace math
{
namespace detail
{
template <typename F> struct FloatEpsilon
{
	using type = typename std::decay<F>::type;
	static_assert(std::is_floating_point<type>::value,
	              "Type must be a floating point type to have an epsilon.");
	static_assert(!std::is_same<type, long double>::value,
	              "The long double type is not supported.");

	static constexpr type value =
	        std::is_same<float, type>::value
	                ? FLT_EPSILON
	                : std::is_same<double, type>::value ? DBL_EPSILON : 0.0;
};
}

/*!
 * Compares the given two floating point values. Returns -1, 0, or 1 if a is
 * less than, equal to, or greater than b, respectively. The two numbers are
 * considered "equal" to each other if they are very close (within some margin
 * of error defined by the epsilon value from <cfloat>, relative to the
 * magnitude of the values being compared).
 *
 * \param a The first number to compare.
 * \param b The second number to compare.
 * \return How a compares to b.
 */
template <typename F> int floatCompare(F a, F b)
{
	using float_type = typename std::decay<F>::type;

	float_type absA = std::abs(a);
	float_type absB = std::abs(b);
	float_type maxVal = std::max(a, b);
	float_type minVal = std::min(a, b);
	float_type maxAbs = std::max(absA, absB);
	float_type minAbs = std::min(absA, absB);
	float_type epsilon = maxAbs * detail::FloatEpsilon<F>::value;

	// If the signs differ, we can return early if the numbers are not
	// particularly close to each other (i.e., close to 0.0).
	if(((a < 0.0) != (b < 0.0)) && (maxAbs >= epsilon))
	{
		if(a < b)
			return -1;
		else if(a > b)
			return 1;
	}

	// The numbers have the same sign, or they are quite close to each
	// other, so we can be sure that this will not overflow.
	float_type diff = std::abs(maxVal - minVal);

	if(diff < epsilon)
		return 0;

	if(a < b)
		return -1;
	else if(a > b)
		return 1;
	else
		return 0;
}
}
}

#endif

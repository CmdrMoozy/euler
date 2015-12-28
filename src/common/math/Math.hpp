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

#ifndef common_math_Math_HPP
#define common_math_Math_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iterator>
#include <type_traits>
#include <utility>

namespace euler
{
namespace math
{
namespace detail
{
/*!
 * \brief This functor implements fast extended division for signed integers.
 */
template <typename T> struct SignedIntegralDivideImpl
{
	static_assert(sizeof(T) <= sizeof(int64_t),
	              "Only values up to 64 bits in length are supported.");

	std::pair<T, T> operator()(T dividend, T divisor)
	{
		T quotient = 0;
		T remainder = 0;
		asm(
		        // idiv operates on rdx:rax, so for a 64-bit value we
		        // need to do a sign extension.
		        "cqo\n"
		        "\tidiv %%rbx"
		        : "=a"(quotient), "=d"(remainder)
		        // We need to cast to int64_t so cqo does the right
		        // thing.
		        : "a"(static_cast<int64_t>(dividend)),
		          "b"(static_cast<int64_t>(divisor))
		        :);
		return std::make_pair(quotient, remainder);
	}
};

/*!
 * \brief This functor implements fast extended division for unsigned integers.
 */
template <typename T> struct UnsignedIntegralDivideImpl
{
	static_assert(sizeof(T) <= sizeof(uint64_t),
	              "Only values up to 64 bits in length are supported.");

	std::pair<T, T> operator()(T dividend, T divisor)
	{
		T quotient = 0;
		T remainder = 0;
		asm(
		        // div operates on rdx:rax, so for <128-bit values we
		        // need to zero rdx.
		        "xor %%rdx, %%rdx\n"
		        "\tdiv %%rbx"
		        : "=a"(quotient), "=d"(remainder)
		        : "a"(dividend), "b"(divisor)
		        :);
		return std::make_pair(quotient, remainder);
	}
};

/*!
 * \brief This functor to specialize to support non-integral type division.
 */
template <typename T> struct DivideImpl
{
	std::pair<T, T> operator()(T dividend, T divisor);
};

/*!
 * \brief A metafunction to select the division implementation type for a type.
 */
template <typename T> struct DivideImplType
{
	typedef typename std::conditional<
	        std::is_integral<T>::value,
	        typename std::conditional<std::is_signed<T>::value,
	                                  SignedIntegralDivideImpl<T>,
	                                  UnsignedIntegralDivideImpl<T>>::type,
	        DivideImpl<T>>::type type;
};
}

/*!
 * Divides the given dividend by the given divisor. The return value is a pair
 * of the quotient and remainder, respectively. This function is implemented
 * with a single instruction for integral types.
 *
 * \param dividend The value being divided.
 * \param divisor The value we are dividing by.
 * \return A pair of the quotient and remainder.
 */
template <typename T> std::pair<T, T> divide(T dividend, T divisor)
{
	typename detail::DivideImplType<T>::type impl;
	return impl(dividend, divisor);
}

/*!
 * This function uses integer math to calculate the result of b^e. This is
 * significantly faster than std::pow, which operates on floating point
 * numbers.
 *
 * \param b The base.
 * \param e The exponent.
 * \return b^e
 */
uint64_t ipow(uint64_t b, uint8_t e);

/*!
 * This algorithm calculates b^e (mod m). This method is known as the
 * "right-to-left binary method," which is explained in more detail here:
 *
 *     http://en.wikipedia.org/wiki/Modular_exponentiation
 *
 * \param b The base.
 * \param e The exponent to raise the base to.
 * \param m The modulus.
 * \return b^e (mod m).
 */
uint64_t ipowmod(uint64_t b, uint64_t e, uint64_t m);

/*!
 * Compute the average of a collection of numbers. The numbers pointed to by
 * the given iterators must be able to be casted to double.
 *
 * \param begin The start of the collection to average.
 * \param end The end of the collection to average.
 * \return The average of the given numbers.
 */
template <typename Iterator> double average(Iterator begin, Iterator end)
{
	double result = 0.0;
	const double count = std::distance(begin, end);
	for(auto it = begin; it != end; ++it)
		result += static_cast<double>(*it) / count;
	return result;
}

namespace detail
{
/*!
 * A generic standard deviation implementation.
 *
 * \param begin The start of the range of values.
 * \param end The end of the range of values.
 * \param correction Divisor correction; to support population vs. sample.
 * \return The standard deviation of the values.
 */
template <typename Iterator>
double stddevImpl(Iterator begin, Iterator end, int correction)
{
	double denominator = static_cast<double>(std::distance(begin, end)) -
	                     static_cast<double>(correction);
	double avg = average(begin, end);
	double stddev = 0.0;
	for(auto it = begin; it != end; ++it)
		stddev += std::pow(*it - avg, 2.0) / denominator;
	return stddev;
}
}

/*!
 * Compute the standard deviation of a population.
 *
 * \param begin The start of the range of values.
 * \param end The end of the range of values.
 * \return The standard deviation of the values.
 */
template <typename Iterator>
double stddevPopulation(Iterator begin, Iterator end)
{
	return detail::stddevImpl(begin, end, 0);
}

/*!
 * Compute the standard deviation of a sample.
 *
 * \param begin The start of the range of values.
 * \param end The end of the range of values.
 * \return The standard deviation of the values.
 */
template <typename Iterator> double stddevSample(Iterator begin, Iterator end)
{
	return detail::stddevImpl(begin, end, -1);
}

/*!
 * Return the nearest ordinal rank for the given percentile, in the given
 * sorted list (it is up to the caller to ensure that the list is sorted).
 *
 * This function returns an iterator to the smallest value in the list such
 * that p percent of the data is less than or equal to that value.
 *
 * \param p The percentile to compute.
 * \param begin The start of the list.
 * \param end The end of the list.
 * \return The desired percentile value's iterator from the list.
 */
template <typename Iterator>
Iterator percentileValue(unsigned int p, Iterator begin, Iterator end)
{
	if(begin == end)
		return end;
	auto distance = std::distance(begin, end);
	const double percentile = static_cast<double>(p) / 100.0;
	const double ordinalRank =
	        percentile * static_cast<double>(std::distance(begin, end));
	Iterator ret(begin);
	std::advance(ret, std::min(static_cast<int>(distance - 1),
	                           static_cast<int>(std::ceil(ordinalRank))));
	return ret;
}
}
}

#endif

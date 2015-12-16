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

#include <cstdint>
#include <iterator>

namespace euler
{
namespace math
{
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
 * the given iterators must be able to be casted to long double.
 *
 * \param begin The start of the collection to average.
 * \param end The end of the collection to average.
 * \return The average of the given numbers.
 */
template <typename Iterator> long double average(Iterator begin, Iterator end)
{
	long double result = 0.0;
	const long double count = std::distance(begin, end);
	for(auto it = begin; it != end; ++it)
		result += static_cast<long double>(*it) / count;
	return result;
}
}
}

#endif

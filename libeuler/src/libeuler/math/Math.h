/*
 * euler - A collection of ProjectEuler solutions, and supporting libraries and tools.
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

#ifndef INCLUDE_LIBEULER_MATH_MATH_H
#define INCLUDE_LIBEULER_MATH_MATH_H

#include <cstdint>

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
}
}

#endif

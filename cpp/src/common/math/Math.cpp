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

#include "Math.hpp"

#include "common/EDefines.h"

namespace
{
/*!
 * This is a utility function which performs a single integer power
 * step. This is a simplified implementation of the typical modular
 * integer power algorithm.
 *
 * \param result The result to update.
 * \param b The base to use and update.
 * \param e The exponent to use and update.
 */
inline void ipowStep(uint64_t &result, uint64_t &b, uint8_t &e)
{
	if(e & 1)
		result *= b;
	e >>= 1;
	b *= b;
}
}

namespace euler
{
namespace math
{
uint64_t ipow(uint64_t b, uint8_t e)
{
	static constexpr uint8_t LG_PLUS_ONE[] = {
	        0,   1,   2,   2,   3,   3,   3,   3,   4,   4,   4,   4,   4,
	        4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,
	        5,   5,   5,   5,   5,   5,   6,   6,   6,   6,   6,   6,   6,
	        6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,
	        6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   6,   255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	        255, 255, 255, 255, 255, 255, 255, 255, 255};

	uint64_t result = 1;
	switch(LG_PLUS_ONE[e])
	{
	case 255:
		if(b == 1)
			return 1;
		return 0;
	case 6:
		ipowStep(result, b, e);
		EFALLTHROUGH;
	case 5:
		ipowStep(result, b, e);
		EFALLTHROUGH;
	case 4:
		ipowStep(result, b, e);
		EFALLTHROUGH;
	case 3:
		ipowStep(result, b, e);
		EFALLTHROUGH;
	case 2:
		ipowStep(result, b, e);
		EFALLTHROUGH;
	case 1:
		ipowStep(result, b, e);
		EFALLTHROUGH;
	default:
		return result;
	}
}

uint64_t ipowmod(uint64_t b, uint64_t e, uint64_t m)
{
	uint64_t result = 1;
	while(e > 0)
	{
		if(e & 1)
			result = (result * b) % m;

		e >>= 1;
		b = (b * b) % m;
	}
	return result;
}
}
}

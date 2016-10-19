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

#include "Bitwise.hpp"

namespace euler
{
namespace util
{
namespace bitwise
{
std::size_t opop(uint64_t x)
{
	x = (x & 0x5555555555555555) + ((x >> 1) & 0x5555555555555555);
	x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
	x = (x & 0x0F0F0F0F0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F0F0F0F0F);
	x = (x & 0x00FF00FF00FF00FF) + ((x >> 8) & 0x00FF00FF00FF00FF);
	x = (x & 0x0000FFFF0000FFFF) + ((x >> 16) & 0x0000FFFF0000FFFF);
	x = (x & 0x00000000FFFFFFFF) + ((x >> 32) & 0x00000000FFFFFFFF);
	return static_cast<std::size_t>(x);
}
}
}
}

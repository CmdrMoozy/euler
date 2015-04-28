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

#include <iostream>
#include <cassert>
#include <cstdint>

/*
 * Triangle, square, pentagonal, hexagonal, heptagonal, and ocatagonal numbers
 *are all
 * figurate (polygonal) numbers and are generated by the following formulae:
 *
 * Triangle	T(n) = n(n+1)/2		1, 3, 6, 10, 15, ...
 * Square	S(n) = n^2		1, 4, 9, 16, 25, ...
 * Pentagonal	P(n) = n(3n-1)/2	1, 5, 12, 22, 35, ...
 * Hexagonal	X(n) = n(2n-1)		1, 6, 15, 28, 45, ...
 * Heptagonal	H(n) = n(5n-3)/2	1, 7, 18, 34, 55, ...
 * Octagonal	O(n) = n(3n-2)		1, 8, 21, 40, 65, ...
 *
 * The ordered set of three 4-digit numbers: 8128, 2882, 8281, has three
 *interesting
 * properties.
 *
 *     1. The set is cyclic, in that the last two digits of each number is the
 *first
 *        two digits of the next number (including the last number with the
 *first).
 *
 *     2. Each polygonal type: triangle (T(127) = 8128), square (S(91) = 8281),
 *        and pentagonal (P(44) = 2882), is represented by a different number in
 *the
 *        set.
 *
 *     3. This is the only set of 4-digit numbers with this property.
 *
 * Find the sum of the only ordered set of six cyclic 4-digit numbers for which
 *each
 * polygonal type: triangle, square, pentagonal, hexagonal, heptagonal, and
 *octagonal,
 * is represented by a different number in the set.
 */

int main(void)
{
	return 0;
}

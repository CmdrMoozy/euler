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

#include <cassert>
#include <cstdint>
#include <iostream>

/*
 * By counting carefully it can be seen that a rectangular grid measuring 3
 * by 2 contains eighteen rectangles:
 *
 *      _ _ _    _ _ _    _ _ _
 *     |X|_|_|  |X|X|_|  |X|X|X|
 *     |_|_|_|  |_|_|_|  |_|_|_|
 *
 *        6        4        2
 *      _ _ _    _ _ _    _ _ _
 *     |X|_|_|  |X|X|_|  |X|X|X|
 *     |X|_|_|  |X|X|_|  |X|X|X|
 *
 *        3        2        1
 *
 * Although there exists no rectangular grid that contains exactly two million
 * rectangles, find the area of the grid with the nearest solution.
 */

namespace
{
/*
 * First, note that the number of rectangles contained in any grid is
 * the same for any grid of the same area which is rotationally
 * symmetric.
 *
 * Next, note that the number of different rectangle sizes contained
 * in a grid is equal to the number of lattice points, excluding those
 * lattice points which lie on the top or left edges of the grid.
 *
 * For each of these contained rectangles, the number of positions it
 * can occupy is given by:
 *
 *     (grid width - rect width + 1) * (grid height - rect height + 1)
 *
 * Since it can be in (grid height - rect height + 1) vertical
 * positions, and (grid width - rect width + 1) horizontal positions.
 */

/*
uint64_t containedRectangleShapes(uint64_t w, uint64_t h)
{
        return ((w + 1) * (h + 1)) - (w + 1) - (h + 1);
}
*/

/*
uint64_t containedRectangles(uint64_t w, uint64_t h)
{
        uint64_t count = 0;
        for(uint64_t rw = 1; rw <= w; ++rw)
                for(uint64_t rh = 1; rh <= h; ++rh)
                        count += ((w + 1) - rw) * ((h + 1) - rh);
        return count;
}
*/
}

int main(void)
{
	return 0;
}

/*
 * euler - A collection of ProjectEuler solutions, and supporting libraries and
 *tools.
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

#ifndef INCLUDE_LIBEULER_EULER_SPIRAL_H
#define INCLUDE_LIBEULER_EULER_SPIRAL_H

#include <cstdint>
#include <vector>

/*!
 * \brief This class represents an n by n matrix (where n is odd) filled in in a
 *spiral pattern.
 *
 * It is such that the CENTER cell's value is 1, and the following cells are
 *filled in
 * in clockwise order, starting with the cell to the immediate right of the
 *center, incrementing
 * the value by 1 with each new cell.
 *
 * Note that addressing is done with (0, 0) being the CENTER cell, (1, 1) II
 *being the cell
 * to the top-left, (1, 1) IV being the cell to the bottom-right and so on.
 */
class ESpiral
{
public:
	/*!
	 * This enum represents a quadrant, according to the cartesian quadrants
	 * (such that quadrant 1 is to the top-right of (0, 0), and they
	 * progress
	 * counter-clockwise).
	 */
	enum Quadrant
	{
		I = 0,
		II = 1,
		III = 2,
		IV = 3
	};

#ifdef LIBEULER_DEBUG
	static void doTestSuite();
#endif

	ESpiral();
	virtual ~ESpiral();

	int getSizeFor(int o);

	void begin();
	uint64_t next();
	uint64_t previous();

	void clearCache();

	uint64_t diagonalValueAt(uint32_t o, ESpiral::Quadrant q);

private:
	static const ESpiral::Quadrant fsmNext[4];
	static const ESpiral::Quadrant fsmPrevious[4];

	std::vector<uint64_t> cacheI, cacheII, cacheIII, cacheIV;

	ESpiral::Quadrant currentQuadrant;
	int currentOffset;
	uint64_t currentValue;
};

#endif

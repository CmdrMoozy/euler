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

#ifndef INCLUDE_LIBEULER_EULER_SUDOKU_H
#define INCLUDE_LIBEULER_EULER_SUDOKU_H

#include <cstddef>
#include <cstdint>
#include <vector>

// Forward declarations.
class EExactCover;

/*!
 * \brief This class implements a simple Sudoku solver.
 *
 * We utilize the dancing links algorithm, implemented by EExactCover, to solve
 *these problems.
 * More information about this technique can be found in the following article:
 *     http://www.ams.org/samplings/feature-column/fcarc-kanoodle
 */
class ESudoku
{
public:
	ESudoku();
	virtual ~ESudoku();

	void clear();
	bool load(const std::vector<int> &p);
	bool solve(bool s = false);
	std::vector<int> getSolution() const;

private:
	std::vector<int> puzzle;
	std::vector<int> solution;
	EExactCover *solver;

	void updateMasks(std::vector<uint16_t> &m, std::size_t i, int v);
	void reduce(std::vector<uint16_t> &m, std::size_t i);
	bool optimizePairs(std::vector<uint16_t> &m);
	void preprocess();

	std::size_t rowOf(std::size_t i) const;
	std::size_t colOf(std::size_t i) const;
	std::size_t boxOf(std::size_t i) const;

	std::size_t rowIndex(std::size_t r, std::size_t i) const;
	std::size_t colIndex(std::size_t c, std::size_t i) const;
	std::size_t boxIndex(std::size_t b, std::size_t i) const;
};

#endif

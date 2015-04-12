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

#include "ESudoku.h"

#include <algorithm>

#include "libeuler/math/EExactCover.h"
#include "libeuler/util/EBitwise.h"

/*!
 * This is our default constructor, which creates a new QSudoku object.
 */
ESudoku::ESudoku()
{
	solver = new EExactCover();
}

/*!
 * This is our default destructor, which cleans up & destroys our object.
 */
ESudoku::~ESudoku()
{
	delete solver;
}

/*!
 * This function clears our object, by clearing both our puzzle and solution buffers, as well as our
 * behind-the-scenes exact cover problem solver object.
 */
void ESudoku::clear()
{
	puzzle.clear();
	solution.clear();
	solver->clear();
}

/*!
 * This function loads the given puzzle, p. p must be a vector contanining 81 elements, where each element, n,
 * stores the number (1-9, or 0 if this cell is not pre-filled-in) that cell n in the puzzle contains.
 *
 * \param p The puzzle to load.
 * \return True on success, or false on failure.
 */
bool ESudoku::load(const std::vector<int> &p)
{
	clear();

	// Set the puzzle.

	if(p.size() != 81) return false;
	puzzle = p;

	// Perform preprocessing to try and speed up (or eliminate the need for) an exact cover solution.

	preprocess();

	// If our preprocessing has solved the puzzle, then just return - no need to do an exact cover solution.

	if(solution.size() != 0) return true;

	// Figure out how many rows & columns we need to represent it.

	int rows = 0, columns = 324;

	for(unsigned int i = 0; i < puzzle.size(); ++i)
	{
		if( (puzzle[i] < 0) || (puzzle[i] > 9) )
		{
			clear();
			return false;
		}

		if(puzzle[i] == 0)
		{
			rows += 9;
		}
		else if( (puzzle[i] >= 1) && (puzzle[i] <= 9) )
		{
			rows += 1;
		}
		else
		{
			clear();
			return false;
		}
	}

	solver->setSize(columns, rows);

	// Take our puzzle and convert it into an exact cover problem.

	int row = 0;
	for(unsigned int i = 0; i < puzzle.size(); ++i)
	{
		/*
		First  node is at (i, row) - to indicate that cell i has a symbol in it.
		Second node is at 81 + ((row * 9) + symbol-1) - to indicate that the row-th row has the symbol in it.
		Third  node is at 162 + ((col * 9) + symbol-1) - to indicate that the col-th column has the symbol in it.
		Fourth node is at 243 + ((box * 9) + symbol-1) - to indicate that the box-th box has the symbol in it.
		*/

		if(puzzle[i] == 0)
		{
			// This is a zero node, so we need to produce nine rows for it.

			for(int s = 1; s <= 9; ++s)
			{ // For each possible symbol, 1-9...
				solver->setAt( i,                              row, true );
				solver->setAt( 81  + ((rowOf(i)) * 9) + (s-1), row, true );
				solver->setAt( 162 + ((colOf(i)) * 9) + (s-1), row, true );
				solver->setAt( 243 + ((boxOf(i)) * 9) + (s-1), row, true );

				++row;
			}

		}
		else
		{
			// This is a filled-in node, so we need to add a single column for it.

			solver->setAt( i                                , row, true );
			solver->setAt( 81  + ((rowOf(i) * 9) + (puzzle[i]-1)), row, true );
			solver->setAt( 162 + ((colOf(i) * 9) + (puzzle[i]-1)), row, true );
			solver->setAt( 243 + ((boxOf(i) * 9) + (puzzle[i]-1)), row, true );

			++row;
		}
	}

	return true;
}

/*!
 * This function solves the puzzle we currently have loaded. No puzzle being loaded is considered an error,
 * and already having a valid solution to the current puzzle results in us taking no action. Note that if the
 * puzzle we have loaded has multiple solutions, we consider this an error - Sudoku puzzles are "supposed"
 * to have only one correct solution.
 *
 * Note that if the puzzle has already been solved, then we take no action.
 *
 * The resulting solution can be retrieved via getSolution().
 *
 * \param s True means we terminate after finding a single solution.
 * \return True on success, or false on error.
 */
bool ESudoku::solve(bool s)
{
	if(solution.size() != 0) return true;
	if(puzzle.size() != 81)	return false;

	// Retrieve the solution from our EExactCover.

	solver->solve(s);

	std::vector< std::vector< std::pair<int, int> > > solutions = solver->getSolutions();
	if(solutions.size() != 1)
		return false;

	// Grab only the pairs whose column is < 81.

	static struct paircmp
	{
		bool operator() (const std::pair<int,int> &a, const std::pair<int,int> &b)
		{
			return a.first < b.first;
		}
	} mycmp;

	std::vector< std::pair<int, int> > stmp;
	for(unsigned int i = 0; i < solutions[0].size(); ++i)
		if(solutions[0][i].first < 81)
			stmp.push_back(solutions[0][i]);

	// Sort these pairs by column.

	std::sort(stmp.begin(), stmp.end(), mycmp);

	// Translate these column/row indices into numbers in the solution.

	solution.clear();
	solution.resize(81, 0);
	int frow = 0;
	for(unsigned int i = 0; i < stmp.size(); ++i)
	{
		if(puzzle[stmp[i].first] != 0)
		{
			solution[stmp[i].first] = puzzle[stmp[i].first];
			++frow;
		}
		else
		{
			solution[stmp[i].first] = (stmp[i].second + 1) - frow;
			frow += 9;
		}
	}

	return true;
}

/*!
 * This function returns a copy of the puzzle's solution. This is represented as a vector, where each index in the
 * vector (0 <= n <= 80) represents the value stored in cell n in the resulting Sudoku puzzle.
 *
 * \return The puzzle's solution.
 */
std::vector<int> ESudoku::getSolution() const
{
	return solution;
}

/*!
 * This function updates a preprocesing mask table with a given new digit located at a given position.
 * This function provides a convenient way to update ALL of the masks when a given cell is filled in,
 * including those in its row, column and box.
 *
 * \param m The mask table to be updated.
 * \param i The index in puzzle of the value to update with.
 * \param v The value to mark as invalid for the appropriate cells.
 */
void ESudoku::updateMasks(std::vector<uint16_t> &m, int i, int v)
{
	uint16_t mask = ~(1 << (v - 1));

	for(int j = 0; j < 9; ++j)
	{
		m[rowIndex(rowOf(i), j)] &= mask;
		m[colIndex(colOf(i), j)] &= mask;
		m[boxIndex(boxOf(i), j)] &= mask;
	}
}

/*!
 * This function is a helper for preprocess, that recursively fills in cells whose value can be calculated
 * deterministically. That is, if only one value is possible for an unknown cell, it is filled in, and then
 * we recurse on each cell we affected with the change (in the modified cell's column, row and box).
 *
 * \param m The preprocessing mask table.
 * \param i The index of the cell to test.
 */
void ESudoku::reduce(std::vector<uint16_t> &m, int i)
{
	int ai;
	uint16_t amask, cmask;
	bool u = false;

	// Do not try to guess non-blank cells.
	if(puzzle.at(i)) return;

	// Fill in any singles.

	if(EBitwise::isPowTwo(m.at(i)))
	{
		// Fill in its value in the puzzle.
		puzzle[i] = EBitwise::lg32(m.at(i)) + 1;
		m[i] = 0;
		u = true;
	}

	// Check for hidden singles in our ROW.

	if(!u)
	{
		amask = 0;

		for(int j = 0; j < 9; ++j)
		{
			ai = rowIndex(rowOf(i), j);
			amask |= (ai != i) ? m.at(ai) : 0;
		}

		cmask = (amask ^ m.at(i)) & m.at(i);

		if(EBitwise::isPowTwo(cmask))
		{
			// Fill in this cell's value in the puzzle.
			puzzle[i] = EBitwise::lg32(cmask) + 1;
			m[i] = 0;
			u = true;
		}
	}

	// Check for hidden singles in our COLUMN.

	if(!u)
	{
		amask = 0;

		for(int j = 0; j < 9; ++j)
		{
			ai = colIndex(colOf(i), j);
			amask |= (ai != i) ? m.at(ai) : 0;
		}

		cmask = (amask ^ m.at(i)) & m.at(i);

		if(EBitwise::isPowTwo(cmask))
		{
			// Fill in this cell's value in the puzzle.
			puzzle[i] = EBitwise::lg32(cmask) + 1;
			m[i] = 0;
			u = true;
		}
	}

	// Check for hidden singles in our BOX.

	if(!u)
	{
		amask = 0;

		for(int j = 0; j < 9; ++j)
		{
			ai = boxIndex(boxOf(i), j);
			amask |= (ai != i) ? m.at(ai) : 0;
		}

		cmask = (amask ^ m.at(i)) & m.at(i);

		if(EBitwise::isPowTwo(cmask))
		{
			// Fill in this cell's value in the puzzle.
			puzzle[i] = EBitwise::lg32(cmask) + 1;
			m[i] = 0;
			u = true;
		}
	}

	// Update our masks, if needed, and recurse on affected cells.

	if(u)
	{
		updateMasks(m, i, puzzle.at(i));

		for(int j = 0; j < 9; ++j)
		{
			reduce(m, rowIndex(rowOf(i), j));
			reduce(m, colIndex(colOf(i), j));
			reduce(m, boxIndex(boxOf(i), j));
		}
	}
}

/*!
 * This function is a helper for preprocess, that scans the current mask table for pairs. This allows us
 * to simplify the puzzle, by eliminating the values present in the pair in the other cells in a group.
 *
 * \param m The preprocessing mask table.
 * \return True if we eliminated some possibilities, or false otherwise.
 */
bool ESudoku::optimizePairs(std::vector<uint16_t> &m)
{
	uint16_t pmask;
	bool r = false;
	int p, k;

	for(int i = 0; i < 81; ++i)
	{
		// Look for cells with exactly two possible values.

		if(EBitwise::opop(m.at(i)) == 2)
		{
			pmask = m.at(i);

			// Look for a pair in this ROW.

			p = 0;

			for(int j = 0; j < 9; ++j)
			{
				// Try to find an identical cell.

				k = rowIndex(rowOf(i), j);
				if(k == i) continue;

				if( m.at(k) == m.at(i) )
				{
					p = k;
					break;
				}
			}

			if(p)
			{
				// We have found a pair - remove the pair values from other cells in this ROW.

				for(int j = 0; j < 9; ++j)
				{
					k = rowIndex(rowOf(i), j);
					if( (k == i) || (k == p) ) continue;

					r |= (m.at(k) & pmask) > 0;
					m[k] &= ~pmask;
				}
			}

			// Look for a pair in this COLUMN.

			p = 0;

			for(int j = 0; j < 9; ++j)
			{
				// Try to find an identical cell.

				k = colIndex(colOf(i), j);
				if(k == i) continue;

				if( m.at(k) == m.at(i) )
				{
					p = k;
					break;
				}
			}

			if(p)
			{
				// We have found a pair - remove the pair values from other cells in this ROW.

				for(int j = 0; j < 9; ++j)
				{
					k = colIndex(colOf(i), j);
					if( (k == i) || (k == p) ) continue;

					r |= (m.at(k) & pmask) > 0;
					m[k] &= ~pmask;
				}
			}

			// Look for a pair in this BOX.

			p = 0;

			for(int j = 0; j < 9; ++j)
			{
				// Try to find an identical cell.

				k = boxIndex(boxOf(i), j);
				if(k == i) continue;

				if( m.at(k) == m.at(i) )
				{
					p = k;
					break;
				}
			}

			if(p)
			{
				// We have found a pair - remove the pair values from other cells in this ROW.

				for(int j = 0; j < 9; ++j)
				{
					k = boxIndex(boxOf(i), j);
					if( (k == i) || (k == p) ) continue;

					r |= (m.at(k) & pmask) > 0;
					m[k] &= ~pmask;
				}
			}
		}
	}

	return r;
}

/*!
 * This function performs preprocessing on our puzzle, in an attempt to either speed up or completely eliminate
 * the need for an exact cover solution. We do this by filling in any cells that are deterministic (i.e., cells
 * where only a single digit is valid), and by using some other techniques (e.g., "naked pairs") to eliminate
 * other candidates.
 */
void ESudoku::preprocess()
{

	std::vector<uint16_t> mask(81, 0x01FF);

	// Build a table of digit masks indicating what digits are still valid.

	for(size_t i = 0; i < puzzle.size(); ++i)
	{
		// Ignore empty cells.
		if(!puzzle.at(i)) continue;

		updateMasks(mask, i, puzzle.at(i));
		mask[i] = 0; // Ensure filled-in cells have a 0 mask.
	}

	// Try to reduce the complexity of the puzzle to be solved.

	do
	{
		for(size_t i = 0; i < puzzle.size(); ++i)
			reduce(mask, i);
	} while(optimizePairs(mask));

	// If we've solved the puzzle, set solution accordingly.

	bool s = true;
	for(size_t i = 0; i < puzzle.size(); ++i)
	{
		if(!puzzle.at(i))
		{
			s = false;
			break;
		}
	}

	if(s) solution = puzzle;
}

/*!
 * This utility function returns the index of the row that contains the given index in our puzzle. Note that
 * this (currently) only works for 9x9 puzzles.
 *
 * NOTE: This function does NOT do bounds-checking!
 *
 * \param i The index of the cell in the puzzle.
 * \return The index of the row that contains this index.
 */
int ESudoku::rowOf(int i) const
{
	static int rowLookup[] = {
		0,0,0,0,0,0,0,0,0,

		1,1,1,1,1,1,1,1,1,

		2,2,2,2,2,2,2,2,2,

		3,3,3,3,3,3,3,3,3,

		4,4,4,4,4,4,4,4,4,

		5,5,5,5,5,5,5,5,5,

		6,6,6,6,6,6,6,6,6,

		7,7,7,7,7,7,7,7,7,

		8,8,8,8,8,8,8,8,8
	};

	return rowLookup[i];
}

/*!
 * This utility function returns the index of the column that contains the given index in our puzzle. Note that
 * this (currently) only works for 9x9 puzzles.
 *
 * NOTE: This function does NOT do bounds-checking!
 *
 * \param i The index of the cell in the puzzle.
 * \return The index of the column that contains this index.
 */
int ESudoku::colOf(int i) const
{
	static int colLookup[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8,
		0, 1, 2, 3, 4, 5, 6, 7, 8,
		0, 1, 2, 3, 4, 5, 6, 7, 8,
		0, 1, 2, 3, 4, 5, 6, 7, 8,
		0, 1, 2, 3, 4, 5, 6, 7, 8,
		0, 1, 2, 3, 4, 5, 6, 7, 8,
		0, 1, 2, 3, 4, 5, 6, 7, 8,
		0, 1, 2, 3, 4, 5, 6, 7, 8,
		0, 1, 2, 3, 4, 5, 6, 7, 8
	};

	return colLookup[i];
}

/*!
 * This utility function returns the index of the box that contains the given index in our puzzle. Note that
 * this (currently) only works for 9x9 puzzles.
 *
 * NOTE: This function does NOT do bounds-checking!
 *
 * \param i The index of the cell in the puzzle.
 * \return The index of the box that contains this index.
 */
int ESudoku::boxOf(int i) const
{
	static int boxLookup[] = {
		0,0,0, 1,1,1, 2,2,2,
		0,0,0, 1,1,1, 2,2,2,
		0,0,0, 1,1,1, 2,2,2,

		3,3,3, 4,4,4, 5,5,5,
		3,3,3, 4,4,4, 5,5,5,
		3,3,3, 4,4,4, 5,5,5,

		6,6,6, 7,7,7, 8,8,8,
		6,6,6, 7,7,7, 8,8,8,
		6,6,6, 7,7,7, 8,8,8
	};

	return boxLookup[i];
}

/*!
 * This utility function returns the index in a single-dimensional array which represents the ith element of row r.
 *
 * NOTE: This function does NOT do bounds-checking!
 *
 * \param r The desired row.
 * \param i The index relative to the given row.
 * \return The single-dimension array index corresponding to the given cell.
 */
int ESudoku::rowIndex(int r, int i) const
{
	return ((r * 9) + i);
}

/*!
 * This utility function returns the index in a single-dimensional array which represents the ith element of
 * column c.
 *
 * NOTE: This function does NOT do bounds-checking!
 *
 * \param c The desired column.
 * \param i The index relative to the given column.
 * \return The single-dimensional array index corresponding to the given cell.
 */
int ESudoku::colIndex(int c, int i) const
{
	return (c + (i * 9));
}

/*!
 * This utility function returns the index in a single-dimensional array which represents the ith element of
 * box b.
 *
 * NOTE: This function does NOT do bounds-checking!
 *
 * \param b The desired box.
 * \param i The index relative to the given box.
 * \return The single-dimensional array index corresponding to the given cell.
 */
int ESudoku::boxIndex(int b, int i) const
{
	int bi = b / 3;
	bi = (bi * 27) + ((b % 3) * 3);
	return ( bi + ( ((i / 3) * 9) + (i % 3) ) );
}

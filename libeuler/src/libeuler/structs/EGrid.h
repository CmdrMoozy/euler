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

#ifndef INCLUDE_LIBEULER_STRUCTS_GRID_H
#define INCLUDE_LIBEULER_STRUCTS_GRID_H

#include <cstdlib>

#include "libeuler/EDefines.h"

#ifdef LIBEULER_DEBUG
#include <iostream>
#endif

/*!
 * \brief This class implements a generic two-dimensional square grid.
 *
 * It is a very simple implementation of a two-dimensional array that does
 *bounds
 * checking and allows for it to be resized.
 */
template <typename T> class EGrid
{
public:
#ifdef LIBEULER_DEBUG
	/*!
	 * This function implements our test suite for this class. It uses
	 * non-abort()'ing
	 * assertions, and merely prints the result to stdout.
	 */
	static void doTestSuite()
	{
		bool success;
		bool rVal;

		std::cout << "\tTesting 'EGrid'...\t\t\t";
		try
		{
			success = true;

			EGrid<int> g(10);

			EASSERT(g.getSize() == 10)

			// Try setting some points.

			g.set(0, 0, 10);
			rVal = g.at(0, 0) == 10;
			EASSERT(rVal)
			g.set(3, 4, 1230);
			rVal = g.at(3, 4) == 1230;
			EASSERT(rVal)
			g.set(1, 9, 5665);
			rVal = g.at(1, 9) == 5665;
			EASSERT(rVal)
			g.set(0, 3, 176);
			rVal = g.at(0, 3) == 176;
			EASSERT(rVal)
			g.set(6, 1, 123);
			rVal = g.at(6, 1) == 123;
			EASSERT(rVal)

			// Try resizing & clearing to test memory.

			g.setSize(20);
			g.setSize(5);
			g.clear();
		}
		catch(EAssertionException &e)
		{
			ELUNUSED(e)
			success = false;
		}
		catch(EOutOfBoundsException &e)
		{
			EDIE_LOGIC(e)
		}

		// Print out our results.
		if(success)
			std::cout << "[ OK ]\n";
		else
			std::cout << "[FAIL]\n";
	}
#endif

	/*!
	 * This is our default constructor, which initializes a new EGrid object
	 * (optionally) with the given size. Note that negative sizes are
	 *treated as
	 * zero.
	 *
	 * \param n The size our object will start with.
	 */
	EGrid(int s = 0) : data(NULL), size(0)
	{
		setSize(s);
	}

	/*!
	 * This is our default destructor, which cleans up & destroys our
	 * object.
	 */
	virtual ~EGrid()
	{
		clear();
	}

	/*!
	 * This function just returns our grid's current size. Note that this is
	 *the size
	 * in both dimensions, i.e., our grid is n by n, where n is the size
	 *returned by
	 * this function.
	 *
	 * \return The size of our grid.
	 */
	int getSize() const
	{
		return size;
	}

	/*!
	 * This function sets the current size of our grid. Note that previous
	 *contents are
	 * not preserved. Note that negative sizes are treated as zero.
	 *
	 * \param n The new size of our grid.
	 */
	void setSize(int s)
	{
		int i;
		clear();

		s = (s >= 0) ? s : 0;

		size = s;
		data = new T *[getSize()];

		for(i = 0; i < getSize(); i++)
			data[i] = new T[getSize()];
	}

	/*!
	 * This function clears all of the contents of our grid. It is
	 * equivalent in functionality
	 * to setSize(0).
	 */
	void clear()
	{
		int i;

		if((data != NULL) && (size > 0))
		{
			for(i = 0; i < getSize(); i++)
				if(data[i] != NULL)
					delete[] data[i];

			delete[] data;
		}

		size = 0;
	}

	/*!
	 * This function returns a copy of the value stored at the given
	 *position in our grid.
	 *
	 * \param i The row at which the given value is found.
	 * \param j The column at which the given value is found.
	 * \exception QOutOfBoundsException This exception is thrown if the
	 *given row and/or column is out-of-bounds.
	 * \return A copy of the value stored at the given position.
	 */
	T &at(int i, int j) const throw(EOutOfBoundsException &)
	{
		if(!indexIsInBounds(i, j))
			throw EOutOfBoundsException(
			        "The index provided is out-of-bounds.");

		return data[i][j];
	}

	/*!
	 * This function sets the value at the given position in our grid.
	 *
	 * \param i The row at which the desired value is found.
	 * \param j The column at which the desired value is found.
	 * \param v The new value that we will store at the given position.
	 * \exception QOutOfBoundsException This exception is thrown if the
	 *given row and/or column is out-of-bounds.
	 */
	void set(int i, int j, const T &v) throw(EOutOfBoundsException &)
	{
		at(i, j) = v;
	}

private:
	T **data;
	int size;

	/*!
	 * This is a utility function that we use for bounds-checking, so we
	 *don't have to duplicate
	 * the same code everywhere.
	 *
	 * \param i The row portion of the given index.
	 * \param j The column portion of the given index.
	 * \return True if the index is in-bounds, or false otherwise.
	 */
	inline bool indexIsInBounds(int i, int j) const
	{
		return ((i >= 0) && (i < getSize()) && (j >= 0) &&
		        (j < getSize()));
	}
};

#endif

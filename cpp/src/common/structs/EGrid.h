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

#ifndef INCLUDE_LIBEULER_STRUCTS_GRID_H
#define INCLUDE_LIBEULER_STRUCTS_GRID_H

#include <cstddef>
#include <cstdlib>

#include "common/EDefines.h"

/*!
 * \brief This class implements a generic two-dimensional square grid.
 *
 * It is a very simple implementation of a two-dimensional array that does
 * bounds checking and allows for it to be resized.
 */
template <typename T> class EGrid
{
public:
	/*!
	 * This is our default constructor, which initializes a new EGrid object
	 * (optionally) with the given size. Note that negative sizes are
	 * treated as zero.
	 *
	 * \param s The size our object will start with.
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
	 * the size in both dimensions, i.e., our grid is n by n, where n is the
	 * size returned by this function.
	 *
	 * \return The size of our grid.
	 */
	int getSize() const
	{
		return size;
	}

	/*!
	 * This function sets the current size of our grid. Note that previous
	 * contents are not preserved. Note that negative sizes are treated as
	 * zero.
	 *
	 * \param s The new size of our grid.
	 */
	void setSize(int s)
	{
		int i;
		clear();

		s = (s >= 0) ? s : 0;

		size = s;
		data = new T *[static_cast<std::size_t>(getSize())];

		for(i = 0; i < getSize(); i++)
			data[i] = new T[static_cast<std::size_t>(getSize())];
	}

	/*!
	 * This function clears all of the contents of our grid. It is
	 * equivalent in functionality to setSize(0).
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
	 * position in our grid.
	 *
	 * \param i The row at which the given value is found.
	 * \param j The column at which the given value is found.
	 * \return A copy of the value stored at the given position.
	 */
	T &at(int i, int j) const
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
	 */
	void set(int i, int j, const T &v)
	{
		at(i, j) = v;
	}

private:
	T **data;
	int size;

	/*!
	 * This is a utility function that we use for bounds-checking, so we
	 * don't have to duplicate the same code everywhere.
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

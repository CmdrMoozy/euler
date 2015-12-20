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

#include "ETriangleStructure.h"

#include <cstdlib>
#include <climits>

#include "common/EDefines.h"

/*!
 * This is our default constructor, which initializes a new ETriangleStructure
 * (optionally) of a given height, or an empty one if no height is provided.
 *
 * \param h The height (number of rows) of our new triangle.
 */
ETriangleStructure::ETriangleStructure(std::size_t h) : height(0), data(NULL)
{
	setHeight(h, ETriangleStructure::ZeroOut);
}

/*!
 * This is our copy-constructor, which initializes a new ETriangleStructure
 * object that is equivalent to the given other object.
 *
 * \param o The other ETriangleStructure object to make ourself equal to.
 */
ETriangleStructure::ETriangleStructure(const ETriangleStructure &o)
        : height(0), data(NULL)
{
	(*this) = o;
}

/*!
 * This is our default destructor, which deletes all of the memory we've
 * allocated for our triangle's contents.
 */
ETriangleStructure::~ETriangleStructure()
{
	clear();
}

/*!
 * This is our assignment operator, which makes our current object equal to that
 * of the given other ETriangleStructure object.
 *
 * \param o The other QTriangleStructure object to make ourself equal to.
 * \return A reference to this, so this operator can be chained.
 */
ETriangleStructure &ETriangleStructure::operator=(const ETriangleStructure &o)
{
	try
	{
		setHeight(o.getHeight(), ETriangleStructure::None);
		for(std::size_t i = 0; i < getHeight(); i++)
			for(std::size_t j = 0; j < getHeight(); j++)
				setAt(i, j, o.at(i, j));
	}
	catch(EOutOfBoundsException &)
	{
#ifdef EULER_DEBUG
		EDIE_LOGIC(std::runtime_error("Got EOutOfBoundsException."))
#endif
	}

	return (*this);
}

/*!
 * This function clears our entire triangle, freeing up all of its memory and
 * (effectively) setting its size to 0.
 */
void ETriangleStructure::clear()
{
	if(data != NULL)
	{
		for(std::size_t i = 0; i < getHeight(); i++)
			if(data[i] != NULL)
				delete[] data[i];

		delete[] data;
	}

	data = NULL;
	height = 0;
}

/*!
 * This function returns the height (number of rows) of our triangle.
 *
 * \return The height of our triangle.
 */
std::size_t ETriangleStructure::getHeight() const
{
	return height;
}

/*!
 * This function sets the height of our triangle. It offers a few different fill
 * modes - it can either not fill the new data list at all, or it can try to
 * preserve as much of the old data as it can, or it can write all 0's to the
 * new list.
 *
 * \param h The new height of our triangle.
 * \param f The "FillMode" we will be using.
 */
void ETriangleStructure::setHeight(std::size_t h,
                                   ETriangleStructure::FillMode f)
{
	int **newData;

	newData = new int *[h];
	for(std::size_t i = 0; i < h; i++)
		newData[i] = new int[h];

	try
	{
		if(f != ETriangleStructure::None)
		{
			for(std::size_t i = 0; i < h; i++)
			{
				for(std::size_t j = 0; j < h; j++)
				{
					if(isInBounds(i, j) &&
					   (f == ETriangleStructure::Preserve))
						newData[i][j] = at(i, j);
					else
						newData[i][j] = 0;
				}
			}
		}
	}
	catch(EOutOfBoundsException &)
	{
#ifdef EULER_DEBUG
		EDIE_LOGIC(std::runtime_error("Got EOutOfBoundsException."))
#endif
	}

	clear();

	data = newData;
	height = h;
}

/*!
 * This function sets the value at the given index in our triangle.
 *
 * \param r The row on which the value is found.
 * \param c The column on which the value is found.
 * \param v The new value the given cell will hold.
 */
void ETriangleStructure::setAt(std::size_t r, std::size_t c, int v)
{
	if(!isInBounds(r, c))
		throw EOutOfBoundsException(
		        "The index provided is out-of-bounds.");

	data[r][c] = v;
}

/*!
 * This function sets every value in an entire row in our triangle. Note that it
 * is up to the caller to make sure the given array of values contains an
 * appropriate number of values for the given row.
 *
 * \param r The row whose values we will be setting.
 * \param v An array of the values we will be setting.
 */
void ETriangleStructure::setRowAt(std::size_t r, const int *v)
{
	for(std::size_t i = 0; i < (r + 1); i++)
		setAt(r, i, v[i]);
}

/*!
 * This function returns the value found at a given position in our triangle.
 *
 * \param r The row on which the value is found.
 * \param c The column in which the value is found.
 * \return The value found at the given index.
 */
int ETriangleStructure::at(std::size_t r, std::size_t c) const
{
	if(!isInBounds(r, c))
		throw EOutOfBoundsException(
		        "The index provided is out-of-bounds.");

	return data[r][c];
}

/*!
 * This function returns the largest possible sum of a path through the
 * triangle, from top to bottom. This function copies our existing triangle in
 * memory so it can operate on it without modifying our object. This function
 * operates in O(n^2) time complexity (note that this is only a fairly tight
 * upper-bound; it actually performs fewer operations), where n is the number
 * of rows in the triangle.
 *
 * \return The largest sum of path elements through the triangle, top to bottom.
 */
int ETriangleStructure::getLargestPathSum() const
{
	int cL, cR;
	ETriangleStructure t((*this));

	try
	{
		for(std::size_t i = 0; i <= (t.getHeight() - 2); ++i)
		{ // For each row from the first to the next-to-last...
			// Subtract to get the index, because we want to iterate
			// over the rows backwards.
			std::size_t idx = (t.getHeight() - 2) - i;
			for(std::size_t j = 0; j < (idx + 1); j++)
			{ // For each cell...
				// Set our left-child's value.
				try
				{
					cL = t.leftChildValue(idx, j);
				}
				catch(EOutOfBoundsException &)
				{
					cL = INT_MIN;
				}

				// Set our right-child's value.
				try
				{
					cR = t.rightChildValue(idx, j);
				}
				catch(EOutOfBoundsException &)
				{
					cR = INT_MIN;
				}

				// Our new value is our old value plus the
				// largest child's value.
				t.setAt(idx, j,
				        t.at(idx, j) + (cL > cR ? cL : cR));
			}
		}

		return t.at(0, 0);
	}
	catch(EOutOfBoundsException &)
	{
#ifdef EULER_DEBUG
		EDIE_LOGIC(std::runtime_error("Got EOutOfBoundsException."))
#endif
	}

	return INT_MIN;
}

/*!
 * This is a convenience function, which returns the value of the "left child"
 * of the cell at the given offset. In this instance, the "left child" is the
 * cell to the bottom left of the given cell, if all of our values were laid
 * out in a triangular shape.
 *
 * \param r The row on which the cell is found.
 * \param c The column in which the cell is found.
 * \return The value of the given cell's left child.
 */
int ETriangleStructure::leftChildValue(std::size_t r, std::size_t c) const
{
	return at(r + 1, c);
}

/*!
 * This is a convenience function, which returns the value of the "right child"
 * of the cell at the given offset. In this instance, the "right child" is the
 * cell to the bottom right of the given cell, if all of our values were laid
 * out in a triangular shape.
 *
 * \param r The row on which the value is found.
 * \param c The column in which the cell is found.
 * \return The value of the given cell's right child.
 */
int ETriangleStructure::rightChildValue(std::size_t r, std::size_t c) const
{
	return at(r + 1, c + 1);
}

/*!
 * This is a convenience function, which checks if the given row and column
 * offset is in-bounds in our current triangle.
 *
 * \param r The row on which the cell is found.
 * \param c The column in which the cell is found.
 * \return True if the given offset is in-bounds, or false otherwise.
 */
bool ETriangleStructure::isInBounds(std::size_t r, std::size_t c) const
{
	return (r < getHeight()) && (c < getHeight());
}

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

#include "libeuler/EDefines.h"

#ifdef LIBEULER_DEBUG
	#include <iostream>
#endif

#ifdef LIBEULER_DEBUG
/*!
 * This function implements our test suite for this class. It uses non-abort()'ing
 * assertions, and merely prints the result to stdout.
 */
void ETriangleStructure::doTestSuite()
{
	bool success;
	int i;

	std::cout << "\tTesting 'ETriangleStructure'...\t\t";
	try
	{
		success = true;

		/*
		 * This is a relatively simple test; it is known that the largest path through
		 * the given triangle is 1074, so we just test if we get the right answer.
		 */

		ETriangleStructure t(15);

		int data[][15] = {
			{ 75                                           },
			{ 95,64                                        },
			{ 17,47,82                                     },
			{ 18,35,87,10                                  },
			{ 20, 4,82,47,65                               },
			{ 19, 1,23,75,03,34                            },
			{ 88, 2,77,73, 7,63,67                         },
			{ 99,65, 4,28, 6,16,70,92                      },
			{ 41,41,26,56,83,40,80,70,33                   },
			{ 41,48,72,33,47,32,37,16,94,29                },
			{ 53,71,44,65,25,43,91,52,97,51,14             },
			{ 70,11,33,28,77,73,17,78,39,68,17,57          },
			{ 91,71,52,38,17,14,91,43,58,50,27,29,48       },
			{ 63,66, 4,68,89,53,67,30,73,16,69,87,40,31    },
			{  4,62,98,27,23, 9,70,98,73,93,38,53,60, 4,23 }
		};

		for(i = 0; i < 15; ++i)
			t.setRowAt(i, data[i]);

		EASSERT(t.getHeight() == 15)
		EASSERT(t.getLargestPathSum() == 1074)
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
 * This is our default constructor, which initializes a new ETriangleStructure (optionally)
 * of a given height, or an empty one if no height is provided.
 *
 * \param h The height (number of rows) of our new triangle.
 */
ETriangleStructure::ETriangleStructure(int h)
	: height(0), data(NULL)
{
	setHeight(h, ETriangleStructure::ZeroOut);
}

/*!
 * This is our copy-constructor, which initializes a new ETriangleStructure object that is
 * equivalent to the given other object.
 *
 * \param o The other ETriangleStructure object to make ourself equal to.
 */
ETriangleStructure::ETriangleStructure(const ETriangleStructure &o)
	: height(0), data(NULL)
{
	(*this) = o;
}

/*!
 * This is our default destructor, which deletes all of the memory we've allocated for
 * our triangle's contents.
 */
ETriangleStructure::~ETriangleStructure()
{
	clear();
}

/*!
 * This is our assignment operator, which makes our current object equal to that of the given
 * other ETriangleStructure object.
 *
 * \param o The other QTriangleStructure object to make ourself equal to.
 * \return A reference to this, so this operator can be chained.
 */
ETriangleStructure &ETriangleStructure::operator=(const ETriangleStructure &o)
{
	int i, j;

	try
	{
		setHeight(o.getHeight(), ETriangleStructure::None);
		for(i = 0; i < getHeight(); i++)
			for(j = 0; j < getHeight(); j++)
				setAt(i, j, o.at(i, j));
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}

	return (*this);
}

/*!
 * This function clears our entire triangle, freeing up all of its memory and (effectively) setting
 * its size to 0.
 */
void ETriangleStructure::clear()
{
	int i;

	if(data != NULL)
	{
		for(i = 0; i < getHeight(); i++)
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
int ETriangleStructure::getHeight() const
{
	return height;
}

/*!
 * This function sets the height of our triangle. It offers a few different fill mdoes - it can either
 * not fill the new data list at all, or it can try to preserve as much of the old data as it can, or
 * it can write all 0's to the new list.
 *
 * \param h The new height of our triangle.
 * \param f The "FillMode" we will be using.
 */
void ETriangleStructure::setHeight(int h, ETriangleStructure::FillMode f)
{
	int i, j;
	int **newData;

	h = (h >= 0 ? h : 0);

	newData = new int *[h];
	for(i = 0; i < h; i++)
		newData[i] = new int[h];

	try
	{
		if(f != ETriangleStructure::None)
		{
			for(i = 0; i < h; i++)
			{
				for(j = 0; j < h; j++)
				{
					if( isInBounds(i, j) && (f == ETriangleStructure::Preserve) )
						newData[i][j] = at(i, j);
					else
						newData[i][j] = 0;
				}
			}
		}
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
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
 * \exception EOutOfBoundsException This exception is thrown if the given row and/or column are out-of-bounds.
 */
void ETriangleStructure::setAt(int r, int c, int v)
	throw(EOutOfBoundsException &)
{
	if(!isInBounds(r, c))
		throw EOutOfBoundsException("The index provided is out-of-bounds.");

	data[r][c] = v;
}

/*!
 * This function sets every value in an entire row in our triangle. Note that it is up to the caller
 * to make sure the given array of values contains an appropriate number of values for the given row.
 *
 * \param r The row whose values we will be setting.
 * \param v An array of the values we will be setting.
 * \exception EOutOfBoundsException This exception is thrown if the row is out-of-bounds.
 */
void ETriangleStructure::setRowAt(int r, const int *v)
	throw(EOutOfBoundsException &)
{
	int i;

	for(i = 0; i < (r + 1); i++)
		setAt(r, i, v[i]);
}

/*!
 * This function returns the value found at a given position in our triangle.
 *
 * \param r The row on which the value is found.
 * \param c The column in which the value is found.
 * \exception EOutOfBoundsException This exception is thrown if the given row and/or column are out-of-bounds.
 * \return The value found at the given index.
 */
int ETriangleStructure::at(int r, int c) const
	throw(EOutOfBoundsException &)
{
	if(!isInBounds(r, c))
		throw EOutOfBoundsException("The index provided is out-of-bounds.");

	return data[r][c];
}

/*!
 * This function returns the largest possible sum of a path through the triangle, from top
 * to bottom. This function copies our existing triangle in memory so it can operate on it
 * without modifying our object. This function operates in O(n^2) time complexity (note that
 * this is only a fairly tight upper-bound; it actually performs fewer operations), where n
 * is the number of rows in the triangle.
 *
 * \return The largest possible sum of the elements of a path through the triangle, from top to bottom.
 */
int ETriangleStructure::getLargestPathSum() const
{
	int i, j;
	int cL, cR;
	ETriangleStructure t( (*this) );

	try
	{
		for(i = (t.getHeight() - 2); i >= 0; i--)
		{ // For each row from the next-to-last to the first...
			for(j = 0; j < (i + 1); j++)
			{ // For each cell...
				// Set our left-child's value.
				try
				{
					cL = t.leftChildValue(i, j);
				}
				catch(EOutOfBoundsException &e)
				{
					ELUNUSED(e)
					cL = INT_MIN;
				}

				// Set our right-child's value.
				try
				{
					cR = t.rightChildValue(i, j);
				}
				catch(EOutOfBoundsException &e)
				{
					ELUNUSED(e)
					cR = INT_MIN;
				}

				// Our new value is our old value plus the largest child's value.
				t.setAt(i, j, t.at(i, j) + ( cL > cR ? cL : cR ));
			}
		}

		return t.at(0, 0);
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}

	return INT_MIN;
}

/*!
 * This is a convenience function, which returns the value of the "left child" of the cell at the
 * given offset. In this instance, the "left child" is the cell to the bottom left of the given cell,
 * if all of our values were laid out in a triangular shape.
 *
 * \param r The row on which the cell is found.
 * \param c The column in which the cell is found.
 * \exception EOutOfBoundsException This exception is thrown if the given index is out-of-bounds, or if it has no valid left child.
 * \return The value of the given cell's left child.
 */
int ETriangleStructure::leftChildValue(int r, int c) const
	throw(EOutOfBoundsException &)
{
	return at(r + 1, c);
}

/*!
 * This is a convenience function, which returns the value of the "right child" of the cell at the
 * given offset. In this instance, the "right child" is the cell to the bottom right of the given cell,
 * if all of our values were laid out in a triangular shape.
 *
 * \param r The row on which the value is found.
 * \param c The column in which the cell is found.
 * \exception EOutOfBoundsException This exception is thrown if the given index is out-of-bounds, or if it has no valid right child.
 * \return The value of the given cell's right child.
 */
int ETriangleStructure::rightChildValue(int r, int c) const
	throw(EOutOfBoundsException &)
{
	return at(r + 1, c + 1);
}

/*!
 * This is a convenience function, which checks if the given row and column offset is in-bounds in our
 * current triangle.
 *
 * \param r The row on which the cell is found.
 * \param c The column in which the cell is found.
 * \return True if the given offset is in-bounds, or false otherwise.
 */
bool ETriangleStructure::isInBounds(int r, int c) const
{
	return ( ((r >= 0) && (r < getHeight())) && ((c >= 0) && (c < getHeight())) );
}

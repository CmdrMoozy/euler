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

#ifndef INCLUDE_LIBEULER_EULER_TRIANGLE_STRUCTURE_H
#define INCLUDE_LIBEULER_EULER_TRIANGLE_STRUCTURE_H

#include <cstdint>

#include "../EExceptions.h"

/*!
 * \brief This class represents a triangle-shaped data structure.
 *
 * We store the values, behind-the-scenes, in a two-dimensional array. Addressing works such that
 * the first row in the triangle (i.e., the one with only a single value in it) is row "0." The element
 * in a row furthest to the left is element "0." All functions that take an index parameter will throw
 * an exception if you give it a value that is out-of-bounds.
 *
 * This class isn't templated because its uses are VERY specific; it isn't really meant to solve a
 * general problem.
 */
class ETriangleStructure
{
	public:
		/*!
		 * This enum defines what type of fill strategy we will use in cases where we are allocating
		 * new memory (e.g., when resizing a triangle).
		 */
		enum FillMode
		{
			Preserve,
			ZeroOut,
			None
		};
		
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
		
		ETriangleStructure(int h = 0);
		ETriangleStructure(const ETriangleStructure &o);
		virtual ~ETriangleStructure();
		
		ETriangleStructure &operator=(const ETriangleStructure &o);
		
		void clear();
		int getHeight() const;
		void setHeight(int h, ETriangleStructure::FillMode f = ETriangleStructure::Preserve);
		
		void setAt(int r, int c, int v) throw(EOutOfBoundsException &);
		void setRowAt(int r, const int *v) throw(EOutOfBoundsException &);
		int at(int r, int c) const throw(EOutOfBoundsException &);
		
		int getLargestPathSum() const;
	
	private:
		int height;
		int **data;
	
		int leftChildValue(int r, int c) const throw(EOutOfBoundsException &);
		int rightChildValue(int r, int c) const throw(EOutOfBoundsException &);
	
		bool isInBounds(int r, int c) const;
};

#endif

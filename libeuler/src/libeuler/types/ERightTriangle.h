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

#ifndef INCLUDE_LIBEULER_TYPES_RIGHT_TRIANGLE_H
#define INCLUDE_LIBEULER_TYPES_RIGHT_TRIANGLE_H

#include "libeuler/types/ETriangle.h"

#include <cstdint>

/*!
 * \brief This class encapsulates a right triangle.
 *
 * It is very similar to its parent class, ETriangle, except it makes sure the
 *side lengths
 * provided are a RIGHT-angle triangle (i.e., it enforces that a^2 + b^2 = c^2).
 *
 * The other main difference between this class and its parent is that this
 *class normalizes the
 * triangle any time its value is changed -- that is, a triangle with sides {3,
 *4, 5} will be EQUAL
 * to a triangle with sides {4, 3, 5}, since they are just mirror images of each
 *other.
 */
class ERightTriangle : public ETriangle
{
public:
#ifdef LIBEULER_DEBUG
	static void doTestSuite();
#endif

	ERightTriangle(uint32_t a = 0, uint32_t b = 0, uint32_t c = 0);
	ERightTriangle(const ERightTriangle &o);

	ERightTriangle &operator=(const ERightTriangle &o);

	virtual void setA(uint32_t a);
	virtual void setB(uint32_t b);
	virtual void setC(uint32_t c);
	virtual void set(uint32_t a, uint32_t b, uint32_t c);

	virtual bool isValidTriangle() const;

private:
	void normalize();
};

#endif

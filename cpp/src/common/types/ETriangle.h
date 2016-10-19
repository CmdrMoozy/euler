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

#ifndef INCLUDE_LIBEULER_TYPES_TRIANGLE_H
#define INCLUDE_LIBEULER_TYPES_TRIANGLE_H

#include <cstdint>

/*!
 * \brief This class encapsulates a generic triangle.
 *
 * It just keeps track of the three side lengths - a, b and c, checks to make
 * sure lengths provided are indeed a valid triangle (i.e., any two sides added
 * together is greater than the third side), and allows for various
 * mathematical manipulation of them.
 */
class ETriangle
{
public:
	ETriangle(uint32_t a = 0, uint32_t b = 0, uint32_t c = 0);
	ETriangle(const ETriangle &o);

	virtual ~ETriangle();

	ETriangle &operator=(const ETriangle &o);

	bool operator==(const ETriangle &o) const;
	bool operator<(const ETriangle &o) const;
	bool operator>(const ETriangle &o) const;
	bool operator<=(const ETriangle &o) const;
	bool operator>=(const ETriangle &o) const;

	uint32_t getA() const;
	virtual void setA(uint32_t a);
	uint32_t getB() const;
	virtual void setB(uint32_t b);
	uint32_t getC() const;
	virtual void setC(uint32_t c);
	virtual void set(uint32_t a, uint32_t b, uint32_t c);

	virtual bool isValidTriangle() const;

protected:
	virtual uint64_t hash() const;

private:
	uint32_t sideA, sideB, sideC;

	void clear();
};

#endif

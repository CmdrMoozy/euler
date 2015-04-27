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

#include "ERightTriangle.h"

#include <algorithm>

#include "libeuler/math/Math.h"

#ifdef LIBEULER_DEBUG
	#include <iostream>

	#include "libeuler/EDefines.h"
#endif

#ifdef LIBEULER_DEBUG
/*!
 * This function implements our test suite for this class. It uses non-abort()'ing
 * assertions, and merely prints the result to stdout.
 */
void ERightTriangle::doTestSuite()
{
	bool success;

	std::cout << "\tTesting 'ERightTriangle'...\t\t";
	try
	{
		success = true;

		ERightTriangle t;

		t.set(5, 3, 4);

		// Test normalization.
		EASSERT( (t.getA() < t.getB()) && (t.getB() < t.getC()) )

		// Test some right triangles.
		t.set(3, 4, 5);
		EASSERT(t.isValidTriangle())
		t.set(5, 12, 13);
		EASSERT(t.isValidTriangle())
		t.set(7, 24, 25);
		EASSERT(t.isValidTriangle())
		t.set(8, 15, 17);
		EASSERT(t.isValidTriangle())
		t.set(9, 40, 41);
		EASSERT(t.isValidTriangle())
		t.set(11, 60, 61);
		EASSERT(t.isValidTriangle())
		t.set(12, 35, 37);
		EASSERT(t.isValidTriangle())
		t.set(13, 84, 85);
		EASSERT(t.isValidTriangle())
		t.set(16, 63, 65);
		EASSERT(t.isValidTriangle())
		t.set(20, 21, 29);
		EASSERT(t.isValidTriangle())
		t.set(28, 45, 53);
		EASSERT(t.isValidTriangle())
		t.set(33, 56, 65);
		EASSERT(t.isValidTriangle())
		t.set(36, 77, 85);
		EASSERT(t.isValidTriangle())
		t.set(39, 80, 89);
		EASSERT(t.isValidTriangle())
		t.set(48, 55, 73);
		EASSERT(t.isValidTriangle())
		t.set(65, 72, 97);
		EASSERT(t.isValidTriangle())

		// Test some non-right-triangles.

		t.set(3, 4, 6);
		EASSERT(!t.isValidTriangle())
		t.set(5, 11, 13);
		EASSERT(!t.isValidTriangle())
		t.set(8, 24, 25);
		EASSERT(!t.isValidTriangle())
		t.set(8, 15, 18);
		EASSERT(!t.isValidTriangle())
		t.set(9, 33, 41);
		EASSERT(!t.isValidTriangle())
	}
	catch(EAssertionException &e)
	{
		ELUNUSED(e)
		success = false;
	}

	// Print out our results.
	if(success)
		std::cout << "[ OK ]\n";
	else
		std::cout << "[FAIL]\n";
}
#endif

/*!
 * This is our default constructor, which initializes a new ERightTriangle.
 */
ERightTriangle::ERightTriangle(uint32_t a, uint32_t b, uint32_t c)
	: ETriangle(a, b, c)
{
	normalize();
}

/*!
 * This is our copy constructor, which initializes our triangle to a value equal to that of the given other
 * triangle.
 *
 * \param o The other object to make ourself equal to.
 */
ERightTriangle::ERightTriangle(const ERightTriangle &o)
	: ETriangle(o)
{
	normalize();
}

/*!
 * This is our assignment operator, which makes our value equal to that of the given other triangle.
 *
 * \param o The other object to make ourself equal to.
 * \return A reference to this, so the operator can be chained.
 */
ERightTriangle &ERightTriangle::operator=(const ERightTriangle &o)
{
	this->ETriangle::operator=(o);
	normalize();
	return (*this);
}

/*!
 * This function sets the value of our "A" side.
 *
 * \param a The new legnth of side A.
 */
void ERightTriangle::setA(uint32_t a)
{
	this->ETriangle::setA(a);
	normalize();
}

/*!
 * This function sets the value of our "B" side.
 *
 * \param a The new legnth of side B.
 */
void ERightTriangle::setB(uint32_t b)
{
	this->ETriangle::setB(b);
	normalize();
}

/*!
 * This function sets the value of our "C" side.
 *
 * \param a The new legnth of side C.
 */
void ERightTriangle::setC(uint32_t c)
{
	this->ETriangle::setC(c);
	normalize();
}

/*!
 * This function sets the side lengths of our triangle. Note that if the lengths provided do not
 * constitute a valid triangle, then our triangle is cleared (i.e., all side lengths are set to 0).
 *
 * \param a The new length of side A.
 * \param a The new length of side B.
 * \param a The new length of side C.
 */
void ERightTriangle::set(uint32_t a, uint32_t b, uint32_t c)
{
	this->ETriangle::setA(a);
	this->ETriangle::setB(b);
	this->ETriangle::setC(c);

	normalize();
}

/*!
 * This is a reimplemented version of the same function on our parent class. It tests whether or not our triangle
 * is valid (i.e., if the sum of any two sides is greater than the length of the third side), and it additionally
 * makes sure we are a RIGHT triangle (i.e., a^2 + b^2 = c^2 holds true).
 *
 * \return True if our triangle is valid, or false otherwise.
 */
bool ERightTriangle::isValidTriangle() const
{
	uint64_t c;

	if(!this->ETriangle::isValidTriangle())
		return false;

	c = euler::math::ipow(getA(), 2) + euler::math::ipow(getB(), 2);
	return (c == euler::math::ipow(getC(), 2));
}

/*!
 * This is our internal function which normalizes our triangle. That is, a triangle with sides {3, 4, 5} will be
 * treated as equal to a triangle with sides {4, 3, 5}, since they are just mirror images of each other. This is
 * achieved by ensuring that the GREATER of A and B is always assigned to A, and the other value is always assigned
 * to B.
 */
void ERightTriangle::normalize()
{
	uint32_t a, b, c;

	c = std::max<uint32_t>( std::max<uint32_t>(getA(), getB()), getC() );
	a = std::min<uint32_t>( std::min<uint32_t>(getA(), getB()), getC() );
	b = (getA() + getB() + getC()) - (a+c);

	this->ETriangle::setA(a);
	this->ETriangle::setB(b);
	this->ETriangle::setC(c);
}

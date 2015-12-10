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

#include "ETriangle.h"

/*!
 * This is a convenience constructor, which allows a new object to be created
 * with initial side lengths given.
 *
 * \param a The length of side A.
 * \param b The length of side B.
 * \param c The length of side C.
 */
ETriangle::ETriangle(uint32_t a, uint32_t b, uint32_t c)
{
	set(a, b, c);
}

/*!
 * This is our copy constructor, which initializes our object to be equal to the
 * given other ETriangle object.
 *
 * \param o The other object to make ourself equal to.
 */
ETriangle::ETriangle(const ETriangle &o)
{
	(*this) = o;
}

/*!
 * This is our default destructor, which cleans up & destroys our object.
 */
ETriangle::~ETriangle()
{
}

/*!
 * This is our assignment operator, which makes our value equal to that of the
 * given other value, and returns a reference to this so the operator can be
 * chained.
 *
 * \param o The other object to make ourself equal to.
 * \return A reference to this, so the operator can be chained.
 */
ETriangle &ETriangle::operator=(const ETriangle &o)
{
	set(o.getA(), o.getB(), o.getC());
	return (*this);
}

/*!
 * This is our equivalence operator, which tests if our triangle is equal to the
 * given other triangle.
 *
 * \param o The other triangle to compare ourself to.
 * \return True if our triangles are exactly equal, or false otherwise.
 */
bool ETriangle::operator==(const ETriangle &o) const
{
	return (hash() == o.hash());
}

/*!
 * This is one of our comparison operators -- it tests if our triangle is less
 * than the given other triangle. Note that this operator exists purely so our
 * objects could be inserted into, for instance, a binary search tree, which
 * requires the elements to be sorted -- the value compared is that of our
 * protected hash() function, which could be overriden arbitrarily.
 *
 * \param o The other triangle to compare ourself to.
 * \return True if we are less than the given other object, or false otherwise.
 */
bool ETriangle::operator<(const ETriangle &o) const
{
	return (hash() < o.hash());
}

/*!
 * This is one of our comparison operators -- it tests if our triangle is
 * greater than the given other triangle. Note that this operator exists purely
 * so our objects could be inserted into, for instance, a binary search tree,
 * which requires the elements to be sorted -- the value compared is that of
 * our protected hash() function, which could be overriden arbitrarily.
 *
 * \param o The other triangle to compare ourself to.
 * \return True if we are greater than the given other object, or false.
 */
bool ETriangle::operator>(const ETriangle &o) const
{
	return (hash() > o.hash());
}

/*!
 * This is one of our comparison operators -- it tests if our triangle is less
 * than or equal to the given other triangle. Note that this operator exists
 * purely so our objects could be inserted into, for instance, a binary search
 * tree, which requires the elements to be sorted -- the value compared is that
 * of our protected hash() function, which could be overriden arbitrarily.
 *
 * \param o The other triangle to compare ourself to.
 * \return True if we are less than or equal to the other object, or false.
 */
bool ETriangle::operator<=(const ETriangle &o) const
{
	return (hash() <= o.hash());
}

/*!
 * This is one of our comparison operators -- it tests if our triangle is
 * greater than or equal to the given other triangle. Note that this operator
 * exists purely so our objects could be inserted into, for instance, a binary
 * search tree, which requires the elements to be sorted -- the value compared
 * is that of our protected hash() function, which could be overriden
 * arbitrarily.
 *
 * \param o The other triangle to compare ourself to.
 * \return True if we are greater than or equal to the other object, or false.
 */
bool ETriangle::operator>=(const ETriangle &o) const
{
	return (hash() >= o.hash());
}

/*!
 * This function retrieves our stored value of side A.
 *
 * \return The length of side A.
 */
uint32_t ETriangle::getA() const
{
	return sideA;
}

/*!
 * This function sets the value of our "A" side.
 *
 * \param a The new legnth of side A.
 */
void ETriangle::setA(uint32_t a)
{
	sideA = a;
}

/*!
 * This function retrieves our stored value of side B.
 *
 * \return The length of side B.
 */
uint32_t ETriangle::getB() const
{
	return sideB;
}

/*!
 * This function sets the value of our "B" side.
 *
 * \param b The new legnth of side B.
 */
void ETriangle::setB(uint32_t b)
{
	sideB = b;
}

/*!
 * This function retrieves our stored value of side C.
 *
 * \return The length of side C.
 */
uint32_t ETriangle::getC() const
{
	return sideC;
}

/*!
 * This function sets the value of our "C" side.
 *
 * \param c The new legnth of side C.
 */
void ETriangle::setC(uint32_t c)
{
	sideC = c;
}

/*!
 * This function sets the side lengths of our triangle. Note that if the lengths
 * provided do not constitute a valid triangle, then our triangle is cleared
 * (i.e., all side lengths are set to 0).
 *
 * \param a The new length of side A.
 * \param b The new length of side B.
 * \param c The new length of side C.
 */
void ETriangle::set(uint32_t a, uint32_t b, uint32_t c)
{
	setA(a);
	setB(b);
	setC(c);
}

/*!
 * This function tests whether or not our triangle is valid (i.e., if the
 * lengths of any two sides added together is greater than the length of the
 * third side).
 *
 * \return True if our triangle is valid, or false otherwise.
 */
bool ETriangle::isValidTriangle() const
{
	return (((sideA + sideB) > sideC) && ((sideA + sideC) > sideB) &&
	        ((sideB + sideC) > sideA));
}

/*!
 * This is our internal hash function, which is used to implement our comparison
 * operators.
 *
 * Note that our default implementation of this function DEPENDS ON OUR VALUE;
 * so if we are already inside a sorted container, and our sides are modified,
 * then the results are undefined.
 *
 * \return A hash code unique to this particular triangle.
 */
uint64_t ETriangle::hash() const
{
	uint64_t r = getA();
	uint32_t b = getB(), c = getC();

	while(b > 0)
	{
		r *= 10;
		b /= 10;
	}

	r += getB();

	while(c > 0)
	{
		r *= 10;
		c /= 10;
	}

	r += getC();

	return r;
}

/*!
 * This utility function clears our triangle, or in other words, sets all of our
 * side lengths to 0.
 */
void ETriangle::clear()
{
	sideA = sideB = sideC = 0;
}

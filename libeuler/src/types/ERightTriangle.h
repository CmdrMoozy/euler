#ifndef INCLUDE_LIBEULER_TYPES_RIGHT_TRIANGLE_H
#define INCLUDE_LIBEULER_TYPES_RIGHT_TRIANGLE_H

#include "../types/ETriangle.h"

#include <cstdint>

/*!
 * \brief This class encapsulates a right triangle.
 *
 * It is very similar to its parent class, ETriangle, except it makes sure the side lengths
 * provided are a RIGHT-angle triangle (i.e., it enforces that a^2 + b^2 = c^2).
 *
 * The other main difference between this class and its parent is that this class normalizes the
 * triangle any time its value is changed -- that is, a triangle with sides {3, 4, 5} will be EQUAL
 * to a triangle with sides {4, 3, 5}, since they are just mirror images of each other.
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

#ifndef INCLUDE_LIBEULER_TYPES_TRIANGLE_H
#define INCLUDE_LIBEULER_TYPES_TRIANGLE_H

#include <cstdint>

/*!
 * \brief This class encapsulates a generic triangle.
 *
 * It just keeps track of the three side lengths - a, b and c, checks to make sure lengths provided are
 * indeed a valid triangle (i.e., any two sides added together is greater than the third side), and allows
 * for various mathematical manipulation of them.
 */
class ETriangle
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
		
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

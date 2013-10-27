#ifndef INCLUDE_LIBEULER_EULER_SPIRAL_H
#define INCLUDE_LIBEULER_EULER_SPIRAL_H

#include <cstdint>
#include <vector>

/*!
 * \brief This class represents an n by n matrix (where n is odd) filled in in a spiral pattern.
 *
 * It is such that the CENTER cell's value is 1, and the following cells are filled in
 * in clockwise order, starting with the cell to the immediate right of the center, incrementing
 * the value by 1 with each new cell.
 *
 * Note that addressing is done with (0, 0) being the CENTER cell, (1, 1) II being the cell
 * to the top-left, (1, 1) IV being the cell to the bottom-right and so on.
 */
class ESpiral
{
	public:
		/*!
		 * This enum represents a quadrant, according to the cartesian quadrants
		 * (such that quadrant 1 is to the top-right of (0, 0), and they progress
		 * counter-clockwise).
		 */
		enum Quadrant
		{
			I   = 0,
			II  = 1,
			III = 2,
			IV  = 3
		};
		
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
		
		ESpiral();
		virtual ~ESpiral();
		
		int getSizeFor(int o);
		
		void begin();
		uint64_t next();
		uint64_t previous();
		
		void clearCache();
		
		uint64_t diagonalValueAt(uint32_t o, ESpiral::Quadrant q);
		
	private:
		static const ESpiral::Quadrant fsmNext[4];
		static const ESpiral::Quadrant fsmPrevious[4];
	
		std::vector<uint64_t> cacheI, cacheII, cacheIII, cacheIV;
		
		ESpiral::Quadrant currentQuadrant;
		int currentOffset;
		uint64_t currentValue;
};

#endif

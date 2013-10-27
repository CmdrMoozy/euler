#ifndef INCLUDE_LIBEULER_EULER_NUMBER_GRID_H
#define INCLUDE_LIBEULER_EULER_NUMBER_GRID_H

#include "../structs/EGrid.h"

// Forward Declarations
class EOutOfBoundsException;

class ENumberGrid : public EGrid<int>
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
	
		ENumberGrid(int s = 0);
	
		int greatestConsecutiveProduct(int n) const throw(EOutOfBoundsException &);
};

#endif

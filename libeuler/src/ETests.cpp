#include "euler/ECircularPrimeSieve.h"
#include "euler/EFastTotient.h"
#include "euler/ENumberGrid.h"
#include "euler/EPoker.h"
#include "euler/ESpiral.h"
#include "euler/ETriangleStructure.h"
#include "geodesy/EGeoCoord.h"
#include "math/EFactorization.h"
#include "math/EMath.h"
#include "math/EPrimeSieve.h"
#include "util/EArray.h"
#include "util/EArrayUtilities.h"
#include "util/EBitwise.h"
#include "util/EByteArray.h"
#include "util/EDate.h"
#include "util/EProfiler.h"
#include "structs/EHashMap.h"
#include "structs/EGrid.h"
#include "types/EBigInteger.h"
#include "types/EDigitInteger.h"
#include "types/EFraction.h"
#include "types/ERightTriangle.h"
#include "types/ETriangle.h"

#include <iostream>

int main(void)
{
	std::cout << "Running test suite for entirety of libeuler...\n";
	
	ECircularPrimeSieve::doTestSuite();
	EFastTotient::doTestSuite();
	ENumberGrid::doTestSuite();
	EPoker::doTestSuite();
	ESpiral::doTestSuite();
	ETriangleStructure::doTestSuite();
	EGeoCoord::doTestSuite();
	EFactorization::doTestSuite();
	EMath::doTestSuite();
	EPrimeSieve::doTestSuite();
	EArray<int>::doTestSuite();
	EArrayUtilities::doTestSuite();
	EBitwise::doTestSuite();
	EByteArray::doTestSuite();
	EDate::doTestSuite();
	EProfiler::doTestSuite();
	EHashMap<int, int>::doTestSuite();
	EGrid<int>::doTestSuite();
	EBigInteger::doTestSuite();
	EDigitInteger::doTestSuite();
	EFraction::doTestSuite();
	ERightTriangle::doTestSuite();
	ETriangle::doTestSuite();
}

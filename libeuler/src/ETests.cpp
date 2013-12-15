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

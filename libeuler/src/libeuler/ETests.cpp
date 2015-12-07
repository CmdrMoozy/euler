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

#include "libeuler/euler/ECircularPrimeSieve.h"
#include "libeuler/euler/EFastTotient.h"
#include "libeuler/euler/ENumberGrid.h"
#include "libeuler/euler/EPoker.h"
#include "libeuler/euler/ESpiral.h"
#include "libeuler/euler/ETriangleStructure.h"
#include "libeuler/geodesy/EGeoCoord.h"
#include "libeuler/math/EFactorization.h"
#include "libeuler/math/EMath.h"
#include "libeuler/util/EArray.h"
#include "libeuler/util/EArrayUtilities.h"
#include "libeuler/util/EBitwise.h"
#include "libeuler/util/EByteArray.h"
#include "libeuler/util/EDate.h"
#include "libeuler/util/Profiler.h"
#include "libeuler/structs/EGrid.h"
#include "libeuler/types/EBigInteger.h"
#include "libeuler/types/ERightTriangle.h"
#include "libeuler/types/ETriangle.h"

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
	EArray<int>::doTestSuite();
	EArrayUtilities::doTestSuite();
	EBitwise::doTestSuite();
	EByteArray::doTestSuite();
	EDate::doTestSuite();
	euler::Profiler::doTestSuite();
	EGrid<int>::doTestSuite();
	EBigInteger::doTestSuite();
	ERightTriangle::doTestSuite();
	ETriangle::doTestSuite();
}

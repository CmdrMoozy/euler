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

#include "ESpiral.h"

#include "EDefines.h"

#ifdef LIBEULER_DEBUG
	#include <iostream>
#endif

// Initialize our static class constants.
const ESpiral::Quadrant ESpiral::fsmNext[4] = {ESpiral::IV, ESpiral::I, ESpiral::II, ESpiral::III};
const ESpiral::Quadrant ESpiral::fsmPrevious[4] = {ESpiral::II, ESpiral::III, ESpiral::IV, ESpiral::I};

#ifdef LIBEULER_DEBUG
/*!
 * This function implements our test suite for this class. It uses non-abort()'ing
 * assertions, and merely prints the result to stdout.
 */
void ESpiral::doTestSuite()
{
	bool success;
	
	std::cout << "\tTesting 'ESpiral'...\t\t\t";
	try
	{
		success = true;
		
		/*
		 * We test that our class generates correct numbers by solving a known problem. It is known that the sum
		 * of the numbers on the diagonals (the ones our class generates) in a spiral grid of 1001 x 1001 elements
		 * is 669171001.
		 */
		
		ESpiral s;
		uint64_t result = 1;
		int i;
		
		i = 1;
		while(s.getSizeFor(i) <= 1001)
		{
			result += s.diagonalValueAt(i, ESpiral::I);
			result += s.diagonalValueAt(i, ESpiral::II);
			result += s.diagonalValueAt(i, ESpiral::III);
			result += s.diagonalValueAt(i, ESpiral::IV);
			
			++i;
		}
		
		EASSERT(result == 669171001)
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
 * This is our default constructor, which creates a new ESpiral object.
 */
ESpiral::ESpiral()
{
	begin();
}

/*!
 * This is our default destructor, which cleans up & destroys our object.
 */
ESpiral::~ESpiral()
{
}

/*!
 * This function returns the size of a matrix that would be required for offset (o, o) to be
 * in-bounds.
 *
 * \param o The desired offset.
 * \return The minimum size required for the offset to be in-bounds.
 */
int ESpiral::getSizeFor(int o)
{
	// The size for offset o is the oth odd number.
	return (1 + (o * 2));
}

/*!
 * This is one of our functions that allows this class to be used like an iterator. You call begin()
 * to reset to the beginning of the spiral, at which point next() and previous() will return the next
 * and previous values respectively.
 */
void ESpiral::begin()
{
	currentQuadrant = ESpiral::I;
	currentOffset = 0;
	currentValue = 1;
}

/*!
 * This function is one of our iterator-style accessors. It returns our current value, and the moves our
 * state to the next value in a clockwise direction.
 *
 * \return Our current value; calculated by the most recent call to previous() or next().
 */
uint64_t ESpiral::next()
{
	uint64_t r = currentValue;
	
	if(r > 1)
	{
		if(currentQuadrant == ESpiral::I) ++currentOffset;
		currentValue += static_cast<uint64_t>(EABS(getSizeFor(currentOffset) - 1));
		currentQuadrant = ESpiral::fsmNext[currentQuadrant];
	}
	else
	{
		currentValue = 3;
		currentOffset = 1;
		currentQuadrant = ESpiral::IV;
	}
	
	return r;
}

/*!
 * This function is one of our iterator-style accessors. It returns our current value, and the moves our
 * state to the previous value in a clockwise direction.
 *
 * \return Our current value; calculated by the most recent call to previous() or next().
 */
uint64_t ESpiral::previous()
{
	uint64_t r = currentValue;
	
	if(r > 3)
	{
		if(currentQuadrant == ESpiral::IV)
		{
			--currentOffset;
			currentValue += 2;
		}
		
		currentValue -= getSizeFor(currentOffset) - 1;
		currentQuadrant = ESpiral::fsmPrevious[currentQuadrant];
	}
	else if(r == 3)
	{
		currentValue = 1;
		currentOffset = 0;
		currentQuadrant = ESpiral::I;
	}
	else if(r == 1)
	{
		begin();
	}
	
	return r;
}

/*!
 * This function clears our class's cache. We use this cache to DRASTICALLY speed up calls to
 * diagonalValueAt(), but this takes up a decently large chunk of memory. Calling this function
 * will reset our cache to that of a new default-cosntructed QSpiral, but subsequent calls
 * to the aforementioned functions will be slower (until the cache is rebuilt).
 */
void ESpiral::clearCache()
{
	cacheI.clear();
	cacheII.clear();
	cacheIII.clear();
	cacheIV.clear();
}

/*!
 * This function returns the value of the cell that is (o, o) away from (0, 0), in the given
 * quadrant q. Note that this function assumes that our spiral was filled in using a CLOCKWISE
 * pattern; counter-clockwise can easily be accounted for by, as the caller, translating the
 * quadrant argument.
 *
 * \param o The offset from (0, 0).
 * \param q The quadrant in which the desired cell lies.
 * \return The value of the cell at the indicated position.
 */
uint64_t ESpiral::diagonalValueAt(uint32_t o, ESpiral::Quadrant q)
{
	uint64_t r, nS, m;
	
	// This function is recursive, and this is our terminating-condition.
	if(o == 0)
		return 1;
	
	// Check if we have already calculated this value.
	switch(q)
	{
		case ESpiral::I:
			if(o < cacheI.size())
				if(cacheI[o] > 0)
					return cacheI[o];
			
			break;
		
		case ESpiral::II:
			if(o < cacheII.size())
				if(cacheII[o] > 0)
					return cacheII[o];
		
			break;
		
		case ESpiral::III:
			if(o < cacheIII.size())
				if(cacheIII[o] > 0)
					return cacheIII[o];
		
			break;
		
		case ESpiral::IV:
			if(o < cacheIV.size())
				if(cacheIV[o] > 0)
					return cacheIV[o];
		
			break;
	};
	
	// Determine our size.
	nS = getSizeFor(o);
	
	// Start with the previous diagonal value, at (o-1, o-1).
	r = diagonalValueAt(o - 1, ESpiral::I) + ((nS - 1) * 4);;
	
	// Determine the correct multiplier based on the quadrant.
	switch(q)
	{
		case ESpiral::I:
			m = 0;
			break;
		
		case ESpiral::II:
			m = 1;
			break;
		
		case ESpiral::III:
			m = 2;
			break;
		
		case ESpiral::IV:
		default:
			m = 3;
			break;
	};
	
	// Backtrack a bit to get the right answer.
	r -= ((nS - 1) * m);
	
	// Cache our answer.
	switch(q)
	{
		case ESpiral::I:
			while(cacheI.size() <= o)
				cacheI.resize(cacheI.size() + 100, 0);
		
			cacheI[o] = r;
			
			break;
		
		case ESpiral::II:
			while(cacheII.size() <= o)
				cacheII.resize(cacheII.size() + 100, 0);
			
			cacheII[o] = r;
		
			break;
		
		case ESpiral::III:
			while(cacheIII.size() <= o)
				cacheIII.resize(cacheIII.size() + 100, 0);
			
			cacheIII[o] = r;
		
			break;
		
		case ESpiral::IV:
			while(cacheIV.size() <= o)
				cacheIV.resize(cacheIV.size() + 100, 0);
			
			cacheIV[o] = r;
			
			break;
	};
	
	// Return our result.
	return r;
}


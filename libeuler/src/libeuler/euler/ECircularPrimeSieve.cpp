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

#include "ECircularPrimeSieve.h"

#include <map>

#include "libeuler/types/EDigitInteger.h"

/*!
 * This is our default constructor, which initializes a new
 * EulerCircularPrimeSieve object with a limit of 0.
 */
ECircularPrimeSieve::ECircularPrimeSieve() : EPrimeSieve()
{
}

/*!
 * This is a reimplementation of generatePrimes(), which will generate the same
 * list as our parent, but will then remove all of the non-circular primes,
 * leaving us with a functional EulerCircularPrimeSieve.
 */
void ECircularPrimeSieve::generatePrimes()
{
	EDigitInteger number, tnumber;
	std::map<uint32_t, PrimeCategory> resultsMap;
	std::set<uint32_t>::iterator sit;
	std::map<uint32_t, PrimeCategory>::iterator mit, tmit;
	int digit;

	// Generate our initial list of primes.
	EPrimeSieve::generatePrimes();

	// Copy our prime numbers into our map.
	for(sit = begin(); sit != end(); sit++)
		resultsMap.insert(
		        std::pair<uint32_t, PrimeCategory>((*sit), Untested));

	// Filter out the non-circular primes.
	for(mit = resultsMap.begin(); mit != resultsMap.end(); mit++)
	{
		// If we've already determined this value, continue.
		if(mit->second != Untested)
			continue;

		// If this prime is a single digit, then it is by definition
		// circular.
		if(mit->first < 10)
		{
			mit->second = Circular;
			continue;
		}

		// Our number cannot contain 0, 2, 4, 5, 6 or 8, or it is
		// definitely not a circular prime.
		number = mit->first;
		for(std::size_t i = 0; i < number.digitCount(); i++)
		{
			digit = number.get(i);
			if((digit == 0) || (digit == 2) || (digit == 4) ||
			   (digit == 5) || (digit == 6) || (digit == 8))
			{
				// Mark this current number as non-circular.
				mit->second = NotCircular;
				break;
			}
		}

		// If we've already determined that our number is non-circular,
		// continue.
		if(mit->second == NotCircular)
			continue;

		// Take the current number, and go through all its rotations. If
		// we find one that isn't prime, mark the original not circular.
		tnumber = number;
		for(std::size_t i = 0; i < (tnumber.digitCount() - 1); i++)
		{
			tnumber.leftDigitalRotate(1);
			tmit = resultsMap.find(
			        static_cast<uint32_t>(tnumber.toInteger()));
			if(tmit == resultsMap.end())
			{
				mit->second = NotCircular;
				break;
			}
		}

		// Set this number and all of its rotations as being the proper
		// type.
		if(mit->second == NotCircular)
		{ // If our number was marked not circular, we need to mark ALL
			// of its rotations not circular.
			for(std::size_t i = 0; i < (number.digitCount() - 1);
			    i++)
			{
				number.leftDigitalRotate(1);
				tmit = resultsMap.find(static_cast<uint32_t>(
				        number.toInteger()));
				if(tmit != resultsMap.end())
				{
					tmit->second = NotCircular;
				}
			}
		}
		else
		{ // Otherwise, mark ALL rotations as BEING CIRCULAR.
			mit->second = Circular;
			for(std::size_t i = 0; i < (number.digitCount() - 1);
			    i++)
			{
				number.leftDigitalRotate(1);
				tmit = resultsMap.find(static_cast<uint32_t>(
				        number.toInteger()));
				if(tmit != resultsMap.end())
					tmit->second = Circular;
			}
		}
	}

	// Iterate through our temporary map and remove all of the non-circular
	// primes from our sieve.
	for(mit = resultsMap.begin(); mit != resultsMap.end(); mit++)
	{
		if(mit->second == NotCircular)
			erase(mit->first);
	}
}

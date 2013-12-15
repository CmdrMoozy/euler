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

#ifndef INCLUDE_LIBEULER_EULER_CIRCULAR_PRIME_SIEVE_H
#define INCLUDE_LIBEULER_EULER_CIRCULAR_PRIME_SIEVE_H

#include "../math/EPrimeSieve.h"

/*!
 * \brief This is an extension of our sieve which searches for circular primes only.
 *
 * It behaves in exactly the same way, except after the primes are generated it proceeds
 * to filter out all non-circular primes.
 */
class ECircularPrimeSieve : public EPrimeSieve
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
	
		ECircularPrimeSieve();
	
	protected:
		virtual void generatePrimes();
	
	private:
		/*!
		 * This enum represents the category of a given prime, whether it hasn't been tested yet,
		 * is definitely Circular, or definitely NotCircular. It is used only internally.
		 */
		enum PrimeCategory
		{
			Untested,
			Circular,
			NotCircular
		};
};

#endif

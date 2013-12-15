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

#include <iostream>
#include <cassert>
#include <cmath>
#include <set>

#include "libeuler/math/EPrimeSieve.h"

#define INITIAL_SIEVE_LIMIT 1000000
#define SIEVE_LIMIT_MULTIPLIER 2

#define LOWER_BOUND 9

/* 
 * It was proposed by Christian Goldbach that every odd composite number can be written as the
 * sum of a prime and twice a square.
 *
 *     9 = 7 + (2 * 1^2)
 *     15 = 7 + (2 * 2^2)
 *     21 = 3 + (2 * 3^2)
 *     25 = 7 + (2 * 3^2)
 *     27 = 19 + (2 * 2^2)
 *     33 = 31 + (2 * 1^2)
 *
 * It turns out that the conjecture was false.
 *
 * What is the smallest odd composite that cannot be written as the sum of a prime and twice a
 * square?
 */

int main(void)
{
	EPrimeSieve sieve;
	std::set<uint32_t>::iterator sit;
	uint32_t n, d;
	double r;
	bool isResult;
	
	sieve.setLimit(INITIAL_SIEVE_LIMIT);
	
	isResult = false;
	for(n = LOWER_BOUND; ; n += 2)
	{ // For each odd composite n...

		// Increase sieve limit as needed.
		while(n > sieve.getLimit())
			sieve.setLimit(sieve.getLimit() * SIEVE_LIMIT_MULTIPLIER);
		
		// Don't test primes.
		if(sieve.contains(n))
			continue;
		
		isResult = true;
		for(sit = sieve.begin(); (sit != sieve.end()) && ((*sit) < n); ++sit)
		{ // For each prime less than n...
			
			// Get our difference.
			d = (n - (*sit));
			
			// The difference must be twice a square, so if it is not even then continue.
			if((d&1))
				continue;
			
			// Get rid of easy possibilities first.
			if( (d == 2) || (d == 8) || (d == 18) )
			{
				isResult = false;
				break;
			}
			
			// Test if this particular prime can be written as twice a square.
			d /= 2;
			r = sqrt(static_cast<double>(d));
			if(r == floor(r))
			{
				isResult = false;
				break;
			}
			
		}
		
		if(isResult)
			break;
		
	}
	
	std::cout << "The smallest odd composite that doesn't fit Goldbach's conjecture is: " << n << "\n";
	
	assert(n == 5777);
	return 0;
}

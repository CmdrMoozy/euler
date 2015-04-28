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

#include <iostream>
#include <cassert>
#include <cstdint>
#include <vector>
#include <algorithm>

#include "libeuler/math/Math.h"
#include "libeuler/math/EPrimeSieve.h"

/*
 * Euler's Totient function, phi(n), is used to determine the number of numbers less than n which are
 * relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively
 * prime to nine, phi(9) = 6.
 *
 * |----|-------------|--------|------------|
 * | n  | Coprimes    | phi(n) | n / phi(n) |
 * |----|-------------|--------|------------|
 * | 2  | 1           | 1      | 2          |
 * | 3  | 1,2         | 2      | 1.5        |
 * | 4  | 1,3         | 2      | 2          |
 * | 5  | 1,2,3,4     | 4      | 1.25       |
 * | 6  | 1,5         | 2      | 3          |
 * | 7  | 1,2,3,4,5,6 | 6      | 1.1666...  |
 * | 8  | 1,3,5,7     | 4      | 2          |
 * | 9  | 1,2,4,5,7,8 | 6      | 1.5        |
 * | 10 | 1,3,7,9     | 4      | 2.5        |
 * |----|-------------|--------|------------|
 *
 * It can be seen that n=6 produces a maximum n / phi(n) for n <= 10.
 *
 * Find the value of n <= 1,000,000 for which n / phi(n) is a maximum.
 */

/*!
 * This function generates a list of all numbers less than or equal to n, excluding 1. The result is
 * given in a vector, which contains a list of numbers which themselves are represented as a list of
 * prime factors (non-squarefree numbers are represented by repeating prime factors in this list).
 *
 * \param p The prime number sieve to use to generate composites.
 * \param n The upper limit for generation.
 * \param m The minimum prime factor to be looked at (use default value for initial call).
 * \return A list of all numbers less than or equal to n, excluding 1.
 */
std::vector< std::vector<uint32_t> > composites(EPrimeSieve &p, uint32_t n, uint32_t m = 0)
{
	std::vector< std::vector<uint32_t> > r;

	for(std::set<uint32_t>::iterator it = p.begin(); it != p.end(); ++it)
	{
		if( (*it) > n )
			break;

		if( (*it) < m )
			continue;

		std::vector<uint32_t> tmp(1, (*it));
		r.push_back(tmp);

		std::vector< std::vector<uint32_t> > s = composites(p, n / (*it), (*it));
		for(size_t sit = 0; sit < s.size(); ++sit)
		{
			tmp = s[sit];
			tmp.push_back( (*it) );
			r.push_back(tmp);
		}
	}

	return r;
}

/*!
 * This function calculates the totient of the given number. The vector given is assumed to be a PRIME FACTORIZATION
 * of the number, where non-squarefree numbers are simply represented by repeated primes in the given list. Also note
 * that, for non-squarefree integers, the given list needs to be SORTED (either ascending or descending will work).
 *
 * \param n The number whose totient we will calculate.
 * \return The totient of n.
 */
uint32_t totient(const std::vector<uint32_t> &n)
{
	uint32_t t = 0, h, p, e;
	size_t i = 0, j;

	while(i < n.size())
	{
		// Retrieve the current prime.

		p = n[i];

		// Calculate its exponent, based upon how many times the prime is repeated.

		for(j = i + 1; j < n.size(); ++j)
		{
			if(n[j] != p)
				break;
		}

		e = j - i;
		i = j;

		// Calculate the totient!

		h = euler::math::ipow(p, e - 1) * (p - 1);
		t = (t == 0) ? h : t * h;
	}

	return t;
}

int main(void)
{
	EPrimeSieve sieve(1000000);
	uint32_t maxn = 0, n;
	double maxr = 0.0, r;

	std::vector< std::vector<uint32_t> > numbers = composites(sieve, 1000000);
	struct scmp {
		bool operator()(uint32_t a, uint32_t b) {
			return a < b;
		}
	} cmp;

	for(size_t i = 0; i < numbers.size(); ++i)
	{
		std::sort(numbers[i].begin(), numbers[i].end(), cmp);

		n = 1;
		for(size_t j = 0; j < numbers[i].size(); ++j)
			n *= numbers[i][j];

		r = static_cast<double>(n) / static_cast<double>(totient(numbers[i]));

		if(r > maxr)
		{
			maxn = n;
			maxr = r;
		}
	}

	std::cout << "The number with the largest n/phi(n) ratio is " << maxn << " (" << maxr << ").\n";
	assert(maxn == 510510);

	return 0;
}

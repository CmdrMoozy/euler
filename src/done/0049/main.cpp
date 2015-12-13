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

#include <set>
#include <cstdint>
#include <iostream>

#include "common/math/EMath.h"
#include "common/math/EPrimeSieve.h"
#include "common/util/Process.hpp"

/*
 * The arithmetic sequence, 1487, 4817, 8147, in which each of the terms
 * increases by 3330, is unusual in two ways: (i) each of the three terms are
 * prime, and, (ii) each of the 4-digit numbers are permutations of one
 * another.
 *
 * There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes,
 * exhibiting this property, but there is one other 4-digit increasing sequence.
 *
 * What 12-digit number do you form by concatenating the three terms in this
 * sequence?
 */

namespace
{
struct Result
{
	uint32_t a;
	uint32_t b;
	uint32_t c;

	bool operator==(Result const &o) const
	{
		return (a == o.a) && (b == o.b) && (c == o.c);
	}
};

std::ostream &operator<<(std::ostream &o, Result const &r)
{
	o << "(" << r.a << "," << r.b << "," << r.c << ")";
	return o;
}

constexpr Result EXPECTED_RESULT{2969, 6299, 9629};

euler::util::process::ProblemResult<Result> problem()
{
	EPrimeSieve sieve(10000);
	std::set<uint32_t>::iterator ita, itb, itc;

	for(ita = sieve.lowerBound(1000); ita != sieve.end(); ita++)
	{ // For each four-digit prime...

		// For each arithmetic increase that would make sense...
		for(uint32_t add = 1; ((*ita) + (add << 1)) < 10000; ++add)
		{
			// See if the second number is prime.
			itb = sieve.find((*ita) + add);
			if(itb != sieve.end())
			{
				// See if the third number is prime.
				itc = sieve.find((*ita) + (add << 1));
				if(itc != sieve.end())
				{
					// See if they are permutations of one
					// another.
					if(EMath::isPermutationOf((*ita),
					                          (*itb)) &&
					   EMath::isPermutationOf((*ita),
					                          (*itc)))
					{
						// See if the sequence we've
						// found isn't just the given
						// one.
						if(((*ita) != 1487) &&
						   ((*itb) != 4817) &&
						   ((*itc) != 8147))
						{
							return {{*ita, *itb,
							         *itc},
							        EXPECTED_RESULT};
						}
					}
				}
			}
		}
	}

	return {{0, 0, 0}, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

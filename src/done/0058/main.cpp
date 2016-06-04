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

#include <cstddef>
#include <cstdint>

#include <gmp.h>
#include <gmpxx.h>

#include "common/euler/ESpiral.h"
#include "common/math/EMath.h"
#include "common/util/Process.hpp"

/*
 * Starting with 1 and spiralling anticlockwise in the following way, a square
 * spiral with side length 7 is formed.
 *
 *    (37)36 35 34 33 32(31)
 *     38(17)16 15 14(13)30
 *     39 18 (5) 4 (3)12 29
 *     40 19  6  1  2 11 28
 *     41 20 (7) 8  9 10 27
 *     42 21 22 23 24 25 26
 *    (43)44 45 46 47 48 49
 *
 * It is interesting to note that the odd squares lie along the bottom right
 * diagonal, but what is more interesting is that 8 out of the 13 numbers lying
 * along both diagonals are prime; that is, a ratio of 8/13 = 62%.
 *
 * If one complete new layer is wrapped around the spiral above, a square
 * spiral with side length 9 will be formed. If this process is continued, what
 * is the side length of the square spiral for which the ratio of primes along
 * both diagonals first falls below 10%?
 */

namespace
{
/*
 * This value is sufficiently high enough for us to get the correct answer,
 * and sufficiently low enough to find the answer very quickly.
 */
constexpr int PRIME_PRECISION = 25;

constexpr std::size_t EXPECTED_RESULT = 26241;

euler::util::process::ProblemResult<std::size_t> problem()
{
	uint32_t primes, o;
	ESpiral sp;

	primes = 0;
	o = 0;
	sp.begin();
	sp.next();
	do
	{
		++o;

		if(EMath::isPrime(mpz_class(sp.next()), PRIME_PRECISION))
			++primes;
		if(EMath::isPrime(mpz_class(sp.next()), PRIME_PRECISION))
			++primes;
		if(EMath::isPrime(mpz_class(sp.next()), PRIME_PRECISION))
			++primes;
		sp.next();
	} while((primes * 10) > ((o * 4) + 1));

	return {sp.getSizeFor(o), EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

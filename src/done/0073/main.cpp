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

#include <cmath>
#include <cstdint>

#include "common/EExceptions.h"
#include "common/EDefines.h"
#include "common/types/EFraction.h"
#include "common/util/Process.hpp"

/*
 * Consider the fraction, n/d, where n and d are positive integers. If n<d and
 * HCF(n,d)=1, it is called a reduced proper fraction.
 *
 * If we list the set of reduced proper fractions fro d <= 8 in ascending order
 * of size, we get:
 *
 *     1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, _3/8_, _2/5_, _3/7_, 1/2, 4/7, 3/5,
 *     5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
 *
 * It can be seen that there are 3 fractions between 1/3 and 1/2.
 *
 * How many fractions lie between 1/3 and 1/2 in the sorted set of reduced
 * proper fractions for d <= 12,000?
 */

namespace
{
/*
 * We will be searching for all fractions inbetween
 * LOWER_TARGET_N / LOWER_TARGET_D and UPPER_TARGET_N / UPPER_TARGET_D, for
 * every denominator from 1 to DENOMINATOR_LIMIT (inclusive).
 */
constexpr uint64_t DENOMINATOR_LIMIT = 12000;
constexpr uint64_t LOWER_TARGET_N = 1;
constexpr uint64_t LOWER_TARGET_D = 3;
constexpr uint64_t UPPER_TARGET_N = 1;
constexpr uint64_t UPPER_TARGET_D = 2;

constexpr uint64_t EXPECTED_RESULT = 7295372;

euler::util::process::ProblemResult<uint64_t> problem()
{
	uint64_t a, b, c, d, i, j, k, count;
	EFraction lower, hold(LOWER_TARGET_N, LOWER_TARGET_D),
	        upper(UPPER_TARGET_N, UPPER_TARGET_D);

	/*
	 * Find the fraction immediately less than our upper limit - more
	 * information: http://en.wikipedia.org/wiki/Mediant_(mathematics)
	 */

	while(hold.getDenominator() <= DENOMINATOR_LIMIT)
	{
		lower = hold;
		hold.mediant(upper);
		hold.reduce();
	}

	/*
	 * At this point, we just continuously calculate the next term until we
	 * reach our lower limit. The formula for doing this can be found here:
	 * http://en.wikipedia.org/wiki/Farey_sequence#Next_term
	 */

	count = 0;
	lower.setNumerator(LOWER_TARGET_N);
	lower.setDenominator(LOWER_TARGET_D);

	a = UPPER_TARGET_N;
	b = UPPER_TARGET_D;
	c = hold.getNumerator();
	d = hold.getDenominator();

	while(EFraction(c, d) > lower)
	{
		++count;

		k = static_cast<uint32_t>(
		        floor(static_cast<double>(DENOMINATOR_LIMIT + b) /
		              static_cast<double>(d)));

		i = a;
		j = b;

		a = c;
		b = d;
		c = (c * k) - i;
		d = (d * k) - j;
	}
	count -= 1; // We always over-count by 1.

	return {count, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

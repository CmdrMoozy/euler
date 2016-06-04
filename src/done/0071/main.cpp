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

#include <cstdint>

#include "common/EDefines.h"
#include "common/EExceptions.h"
#include "common/types/EFraction.h"
#include "common/util/Process.hpp"

/*
 * Consider the fraction, n/d, where n and d are positive integers. If n<d and
 * HCF(n,d)=1, it is called a reduced proper fraction.
 *
 * If we list the set of reduced proper fractions for d <= 8 in ascending order
 * of size, we get:
 *
 *     1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, _2/5_, 3/7, 1/2, 4/7, 3/5, 5/8,
 *     2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
 *
 * It can be seen that 2/5 is the fraction immediately to the left of 3/7.
 *
 * By listing the set of reduced proper fractions for d <= 1,000,000 in
 * ascending order of size, find the numerator of the fraction immediately to
 * the left of 3/7.
 */

namespace
{
/*
 * We will be searching, in a sorted list of all fractions where the denominator
 * is <= DENOMINATOR_LIMIT, for the fraction immedately to the left of
 * TARGET_N / TARGET_D.
 */
constexpr uint64_t DENOMINATOR_LIMIT = 1000000;
constexpr uint64_t TARGET_N = 3;
constexpr uint64_t TARGET_D = 7;

constexpr uint64_t EXPECTED_RESULT = 428570;

euler::util::process::ProblemResult<uint64_t> problem()
{
	EFraction lower(0, 1);
	EFraction mediant(0, 1);
	const EFraction upper(TARGET_N, TARGET_D);

	while(mediant.getDenominator() <= DENOMINATOR_LIMIT)
	{
		lower = mediant;
		mediant.mediant(upper);
		mediant.reduce();
	}

	return {lower.getNumerator(), EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

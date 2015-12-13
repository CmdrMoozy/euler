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

#include <gmp.h>
#include <gmpxx.h>

#include "common/types/EDigitInteger.h"
#include "common/util/Process.hpp"

/*
 * n! means n x  (n - 1) x ... x 3 x 2 x 1
 *
 * Find the sum of the digits in the number 100!
 */

namespace
{
constexpr int EXPECTED_RESULT = 648;

euler::util::process::ProblemResult<int> problem()
{
	EDigitInteger eda;
	mpz_class number, sum;

	mpz_fac_ui(number.get_mpz_t(), 100);

	eda = number;
	return {eda.sumOfDigits(), EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

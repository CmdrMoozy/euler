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

#include "common/types/EDigitInteger.h"
#include "common/util/Process.hpp"

/*
 * 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
 *
 * What is the sum of the digits of the number 2^1000?
 */

namespace
{
constexpr int EXPECTED_RESULT = 1366;

euler::util::process::ProblemResult<int> problem()
{
	EDigitInteger eda;
	mpz_class number;

	number = 2;
	mpz_pow_ui(number.get_mpz_t(), number.get_mpz_t(), 1000);

	eda = number;
	return {eda.sumOfDigits(), EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

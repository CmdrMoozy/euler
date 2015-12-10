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

#include <cassert>
#include <cstddef>
#include <iostream>

#include <gmp.h>
#include <gmpxx.h>

#include "common/types/EDigitInteger.h"

/*
 * n! means n x  (n - 1) x ... x 3 x 2 x 1
 *
 * Find the sum of the digits in the number 100!
 */

int main(void)
{
	EDigitInteger eda;
	mpz_class number, sum;
	int result;

	mpz_fac_ui(number.get_mpz_t(), 100);

	eda = number;
	result = eda.sumOfDigits();
	std::cout << "The sum of the digits in 100! is: " << result << "\n";

	assert(result == 648);
	return 0;
}

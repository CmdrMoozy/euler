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

#include <gmp.h>

#include "libeuler/types/EDigitInteger.h"

/*
 * 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
 *
 * What is the sum of the digits of the number 2^1000?
 */

int main(void)
{
	EDigitInteger eda;
	mpz_class number;
	int sum;
	
	number = 2;
	mpz_pow_ui(number.get_mpz_t(), number.get_mpz_t(), 1000);
	
	eda = number;
	sum = eda.sumOfDigits();
	std::cout << "The sum of the digits in 2^1000 is: " << sum << "\n";
	
	assert(sum == 1366);
	return 0;
}

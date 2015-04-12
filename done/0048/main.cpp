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

#include <cassert>
#include <cstddef>
#include <iostream>

#include <gmp.h>
#include <gmpxx.h>

/*
 * The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
 *
 * Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
 */

int main(void)
{
	uint32_t i, j;
	mpz_class power, m;
	uint32_t sum[10] = {0,0,0,0,0,0,0,0,0,0};
	uint32_t assertResult[10] = {9,1,1,0,8,4,6,7,0,0};

	// Add the last ten digits of each number.
	for(i = 1; i <= 1000; i++)
	{
		mpz_ui_pow_ui(power.get_mpz_t(), i, i);

		j = 1;
		while( (power > 0) && (j <= 10) )
		{
			m = (power % 10);
			sum[10 - (j++)] += m.get_ui();
			power /= 10;
		}
	}

	// Carry everything.
	for(i = 9; i > 0; i--)
	{
		sum[i-1] += sum[i]/10;
		sum[i] %= 10;
	}
	sum[0] %= 10;

	// Print out our result.
	std::cout << "The last 10 digits of the result are: ";
	for(i = 0; i < 10; i++)
		std::cout << sum[i];
	std::cout << "\n";

	for(i = 0; i < 10; i++)
		assert(sum[i] == assertResult[i]);
	return 0;
}

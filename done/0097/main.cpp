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
#include <cstdint>
#include <iostream>

#include <gmp.h>
#include <gmpxx.h>

/*
 * The first known prime found to exceed one million digits was discovered in 1999, and is a Mersenne prime of the form
 * 2^6972593 - 1; it contains exactly 2,098,960 digits. Subsequently other Mersenne primes, of the form 2^p - 1, have
 * been found which contain more digits.
 *
 * However, in 2004 there was found a massive non-Mersenne prime which contains 2,357,207 digits: 28433 x 2^7830457 + 1.
 *
 * Find the last ten digits of this prime number.
 */

int main(void)
{
	/*
	 * We need the last 10 digits of 28,433 * 2^7,830,457 + 1
	 *
	 * Calculate it directly because GMP is stupid hella fast.
	 */

	mpz_class prime = 28433, mod;

	mpz_mul_2exp(prime.get_mpz_t(), prime.get_mpz_t(), 7830457);
	++prime;


	// Get the last ten digits.

	uint64_t digits = 0;
	for(int i = 0; i < 10; ++i)
	{
		mod = 1000000000;
		mod *= prime % 10;
		digits = (digits / 10) + mod.get_ui();
		prime /= 10;
	}

	std::cout << "The last ten digits of the prime are: " << digits << "\n";
	assert(digits == 8739992577);

	return 0;
}

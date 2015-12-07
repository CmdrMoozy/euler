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

#include "libeuler/math/EPrimeSieve.h"
#include "libeuler/types/EDigitInteger.h"

/*
 * The number 3797 has an interesting property. Being prime itself, it is
 * possible to continuously remove digits from left to right, and remain prime
 * at each stage: 3797, 797, 97, and 7. Similarly we can work from right to
 * left: 3797, 379, 37, and 3.
 *
 * Find the sum of the only eleven primes that are both truncatable from left to
 * right and right to left.
 *
 * NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
 */

namespace
{
constexpr uint32_t INITIAL_SIEVE_LIMIT = 1000000;
constexpr uint32_t SIEVE_STEPPING = 2;
constexpr std::size_t TARGET_COUNT = 11;

constexpr uint64_t EXPECTED_RESULT = 748317;

bool numberIsLeftToRightTruncatablePrime(EDigitInteger const &number,
                                         EPrimeSieve const &sieve)
{
	for(std::size_t i = 1; i < number.digitCount(); ++i)
	{
		uint32_t truncated = static_cast<uint32_t>(
		        number.rangeToInteger(0, number.digitCount() - 1 - i));
		if(sieve.find(truncated) == sieve.end())
			return false;
	}
	return true;
}

bool numberIsRightToLeftTruncatablePrime(EDigitInteger const &number,
                                         EPrimeSieve const &sieve)
{
	for(std::size_t i = 1; i < number.digitCount(); ++i)
	{
		uint32_t truncated = static_cast<uint32_t>(
		        number.rangeToInteger(i, number.digitCount() - 1));
		if(sieve.find(truncated) == sieve.end())
			return false;
	}
	return true;
}
}

int main(void)
{
	EPrimeSieve sieve;
	sieve.setLimit(INITIAL_SIEVE_LIMIT);

	assert(sieve.find(3797) != sieve.end());
	assert(numberIsLeftToRightTruncatablePrime(EDigitInteger(3797), sieve));
	assert(numberIsRightToLeftTruncatablePrime(EDigitInteger(3797), sieve));

	// Skip past the single-digit primes excluded by the problem desc.
	auto it = sieve.begin();
	while((it != sieve.end()) && (*it < 10))
		++it;

	// Keep going until we hit our target count of primes.
	std::size_t count = 0;
	uint64_t sum = 0;
	while(count < TARGET_COUNT)
	{
		assert(*it <= EXPECTED_RESULT);
		EDigitInteger number(*it);

		if(numberIsLeftToRightTruncatablePrime(number, sieve) &&
		   numberIsRightToLeftTruncatablePrime(number, sieve))
		{
			++count;
			sum += *it;
		}

		uint32_t previous = *it;
		++it;
		if(it == sieve.end())
		{
			// If we've reached the end of our current sieve,
			// resize it and reset our iterator.
			sieve.setLimit(sieve.getLimit() * SIEVE_STEPPING);
			it = sieve.find(previous);
			++it;

			assert(it != sieve.end());
		}
	}

	std::cout << "The sum of the only eleven truncatable primes is: " << sum
	          << "\n";

	assert(sum == EXPECTED_RESULT);
	return 0;
}

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

#include "PrimeSieve.hpp"

#include "common/math/Math.hpp"
#include "common/structs/BitArray.hpp"

namespace
{
euler::structs::BitArray sieve(uint64_t limit)
{
	euler::structs::BitArray isPrime(
	        limit + 1, euler::structs::BitArrayFillPolicy::CLEAR);
	uint64_t root = euler::math::isqrt(limit);

	for(uint64_t x = 1; x <= root; ++x)
	{
		uint64_t a = (x * x);
		uint64_t b = 3 * a;
		a *= 4;

		for(uint64_t y = 1; y <= root; ++y)
		{
			uint64_t c = (y * y);

			uint64_t n = a + c;
			if((n <= limit) && (((n % 12) == 1) || ((n % 12) == 5)))
			{
				isPrime.flip(n);
			}

			n = b + c;
			if((n <= limit && ((n % 12) == 7)))
				isPrime.flip(n);

			n = b - c;
			if((x > y) && (n <= limit) && ((n % 12) == 11))
				isPrime.flip(n);
		}
	}

	for(uint64_t n = 5; n <= root; n += 2)
	{
		if(isPrime.test(n))
		{
			uint64_t s = n * n;
			for(uint64_t k = s; k <= limit; k += s)
				isPrime.set(k, false);
		}
	}

	isPrime.set(2, true);
	isPrime.set(3, true);

	return isPrime;
}
}

namespace euler
{
namespace math
{
PrimeSieve::PrimeSieve(uint64_t l) : limit(l), isPrime(sieve(l))
{
}

uint64_t PrimeSieve::getLimit() const
{
	return limit;
}

void PrimeSieve::setLimit(uint64_t l)
{
	limit = l;
	isPrime = sieve(l);
}

std::size_t PrimeSieve::size() const
{
	return isPrime.count();
}

bool PrimeSieve::contains(uint64_t n) const
{
	return isPrime.test(n);
}
}
}

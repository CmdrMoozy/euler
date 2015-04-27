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

#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <unordered_set>

/*
 * The number 145 is well known for the property that the sum of the factorial
 * of its digits is equal to 145:
 *
 *     1! + 4! + 5! = 1 + 24 + 120 = 145
 *
 * Perhaps less well known is 169, in that it produces the longest chain of
 * numbers that link back to 169; it turns out that there are only three such
 * loops that exist:
 *
 *     169 -> 363601 -> 1454 -> 169
 *     871 -> 45361 -> 871
 *     872 -> 45362 -> 872
 *
 * It is not difficult to prove that EVERY starting number will eventually get
 * stuck in a loop. For example,
 *
 *     69 -> 363600 -> 1454 -> 169 -> 363601 (-> 1454)
 *     78 -> 45360 -> 871 -> 46361 (-> 871)
 *     540 -> 145 (-> 145)
 *
 * Starting with 69 produces a chain of five non-repeating terms, but the
 * longest non-repeating chain with a starting number below one million is
 * sixty terms.
 *
 * How many chains, with a starting number below one million, contain exactly
 * sixty non-repeating terms?
 */

namespace
{
	constexpr uint64_t MIN_START = 0;
	constexpr uint64_t MAX_START = 999999;

	constexpr uint64_t DESIRED_CHAIN_LENGTH = 60;

	inline uint64_t factorialOfDigit(uint64_t digit)
	{
		static constexpr uint64_t LOOKUP_TABLE[] = {
			1,
			1,
			2,
			6,
			24,
			120,
			720,
			5040,
			40320,
			362880
		};

		assert(digit < 10);
		return LOOKUP_TABLE[digit];
	}

	uint64_t digitFactorial(uint64_t v)
	{
		uint64_t result = 0;
		while(v)
		{
			result += factorialOfDigit(v % 10);
			v /= 10;
		}
		return result;
	}
}

int main(void)
{
	uint64_t count = 0;
	std::array<uint64_t, MAX_START + 1> lengthCache;
	lengthCache.fill(0);

	for(uint64_t n = MIN_START; n <= MAX_START; ++n)
	{
		std::unordered_set<uint64_t> set(DESIRED_CHAIN_LENGTH);
		uint64_t v = n;
		uint64_t cachedLength = 0;
		while(true)
		{
			if(v <= MAX_START)
			{
				if(lengthCache[v] != 0)
				{
					// We've seen this number before. Use
					// the cached length from this point.
					cachedLength = lengthCache[v];
					break;
				}
			}

			if(!set.insert(v).second)
				break;
			v = digitFactorial(v);
		}

		lengthCache[n] = set.size() + cachedLength;
		if(lengthCache[n] == DESIRED_CHAIN_LENGTH)
			++count;
	}

	std::cout << count << " values below one million produce 60-term " <<
		"digit factorial sequences.\n";
	assert(count == 402);

	return 0;
}

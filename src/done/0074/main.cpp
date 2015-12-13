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

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <unordered_map>
#include <utility>
#include <vector>

#include "common/util/Process.hpp"

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

constexpr uint64_t EXPECTED_RESULT = 402;

uint64_t factorialOfDigit(uint64_t digit)
{
	static constexpr uint64_t LOOKUP_TABLE[] = {
	        1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

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

inline std::pair<std::vector<uint64_t>::const_iterator, bool>
findRepeat(const std::vector<uint64_t> &chain, const uint64_t &value)
{
	// The longest loop is of size 3, as given in the problem
	// statement. Thus, if the chain is longer, we don't need to
	// continue searching past the last three elements.
	std::vector<uint64_t>::const_reverse_iterator end =
	        chain.size() > 3 ? chain.rbegin() + 3 : chain.rend();
	auto it = std::find(chain.rbegin(), end, value);
	return std::make_pair(it.base() + 1, it != end);
}

euler::util::process::ProblemResult<uint64_t> problem()
{
	uint64_t count = 0;

	std::unordered_map<uint64_t, uint64_t> lengthCache(MAX_START);
	std::vector<uint64_t> chain;
	chain.reserve(DESIRED_CHAIN_LENGTH);

	for(uint64_t n = MIN_START; n <= MAX_START; ++n)
	{
		chain.clear();
		uint64_t repeat = 0;
		uint64_t cachedLength = 0;

		uint64_t v = n;
		while(true)
		{
			auto it = lengthCache.find(v);
			if(it != lengthCache.end())
			{
				// We've seen this number before. Use the
				// cached length from this point.
				cachedLength = it->second;
				break;
			}

			auto repeatPair = findRepeat(chain, v);
			if(repeatPair.second)
			{
				repeat = *repeatPair.first;
				break;
			}
			chain.push_back(v);
			v = digitFactorial(v);
		}

		// We know the chain length of every number in this chain up
		// to the first instance of the number we repeated. Cache the
		// length of each of these numbers.
		uint64_t length = chain.size() + cachedLength;
		for(std::vector<uint64_t>::size_type idx = 0;
		    idx < chain.size(); ++idx)
		{
			lengthCache.insert(
			        std::make_pair(chain[idx], length - idx));

			// If we've hit the repeat point, then stop here.
			if(chain[idx] == repeat)
				break;
		}

		if(length == DESIRED_CHAIN_LENGTH)
			++count;
	}

	return {count, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

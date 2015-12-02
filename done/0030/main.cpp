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

#include <iostream>
#include <cassert>

/*
 * Because this problem says to find "all numbers", we need to establish sane
 *bounds for our search.
 * The lower bound of 10 is implied because single-digit numbers are not sums,
 *and as such are not
 * included.
 *
 * For the upper bound, it can be said that, if n is a d-digit number that can
 *be written as the sum
 * of the fifth powers of its digits:
 *
 *     10^(d-1) <= n <= 9^5 * d
 *
 * 10^(d-1) is the smallest number with at least d digits; i.e., the smallest
 *3-digit number is 100.
 *
 * 9^5 * d is the largest number we could have since, for instance, 999 would be
 *9^5 + 9^5 + 9^5 (or
 * 9^5 * 3).
 *
 * This formula only holds true while d < 7; at d = 7, our formula would be
 *stating:
 *     1,000,000 <= n <= 413,343
 * which is obviously false. Therefore, we can conclude that the largest
 *possible number we need to search
 * for is a 6-digit number. However, 999,999 is larger than the upper bound at
 *d=6, so our real upper bound
 * is 9^5 * 6, or 354,294.
 */

#define LOWER_BOUND 10
#define UPPER_BOUND 354294

/*
 * Surprisingly there are only three numbers that can be written as the sum of
 *fourth powers
 * of their digits:
 *
 *     1634 = 1^4 + 6^4 + 3^4 + 4^4
 *     8208 = 8^4 + 2^4 + 0^4 + 8^4
 *     9474 = 9^4 + 4^4 + 7^4 + 4^4
 *
 * As 1 = 1^4 is not a sum it is not included.
 *
 * The sum of these numbers is 1634 + 8208 + 9474 = 19316.
 *
 * Find the sum of all the numbers that can be written as the sum of fifth
 *powers of their digits.
 */

int main(void)
{
	uint32_t i, sum, result, n;

	// A lookup table for our fifth-power values: digitPower[n] = n^5.
	uint32_t digitPower[10] = {0,    1,    32,    243,   1024,
	                           3125, 7776, 16807, 32768, 59049};

	/*
	 * Note that we are not including a function to test this in libeuler
	 * because a) using a lookup
	 * table greatly improves our speed, and doing so isn't very clean in a
	 * static function, and b)
	 * it is not really a useful function outside of this particular
	 * problem.
	 */

	// Check each number in range for being equal to the sum of the fifth
	// powers of its digits.
	for(result = 0, i = LOWER_BOUND; i <= UPPER_BOUND; i++)
	{
		sum = 0;
		n = i;

		// Get the sum of the fifth powers of our number's digits.
		while(n > 0)
		{
			sum += digitPower[n % 10];
			n /= 10;
		}

		// If the sum is equal to the original, this is a number we
		// want; add it to the result.
		if(sum == i)
			result += sum;
	}

	std::cout << "The sum of all numbers that are the sum of the fifth "
	             "powers of its digit is: "
	          << result << "\n";

	assert(result == 443839);
	return 0;
}

#include <iostream>
#include <cassert>

/*
 * Because this problem just says "find all numbers," we need to establish search bounds. The lower
 * bound is obvious; the problem says n! = n (where n is a 1-digit number) doesn't count, since that
 * is not a sum, so we can start at 10.
 *
 * For the upper bound, it can be said that, if n is a d-digit factorion:
 *
 *     10^(d-1) <= n <= 9! * d
 *
 * 10^(d-1) is the smallest number with at least d digits; i.e., the smallest 3-digit number is 100.
 *
 * 9! * d is the largest number we could have, since, for instance, 999 would be 9! + 9! + 9! (or 9! * 3).
 *
 * This formula only holds true while d < 8; at d = 8, our formula would be stating:
 *     10,000,000 <= n <= 2,903,040
 * which is obviously false. Therefore, we can conclude that the largest possible factorion is a 7-digit
 * number. However, 9,999,999 is larger than the upper bound at d=7, so our real upper bound is 9! * 7,
 * or 2,540,160.
 */

#define LOWER_BOUND 10
#define UPPER_BOUND 2540160

/*
 * 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
 *
 * Find the sum of all numbers which are equal to the sum of the factorial of their digits.
 *
 * Note: as 1! = 1 and 2! = 2 are not sums they are not included.
 */

int main(void)
{
	uint32_t i, sum, result, n;
	
	// A lookup table for our factorial values: factorials[n] = n!.
	uint32_t factorials[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
	
	/*
	 * Note that we are not including "isFactorion()" or similar in libeuler because a) using a lookup
	 * table greatly improves our speed, and doing so isn't very clean in a static function, and b) it
	 * is not really a useful function outside of this particular problem.
	 */
	
	// Check each number in range for being a factorion.
	for(result = 0, i = LOWER_BOUND; i <= UPPER_BOUND; i++)
	{
		sum = 0;
		n = i;
		
		// Get the sum of the factorial of our number's digits.
		while(n > 0)
		{
			sum += factorials[n % 10];
			n /= 10;
		}
		
		// If the sum is equal to the original, this is a factorion; add it to the result.
		if(sum == i)
			result += sum;
	}
	
	std::cout << "The sum of all factorions is: " << result << "\n";
	
	assert(result == 40730);
	return 0;
}

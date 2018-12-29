// Copyright 2013 Axel Rasmussen
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Surprisingly there are only three numbers that can be written as the sum of
// fourth powers of
// their digits:
//
//     1634 = 1^4 + 6^4 + 3^4 + 4^4
//     8208 = 8^4 + 2^4 + 0^4 + 8^4
//     9474 = 9^4 + 4^4 + 7^4 + 4^4
//
// As 1 = 1^4 is not a sum it is not included.
//
// The sum of these numbers is 1634 + 8208 + 9474 = 19316.
//
// Find the sum of all the numbers that can be written as the sum of fifth
// powers of their digits.

use euler::util::error::*;
use euler::util::problem::*;

// Because this problem says to find "all numbers", we need to establish sane
// bounds for our search. The lower bound of 10 is implied because single-digit
// numbers are not sums, and as such are not included.
//
// For the upper bound, it can be said that, if n is a d-digit number that can
// be written as the sum of the fifth powers of its digits:
//
//     10^(d-1) <= n <= 9^5 * d
//
// 10^(d-1) is the smallest number with at least d digits; i.e., the smallest
// 3-digit number is 100.
//
// 9^5 * d is the largest number we could have since, for instance, 999 would
// be 9^5 + 9^5 + 9^5 (or 9^5 * 3).
//
// This formula only holds true while d < 7; at d = 7, our formula would be
// stating:
//
//     1,000,000 <= n <= 413,343
//
// which is obviously false. Therefore, we can conclude that the largest
// possible number we need to search for is a 6-digit number. However, 999,999
// is larger than the upper bound at d=6, so our real upper bound is 9^5 * 6,
// or 354,294.
const LOWER_BOUND: u64 = 10;
const UPPER_BOUND: u64 = 354294;

static DIGIT_FIFTH_POWERS: &'static [u64] = &[0, 1, 32, 243, 1024, 3125, 7776, 16807, 32768, 59049];

const EXPECTED_RESULT: u64 = 443839;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut result: u64 = 0;
        for i in LOWER_BOUND..(UPPER_BOUND + 1) {
            // Compute the sum of the fifth powers of this number's digits.
            let mut sum: u64 = 0;
            let mut n = i;
            while n > 0 {
                sum += DIGIT_FIFTH_POWERS[(n % 10) as usize];
                n /= 10;
            }

            // If the sum is equal to the original, this is a number we want.
            if sum == i {
                result += sum;
            }
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

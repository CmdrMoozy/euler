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

// The number, 1406357289, is a 0 to 9 pandigital number because it is made up
// of each of the digits 0 to 9 in some order, but it also has a rather
// interesting sub-string divisibility property.
//
// Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we
// note the following:
//
//     - d2d3d4  = 406 is divisible by 2
//     - d3d4d5  = 063 is divisible by 3
//     - d4d5d6  = 635 is divisible by 5
//     - d5d6d7  = 357 is divisible by 7
//     - d6d7d8  = 572 is divisible by 11
//     - d7d8d9  = 728 is divisible by 13
//     - d8d9d10 = 289 is divisible by 17
//
// Find the sum of all 0 to 9 pandigital numbers with this property.

use euler::algorithm::sequence;
use euler::util::error::*;
use euler::util::problem::*;

static DIVISORS: &'static [u64] = &[2, 3, 5, 7, 11, 13, 17];

const EXPECTED_RESULT: u64 = 16695334890;

fn collect_digits(digits: &[u64]) -> u64 {
    let mut n: u64 = 0;
    for digit in digits {
        n = (n * 10) + digit;
    }
    n
}

fn number_matches(digits: &[u64]) -> bool {
    for (idx, divisor) in DIVISORS.iter().enumerate() {
        // The first divisor index is 0, but the first digit index we want to check is
        // 1 (per the problem description - keep in mind that the problem description
        // uses 1-indexed digits).
        let idx = idx + 1;
        // Check if the number containing these three digits is divisible by this
        // divisor.
        if collect_digits(&digits[idx..idx + 3]) % divisor != 0 {
            return false;
        }
    }
    true
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut sum: u64 = 0;
        // We start with the number 1023456789 because numbers with leading zeros are
        // actually NOT 0-9 pandigital, and this is the smallest number which doesn't
        // have a leading zero.
        let mut digits: Vec<u64> = vec![1, 0, 2, 3, 4, 5, 6, 7, 8, 9];

        loop {
            if number_matches(digits.as_slice()) {
                sum += collect_digits(digits.as_slice());
            }

            if !sequence::permutate_lt(&mut digits) {
                break;
            }
        }

        Ok(ProblemAnswer {
            actual: sum,
            expected: EXPECTED_RESULT,
        })
    });
}

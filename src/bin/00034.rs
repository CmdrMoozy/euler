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

// 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
//
// Find the sum of all numbers which are equal to the sum of the factorial of
// their digits.
//
// Note: as 1! = 1 and 2! = 2 are not sums they are not included.

use std::collections::HashMap;

#[macro_use]
extern crate lazy_static;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

// First, there is an official name for the numbers we're looking for: they are
// called factorions (https://en.wikipedia.org/wiki/Factorion).
//
// Because this problem just says "find all numbers", we need to establish
// search bounds. The lower bound is obvious; the problem says n! = n (where n
// is a 1-digit number) doesn't count, since that is not a sum, so we can start
// at 10.
//
// For the upper bound, it can be said that, if n is a d-digit factorion:
//
//     10^(d-1) <= n <= 9! * d
//
// 10^(d-1) is the smallest number with at least d digits; i.e., the smallest
// 3-digit number is 100.
//
// 9! * d is the largest number we could have, since, for instance, 999 would
// be 9! + 9! + 9! (or 9! * 3).
//
// This formula only holds true while d < 8; at d = 8, our formula would be
// stating:
//
//     10,000,000 <= n <= 2,903,040
//
// which is obviously false. Therefore, we can conclude that the largest
// possible factorion is a 7-digit number. However, 9,999,999 is larger than
// the upper bound at d=7, so our real upper bound is 9! * 7, or 2,540,160.
const LOWER_BOUND: u64 = 10;
const UPPER_BOUND: u64 = 2540160;

lazy_static! {
    static ref FACTORIALS: HashMap<char, u64> = {
        let mut m = HashMap::new();
        m.insert('0', 1);
        m.insert('1', 1);
        m.insert('2', 2);
        m.insert('3', 6);
        m.insert('4', 24);
        m.insert('5', 120);
        m.insert('6', 720);
        m.insert('7', 5040);
        m.insert('8', 40320);
        m.insert('9', 362880);
        m
    };
}

const EXPECTED_RESULT: u64 = 40730;

/// Returns the sum of the factorials of the digits in the given integer.
fn factorion(n: u64) -> u64 {
    n.to_string().chars().map(|c| FACTORIALS.get(&c).unwrap()).fold(0, |acc, f| acc + f)
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut result: u64 = 0;
        // Just test every number in range...
        for i in LOWER_BOUND..(UPPER_BOUND + 1) {
            if i == factorion(i) {
                result += i;
            }
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

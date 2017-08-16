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

// 2520 is the smallest number that can be divided by each of the numbers from
// 1 to 10 without any remainder.
//
// What is the smallest positive number that is evenly divisible by all of the
// numbers from 1 to 20?

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 232792560;
// We don't need to check each potential in the range [1, 20], since some such
// numbers are themselves factors of other numbers in the range. So, define the
// minimal list of factors we need to test for.
const FACTORS: &'static [u64] = &[20, 19, 18, 17, 16, 15, 14, 13, 12, 11];

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut result: u64 = 0;
        // We can start with 20, since clearly any number smaller would not be
        // divisible by 20.
        let mut n: u64 = 20;
        while result == 0 {
            if FACTORS
                .iter()
                .map(|f| n % *f == 0)
                .fold(true, |acc, is_factor| acc && is_factor)
            {
                result = n;
            }
            // We know the answer must be a multiple of 20, so we can increase by that step.
            n += 20;
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

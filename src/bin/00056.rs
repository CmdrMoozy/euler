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

// A googol (10^100) is a massive number: one followed by one-hundred zeros;
// 100^100 is almost unimaginably large: one followed by two-hundred zeros.
// Despite their size, the sum of the digits in each number is only 1.
//
// Considering natural numbers of the form, a^b, where a, b < 100, what is the
// maximum digital sum?

extern crate rug;
use rug::ops::Pow;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 972;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut result: u64 = 0;
        for a in (1..100).rev() {
            // Skip any powers of 10; they always have a sum of 1.
            if a % 10 == 0 {
                continue;
            }

            for b in (1..100).rev() {
                let n = rug::Integer::from(a).pow(b);
                let sum = n
                    .to_string()
                    .chars()
                    .fold(0_u64, |acc, d| acc + (d.to_digit(10).unwrap() as u64));
                if sum > result {
                    result = sum;
                }
            }
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

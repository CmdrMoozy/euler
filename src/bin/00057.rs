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

// It is possible to show that the square root of two can be expressed as an
// infinite continued fraction.
//
//     sqrt(2) = 1 + 1/(2 + 1/(2 + 1/(2 + ... ))) = 1.414213...
//
// By expanding this for the first four iterations, we get:
//
//     1 + 1/2 = 3/2 = 1.5
//     1 + 1/(2 + 1/2) = 7/5 = 1.4
//     1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...
//     1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...
//
// The next three expansions are 99/70, 239/169, and 577/408, but the eighth
// expansion, 1393/985, is the first example where the number of digits in the
// numerator exceeds the number of digits in the denominator.
//
// In the first one-thousand expansions, how many fractions contain a numerator
// with more digits than denominator?

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

extern crate rug;

const EXPECTED_RESULT: usize = 153;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let mut num = rug::Integer::from(1);
        let mut den = rug::Integer::from(1);
        let mut count: usize = 0;
        for _ in 0..1000 {
            // If this expansion's numerator has more digits than the denominator,
            // increment the count.
            if num.to_string().len() > den.to_string().len() {
                count += 1;
            }

            // Compute the next expansion.
            num = num + &den + &den;
            den = &num - den;
            let gcd = (num.clone()).gcd(&den);
            num = num / &gcd;
            den = den / &gcd;
        }

        Ok(ProblemAnswer {
            actual: count,
            expected: EXPECTED_RESULT,
        })
    });
}

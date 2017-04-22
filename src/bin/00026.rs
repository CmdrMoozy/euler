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

// A unit faction contains 1 in the numerator. The decimal representation of
// the unit fractions with denominators 2 to 10 are given:
//
//     1/2  = 0.5
//     1/3  = 0.(3)
//     1/4  = 0.25
//     1/5  = 0.2
//     1/6  = 0.1(6)
//     1/7  = 0.(142857)
//     1/8  = 0.125
//     1/9  = 0.(1)
//     1/10 = 0.1
//
// Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be
// seen that 1/7 has a 6-digit recurring cycle.
//
// Find the value of d < 1000 for which 1/d contains the longest recurring
// cycle in its decimal fraction part.

extern crate euler;
use self::euler::math::division;
use self::euler::math::prime::PrimeSieve;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 983;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let sieve = PrimeSieve::new(1000);
        let mut max_n: u64 = 0;
        let mut max_repetend_length: u64 = 0;
        for n in 2..1000 {
            let repetend_length = division::repetend_length(n, &sieve, None)?;
            if repetend_length > max_repetend_length {
                max_n = n;
                max_repetend_length = repetend_length;
            }
        }

        Ok(ProblemAnswer {
            actual: max_n,
            expected: EXPECTED_RESULT,
        })
    });
}

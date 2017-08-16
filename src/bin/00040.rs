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

// An irrational decimal fraction is created by concatenating the positive
// integers:
//
//     0.12345678910_1_112131415161718192021...
//
// It can be seen that the 12th digit of the fractional part is 1.
//
// If d(n) represents the nth digit of the fractional part, find the value of
// the following expression:
//
//     d(1) x d(10) x d(100) x d(1000) x d(10000) x d(100000) x d(1000000)

extern crate euler;
use self::euler::math::exp::log10;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 210;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut digits = vec![0; 1000000];
        let mut i = 0;
        let mut on = 1;
        while i < 1000000 {
            let mut n = on;
            let log = log10(on);

            let mut j = i + log;
            while n > 0 {
                if j < digits.len() as u64 {
                    digits[j as usize] = n % 10;
                }
                n /= 10;
                if n > 0 {
                    j -= 1;
                }
            }
            i += log + 1;

            on += 1;
        }

        Ok(ProblemAnswer {
            actual: digits[0] * digits[9] * digits[99] * digits[999] * digits[9999] *
                digits[99999] * digits[999999],
            expected: EXPECTED_RESULT,
        })
    });
}

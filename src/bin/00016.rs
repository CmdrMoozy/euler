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

// 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
//
// What is the sum of the digits of the number 2^1000?

extern crate gmp;
use self::gmp::mpz::*;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const BASE: u64 = 2;
const EXPONENT: u32 = 1000;

const EXPECTED_RESULT: u64 = 1366;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut value: Mpz = Mpz::from(BASE);
        value = value.pow(EXPONENT);

        let value_string: String = format!("{}", value);

        Ok(ProblemAnswer {
            actual: value_string.chars()
                .map(|c| c.to_digit(10).unwrap() as u64)
                .fold(0, |acc, d| acc + d),
            expected: EXPECTED_RESULT,
        })
    });
}

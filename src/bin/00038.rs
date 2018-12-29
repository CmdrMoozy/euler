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

// Take the number 192 and multiply it by each of 1, 2, and 3:
//
//     192 x 1 = 192
//     192 x 2 = 384
//     192 x 3 = 576
//
// By concatenating each product we get the 1 to 9 pandigital, 192384576. We
// will call 192384576 the concatenated product of 192 and (1, 2, 3).
//
// The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4,
// and 5, giving the pandigital, 918273645, which is the concatenated product
// of 9 and (1, 2, 3, 4, 5).
//
// What is the largest 1 to 9 pandigital 9-digit number that can be formed as
// the concatenated product of an integer with (1, 2, ..., n) where n > 1?

use euler::math::exp;
use euler::util::error::*;
use euler::util::problem::*;

const EXPECTED_RESULT: u64 = 932718654;

fn concatenate(a: u64, b: u64) -> u64 {
    a * 10u64.pow(exp::log10(b) as u32 + 1) + b
}

fn is_pandigital(n: u64) -> bool {
    // If the number isn't exactly 9 digits, it cannot be a 9-digit pandigital.
    if exp::log10(n) != 8 {
        return false;
    }

    let mut digits: Vec<char> = n.to_string().chars().collect();
    digits.sort();
    let sorted: String = digits.into_iter().collect();

    sorted == "123456789"
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut result: u64 = 0;

        // Test every number of multiples from [2, 9], since 9 is the largest number of
        // multiples we can take that can still possibly produce a 9-digit number
        // (assuming the base is one). We'll call the largest number we'll multiply the
        // base by n.
        for n in 2..10 {
            // We calculate lower and upper bounds for the base number based on the fact
            // that the end number needs to be nine digits in length. Thus, we generate the
            // largest number which would produce a result of less than nine digits:
            //
            //     10^(floor(9/n) - 1)
            //
            // And the smallest number which would produce a result of more than nine
            // digits:
            //
            //     10^(floor(9/n))
            //
            // For instance, when n = 3, our bounds are going to be: (99, 1000), which
            // would result in us testing numbers in the inclusive range [100, 999].
            let lower_bound = 10u64.pow((9f64 / n as f64).floor() as u32 - 1);
            let upper_bound = 10u64.pow((9f64 / n as f64).floor() as u32);

            for base in lower_bound..upper_bound {
                // The problem description gives that the pandigital 918273645 exists, which
                // means that the greatest pandigital must be greater than or equal to the
                // given one. Thus, the first digit of our base must be a 9.
                if base / 10u64.pow(exp::log10(base) as u32) != 9 {
                    continue;
                }

                // Formulate the number.
                let mut concatenated: u64 = 0;
                for i in 1..(n + 1) {
                    concatenated = concatenate(concatenated, base * i);

                    // If the number is already too large, stop now.
                    if exp::log10(concatenated) > 8 {
                        concatenated = 0;
                        break;
                    }
                }

                // If the number is pandigital, and it's the largest we've seen, record it.
                if concatenated > result && is_pandigital(concatenated) {
                    result = concatenated;
                }
            }
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

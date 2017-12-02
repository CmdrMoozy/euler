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

// n! means n x (n - 1) x ... x 3 x 2 x 1
//
// Find the sum of the digits in the number 100!

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

extern crate rug;

const EXPECTED_RESULT: u64 = 648;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut factorial = rug::Integer::from(2);
        for n in 3..101 {
            factorial *= n;
        }
        let factorial_str = factorial.to_string();

        Ok(ProblemAnswer {
            actual: factorial_str
                .chars()
                .map(|c| c.to_string().parse::<u64>().unwrap())
                .fold(0, |sum, d| sum + d),
            expected: EXPECTED_RESULT,
        })
    });
}

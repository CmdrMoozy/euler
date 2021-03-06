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

// The sum of the squares of the first ten natural numbers is,
//
//     1^2 + 2^2 + ... + 10^2 = 385
//
// The square of the sum of the first ten natural numbers is,
//
//     (1 + 2 + ... + 10)^2 = 55^2 = 3025
//
// Hence the difference between the sum of the squares of the first ten natural
// numbers and the square of the sum is 3025 - 385 = 2640.
//
// Find the difference between the sum of the squares of the first one hundred
// natural numbers and the square of the sum.

use euler::util::error::*;
use euler::util::problem::*;
use rug::ops::Pow;

const START_NUMBER: u64 = 1;
const END_NUMBER: u64 = 100;
const EXPECTED_RESULT: u64 = 25164150;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut result = rug::Integer::new();

        for n in START_NUMBER..(END_NUMBER + 1) {
            result += rug::Integer::from(n);
        }
        result = result.pow(2);

        let mut sum_of_squares = rug::Integer::new();
        for n in START_NUMBER..(END_NUMBER + 1) {
            sum_of_squares += rug::Integer::from(n * n);
        }
        result -= sum_of_squares;

        Ok(ProblemAnswer {
            actual: result.to_u64().unwrap(),
            expected: EXPECTED_RESULT,
        })
    });
}

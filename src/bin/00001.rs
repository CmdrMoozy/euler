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

// If we list all the natural numbers below 10 that are multiples of 3 or 5, we
// get 3, 5, 6 and 9. The sum of these multiples is 23.
//
// Find the sum of all the multiples of 3 or 5 below 1000.

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: i64 = 233168;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<i64>> {
        let mut total: i64 = 0;
        for i in 0..1000 {
            if ((i % 5) == 0) || ((i % 3) == 0) {
                total += i;
            }
        }
        Ok(ProblemAnswer {
            actual: total,
            expected: EXPECTED_RESULT,
        })
    });
}

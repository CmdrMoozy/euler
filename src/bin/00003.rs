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

// The prime factors of 13195 are 5, 7, 13 and 29.
//
// What is the largest prime factor of the number 600851475143?

use euler::math::exp;
use euler::math::prime;
use euler::util::error::*;
use euler::util::problem::*;

const VALUE_TO_FACTOR: u64 = 600851475143;
const EXPECTED_RESULT: u64 = 6857;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let sieve = prime::PrimeSieve::new(exp::isqrt(VALUE_TO_FACTOR));
        let mut answer: u64 = 0;
        for prime in sieve.iter().rev() {
            if VALUE_TO_FACTOR % prime == 0 {
                answer = prime;
                break;
            }
        }

        Ok(ProblemAnswer {
            actual: answer,
            expected: EXPECTED_RESULT,
        })
    });
}

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

// By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see
// that the 6th prime is 13.
//
// What is the 10001st prime number?

extern crate euler;
use self::euler::math::prime::PrimeSieve;
use self::euler::math::sieve::Sieve;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const TARGET_PRIME: usize = 10001;
const INITIAL_SIEVE_LIMIT: u64 = 1000000;
const SIEVE_SCALING_FACTOR: u64 = 2;
const EXPECTED_RESULT: u64 = 104743;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut result: u64 = 0;
        let mut limit: u64 = INITIAL_SIEVE_LIMIT;
        while result == 0 {
            let sieve = PrimeSieve::new(limit);
            if let Some(p) = sieve.get_nth(TARGET_PRIME) {
                result = p;
                break;
            }
            limit *= SIEVE_SCALING_FACTOR;
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

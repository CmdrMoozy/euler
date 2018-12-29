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

// It was proposed by Christian Goldbach that every odd composite number can be
// written as the sum of a prime and twice a square.
//
//     9 = 7 + (2 * 1^2)
//     15 = 7 + (2 * 2^2)
//     21 = 3 + (2 * 3^2)
//     25 = 7 + (2 * 3^2)
//     27 = 19 + (2 * 2^2)
//     33 = 31 + (2 * 1^2)
//
// It turns out that the conjecture was false.
//
// What is the smallest odd composite that cannot be written as the sum of a
// prime and twice a square?

use euler::math::exp;
use euler::math::prime::PrimeSieve;
use euler::math::sieve::Sieve;
use euler::util::error::*;
use euler::util::problem::*;

const INITIAL_SIEVE_LIMIT: u64 = 1000000;
const SIEVE_LIMIT_MULTIPLIER: u64 = 2;

const LOWER_BOUND: u64 = 9;

const EXPECTED_RESULT: u64 = 5777;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut sieve = PrimeSieve::new(INITIAL_SIEVE_LIMIT);

        // Iterate over each odd composite.
        let mut n: u64 = LOWER_BOUND;
        loop {
            // Increase the sieve limit if needed.
            if sieve.get_limit() < n {
                let new_limit = sieve.get_limit() * SIEVE_LIMIT_MULTIPLIER;
                sieve = PrimeSieve::new(new_limit);
            }

            // Don't test primes.
            if sieve.contains(n).unwrap_or(false) {
                n += 2;
                continue;
            }

            let mut is_result = true;
            for prime in sieve.iter() {
                if prime >= n {
                    break;
                }

                let diff = n - prime;

                // The difference must be twice a square, so it must be even.
                if diff & 1 != 0 {
                    continue;
                }

                // Get rid of easy possibilities first.
                if diff == 2 || diff == 8 || diff == 18 {
                    is_result = false;
                    break;
                }

                // Test if the difference is twice a square.
                if exp::is_square(diff / 2) {
                    is_result = false;
                    break;
                }
            }

            if is_result {
                break;
            }

            n += 2;
        }

        Ok(ProblemAnswer {
            actual: n,
            expected: EXPECTED_RESULT,
        })
    });
}

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

// The prime 41 can be written as the sum of six consecutive primes:
//
//     41 = 2 + 3 + 5 + 7 + 11 + 13
//
// This is the longest sum of consecutive primes that adds to a prime below
// one-hundred.
//
// The longest sum of consecutive primes below one-thousand that adds to a
// prime, contains 21 terms, and is equal to 953.
//
// Which prime, below one-million, can be written as the sum of the most
// consecutive primes?

use euler::math::prime::PrimeSieve;
use euler::math::sieve::Sieve;
use euler::util::error::*;
use euler::util::problem::*;

const EXPECTED_RESULT: u64 = 997651;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        // It can be determined by adding the first n primes that the largest possible
        // set of consecutive primes added together to form a number less than
        // 1,000,000 is 546. Thus, this is our starting upper liimit.

        let sieve = PrimeSieve::new(1000000);
        let primes: Vec<u64> = sieve.iter().collect();
        let mut result: u64 = 0;

        for length in (1..547).rev() {
            // For each possible length, we try to see if the sum of that number of any
            // consecutive primes produces a prime.
            let mut start = 0;
            let mut end = start + length;
            while end <= sieve.get_size() {
                let sum: u64 = primes[start..end].iter().fold(0, |acc, p| acc + *p);
                if sum >= 1000000 {
                    break;
                }

                // If the resulting number is prime, we've found the one we wanted!
                if sieve.contains(sum).unwrap_or(false) {
                    result = sum;
                    break;
                }

                // Otherwise, increment the range we are working with.
                start += 1;
                end += 1;
            }

            if result != 0 {
                break;
            }
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

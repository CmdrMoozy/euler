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

// The number, 197, is called a circular prime because all rotations of the
// digits: 197, 971, and 719, are themselves prime.
//
// There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37,
// 71, 73, 79, and 97.
//
// How many circular primes are there below one million?

use euler::dsc::circular_prime_sieve::CircularPrimeSieve;
use euler::math::sieve::Sieve;
use euler::util::error::*;
use euler::util::problem::*;

const PRIME_LIMIT: u64 = 1000000;
const EXPECTED_RESULT: usize = 55;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let sieve = CircularPrimeSieve::new(PRIME_LIMIT);
        Ok(ProblemAnswer {
            actual: sieve.get_size(),
            expected: EXPECTED_RESULT,
        })
    });
}

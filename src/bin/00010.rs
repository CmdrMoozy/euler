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

// The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
//
// Find the sum of all the primes below two million.

use euler::math::prime::PrimeSieve;
use euler::util::error::*;
use euler::util::problem::*;

// Although we want primes *less than* two million, two million itself is
// clearly composite, so we can use it as an upper bound.
const PRIME_SIEVE_LIMIT: u64 = 2000000;
const EXPECTED_RESULT: u64 = 142913828922;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let sieve = PrimeSieve::new(PRIME_SIEVE_LIMIT);
        Ok(ProblemAnswer {
            actual: sieve.iter().sum(),
            expected: EXPECTED_RESULT,
        })
    });
}

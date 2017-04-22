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

// The first known prime found to exceed one million digits was discovered in
// 1999, and is a Mersenne prime of the form 2^6972593 - 1; it contains exactly
// 2,098,960 digits. Subsequently other Mersenne primes, of the form 2^p - 1,
// have been found which contain more digits.
//
// However, in 2004 there was found a massive non-Mersenne prime which contains
// 2,357,207 digits: 28433 x 2^7830457 + 1.
//
// Find the last ten digits of this prime number.

extern crate gmp;
use gmp::mpz::Mpz;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 8739992577;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        // We need the last 10 digits of 28,433 * 2^7,830,457 + 1. We can just
        // calculate it directly, since GMP is fast enough.
        let prime = Mpz::from(28433);
        let prime = prime << 7830457;
        let prime = prime + 1;
        let last_ten_digits = prime.modulus(&Mpz::from(10000000000_u64));
        let last_ten_digits = last_ten_digits.to_str_radix(10).parse::<u64>()?;

        Ok(ProblemAnswer {
            actual: last_ten_digits,
            expected: EXPECTED_RESULT,
        })
    });
}

// euler - A collection of ProjectEuler libraries, tools, and solutions.
// Copyright (C) 2013 Axel Rasmussen
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

extern crate euler;
use self::euler::math::exp;
use self::euler::math::prime::PrimeSieve;
use self::euler::math::sieve::Sieve;
use self::euler::util::error::*;
use self::euler::util::problem::*;

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

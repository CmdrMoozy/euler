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

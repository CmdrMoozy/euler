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

// The prime factors of 13195 are 5, 7, 13 and 29.
//
// What is the largest prime factor of the number 600851475143?

extern crate euler;
use self::euler::math::exp;
use self::euler::math::prime;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const VALUE_TO_FACTOR: u64 = 600851475143;
const EXPECTED_RESULT: u64 = 6857;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let sieve = prime::Sieve::new(exp::isqrt(VALUE_TO_FACTOR));
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

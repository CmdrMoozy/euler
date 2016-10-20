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

// The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
//
// Find the sum of all the primes below two million.

extern crate euler;
use self::euler::math::prime;
use self::euler::util::error::*;
use self::euler::util::problem::*;

// Although we want primes *less than* two million, two million itself is
// clearly composite, so we can use it as an upper bound.
const PRIME_SIEVE_LIMIT: u64 = 2000000;
const EXPECTED_RESULT: u64 = 142913828922;

fn main() {
    main_impl(|| -> EulerResult<ProblemAnswer<u64>> {
        let sieve = prime::Sieve::new(PRIME_SIEVE_LIMIT);
        Ok(ProblemAnswer {
            actual: sieve.iter().sum(),
            expected: EXPECTED_RESULT,
        })
    });
}

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

// The number, 197, is called a circular prime because all rotations of the
// digits: 197, 971, and 719, are themselves prime.
//
// There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37,
// 71, 73, 79, and 97.
//
// How many circular primes are there below one million?

extern crate euler;
use self::euler::dsc::circular_prime_sieve::CircularPrimeSieve;
use self::euler::math::sieve::Sieve;
use self::euler::util::error::*;
use self::euler::util::problem::*;

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

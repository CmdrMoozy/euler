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

// The sum of the squares of the first ten natural numbers is,
//
//     1^2 + 2^2 + ... + 10^2 = 385
//
// The square of the sum of the first ten natural numbers is,
//
//     (1 + 2 + ... + 10)^2 = 55^2 = 3025
//
// Hence the difference between the sum of the squares of the first ten natural
// numbers and the square of the sum is 3025 - 385 = 2640.
//
// Find the difference between the sum of the squares of the first one hundred
// natural numbers and the square of the sum.

extern crate gmp;
use self::gmp::mpz::*;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const START_NUMBER: u64 = 1;
const END_NUMBER: u64 = 100;
const EXPECTED_RESULT: u64 = 25164150;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut result: Mpz = Mpz::from(0);

        for n in START_NUMBER..(END_NUMBER + 1) {
            result = result + n;
        }
        result = result.pow(2);

        let mut sum_of_squares: Mpz = Mpz::from(0);
        for n in START_NUMBER..(END_NUMBER + 1) {
            sum_of_squares = sum_of_squares + (n * n);
        }
        result = result - sum_of_squares;

        let result_u64: Option<u64> = (&result).into();

        Ok(ProblemAnswer {
            actual: result_u64.unwrap(),
            expected: EXPECTED_RESULT,
        })
    });
}

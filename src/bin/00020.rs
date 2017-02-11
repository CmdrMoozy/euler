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

// n! means n x (n - 1) x ... x 3 x 2 x 1
//
// Find the sum of the digits in the number 100!

extern crate gmp;
use self::gmp::mpz::*;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 648;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut factorial: Mpz = Mpz::from(2);
        for n in 3..101 {
            factorial = factorial * (n as u64);
        }
        let factorial_str = factorial.to_string();

        Ok(ProblemAnswer {
            actual: factorial_str.chars()
                .map(|c| c.to_string().parse::<u64>().unwrap())
                .fold(0, |sum, d| sum + d),
            expected: EXPECTED_RESULT,
        })
    });
}

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

// 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
//
// What is the sum of the digits of the number 2^1000?

extern crate gmp;
use self::gmp::mpz::*;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const BASE: u64 = 2;
const EXPONENT: u32 = 1000;

const EXPECTED_RESULT: u64 = 1366;

fn main() {
    main_impl(|| -> EulerResult<ProblemAnswer<u64>> {
        let mut value: Mpz = Mpz::from(BASE);
        value = value.pow(EXPONENT);

        let value_string: String = format!("{}", value);

        Ok(ProblemAnswer {
            actual: value_string.chars()
                .map(|c| c.to_digit(10).unwrap() as u64)
                .fold(0, |acc, d| acc + d),
            expected: EXPECTED_RESULT,
        })
    });
}

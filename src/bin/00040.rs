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

// An irrational decimal fraction is created by concatenating the positive
// integers:
//
//     0.12345678910_1_112131415161718192021...
//
// It can be seen that the 12th digit of the fractional part is 1.
//
// If d(n) represents the nth digit of the fractional part, find the value of
// the following expression:
//
//     d(1) x d(10) x d(100) x d(1000) x d(10000) x d(100000) x d(1000000)

extern crate euler;
use self::euler::math::exp::log10;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 210;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut digits = vec![0; 1000000];
        let mut i = 0;
        let mut on = 1;
        while i < 1000000 {
            let mut n = on;
            let log = log10(on);

            let mut j = i + log;
            while n > 0 {
                if j < digits.len() as u64 {
                    digits[j as usize] = n % 10;
                }
                n /= 10;
                if n > 0 {
                    j -= 1;
                }
            }
            i += log + 1;

            on += 1;
        }

        Ok(ProblemAnswer {
            actual: digits[0] * digits[9] * digits[99] * digits[999] * digits[9999] *
                    digits[99999] * digits[999999],
            expected: EXPECTED_RESULT,
        })
    });
}

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

// The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.
//
// Find the sum of all numbers, less than one million, which are palindromic in
// base 10 and base 2.
//
// (Please note that the palindromic number, in either base, may not include
// leading zeros.)

extern crate euler;
use self::euler::util::bitwise::is_bitwise_palindromic;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 872187;

fn is_digital_palindrome(n: u64) -> bool {
    n == n.to_string().chars().rev().collect::<String>().parse::<u64>().unwrap()
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut sum: u64 = 0;
        for n in 1..1000000 {
            if is_bitwise_palindromic(n) && is_digital_palindrome(n) {
                sum += n;
            }
        }

        Ok(ProblemAnswer {
            actual: sum,
            expected: EXPECTED_RESULT,
        })
    });
}

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

// A paldinromic number reads the same both ways. The largest palindrome made
// from the product of two 2-digit numbers is 9009 = 91 x 99.
//
// Find the largest palindrome made from the product of two 3-digit numbers.

use std::collections::BTreeSet;
use std::string::String;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 906609;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        // Formulate a list of all of the products of two three-digit numbers.
        let mut products: BTreeSet<u64> = BTreeSet::new();
        for a in 100..1000 {
            for b in 100..(a + 1) {
                products.insert(a * b);
            }
        }

        // Starting with the largest number, search backwards until we find a
        // palindrome.
        let mut result: u64 = 0;
        for n in products.iter().rev() {
            let str_n: String = format!("{}", n);
            // Since this string only contains the characters 0-9, just reverse the bytes.
            let rev_str_n: String =
                String::from_utf8(str_n.as_bytes().iter().rev().cloned().collect())?;
            if str_n == rev_str_n {
                result = *n;
                break;
            }
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

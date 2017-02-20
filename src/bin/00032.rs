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

// We shall say that an n-digit number is pandigital if it makes use of all the
// digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1
// through 5 pandigital.
//
// The product 7254 is unusual, as the identity, 39 x 186 = 7254, containing
// multiplicand, multiplier, and product is 1 through 9 pandigital.
//
// Find the sum of all products whose multiplicand / multiplier / product
// identity can be written as a 1 through 9 pandigital.
//
// HINT: Some products can be obtained in more than one way so be sure to
// include it only once in your sum.

use std::collections::HashSet;

extern crate euler;
use self::euler::algorithm;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 45228;

fn collect_digits(digits: &[u64]) -> u64 {
    let mut value: u64 = 0;
    for digit in digits.iter() {
        value = (value * 10) + digit;
    }
    value
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        // Use a set to eliminate any duplicate products.
        let mut products: HashSet<u64> = HashSet::new();

        let mut digits: Vec<u64> = vec![1, 2, 3, 4, 5, 6, 7, 8, 9];
        loop {
            // We know that the product of two numbers which contain m and n digits
            // respectively is always between (m+n-1) and (m+n) in length.
            //
            // Because of this, along with the fact that the multiplicative identity we are
            // checking MUST contain all 9 numbers from 1-9 (inclusive), we know that the
            // product must be either 4 or 5 digits in length.
            //
            // (If the product were more than 5 digits in length, there aren't enough
            // remaining digits to produce it. If the product were less than 4 digits, the
            // remaining digits would have to produce a larger product than the one given.)

            // Test the four-digit product. By the reasoning above, the first factor must
            // have between 1 and 4 digits.
            let product = collect_digits(&digits[5..]);
            for i in 1..5 {
                let (a_digits, b_digits) = (&digits[0..5]).split_at(i);
                if product == collect_digits(a_digits) * collect_digits(b_digits) {
                    products.insert(product);
                }
            }

            // Test the five-digit product. Similarly to above, the first factor must have
            // between 1 and 3 digits.
            let product = collect_digits(&digits[4..]);
            for i in 1..4 {
                let (a_digits, b_digits) = (&digits[0..4]).split_at(i);
                if product == collect_digits(a_digits) * collect_digits(b_digits) {
                    products.insert(product);
                }
            }

            // Permutate the digits we test, stopping if there are no more permutations.
            if !algorithm::permutate_lt(&mut digits) {
                break;
            }
        }

        Ok(ProblemAnswer {
            actual: products.iter().fold(0, |acc, p| acc + p),
            expected: EXPECTED_RESULT,
        })
    });
}

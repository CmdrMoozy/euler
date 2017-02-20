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
// digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is
// also prime.
//
// What is the largest n-digit pandigital prime that exists?

#[macro_use]
extern crate lazy_static;

extern crate euler;
use self::euler::algorithm;
use self::euler::math::prime;
use self::euler::util::error::*;
use self::euler::util::problem::*;

lazy_static! {
    static ref PANDIGITALS: Vec<Vec<u64>> = vec![
        vec![9, 8, 7, 6, 5, 4, 3, 2, 1],
        vec![8, 7, 6, 5, 4, 3, 2, 1],
        vec![7, 6, 5, 4, 3, 2, 1],
        vec![6, 5, 4, 3, 2, 1],
        vec![5, 4, 3, 2, 1],
        vec![4, 3, 2, 1],
        vec![3, 2, 1],
        vec![2, 1],
        vec![1],
    ];
}

const PRIMALITY_TEST_PRECISION: u64 = 100;
const EXPECTED_RESULT: u64 = 7652413;

fn collect_digits(digits: &[u64]) -> u64 {
    let mut n: u64 = 0;
    for digit in digits.iter().rev() {
        n = (n * 10) + digit;
    }
    n
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut result: u64 = 0;
        for i in 0..10 {
            let mut digits = PANDIGITALS[i].clone();
            loop {
                let j = collect_digits(digits.as_slice());
                if j > result && prime::is_prime(j, PRIMALITY_TEST_PRECISION) {
                    result = j;
                }

                if !algorithm::permutate(&mut digits, |a, b| a.cmp(b).reverse()) {
                    break;
                }
            }

            if result != 0 {
                break;
            }
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

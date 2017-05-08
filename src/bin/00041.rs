// Copyright 2013 Axel Rasmussen
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// We shall say that an n-digit number is pandigital if it makes use of all the
// digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is
// also prime.
//
// What is the largest n-digit pandigital prime that exists?

#[macro_use]
extern crate lazy_static;

extern crate euler;
use self::euler::algorithm::sequence;
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

                if !sequence::permutate(&mut digits, |a, b| a.cmp(b).reverse()) {
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

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

// The Fibonacci sequence is defined by the recursive relation:
//
//     F(n) = F(n-1) + F(n-2), where F(1) = 1 and F(2) = 1.
//
// Hence the first 12 terms will be:
//
//     F(1) = 1
//     F(2) = 1
//     F(3) = 2
//     F(4) = 3
//     F(5) = 5
//     F(6) = 8
//     F(7) = 13
//     F(8) = 21
//     F(9) = 34
//     F(10) = 55
//     F(11) = 89
//     F(12) = 144
//
// The 12th term, F(12), is the first term to contain three digits.
//
// What is the first term in the Fibonacci sequence to contain 1000 digits?

extern crate euler;
use self::euler::math::sequence::{get_nth_fibonacci_number, sequence_search};
use self::euler::util::error::*;
use self::euler::util::problem::*;

extern crate gmp;
use gmp::mpz::Mpz;

const EXPECTED_RESULT: u64 = 4782;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let target: Mpz = Mpz::from(10).pow(999);
        let (index, _) = sequence_search(1, target, get_nth_fibonacci_number);
        Ok(ProblemAnswer {
            actual: index,
            expected: EXPECTED_RESULT,
        })
    });
}

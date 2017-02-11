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

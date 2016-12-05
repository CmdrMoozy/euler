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

// The sequence of triangle numbers is generated by adding the natural numbers.
// So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The
// first ten terms would be:
//
// 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
//
// Let us list the factors of the first seven triangle numbers:
// 1: 1
// 3: 1,3
// 6: 1,2,3,6
// 10: 1,2,5,10
// 15: 1,3,5,15
// 21: 1,3,7,21
// 28: 1,2,4,7,14,28
//
// We can see that 28 is the first triangle number to have over five divisors.
// What is the value of the first triangle number to have over five hundred
// divisors?

extern crate euler;
use self::euler::math;
use self::euler::math::sequence;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 76576500;

// This is the smallest number that has exactly 500 factors -- we use this as
// our lower-bound. The theory behind how this number was calculated is
// described here:
// http://www.primepuzzles.net/problems/prob_019.htm
const MINIMUM_NUMBER: u64 = 62370000;

const TARGET_NUM_DIVISORS: u64 = 500;

fn main() {
    main_impl(|| -> EulerResult<ProblemAnswer<u64>> {
        let (mut idx, mut value) =
            sequence::sequence_search(1, MINIMUM_NUMBER, sequence::get_nth_triangle_number);
        while math::aliquot_number_divisors(value) <= TARGET_NUM_DIVISORS {
            idx += 1;
            value = sequence::get_nth_triangle_number(idx);
        }

        Ok(ProblemAnswer {
            actual: value,
            expected: EXPECTED_RESULT,
        })
    });
}

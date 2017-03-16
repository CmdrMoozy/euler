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

// It can be seen that the number, 125874, and its double, 251748, contain
// exactly the same digits, but in a different order.
//
// Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x,
// contain the same digits.

extern crate euler;
use self::euler::algorithm::is_permutation_of;
use self::euler::math::exp::log10;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 142857;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut x: u64 = 1;
        loop {
            // If log10(6x) > log10(x), we can skip x up to 10^(log10(x) + 1).
            let logx = log10(x);
            if log10(6 * x) > logx {
                x = 10_u64.pow(logx as u32 + 1);
                continue;
            }

            // If x contains the same digits as [2, 6]x, then we have found the answer.
            let all_are_permutations = (2..7)
                .map(|multiple| is_permutation_of(&x, &(x * multiple)))
                .fold(true, |acc, is_permutation| acc && is_permutation);
            if all_are_permutations {
                break;
            }

            x += 1;
        }

        Ok(ProblemAnswer {
            actual: x,
            expected: EXPECTED_RESULT,
        })
    });
}

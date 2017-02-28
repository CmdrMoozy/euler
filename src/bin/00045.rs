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

// Triangle, pentagonal, and hexagonal numbers are generated by the following
// formulae:
//
// Triangle      T(n) = n(n+1) / 2     1, 3, 6, 10, 15, ...
// Pentagonal    P(n) = n(3n-1) / 2    1, 5, 12, 22, 35, ...
// Hexagonal     H(n) = n(2n-1)        1, 6, 15, 28, 45, ...
//
// It can be verified that T(285) = P(165) = H(143) = 40755.
//
// Find the next triangle number that is also pentagonal and hexagonal.

extern crate euler;
use self::euler::math::sequence::{get_nth_triangle_number, get_nth_pentagonal_number,
                                  get_nth_hexagonal_number, sequence_search};
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 1533776805;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut t_idx: u64 = 286;
        let mut result: u64;
        loop {
            result = get_nth_triangle_number(t_idx);
            if sequence_search(t_idx, result, get_nth_pentagonal_number).1 == result &&
               sequence_search(t_idx, result, get_nth_hexagonal_number).1 == result {
                break;
            }
            t_idx += 1;
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

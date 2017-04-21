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

// Starting with the number 1 and moving to the right in a clockwise direction
// a 5 by 5 spiral is formed as follows:
//
//   21 22 23 24 25
//   20  7  8  9 10
//   19  6  1  2 11
//   18  5  4  3 12
//   17 16 15 14 13
//
// It can be verified that the sum of the numbers on the diagonals is 101.
//
// What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral
// formed in the same way?

extern crate euler;
use self::euler::dsc::spiral;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 669171001;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut spiral = spiral::Spiral::new();
        let mut result: u64 = 1;
        let mut i: i64 = 1;
        while spiral::diagonal_size_to_edge_size(i) <= 1001 {
            for x in vec![-i, i] {
                for y in vec![-i, i] {
                    result += spiral.get_diagonal_value(&spiral::Address { x: x, y: y })?;
                }
            }

            i += 1;
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

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

// By starting at the top of the triangle below and moving to adjacent numbers
// on the row below, the maximum total from top to bottom is 23.
//
//        3
//       7 4
//      2 4 6
//     8 5 9 3
//
// That is, 3 + 7 + 4 + 9 = 23.
//
// Find the maximum total from top to bottom in triangle.txt (right click and
// 'Save Link/Target As...'), a 15K text file containing a triangle with
// one-hundred rows.
//
// NOTE: This is a much more difficult version of Problem 18. It is not
// possible to try every route to solve this problem, as there are 2^99
// altogether! If you could check one trillion (10^12) routes every second, it
// would take over twenty billion years to check them all. There is an
// efficient algorithm to solve it. ;o)

extern crate euler;
use self::euler::dsc::triangle::Triangle;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const TRIANGLE_VALUES: &'static str = include_str!("00067.txt");

const EXPECTED_RESULT: u64 = 7273;

fn main() {
    main_impl(|| -> EulerResult<ProblemAnswer<u64>> {
        let mut triangle: Triangle<u64> = Triangle::new(TRIANGLE_VALUES.split('\n').count());
        for row_pair in TRIANGLE_VALUES.split('\n').enumerate() {
            for value_pair in row_pair.1.split(' ').enumerate() {
                try!(triangle.set(row_pair.0, value_pair.0, try!(value_pair.1.parse::<u64>())));
            }
        }

        Ok(ProblemAnswer {
            actual: try!(triangle.get_largest_path_sum()),
            expected: EXPECTED_RESULT,
        })
    });
}

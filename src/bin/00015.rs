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

// Starting in the top left corner of a 2x2 grid, there are 6 routes (without
// backtracking) to the bottom right corner.
//
//   [... see 00015.gif ...]
//
// How many routes are there through a 20x20 grid?

extern crate euler;
use self::euler::math::combinatorics;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 137846528820;

fn main() {
    main_impl(|| -> EulerResult<ProblemAnswer<u64>> {
        // It is well-defined that the number of paths (without backtracking) through
        // an m by n grid is: (m + n) combinations of n.
        Ok(ProblemAnswer {
            actual: try!(combinatorics::combinations(40, 20)),
            expected: EXPECTED_RESULT,
        })
    });
}

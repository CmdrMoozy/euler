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

// If we list all the natural numbers below 10 that are multiples of 3 or 5, we
// get 3, 5, 6 and 9. The sum of these multiples is 23.
//
// Find the sum of all the multiples of 3 or 5 below 1000.

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: i64 = 233168;

fn main() {
    main_impl(|| -> EulerResult<ProblemAnswer<i64>> {
        let mut total: i64 = 0;
        for i in 0..1000 {
            if ((i % 5) == 0) || ((i % 3) == 0) {
                total += i;
            }
        }
        Ok(ProblemAnswer {
            actual: total,
            expected: EXPECTED_RESULT,
        })
    });
}

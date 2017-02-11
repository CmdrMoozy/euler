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

// 2520 is the smallest number that can be divided by each of the numbers from
// 1 to 10 without any remainder.
//
// What is the smallest positive number that is evenly divisible by all of the
// numbers from 1 to 20?

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 232792560;
// We don't need to check each potential in the range [1, 20], since some such
// numbers are themselves factors of other numbers in the range. So, define the
// minimal list of factors we need to test for.
const FACTORS: &'static [u64] = &[20, 19, 18, 17, 16, 15, 14, 13, 12, 11];

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut result: u64 = 0;
        // We can start with 20, since clearly any number smaller would not be
        // divisible by 20.
        let mut n: u64 = 20;
        while result == 0 {
            if FACTORS.iter().map(|f| n % *f == 0).fold(true, |acc, is_factor| acc && is_factor) {
                result = n;
            }
            // We know the answer must be a multiple of 20, so we can increase by that step.
            n += 20;
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

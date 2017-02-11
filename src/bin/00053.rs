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

// There are exactly ten ways of selecting three from five, 12345:
//
//   123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
//
// In combinatorics, we use the notation, 5C3 = 10.
//
// In general,
//
// nCr = n! / (r! * (n-r)!), where r <= n, n! = n * n-1 * ... * 3 * 2 * 1,
// and 0! = 1.
//
// It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.
//
// How many, not necessarily distinct, values of nCr, for 1 <= n <= 100, are
// greater than one-million?

extern crate euler;
use self::euler::math::combinatorics;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const N_MAX: u64 = 100;
const OUTPUT_TARGET: u64 = 1000000;

const EXPECTED_RESULT: u64 = 4075;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut count: u64 = 0;

        for n in 1..N_MAX + 1 {
            let mut min_r: u64 = 0;
            for r in 1..n + 1 {
                if combinatorics::combinations(n, r).ok().unwrap() > OUTPUT_TARGET {
                    min_r = r;
                    break;
                }
            }
            if min_r == 0 {
                continue;
            }

            let mut max_r: u64 = 0;
            for r in (1..n + 1).rev() {
                if combinatorics::combinations(n, r).ok().unwrap() > OUTPUT_TARGET {
                    max_r = r;
                    break;
                }
            }

            count += max_r - min_r + 1;
        }

        Ok(ProblemAnswer {
            actual: count,
            expected: EXPECTED_RESULT,
        })
    });
}

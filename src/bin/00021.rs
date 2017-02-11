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

// Let d(n) be defined as the sum of proper divisors of n (numbers less than n
// which divide evenly into n). If d(a) = b and d(b) = a, where a != b, then a
// and b are an amicable pair and each of a and b are called amicable numbers.
//
// For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44,
// 55 and 110; therefore d(22) = 284. The proper divisors of 284 are 1, 2, 4,
// 71 and 142; so d(284) = 220.
//
// Evaluate the sum of all the amicable numbers under 10000.

use std::collections::HashSet;

extern crate euler;
use self::euler::math::division::aliquot_sum_proper_divisors;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 31626;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut b_set: HashSet<u64> = HashSet::new();

        let mut sum: u64 = 0;
        for a in 0..10001 {
            if b_set.contains(&a) {
                continue;
            }

            let b: u64 = aliquot_sum_proper_divisors(a);
            if a == b {
                continue;
            }

            if aliquot_sum_proper_divisors(b) == a {
                sum += a;
                sum += b;
                b_set.insert(b);
            }
        }

        Ok(ProblemAnswer {
            actual: sum,
            expected: EXPECTED_RESULT,
        })
    });
}

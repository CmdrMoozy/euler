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

// A perfect number is a number for which the sum of its proper divisors is
// exactly equal to the number. For example, the sum of the proper divisors of
// 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
//
// A number n is called deficient if the sum of its proper divisors is less
// than n and it is called abundant if this sum exceeds n.
//
// As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest
// number thatn can be written as the sum of two abundant numbers is 24. By
// mathematical analysis, it can be shown that all integers greater than 28123
// can be written as the sum of two abundant numbers. However, this upper limit
// cannot be reduced by analysis even though it is known that the greatest
// number that cannot be expressed as the sum of two abundant numbers is less
// than this limit.
//
// Find the sum of all the positive integers which cannot be written as the sum
// of two abundant numbers.

use std::collections::HashSet;

extern crate euler;
use self::euler::math::division::aliquot_sum_proper_divisors;
use self::euler::util::error::*;
use self::euler::util::problem::*;

// We reduce the upper limit as per:
// http://en.wikipedia.org/wiki/Abundant_number
const LIMIT: u64 = 20161;

const EXPECTED_RESULT: u64 = 4179871;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut abundant_numbers: HashSet<u64> = HashSet::new();
        // Build a set of all abundant numbers in range. 12 is the smallest abundant
        // number, so start there.
        for i in 12..(LIMIT + 1) {
            if abundant_numbers.contains(&i) {
                continue;
            }

            if aliquot_sum_proper_divisors(i) > i {
                // If this number is abundant, add all of its multiples to the list.
                let mut k: u64 = i;
                while k <= LIMIT {
                    abundant_numbers.insert(k.clone());
                    k += i;
                }
            }
        }

        // For each abundant number in range, see if it can be written as a sum of
        // abundant numbers.
        let mut total: u64 = 0;
        for i in 1..(LIMIT + 1) {
            let mut sum: bool = false;

            for j in 0..(LIMIT + 1) {
                if let Some(v) = abundant_numbers.get(&j) {
                    if *v >= i {
                        break;
                    }

                    let k: u64 = i - v;
                    if k <= LIMIT {
                        if abundant_numbers.get(&k).cloned().unwrap_or(0) == k {
                            sum = true;
                            break;
                        }
                    }
                }
            }

            if !sum {
                total += i;
            }
        }

        Ok(ProblemAnswer {
            actual: total,
            expected: EXPECTED_RESULT,
        })
    });
}

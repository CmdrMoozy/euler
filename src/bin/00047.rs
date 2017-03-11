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

// The first two consecutive numbers to have two distinct prime factors are:
//
//     14 = 2 x 7
//     15 = 3 x 5
//
// The first three consecutive numbers to have three distinct prime factors are:
//
//     644 = 2^2 x 7 x 23
//     645 = 3 x 5 x 43
//     646 = 2 x 17 x 19
//
// Find the first four consecutive integers to have four distinct prime
// factors. What is the first of these numbers?

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const STARTING_UPPER_LIMIT: usize = 200000;
const UPPER_LIMIT_MULTIPLIER: usize = 2;

const EXPECTED_RESULT: usize = 134043;

fn sieve(limit: usize) -> Vec<usize> {
    let mut list = vec![0; limit];
    for i in 2..limit {
        if list[i] > 0 {
            continue;
        }

        let mut j = i;
        while j < limit {
            list[j] += 1;
            j += i;
        }
    }
    list
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let mut result: usize = 0;
        let mut limit: usize = STARTING_UPPER_LIMIT;
        while result == 0 {
            let list = sieve(limit);

            let mut i = 0;
            while i + 3 < limit {
                if list[i] == 4 {
                    if list[i + 3] == 4 {
                        if list[i + 1] == 4 {
                            if list[i + 2] == 4 {
                                result = i;
                                break;
                            } else {
                                i += 3;
                            }
                        } else {
                            i += 3;
                        }
                    } else {
                        i += 4;
                    }
                } else {
                    i += 1;
                }
            }

            limit *= UPPER_LIMIT_MULTIPLIER;
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

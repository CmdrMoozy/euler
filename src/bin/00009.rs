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

// A Pythagorean triplet is a set of three natural numbers, a < b < c, for
// which,
//
//     a^2 + b^2 = c^2
//
// For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2
//
// There exists a Pythagorean triplet for which a + b + c = 1000. Find the
// product abc.

#![feature(step_by)]

#[macro_use]
extern crate error_chain;

extern crate euler;
use self::euler::math::geometry;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 31875000;

fn check_solution(m: u64, n: u64, k: u64) -> Option<u64> {
    let (a, b, c) = geometry::get_pythagorean_triple(m, n, k);
    match a + b + c == 1000 {
        false => None,
        true => Some(a * b * c),
    }
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        for range_max in (5..1000).step_by(5) {
            for m in 1..(range_max + 1) {
                for n in 1..m {
                    for k in 1..(range_max + 1) {
                        if let Some(product) = check_solution(m, n, k) {
                            return Ok(ProblemAnswer {
                                actual: product,
                                expected: EXPECTED_RESULT,
                            });
                        }
                    }
                }
            }
        }

        bail!("No solution found");
    });
}

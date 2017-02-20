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

// If p is the perimeter of a right angle triangle with integral length sides,
// {a, b, c}, there are exactly three solutions for p = 120.
//
// {20, 48, 52}, {24, 45, 51}, {30, 40, 50}
//
// For which value of p <= 1000, is the number of solutions maximised?

use std::cmp;
use std::collections::{HashMap, HashSet};

extern crate euler;
use self::euler::math::exp;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const PERIMETER_MAX: u64 = 1000;

const EXPECTED_RESULT: u64 = 840;

fn normalized_triple(a: u64, b: u64, c: u64) -> (u64, u64, u64) {
    let normalized_c = cmp::max(cmp::max(a, b), c);
    let normalized_a = cmp::min(cmp::min(a, b), c);
    (normalized_a, (a + b + c) - (normalized_a + normalized_c), normalized_c)
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut counts: HashMap<u64, HashSet<(u64, u64, u64)>> = HashMap::new();

        for a in 1..999 {
            for b in 1..999 {
                let c_squared = (a * a) + (b * b);
                let c = exp::isqrt(c_squared);

                if c * c != c_squared {
                    // This isn't actually a valid triple.
                    continue;
                }

                let p = a + b + c;
                if p > PERIMETER_MAX {
                    // This triangle's perimeter is too large.
                    continue;
                }

                let perimeter_set = counts.entry(p).or_insert_with(HashSet::new);
                perimeter_set.insert(normalized_triple(a, b, c));
            }
        }

        let mut max_perimeter: u64 = 0;
        let mut max_count: usize = 0;
        for (perimeter, triples) in counts {
            if triples.len() > max_count {
                max_perimeter = perimeter;
                max_count = triples.len();
            }
        }

        Ok(ProblemAnswer {
            actual: max_perimeter,
            expected: EXPECTED_RESULT,
        })
    });
}

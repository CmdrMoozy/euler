// Copyright 2013 Axel Rasmussen
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
    (
        normalized_a,
        (a + b + c) - (normalized_a + normalized_c),
        normalized_c,
    )
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

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

// A Pythagorean triplet is a set of three natural numbers, a < b < c, for
// which,
//
//     a^2 + b^2 = c^2
//
// For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2
//
// There exists a Pythagorean triplet for which a + b + c = 1000. Find the
// product abc.

use euler::math::geometry;
use euler::util::error::*;
use euler::util::problem::*;
use failure::bail;

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
        let mut range_max = 5;
        while range_max < 1000 {
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
            range_max += 5;
        }

        bail!("No solution found");
    });
}

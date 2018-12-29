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

// The cube, 41063625 (345^3), can be permutated to produce two other cubes:
// 56623104 (384^3) and 64430125 (405^3). In fact, 41063625 is the smallest
// cube which has exactly three permutations of its digits which are also cube.
//
// Find the smallest cube for which exactly five permutations of its digits are
// cube.

use euler::algorithm::sequence;
use euler::math::exp;
use euler::util::error::*;
use euler::util::problem::*;

// "Find the smallest cube for which exactly CUBIC_PERMS_TARGET permutations of
// its digits are cube."
// const CUBIC_PERMS_TARGET: usize = 3;
const CUBIC_PERMS_TARGET: usize = 5;

const EXPECTED_RESULT: u64 = 5027;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut result: Option<u64> = None;
        // We can start with 8-digit cubes, since we're given that 41063625 is the
        // smallest 3-permutation.
        let mut digits: u64 = 8;

        while result.is_none() {
            // Build the range of numbers we'll be testing for this digit count.
            let min = exp::icbrt(10_u64.pow(digits as u32 - 1)) + 1;
            let max = exp::icbrt(10_u64.pow(digits as u32));
            let mut bases = vec![0_u64; (max - min) as usize];
            for base in min..max {
                bases[(base - min) as usize] = base;
            }

            // For each base in this range, compute its cube root. For each other value in
            // this range, if it's a permutation of the current value, we count it.
            //
            // If this value has exactly CUBIC_PERMS_TARGET permutations which are cubes in
            // the same range, we're done. Otherwise, we can remove ALL permutations of
            // this value from our list, since they have already been checked by proxy.
            for idx in 0..bases.len() {
                // If this base has already been checked, skip it.
                let base = bases[idx];
                if base == 0 {
                    continue;
                }
                let value = base * base * base;

                // For each other value, test if it's a permutation of this value.
                let mut permutation_idxes: Vec<usize> = Vec::with_capacity(CUBIC_PERMS_TARGET);
                for other_idx in idx + 1..bases.len() {
                    // If we have already found too many permutations, stop.
                    if permutation_idxes.len() >= CUBIC_PERMS_TARGET {
                        break;
                    }

                    // Once again, skip this value if it has already been checked.
                    let other_base = bases[other_idx];
                    if other_base == 0 {
                        continue;
                    }
                    let other_value = other_base * other_base * other_base;

                    // If this other value is a permutation, add it to the list and continue.
                    if sequence::integer_is_permutation_of(value, other_value)? {
                        permutation_idxes.push(other_idx);
                    }
                }

                // If we found the right number of permutations, we're done. Otherwise, mark
                // all of the values as checked.
                if permutation_idxes.len() == CUBIC_PERMS_TARGET - 1 {
                    result = Some(bases[idx]);
                    break;
                } else {
                    bases[idx] = 0;
                    for other_idx in &permutation_idxes {
                        bases[*other_idx] = 0;
                    }
                }
            }

            digits += 1;
        }

        Ok(ProblemAnswer {
            actual: result.unwrap(),
            expected: EXPECTED_RESULT,
        })
    });
}

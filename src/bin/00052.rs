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

// It can be seen that the number, 125874, and its double, 251748, contain
// exactly the same digits, but in a different order.
//
// Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x,
// contain the same digits.

extern crate euler;
use self::euler::algorithm::sequence::integer_is_permutation_of;
use self::euler::math::exp::log10;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 142857;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut x: u64 = 1;
        loop {
            // If log10(6x) > log10(x), we can skip x up to 10^(log10(x) + 1).
            let logx = log10(x);
            if log10(6 * x) > logx {
                x = 10_u64.pow(logx as u32 + 1);
                continue;
            }

            // If x contains the same digits as [2, 6]x, then we have found the answer.
            let all_are_permutations: Result<bool> = (2..7)
                .map(|multiple| integer_is_permutation_of(x, x * multiple))
                .fold(Ok(true), |acc, is_permutation| Ok(acc? && is_permutation?));
            if all_are_permutations? {
                break;
            }

            x += 1;
        }

        Ok(ProblemAnswer {
            actual: x,
            expected: EXPECTED_RESULT,
        })
    });
}

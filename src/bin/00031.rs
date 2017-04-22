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

// In England, the currency is made up of pound and pence, and there are eight
// coins in general
// circulation:
//
//     1p, 2p, 5p, 10p, 20p, 50p, 1pound and 2pound
//
// It is possible to make 2 pounds in the following way:
//
//     1x1pound + 1x50p + 2x20p + 1x5p + 1x2p + 3x1p
//
// How many different ways can 2 pounds be made using any number of coins?

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: usize = 73682;

/// Count the number of ways the given target value can be made from the given
/// list of coins. Note that both coin values and the target value should be
/// specified in the same unit (e.g., pence, cents, etc.). For the initial
/// call, existing_value should be 0 (this function is recursive).
fn count_coin_combinations(coins: &[i64], existing_value: i64, target: i64) -> usize {
    let mut count: usize = 0;
    let coin: i64 = coins[0];
    let remaining_coins = &coins[1..];

    let mut v: i64 = target;
    while v >= 0 {
        let value: i64 = existing_value + v;
        v -= coin;
        if value > target {
            continue;
        }

        if remaining_coins.is_empty() {
            if value == target {
                count += 1;
            }
        } else {
            count += count_coin_combinations(remaining_coins, value, target);
        }
    }

    count
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        // Just calculate the answer using brute force, skipping the interior loops if
        // the total produced by the outer loops is already too great. This is a stupid
        // solution, but it is acceptably fast.

        Ok(ProblemAnswer {
            actual: count_coin_combinations(&[1, 2, 5, 10, 20, 50, 100, 200], 0, 200),
            expected: EXPECTED_RESULT,
        })
    });
}

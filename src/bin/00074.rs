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

// The number 145 is well known for the property that the sum of the factorial
// of its digits is equal to 145:
//
//     1! + 4! + 5! = 1 + 24 + 120 = 145
//
// Perhaps less well known is 169, in that it produces the longest chain of
// numbers that link back to 169; it turns out that there are only three such
// loops that exist:
//
//     169 -> 363601 -> 1454 -> 169
//     871 -> 45361 -> 871
//     872 -> 45362 -> 872
//
// It is not difficult to prove that EVERY starting number will eventually get
// stuck in a loop. For example,
//
//     69 -> 363600 -> 1454 -> 169 -> 363601 (-> 1454)
//     78 -> 45360 -> 871 -> 46361 (-> 871)
//     540 -> 145 (-> 145)
//
// Starting with 69 produces a chain of five non-repeating terms, but the
// longest non-repeating chain with a starting number below one million is
// sixty terms.
//
// How many chains, with a starting number below one million, contain exactly
// sixty non-repeating terms?

use std::collections::HashMap;

#[macro_use]
extern crate error_chain;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const MIN_START: u64 = 0;
const MAX_START: u64 = 999999;

const TARGET_CHAIN_LENGTH: usize = 60;

const EXPECTED_RESULT: usize = 402;

fn is_repeat(chain: &Vec<u64>, value: u64) -> bool {
    // The longest loop is of length 4 (including the repeat), as given in the
    // problem statement. So, we only need to examine the last 4 items of the chain.
    chain.iter().rev().take(4).find(|&&v| v == value).is_some()
}

fn factorial_of_digit(digit: u64) -> Result<u64> {
    static DIGIT_FACTORIAL_TABLE: &'static [u64] = &[1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880];
    if digit >= 10 {
        bail!("factorial_of_digit requires that the digit is in the range [0, 9]");
    }
    Ok(DIGIT_FACTORIAL_TABLE[digit as usize])
}

fn digit_factorial(mut v: u64) -> Result<u64> {
    let mut result: u64 = 0;
    while v > 0 {
        result += factorial_of_digit(v % 10)?;
        v /= 10;
    }
    Ok(result)
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let mut count: usize = 0;
        let mut length_cache: HashMap<u64, usize> = HashMap::new();
        let mut chain: Vec<u64> = Vec::with_capacity(TARGET_CHAIN_LENGTH);

        for n in MIN_START..MAX_START + 1 {
            chain.clear();
            let mut repeat: u64 = 0;
            let mut cached_length: usize = 0;

            let mut v: u64 = n;
            loop {
                // If we already have a cached chain length for this value, stop here.
                if let Some(&cl) = length_cache.get(&v) {
                    cached_length = cl;
                    break;
                }

                // If we've ended up in a loop, stop here.
                if is_repeat(&chain, v) {
                    repeat = v;
                    break;
                }

                chain.push(v);
                v = digit_factorial(v)?;
            }

            // We know the chain length of every number in this chain up to the first
            // instance of the number we repeated. Cache the length of each of these
            // numbers.
            let length = chain.len() + cached_length;
            for idx in 0..chain.len() {
                length_cache.insert(chain[idx], length - idx);
                // If we've hit the repeat point, then stop here.
                if chain[idx] == repeat {
                    break;
                }
            }

            // If we've found a chain with the desired length, count it.
            if length == TARGET_CHAIN_LENGTH {
                count += 1;
            }
        }

        Ok(ProblemAnswer {
            actual: count,
            expected: EXPECTED_RESULT,
        })
    });
}

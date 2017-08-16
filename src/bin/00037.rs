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

// The number 3797 has an interesting property. Being prime itself, it is
// possible to continuously remove digits from left to right, and remain prime
// at each stage: 3797, 797, 97, and 7. Similarly we can work from right to
// left: 3797, 379, 37, and 3.
//
// Find the sum of the only eleven primes that are both truncatable from left
// to right and right to left.
//
// NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.

use std::collections::VecDeque;

extern crate euler;
use self::euler::math::prime::PrimeSieve;
use self::euler::math::sieve::Sieve;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const INITIAL_SIEVE_LIMIT: u64 = 1000000;
const SIEVE_STEPPING: u64 = 2;
const TARGET_COUNT: usize = 11;

const EXPECTED_RESULT: u64 = 748317;

fn is_ltr_truncatable_prime(n: u64, sieve: &PrimeSieve) -> bool {
    if n < 10 {
        return true;
    }

    let digits: VecDeque<char> = n.to_string().chars().collect();
    for skip in 1..digits.len() {
        let truncated: u64 = digits
            .iter()
            .skip(skip)
            .cloned()
            .collect::<String>()
            .parse()
            .unwrap();
        if !sieve.contains(truncated).unwrap() {
            return false;
        }
    }
    true
}

fn is_rtl_truncatable_prime(mut n: u64, sieve: &PrimeSieve) -> bool {
    n /= 10;
    while n > 0 {
        if !sieve.contains(n).unwrap() {
            return false;
        }
        n /= 10;
    }
    true
}

fn find_truncatable_primes(
    limit: u64,
    old_limit: u64,
    mut count: usize,
    mut sum: u64,
) -> (usize, u64) {
    let sieve = PrimeSieve::new(limit);
    let mut iter = sieve.iter().skip_while(move |p| *p <= old_limit).peekable();
    while count < TARGET_COUNT && iter.peek().is_some() {
        let p = iter.next().unwrap();

        // Skip single-digit primes, as described in the problem.
        if p < 10 {
            continue;
        }

        if is_ltr_truncatable_prime(p, &sieve) && is_rtl_truncatable_prime(p, &sieve) {
            count += 1;
            sum += p;
        }
    }
    return (count, sum);
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut limit: u64 = INITIAL_SIEVE_LIMIT;
        let mut old_limit: u64 = 0;
        let mut count: usize = 0;
        let mut sum: u64 = 0;
        while count < TARGET_COUNT {
            let (c, s) = find_truncatable_primes(limit, old_limit, count, sum);
            count = c;
            sum = s;

            if count < TARGET_COUNT {
                old_limit = limit;
                limit *= SIEVE_STEPPING;
            }
        }

        Ok(ProblemAnswer {
            actual: sum,
            expected: EXPECTED_RESULT,
        })
    });
}

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

// Euler's Totient function, phi(n), is used to determine the number of numbers
// less than n which are relatively prime to n. For example, as 1, 2, 4, 5, 7,
// and 8, are all less than nine and relatively prime to nine, phi(9) = 6.
//
// |----|-------------|--------|------------|
// | n  | Coprimes    | phi(n) | n / phi(n) |
// |----|-------------|--------|------------|
// | 2  | 1           | 1      | 2          |
// | 3  | 1,2         | 2      | 1.5        |
// | 4  | 1,3         | 2      | 2          |
// | 5  | 1,2,3,4     | 4      | 1.25       |
// | 6  | 1,5         | 2      | 3          |
// | 7  | 1,2,3,4,5,6 | 6      | 1.1666...  |
// | 8  | 1,3,5,7     | 4      | 2          |
// | 9  | 1,2,4,5,7,8 | 6      | 1.5        |
// | 10 | 1,3,7,9     | 4      | 2.5        |
// |----|-------------|--------|------------|
//
// It can be seen that n=6 produces a maximum n / phi(n) for n <= 10.
//
// Find the value of n <= 1,000,000 for which n / phi(n) is a maximum.

extern crate euler;
use self::euler::algorithm;
use self::euler::math::prime::PrimeSieve;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const UPPER_BOUND: u64 = 1000000; // 1000000;

const EXPECTED_RESULT: u64 = 510510;

/// This function recursively generates a list of all numbers less than or
/// equal to n, excluding 1. Each number in the list is represented as its
/// prime factorization (non-squarefree numbers are represented by repeated
/// prime factors in their lists).
///
/// The minimum_prime_factor is used to limit the work we do when recursing.
/// This value should be 0 for the initial call to this function.
fn get_composites(primes: &Vec<u64>, n: u64, minimum_prime_factor: u64) -> Vec<Vec<u64>> {
    if minimum_prime_factor >= n {
        return Vec::new();
    }

    let start_idx = algorithm::lower_bound(primes, &minimum_prime_factor);
    let end_idx = algorithm::upper_bound(primes, &n);

    let mut result: Vec<Vec<u64>> = Vec::new();
    for &prime in &primes[start_idx..end_idx] {
        result.push(vec![prime]);

        let s = get_composites(primes, n / prime, prime);
        for mut list in s.into_iter() {
            list.push(prime);
            result.push(list);
        }
    }
    result
}

/// This function computes the totient of the given number. The given vector is
/// assumed to be a prime factorization of the number, where non-squarefree
/// numbers are represented by repeated primes in the list. Also note that, for
/// non-squarefree integers, the given list needs to be sorted (in either
/// ascending or descending order).
fn totient(n: &Vec<u64>) -> u64 {
    let mut totient: u64 = 0;
    let mut i: usize = 0;

    while i < n.len() {
        let prime: u64 = n[i];
        let exponent: usize = n[i..].iter().filter(|p| **p == prime).count();
        i += exponent;

        let step = prime.pow(exponent as u32 - 1) * (prime - 1);
        totient = match totient {
            0 => step,
            _ => totient * step,
        };
    }

    totient
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let sieve = PrimeSieve::new(UPPER_BOUND);
        let primes: Vec<u64> = sieve.iter().collect();
        let numbers = get_composites(&primes, UPPER_BOUND, 0);
        let mut maxr: f64 = 0.0;
        let mut maxn: u64 = 0;

        for i in 0..numbers.len() {
            let n = numbers[i].iter().fold(1, |acc, p| acc * p);
            let r = (n as f64) / (totient(numbers.get(i).unwrap()) as f64);

            if r > maxr {
                maxn = n;
                maxr = r;
            }
        }

        Ok(ProblemAnswer {
            actual: maxn,
            expected: EXPECTED_RESULT,
        })
    });
}

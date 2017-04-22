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

// Euler published the remarkable quadratic formula:
//
//     n^2 + n + 41
//
// it turns out that the formula will produce 40 primes for the consecutive
// values n=0 to 39. However, when n=40, 40^2 + 40 + 41 = 40(40+1) + 41 is
// divisible by 41, and certainly when n=41, 41^2 + 41 + 41 is clearly
// divisible by 41.
//
// Using computers, the incredible formula n^2 - 79n + 1601 was discovered,
// which produces 80 primes for the consecutive values n=0 to 79. The product
// of the coefficients, -79 and 1601, is -126479.
//
// Considering quadratics of the form:
//
//     n^2 + an + b, where |a| < 1000 and |b| < 1000
//
// Find the product of the coefficients, a and b, for the quadratic expression
// that produces the longest maximum number of primes for consecutive values of
// n, starting with n=0.

extern crate euler;
use self::euler::math::prime::{self, PrimeSieve};
use self::euler::math::sieve::Sieve;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const SIEVE_LIMIT: u64 = 1000000;
const PRIME_PRECISION: u64 = 200;

const EXPECTED_RESULT: i64 = -59231;

// This function returns the result of our polynomial with the given value of
// n, and the given coefficients.
fn polynomial(n: i64, a: i64, b: i64) -> i64 { (n * n) + (a * n) + b }

fn main() {
    main_impl(|| -> Result<ProblemAnswer<i64>> {
        let sieve = PrimeSieve::new(SIEVE_LIMIT);

        let mut result_a: i64 = 0;
        let mut result_b: i64 = 0;
        let mut max_count: usize = 0;

        // Test each possible polynomial.
        for i in -999..1000 {
            for j in -999..1000 {
                // Test each possible n value in this polynomial.
                let mut current_count: usize = 0;
                let mut n: i64 = 0;
                loop {
                    let v = polynomial(n, i, j);

                    // Negative numbers are not prime.
                    if v < 0 {
                        break;
                    }
                    let v = v as u64;

                    let is_prime = match sieve.contains(v) {
                        Some(is_prime) => is_prime,
                        None => prime::is_prime(v, PRIME_PRECISION),
                    };

                    if !is_prime {
                        break;
                    }
                    current_count += 1;

                    n += 1;
                }

                // If this sequence is the longest we've found, update our results.
                if current_count > max_count {
                    result_a = i;
                    result_b = j;
                    max_count = current_count;
                }
            }
        }

        Ok(ProblemAnswer {
            actual: result_a * result_b,
            expected: EXPECTED_RESULT,
        })
    });
}

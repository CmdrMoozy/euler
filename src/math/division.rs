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

use math::exp;
use math::prime;
use std::ops::{Div, Rem};
use util::error::*;

/// This function divides the given dividend by the given divisor, and returns
/// a tuple of the resulting quoteient and remainder.
pub fn divide<T: Copy + Div<Output = T> + Rem<Output = T>>(dividend: T, divisor: T) -> (T, T) {
    (dividend / divisor, dividend % divisor)
}

/// Returns the greatest common divisor of a and b.
pub fn gcd(a: u64, b: u64) -> u64 {
    if a == 0 {
        return b;
    } else if b == 0 {
        return a;
    }

    let mut u: u64 = a;
    let mut v: u64 = b;

    // Find the largest power of 2 that divides both u and v. That is, divide u and
    // v by the smallest 2^k value such that u and v are not both even.
    let mut k: u64 = 0;
    while (u | v) & 1 == 0 {
        u /= 2;
        v /= 2;
        k += 1;
    }

    // Keep halving u until it is odd.
    while u % 2 == 0 {
        u /= 2;
    }

    while v != 0 {
        while v % 2 == 0 {
            v /= 2;
        }

        if u < v {
            v -= u;
        } else {
            let d = u - v;
            u = v;
            v = d;
        }

        v /= 2;
    }

    // Return u * 2^k.
    u << k
}

/// This function returns the least common multiple of a and b. To make it
/// easy, we reduce this problem to being able to find the greatest common
/// divisor, which we have a relatively efficient algorithm for. For more
/// information:
///
/// http://en.wikipedia.
/// org/wiki/Least_common_multiple#Reduction_by_the_greatest_common_divisor
///
/// If both a and b are zero, then zero is returned.
pub fn lcm(a: u64, b: u64) -> u64 {
    let gcd = gcd(a, b);
    match gcd {
        0 => 0,
        _ => (a * b) / gcd,
    }
}

/// This function tests if the two given integers, a and b, are coprime. Two
/// integers are considered coprime if their greatest common divisor is equal
/// to 1.
pub fn are_coprime(a: u64, b: u64) -> bool {
    gcd(a, b) == 1
}

/// The totient of anumber (also called phi(n)) is defined as the number of
/// positive integers less than or equal to n that are coprime to n. Note that,
/// for anything but small values of n, this function involves computing many
/// divisions, so it is in general expensive.
pub fn totient(n: u64) -> u64 {
    let mut r: u64 = 0;
    for i in 1..(n + 1) {
        if are_coprime(i, n) {
            r += 1;
        }
    }
    r
}

/// This function returns the length of the repeating portion of the decimal
/// part of the reciprocal of n.
///
/// This function's behavior is explained in-depth here:
///     http://mathforum.org/library/drmath/view/67018.html
///
/// It is a requirement that the given prime number sieve's limit must be at
/// least equivalent to isqrt(totient(x)), where x is equal to n with all
/// factors of 10 divided out. Otherwise, an error will be returned.
pub fn repetend_length(
    mut n: u64,
    sieve: &prime::PrimeSieve,
    primality_test_precision: Option<u64>,
) -> Result<u64> {
    // Remove all factors of 10 from our number.
    while n % 2 == 0 {
        n /= 2;
    }
    while n % 5 == 0 {
        n /= 5;
    }

    // For numbers that simply do not repeat, we return 0.
    if n == 1 {
        return Ok(0);
    }

    let mut d: u64 = totient(n);
    let f = prime::Factorization::new(d, sieve, primality_test_precision)?;

    for (factor, _) in f.iter() {
        if exp::ipowmod(10, d / factor, n) == 1 {
            d /= *factor;
        }
    }

    Ok(d)
}

/// This function returns the number of divisors of the given number. The
/// definition for this function is provided by:
/// http://en.wikipedia.org/wiki/Aliquot_sum#Definition.
pub fn aliquot_number_divisors(n: u64) -> u64 {
    if n == 0 {
        return 0;
    } else if n == 1 {
        return 1;
    }

    let mut i: u64 = 1;
    let mut limit: u64 = n;
    let mut result: u64 = 0;
    while i < limit {
        if (n % i) == 0 {
            limit = n / i;
            result += 1;
        }
        i += 1;
    }

    result *= 2;
    if exp::is_square(n) {
        result -= 1;
    }

    result
}

/// This function returns the sum of the proper divisors of the given number.
/// The definition for this function is provided by:
/// http://en.wikipedia.org/wiki/Aliquot_sum#Definition.
pub fn aliquot_sum_proper_divisors(n: u64) -> u64 {
    if n <= 1 {
        return 0;
    }

    let mut sum: u64 = 1;
    for i in 2..(exp::isqrt(n) + 1) {
        if (n % i) == 0 {
            sum += i;

            let mut j: u64 = n / i;
            j = if j == i { 0 } else { j };

            sum += j;
        }
    }

    sum
}

/// This function returns the sum of the divisors of the given number. The
/// definition of this function is provided by:
/// http://en.wikipedia.org/wiki/Aliquot_sum#Definition.
pub fn aliquot_sum_divisors(n: u64) -> u64 {
    aliquot_sum_proper_divisors(n) + n
}

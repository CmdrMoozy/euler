// euler - A collection of ProjectEuler libraries, tools, and solutions.
// Copyright (C) 2013 Axel Rasmussen
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

use math::exp;
use std::ops::{Div, Rem};

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

/// This function tests if the two given integers, a and b, are coprime. Two
/// integers are considered coprime if their greatest common divisor is equal
/// to 1.
pub fn are_coprime(a: u64, b: u64) -> bool { gcd(a, b) == 1 }

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
pub fn aliquot_sum_divisors(n: u64) -> u64 { aliquot_sum_proper_divisors(n) + n }

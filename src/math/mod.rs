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

pub mod exp;
pub mod geometry;
pub mod prime;
pub mod sequence;
pub mod stats;

use std::cmp;
use std::ops::{Div, Rem};
use ::util::error::*;

/// This function divides the given dividend by the given divisor, and returns
/// a tuple of the resulting quoteient and remainder.
pub fn divide<T: Copy + Div<Output = T> + Rem<Output = T>>(dividend: T, divisor: T) -> (T, T) {
    (dividend / divisor, dividend % divisor)
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

/// This function returns the number of ways r objects can be drawn from n
/// objects, assuming that order doesn't make any difference.
pub fn combinations(n: u64, r: u64) -> EulerResult<u64> {
    // We cannot draw r objects from n objects of r > n.
    if r > n {
        return Err(EulerError::new(ErrorKind::InvalidArgument {
            message: "Undefined combination.".to_owned(),
        }));
    }

    // The number of ways r objects can be drawn from n objects, assuming order
    // doesn't matter, is:
    //
    //   n! / ((n-r)! * r!)
    //
    // Because factorials get large very fast, we are going to "cancel" factors as
    // much as possible. If we define pi(a..b) = a * a + 1 * ... * b (for a <= b),
    // and if we let x = max(n - r, r) and y = min(n - r, r), we only need to
    // compute:
    //
    //   pi(x+1..n) / pi(1..y)

    let x: u64 = cmp::max(n - r, r);
    let y: u64 = cmp::min(n - r, r);
    Ok((x + 1..n + 1).fold(1, |acc, v| acc * v) / (1..y + 1).fold(1, |acc, v| acc * v))
}

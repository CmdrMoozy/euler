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

use ::math::exp;
use std::ops::{Div, Rem};

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

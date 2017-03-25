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

/// Returns x ^ n, or None if the computation overflowed. The result is
/// computed using exponentiation by squaring, just like the "pow" functions in
/// the standard library.
pub fn checked_ipow(x: u64, n: u64) -> Option<u64> {
    if n == 0 {
        Some(1)
    } else if n == 1 {
        Some(x)
    } else {
        match x.checked_mul(x) {
            Some(x_squared) => {
                if n & 1 == 0 {
                    checked_ipow(x_squared, n / 2)
                } else {
                    match checked_ipow(x_squared, (n - 1) / 2) {
                        Some(exp) => x.checked_mul(exp),
                        None => None,
                    }
                }
            },
            None => None,
        }
    }
}

/// This algorithm calculates b^e (mod m). This method is known as the
/// "right-to-left binary method," which is explained in more detail here:
/// http://en.wikipedia.org/wiki/Modular_exponentiation
pub fn ipowmod(mut base: u64, mut exponent: u64, modulus: u64) -> u64 {
    let mut result: u64 = 1;
    while exponent > 0 {
        if (exponent & 1) > 0 {
            result = (result * base) % modulus;
        }
        exponent >>= 1;
        base = (base * base) % modulus;
    }
    result
}

/// This function returns the floor of the base-10 logarithm of the given
/// number.
pub fn log10(n: u64) -> u64 {
    if n >= 10000000000000000000 {
        19
    } else if n >= 1000000000000000000 {
        18
    } else if n >= 100000000000000000 {
        17
    } else if n >= 10000000000000000 {
        16
    } else if n >= 1000000000000000 {
        15
    } else if n >= 100000000000000 {
        14
    } else if n >= 10000000000000 {
        13
    } else if n >= 1000000000000 {
        12
    } else if n >= 100000000000 {
        11
    } else if n >= 10000000000 {
        10
    } else if n >= 1000000000 {
        9
    } else if n >= 100000000 {
        8
    } else if n >= 10000000 {
        7
    } else if n >= 1000000 {
        6
    } else if n >= 100000 {
        5
    } else if n >= 10000 {
        4
    } else if n >= 1000 {
        3
    } else if n >= 100 {
        2
    } else if n >= 10 {
        1
    } else {
        0
    }
}

/// This function computes the integer square root of the given number. That
/// is, isqrt(x) is equivalent to floor(sqrt(x)). Note that, because we do not
/// use any floating-point arithmetic for this result, it is faster than the
/// built-in sqrt() function.
pub fn isqrt(mut n: u64) -> u64 {
    let mut res: u64 = 0;

    let mut bit: u64 = 1 << 62;
    while bit > n {
        bit >>= 2;
    }

    while bit != 0 {
        if n >= (res + bit) {
            n -= res + bit;
            res = (res >> 1) + bit;
        } else {
            res >>= 1;
        }
        bit >>= 2;
    }
    res
}

/// This function returns whether or not the given number is a perfect square.
pub fn is_square(n: u64) -> bool {
    let root = isqrt(n);
    (root * root) == n
}

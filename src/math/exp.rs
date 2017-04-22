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

/// This function returns the integer cube root of the given number. In
/// general, this is equivalent to floor(cbrt(n)), but is in theory much faster
/// because it uses no floating point arithmetic.
pub fn icbrt(mut n: u64) -> u64 {
    let mut s: i64 = 63;
    let mut y: u64 = 0;

    while s >= 0 {
        y += y;
        let b: u64 = 3 * y * (y + 1) + 1;

        if n >> s >= b {
            n -= b << s;
            y += 1;
        }

        s -= 3;
    }

    y
}

/// This function returns whether or not the given number is a perfect square.
pub fn is_square(n: u64) -> bool {
    let root = isqrt(n);
    (root * root) == n
}

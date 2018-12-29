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

/// This function returns the number of leading zeros for the given number.
pub fn nlz(mut x: u64) -> u64 {
    let mut num_leading_zeros: u64 = 64;
    let mut c: u64 = 32;

    loop {
        let y: u64 = x >> c;
        if y != 0 {
            num_leading_zeros = num_leading_zeros - c;
            x = y;
        }
        c >>= 1;

        if c == 0 {
            break;
        }
    }

    num_leading_zeros - x
}

/// This function returns the base-two logarithm of the given value. The
/// fractional portion of the result is truncated.
pub fn lg(x: u64) -> u64 {
    63 - nlz(x)
}

/// This function reverses the order of ALL of the bits in the given number,
/// including any leading zeros.
pub fn reverse_all_bits(mut n: u64) -> u64 {
    let mut result = n;
    n >>= 1;
    let mut remaining_shift: usize = 63;

    while n > 0 {
        result <<= 1;
        result |= n & 1;
        remaining_shift -= 1;
        n >>= 1;
    }

    result << remaining_shift
}

/// This function reverses the order of the bits in the given number, ignoring
/// any leading zeros.
pub fn reverse_bits(n: u64) -> u64 {
    reverse_all_bits(n) >> (63 - lg(n))
}

/// This function tests if the given 64-bit integer is palindromic in base 2.
pub fn is_bitwise_palindromic(n: u64) -> bool {
    n == reverse_bits(n)
}

/// This function returns the input value with the right-most one bit turned
/// off.
pub fn rmo_off(x: u64) -> u64 {
    match x == 0 {
        true => 0,
        false => x & (x - 1),
    }
}

/// This function tests whether or not the input value is a power of two.
pub fn is_pow_two(x: u64) -> bool {
    (x != 0) && (rmo_off(x) == 0)
}

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
pub fn lg(x: u64) -> u64 { 63 - nlz(x) }

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
pub fn reverse_bits(n: u64) -> u64 { reverse_all_bits(n) >> (63 - lg(n)) }

/// This function tests if the given 64-bit integer is palindromic in base 2.
pub fn is_bitwise_palindromic(n: u64) -> bool { n == reverse_bits(n) }

/// This function returns the input value with the right-most one bit turned
/// off.
pub fn rmo_off(x: u64) -> u64 {
    match x == 0 {
        true => 0,
        false => x & (x - 1),
    }
}

/// This function tests whether or not the input value is a power of two.
pub fn is_pow_two(x: u64) -> bool { (x != 0) && (rmo_off(x) == 0) }

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

use gmp::mpz::Mpz;
use math::exp::{is_square, isqrt};
use mpfr::mpfr::Mpfr;
use std::cmp::max;
use std::convert::TryFrom;
use std::ops::{Add, AddAssign, Sub, SubAssign, Mul, MulAssign, Div, DivAssign};

/// This function returns the nth Fibonacci number.
///
/// The Fibonacci sequence is defined such that F(0) = 0, F(1) = 1, and F(n) =
/// F(n-1) + F(n-2). For this function, however, we use a closed-form solution
/// to the Fibonacci sequence, so we can avoid unnecessary recursion.
///
/// Note that precision is only guaranteed up to n = 5000.
pub fn get_nth_fibonacci_number(n: u64) -> Mpz {
    // We use the closed-form solution called "Binet's Formula," defined here:
    // http://en.wikipedia.org/wiki/Fibonacci_number#Relation_to_the_golden_ratio
    //
    // The formula is: F(n) = (p^n - (1 - p)^n) / sqrt(5) where p is phi, the
    // Golden Ratio: p = (1 + sqrt(5)) / 2

    let sqrt_five = Mpfr::from(5 as i64).sqrt();
    let phi = (1.0 + &sqrt_five) / 2.0;
    let psi = (1.0 - &sqrt_five) / 2.0;
    let fib = (phi.pow(&Mpfr::from(n)) - psi.pow(&Mpfr::from(n))) / &sqrt_five;

    (&fib).into()
}

/// This function returns the nth triangle number.
///
/// A triangle number is equal to the sum of the positive integers less than or
/// equal to its place, i.e., the 7th triangle number = 7 + 6 + 5 + 4 + 3 + 2 +
/// 1.
pub fn get_nth_triangle_number(n: u64) -> u64 {
    // Using Faulhaber's formula we can express triangle numbers as the statement
    // below:
    (n * (n + 1)) / 2
}

/// This function returns the nth pentagonal number. For details, see:
/// https://en.wikipedia.org/wiki/Pentagonal_number
pub fn get_nth_pentagonal_number(n: u64) -> u64 { (3 * n * n - n) / 2 }

/// A given number, n, can be shown to be pentagonal if and only if (sqrt(24 *
/// n + 1) + 1) / 6 is a natural number. Thus, we test if (24 * n + 1) is a
/// perfect square, and if so then we test if sqrt(24 * n + 1) + 1 is evenly
/// divisible by 6.
pub fn is_pentagonal_number(n: u64) -> bool {
    let square = (n * 24) + 1;
    if !is_square(square) {
        return false;
    }

    let root = isqrt(square) + 1;
    if root & 1 > 0 {
        return false;
    }
    root % 3 == 0
}

/// This function returns the nth hexagonal number. For details, see:
/// https://en.wikipedia.org/wiki/Hexagonal_number
pub fn get_nth_hexagonal_number(n: u64) -> u64 { 2 * n * n - n }

fn binary_sequence_search<Index, Value, SequenceFn>(
    lower: Index, upper: Index, target: Value, sequence: SequenceFn) -> (Index, Value)
        where Index: Copy + PartialEq + Add<Output = Index> + AddAssign +
                Sub<Output = Index> + SubAssign + Mul<Output = Index> + MulAssign +
                Div<Output = Index> + DivAssign + TryFrom<usize> + Ord,
              Value: Clone + PartialOrd,
              SequenceFn: Fn(Index) -> Value {
    let mut midpoint: Index = lower + ((upper - lower) / Index::try_from(2 as usize).ok().unwrap());
    let mut value: Value = sequence(midpoint);

    if lower == midpoint {
        if value < target {
            while value < target {
                midpoint += Index::try_from(1 as usize).ok().unwrap();
                value = sequence(midpoint);
            }
        } else if value > target {
            while value >= target {
                midpoint -= Index::try_from(1 as usize).ok().unwrap();
                value = sequence(midpoint);
            }
        }
        return (midpoint, value);
    }

    if value < target {
        return binary_sequence_search(midpoint, upper, target, sequence);
    } else if value > target {
        return binary_sequence_search(lower, midpoint, target, sequence);
    } else {
        return (midpoint, value);
    }
}

/// This function performs a binary search on the given sequence (defined by a
/// function which returns the sequence member for an arbitrary nth index).
/// This function returns the smallest value (and its index) in the sequence
/// which is greater than or equal to the given target value.
///
/// This function requires that the given sequence is monotonically increasing
/// (i.e., f(n) <= f(n + 1) for any n). If this is not met, the result is
/// undefined.
///
/// Ideally, the caller should provide a start index which points to a sequence
/// value less than the target, but as close to it as possible. However, any
/// starting index will still produce a correct result.
pub fn sequence_search<Index, Value, SequenceFn>(
    start: Index, target: Value, sequence: SequenceFn) -> (Index, Value)
        where Index: Copy + PartialEq + Add<Output = Index> + AddAssign +
                Sub<Output = Index> + SubAssign + Mul<Output = Index> + MulAssign +
                Div<Output = Index> + DivAssign + TryFrom<usize> + Ord,
              Value: Clone + PartialOrd,
              SequenceFn: Fn(Index) -> Value {
    let mut lower_index: Index = start;
    let mut lower_value: Value = sequence(lower_index);

    while lower_value > target {
        lower_index /= Index::try_from(2 as usize).ok().unwrap();
        lower_value = sequence(lower_index);
    }

    let mut upper_index: Index = max(lower_index, Index::try_from(1 as usize).ok().unwrap());
    let mut upper_value: Value = lower_value;
    while upper_value <= target {
        upper_index *= Index::try_from(2 as usize).ok().unwrap();
        upper_value = sequence(upper_index);
    }

    binary_sequence_search(lower_index, upper_index, target, sequence)
}

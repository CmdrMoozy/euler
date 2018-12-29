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

use crate::math::exp::{is_square, isqrt};
use crate::math::FLOAT_DEFAULT_PRECISION;
use num::{Num, One};
use rug;
use std::cmp::max;

/// This function returns the nth Fibonacci number.
///
/// The Fibonacci sequence is defined such that F(0) = 0, F(1) = 1, and F(n) =
/// F(n-1) + F(n-2). For this function, however, we use a closed-form solution
/// to the Fibonacci sequence, so we can avoid unnecessary recursion.
///
/// Note that precision is only guaranteed up to n = 5000.
pub fn get_nth_fibonacci_number(n: u64) -> rug::Integer {
    use rug::ops::Pow;

    // We use the closed-form solution called "Binet's Formula," defined here:
    // http://en.wikipedia.org/wiki/Fibonacci_number#Relation_to_the_golden_ratio
    //
    // The formula is: F(n) = (p^n - (1 - p)^n) / sqrt(5) where p is phi, the
    // Golden Ratio: p = (1 + sqrt(5)) / 2

    let n = rug::Float::with_val(FLOAT_DEFAULT_PRECISION, n);
    let sqrt_five = rug::Float::with_val(FLOAT_DEFAULT_PRECISION, 5).sqrt();
    let phi: rug::Float = (1.0 + sqrt_five.clone()) / 2.0;
    let psi: rug::Float = (1.0 - sqrt_five.clone()) / 2.0;
    let fib = (phi.pow(n.clone()) - psi.pow(n)) / sqrt_five;
    fib.to_integer().unwrap()
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
pub fn get_nth_pentagonal_number(n: u64) -> u64 {
    (3 * n * n - n) / 2
}

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
pub fn get_nth_hexagonal_number(n: u64) -> u64 {
    2 * n * n - n
}

fn binary_sequence_search<Index, Value, SequenceFn>(
    lower: Index,
    upper: Index,
    target: Value,
    sequence: SequenceFn,
) -> (Index, Value)
where
    Index: Copy + Num + One + Ord,
    Value: Clone + PartialOrd,
    SequenceFn: Fn(Index) -> Value,
{
    let mut midpoint: Index = lower + ((upper - lower) / (Index::one() + Index::one()));
    let mut value: Value = sequence(midpoint);

    if lower == midpoint {
        if value < target {
            while value < target {
                midpoint = midpoint + Index::one();
                value = sequence(midpoint);
            }
        } else if value > target {
            while value >= target {
                midpoint = midpoint - Index::one();
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
    start: Index,
    target: Value,
    sequence: SequenceFn,
) -> (Index, Value)
where
    Index: Copy + Num + One + Ord,
    Value: Clone + PartialOrd,
    SequenceFn: Fn(Index) -> Value,
{
    let mut lower_index: Index = start;
    let mut lower_value: Value = sequence(lower_index);

    while lower_value > target {
        lower_index = lower_index / (Index::one() + Index::one());
        lower_value = sequence(lower_index);
    }

    let mut upper_index: Index = max(lower_index, Index::one());
    let mut upper_value: Value = lower_value;
    while upper_value <= target {
        upper_index = upper_index * (Index::one() + Index::one());
        upper_value = sequence(upper_index);
    }

    binary_sequence_search(lower_index, upper_index, target, sequence)
}

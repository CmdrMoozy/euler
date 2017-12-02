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

use itoa::{self, Integer};
use pdqsort;
use std::cmp::Ordering;
use std::fmt::Display;
use util::error::*;

/// Returns whether or not the given value is a palindrome. This works as
/// expected e.g. for integers, because we compare the string representations
/// provided by Display.
pub fn is_palindrome<T: Display>(x: &T) -> bool {
    let s = x.to_string();
    s == s.chars().rev().collect::<String>()
}

/// This is an implementation of Knuth's "Algorithm L", which permutates a
/// given vector of elements in lexicographic order according to the given
/// comparator. That is, because of this ordering, if the Vec is sorted in
/// ascending order according to the given comparator, then it contains the
/// "first" permutation.
///
/// More information:
/// http://en.wikipedia.
/// org/wiki/Permutation#Systematic_generation_of_all_permutations
///     http://blog.bjrn.se/2008/04/lexicographic-permutations-using.html
///
/// This function returns true if the Vec was permutated, or false if it
/// already contained the last permutation.
pub fn permutate<T, F: FnMut(&T, &T) -> Ordering>(v: &mut Vec<T>, mut compare: F) -> bool {
    // Vecs of size 0 or 1 have no other permutations.
    if v.len() < 2 {
        return false;
    }

    // Step 1: Find the largest index k such that v[k] < v[k + 1]. If no such index
    // exists, then the existing Vec contains the last permutation.
    let mut k: Option<usize> = None;
    for i in (0..(v.len() - 1)).rev() {
        if compare(&v[i], &v[i + 1]) == Ordering::Less {
            k = Some(i);
            break;
        }
    }
    if k.is_none() {
        return false;
    }
    let k = k.unwrap();

    // Step 2: Find the largest index l such that v[k] < v[l]. Since k + 1 is such
    // an index, l is well defined and satisfies k < l.
    let mut l: usize = k + 1;
    for i in ((k + 2)..v.len()).rev() {
        if compare(&v[k], &v[i]) == Ordering::Less {
            l = i;
            break;
        }
    }

    // Step 3: Swap v[k] and v[l].
    v.swap(k, l);

    // Step 4: Reverse the sequence from v[k + 1] up to and including the final
    // element v[n].
    &mut v[k + 1..].reverse();

    true
}

/// This is a convenient shorthand to call permutate() with a standard <
/// comparator.
pub fn permutate_lt<T: Ord>(v: &mut Vec<T>) -> bool { permutate(v, |a, b| a.cmp(b)) }

/// Returns true if the characters in a and b's string representations are
/// permutations of each other. This works for strings, but can also be used
/// for e.g. integers.
pub fn is_permutation_of<T: Display>(a: &T, b: &T) -> bool {
    let mut a = a.to_string().chars().collect::<Vec<char>>();
    let mut b = b.to_string().chars().collect::<Vec<char>>();
    pdqsort::sort(a.as_mut_slice());
    pdqsort::sort(b.as_mut_slice());
    a == b
}

/// This function is equivalent to `is_permutation_of`, but since it is
/// restricted to working only with integers we can enable some optimizations
/// which drastically improve performance.
pub fn integer_is_permutation_of<I: Integer>(a: I, b: I) -> Result<bool> {
    // We assume that I is at most 64-bits in length, so its string representation
    // is at most 20 digits long (i.e., bytes).
    let mut abuf = [0_u8; 20];
    itoa::write(&mut abuf[..], a)?;
    let mut bbuf = [0_u8; 20];
    itoa::write(&mut bbuf[..], b)?;

    // Check using a parity bit first to avoid doing an expensive sort.
    if (abuf[0] ^ abuf[1] ^ abuf[2] ^ abuf[3] ^ abuf[4] ^ abuf[5] ^ abuf[6] ^ abuf[7] ^ abuf[8]
        ^ abuf[9] ^ abuf[10] ^ abuf[11] ^ abuf[12] ^ abuf[13] ^ abuf[14] ^ abuf[15]
        ^ abuf[16] ^ abuf[17] ^ abuf[18] ^ abuf[19]) & 1
        != (bbuf[0] ^ bbuf[1] ^ bbuf[2] ^ bbuf[3] ^ bbuf[4] ^ bbuf[5] ^ bbuf[6] ^ bbuf[7] ^ bbuf[8]
            ^ bbuf[9] ^ bbuf[10] ^ bbuf[11] ^ bbuf[12] ^ bbuf[13] ^ bbuf[14] ^ bbuf[15]
            ^ bbuf[16] ^ bbuf[17] ^ bbuf[18] ^ bbuf[19]) & 1
    {
        return Ok(false);
    }

    pdqsort::sort(&mut abuf[..]);
    pdqsort::sort(&mut bbuf[..]);
    Ok(abuf == bbuf)
}

/// Returns the index of the first element in the given sorted vector that is
/// *not less* than (i.e. greater or equal to) the given value x. If no such
/// element could be found, returns v.len() instead.
///
/// This function is logarithmic in the length of the given vector. If the
/// given vector is not sorted in ascending order, the result is undefined.
pub fn lower_bound<T: Ord>(v: &Vec<T>, x: &T) -> usize {
    let mut first = 0;
    let mut count = v.len();
    let mut idx;

    while count > 0 {
        idx = first;
        let step = count / 2;
        idx += step;
        if v[idx] < *x {
            first = idx + 1;
            count -= step + 1;
        } else {
            count = step;
        }
    }

    first
}

/// Returns the index of the first element in the given sorted vector that is
/// *greater* than the given value x. If no such element could be found,
/// returns v.len() instead.
///
/// This function is logarithmic in the length of the given vector. If the
/// given vector is not sorted in ascending order, the result is undefined.
pub fn upper_bound<T: Ord>(v: &Vec<T>, x: &T) -> usize {
    let mut first = 0;
    let mut count = v.len();
    let mut idx;

    while count > 0 {
        idx = first;
        let step = count / 2;
        idx += step;
        if *x >= v[idx] {
            first = idx + 1;
            count -= step + 1;
        } else {
            count = step;
        }
    }

    first
}

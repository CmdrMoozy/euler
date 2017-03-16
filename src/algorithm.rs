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

use std::cmp::Ordering;
use std::fmt::Display;

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
    a.sort();
    b.sort();
    a == b
}

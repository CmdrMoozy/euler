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

// The fraction 49/98 is a curious fraction, as an inexperienced mathematician
// in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which
// is correct, is obtained by cancelling the 9s.
//
// We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
//
// There are exactly four non-trivial examples of this type of fraction, less
// than one in value, and containing two digits in the numerator and
// denominator.
//
// If the product of these four fractions is given in its lowest common terms,
// find the value of the demoninator.

use std::collections::HashSet;
use std::iter::FromIterator;

extern crate euler;
use self::euler::structs::fraction::Fraction;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 100;

/// Returns true if the given fraction is a "trivial fraction" with regards to
/// this problem. That is, if both the numerator and denominator are evenly
/// divisible by 10.
fn is_trivial(f: &Fraction) -> bool { f.numerator() % 10 == 0 && f.denominator() % 10 == 0 }

/// Collects the digits (characters) of the given number into an arbitrary data
/// structure.
fn to_digits<F: FromIterator<char>>(v: u64) -> F { v.to_string().chars().collect() }

/// Returns a set of all of the digit characters which a and b have in common.
fn common_digits(a: u64, b: u64) -> HashSet<char> {
    let a_digits: HashSet<char> = to_digits(a);
    let b_digits: HashSet<char> = to_digits(b);
    a_digits.intersection(&b_digits).map(|c| *c).collect()
}

/// Returns a new integer by taking the existing integer, removing any digits
/// present in the given exclusion list, and then returning the remaining
/// digits (in the same order). If all digits were eliminated, 0 is returned
/// instead.
fn filter_digits(v: u64, exclude: &HashSet<char>) -> Result<u64> {
    let filtered: String = v.to_string()
        .chars()
        .filter(|d| !exclude.contains(d))
        .collect();
    Ok((match filtered.is_empty() {
        false => filtered.as_str(),
        true => "0",
    }).parse()?)
}

/// "Cancel" all of the digits in the given fraction's numerator and
/// denominator, according to the problem statement above.
fn cancel_all(f: &Fraction) -> Result<Fraction> {
    let common_digits = common_digits(f.numerator(), f.denominator());
    Fraction::new(
        filter_digits(f.numerator(), &common_digits)?,
        filter_digits(f.denominator(), &common_digits)?,
    )
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut fractions: Vec<Fraction> = vec![];

        for denominator in 10..100 {
            for numerator in 10..denominator {
                let a = Fraction::new(numerator, denominator)?;
                if is_trivial(&a) {
                    continue;
                }

                // Only consider fractions where our "digit cancelling" technique produces a
                // non-zero numerator and denominator.
                if let Ok(b) = cancel_all(&a) {
                    // Count this pair if we really did cancel some digits, and if the result is
                    // still equivalent.
                    if !a.is_identical(&b) && a == b {
                        fractions.push(a.reduce().0);
                    }
                }
            }
        }

        Ok(ProblemAnswer {
            actual: Fraction::new(
                fractions
                    .iter()
                    .map(|f| f.numerator())
                    .fold(1, |acc, n| acc * n),
                fractions
                    .iter()
                    .map(|f| f.denominator())
                    .fold(1, |acc, d| acc * d),
            )?.reduce()
                .0
                .denominator(),
            expected: EXPECTED_RESULT,
        })
    });
}

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
    let filtered: String = v.to_string().chars().filter(|d| !exclude.contains(d)).collect();
    Ok(try!((match filtered.is_empty() {
            false => filtered.as_str(),
            true => "0",
        })
        .parse()))
}

/// "Cancel" all of the digits in the given fraction's numerator and
/// denominator, according to the problem statement above.
fn cancel_all(f: &Fraction) -> Result<Fraction> {
    let common_digits = common_digits(f.numerator(), f.denominator());
    Fraction::new(try!(filter_digits(f.numerator(), &common_digits)),
                  try!(filter_digits(f.denominator(), &common_digits)))
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut fractions: Vec<Fraction> = vec![];

        for denominator in 10..100 {
            for numerator in 10..denominator {
                let a = try!(Fraction::new(numerator, denominator));
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
            actual: try!(Fraction::new(fractions.iter()
                                           .map(|f| f.numerator())
                                           .fold(1, |acc, n| acc * n),
                                       fractions.iter()
                                           .map(|f| f.denominator())
                                           .fold(1, |acc, d| acc * d)))
                .reduce()
                .0
                .denominator(),
            expected: EXPECTED_RESULT,
        })
    });
}

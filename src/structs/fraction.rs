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

use math::division;
use std::cmp::Ordering;
use util::error::*;

#[derive(Clone, Debug)]
pub struct Fraction(u64, u64);

impl PartialEq for Fraction {
    fn eq(&self, other: &Fraction) -> bool {
        if self.is_identical(other) {
            true
        } else {
            self.reduce().0.is_identical(&other.reduce().0)
        }
    }
}

impl Eq for Fraction {}

impl Ord for Fraction {
    fn cmp(&self, other: &Fraction) -> Ordering {
        let multiple = division::lcm(self.1, other.1);
        let self_numerator = self.0 * (multiple / self.1);
        let other_numerator = other.0 * (multiple / other.1);
        self_numerator.cmp(&other_numerator)
    }
}

impl PartialOrd for Fraction {
    fn partial_cmp(&self, other: &Fraction) -> Option<Ordering> { Some(self.cmp(other)) }
}

impl Fraction {
    pub fn new(numerator: u64, denominator: u64) -> Result<Fraction> {
        if denominator == 0 {
            bail!("Fractions must have a non-zero denominator")
        }
        Ok(Fraction(numerator, denominator))
    }

    pub fn numerator(&self) -> u64 { self.0 }

    pub fn denominator(&self) -> u64 { self.1 }

    /// Returns true if this fraction and the given other fraction are
    /// *identical* (i.e., they have exactly the same numerator and
    /// denominator).
    pub fn is_identical(&self, other: &Fraction) -> bool { self.0 == other.0 && self.1 == other.1 }

    /// Reduce this fraction to its lowest terms, returning the result as a
    /// copy. Also return a boolean where false indicates that this fraction
    /// was already in lowest terms, whereas true indicates that some reduction
    /// was performed.
    pub fn reduce(&self) -> (Fraction, bool) {
        let gcd = division::gcd(self.0, self.1);
        if gcd == 0 || gcd == 1 {
            (self.clone(), false)
        } else {
            (Fraction(self.0 / gcd, self.1 / gcd), true)
        }
    }
}

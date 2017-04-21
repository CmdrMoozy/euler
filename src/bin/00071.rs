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

// Consider the fraction, n/d, where n and d are positive integers. If n<d and
// HCF(n,d)=1, it is called a reduced proper fraction.
//
// If we list the set of reduced proper fractions for d <= 8 in ascending order
// of size, we get:
//
//     1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, _2/5_, 3/7, 1/2, 4/7, 3/5, 5/8,
//     2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
//
// It can be seen that 2/5 is the fraction immediately to the left of 3/7.
//
// By listing the set of reduced proper fractions for d <= 1,000,000 in
// ascending order of size, find the numerator of the fraction immediately to
// the left of 3/7.

extern crate euler;
use self::euler::structs::fraction::Fraction;
use self::euler::util::error::*;
use self::euler::util::problem::*;

// We will be searching, in a sorted list of all fractions where the
// denominator is <= DENOMINATOR_LIMIT, for a fraction immediately to the left
// of TARGET_N / TARGET_D.
const DENOMINATOR_LIMIT: u64 = 1000000;
const TARGET_N: u64 = 3;
const TARGET_D: u64 = 7;

const EXPECTED_RESULT: u64 = 428570;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut lower = Fraction::new(0, 1)?;
        let mut mediant = Fraction::new(0, 1)?;
        let upper = Fraction::new(TARGET_N, TARGET_D)?;

        while mediant.denominator() <= DENOMINATOR_LIMIT {
            lower = mediant;
            mediant = lower.mediant(&upper)?.0;
        }

        Ok(ProblemAnswer {
            actual: lower.numerator(),
            expected: EXPECTED_RESULT,
        })
    });
}

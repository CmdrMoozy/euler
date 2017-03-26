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
// If we list the set of reduced proper fractions from d <= 8 in ascending
// order of size, we get:
//
//     1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, _3/8_, _2/5_, _3/7_, 1/2, 4/7, 3/5,
//     5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
//
// It can be seen that there are 3 fractions between 1/3 and 1/2.
//
// How many fractions lie between 1/3 and 1/2 in the sorted set of reduced
// proper fractions for d <= 12,000?

extern crate euler;
use self::euler::structs::fraction::Fraction;
use self::euler::util::error::*;
use self::euler::util::problem::*;

// We will be searching for all fractions inbetween LOWER_TARGET_N /
// LOWER_TARGET_D and UPPER_TARGET_N / UPPER_TARGET_D, for every denominator
// from 1 to DENOMINATOR_LIMIT (inclusive).
const DENOMINATOR_LIMIT: u64 = 12000;
const LOWER_TARGET_N: u64 = 1;
const LOWER_TARGET_D: u64 = 3;
const UPPER_TARGET_N: u64 = 1;
const UPPER_TARGET_D: u64 = 2;

const EXPECTED_RESULT: usize = 7295372;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let mut lower: Fraction;
        let mut hold = try!(Fraction::new(LOWER_TARGET_N, LOWER_TARGET_D));
        let upper = try!(Fraction::new(UPPER_TARGET_N, UPPER_TARGET_D));

        // Find the fraction immediately less than our upper limit.
        while hold.denominator() <= DENOMINATOR_LIMIT {
            lower = hold;
            hold = try!(lower.mediant(&upper)).0;
        }

        // At this point, we just continuously calculate the next term until we reach
        // our lower limit. The formula for doing this can be found here:
        //
        //     http://en.wikipedia.org/wiki/Farey_sequence#Next_term
        let mut count: usize = 0;
        lower = try!(Fraction::new(LOWER_TARGET_N, LOWER_TARGET_D));
        let mut a = UPPER_TARGET_N;
        let mut b = UPPER_TARGET_D;
        let mut c = hold.numerator();
        let mut d = hold.denominator();
        while try!(Fraction::new(c, d)) > lower {
            count += 1;

            let k: u64 = ((DENOMINATOR_LIMIT + b) as f64 / d as f64).floor() as u64;

            let i = a;
            let j = b;

            a = c;
            b = d;
            c = (c * k) - i;
            d = (d * k) - j;
        }
        count -= 1; // We always over-count by 1.

        Ok(ProblemAnswer {
            actual: count,
            expected: EXPECTED_RESULT,
        })
    });
}

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

// It is possible to show that the square root of two can be expressed as an
// infinite continued fraction.
//
//     sqrt(2) = 1 + 1/(2 + 1/(2 + 1/(2 + ... ))) = 1.414213...
//
// By expanding this for the first four iterations, we get:
//
//     1 + 1/2 = 3/2 = 1.5
//     1 + 1/(2 + 1/2) = 7/5 = 1.4
//     1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...
//     1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...
//
// The next three expansions are 99/70, 239/169, and 577/408, but the eighth
// expansion, 1393/985, is the first example where the number of digits in the
// numerator exceeds the number of digits in the denominator.
//
// In the first one-thousand expansions, how many fractions contain a numerator
// with more digits than denominator?

extern crate gmp;
use gmp::mpz::Mpz;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: usize = 153;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let mut num = Mpz::from(1);
        let mut den = Mpz::from(1);
        let mut count: usize = 0;
        for _ in 0..1000 {
            // If this expansion's numerator has more digits than the denominator,
            // increment the count.
            if num.to_string().len() > den.to_string().len() {
                count += 1;
            }

            // Compute the next expansion.
            num = num + &den + &den;
            den = &num - den;
            let gcd = num.gcd(&den);
            num = num / &gcd;
            den = den / &gcd;
        }

        Ok(ProblemAnswer {
            actual: count,
            expected: EXPECTED_RESULT,
        })
    });
}

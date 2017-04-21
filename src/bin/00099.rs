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

// Comparing two numbers written in index form like 2^11 and 3^7 is not
// difficult, as any calculator would confirm that 2^11 = 2048 < 3^7 = 2187.
//
// However, confirming that 632382^518061 > 519432^525806 would be much more
// difficult, as both numbers contain over three million digits.
//
// Using base_exp.txt, a 22K text file containing one thousand lines with a
// base/exponent pair on each line, determine which line number has the
// greatest numerical value.
//
// NOTE: The first two lines in the file represent the numbers in the example
// given above.

use std::cmp::Ordering;

#[macro_use]
extern crate error_chain;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const INPUT_VALUES: &'static str = include_str!("00099.txt");

const EXPECTED_RESULT: usize = 709;

/// This function compares two b^e values. We take advantage of the fact that
/// deciding if:
///
/// a^b > c^d is equivalent to deciding if:
/// log(a^b) > log(c^d)
/// blog(a) > dlog(c)
fn compare_powers(ba: u32, ea: u32, bb: u32, eb: u32) -> Option<Ordering> {
    let a = f64::from(ba).log10() * f64::from(ea);
    let b = f64::from(bb).log10() * f64::from(eb);
    a.partial_cmp(&b)
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let mut line_number: usize = 0;
        let mut max_base: u32 = 1;
        let mut max_exponent: u32 = 1;
        let mut max_line_number: usize = 0;

        for line in INPUT_VALUES.lines() {
            line_number += 1;
            if line.len() == 0 {
                continue;
            }

            let pieces: Vec<&'static str> = line.split(',').collect();
            if pieces.len() != 2 {
                bail!("Line isn't a valid base,exponent pair");
            }
            let base = pieces[0].parse::<u32>()?;
            let exponent = pieces[1].parse::<u32>()?;
            if base == 0 || exponent == 0 {
                bail!("Encountered invalid 0 base or exponent");
            }

            if let Some(ord) = compare_powers(max_base, max_exponent, base, exponent) {
                if ord == Ordering::Less {
                    max_base = base;
                    max_exponent = exponent;
                    max_line_number = line_number;
                }
            }
        }

        Ok(ProblemAnswer {
            actual: max_line_number,
            expected: EXPECTED_RESULT,
        })
    });
}

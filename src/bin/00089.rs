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

// The rules for writing Roman numerals allow for many ways of writing each
// number (see About Roman Numerals...). However, there is always a "best" way
// of writing a particular number.
//
// For example, the following represent all of the legitimate ways of writing
// the number sixteen:
//
//     IIIIIIIIIIIIIIII
//     VIIIIIIIIIII
//     VVIIIIII
//     XIIIIII
//     VVVI
//     XVI
//
// The last example being considered the most efficient, as it uses the least
// number of numerals.
//
// The 11K text file, roman.txt (right click and 'Save Link/Target As...'),
// contains one thousand numbers written in valid, but not necessarily minimal,
// Roman numerals; that is, they are arranged in descending units and obey the
// subtractive pair rule (see About Roman Numerals... for the definitive rules
// for this problem).
//
// Find the number of characters saved by writing each of these in their
// minimal form.
//
// Note: You can assume that all the Roman numerals in the file contain no more
// than four consecutive identical units.

extern crate euler;
use self::euler::dsc::roman_numeral::RomanNumeral;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const INPUT_VALUES: &'static str = include_str!("00089.txt");

const EXPECTED_RESULT: usize = 743;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let mut in_chars: usize = 0;
        let mut out_chars: usize = 0;

        for line in INPUT_VALUES.lines() {
            // Note the input length.
            let line = line.trim();
            in_chars += line.len();

            // Parse this line, and get the output length.
            let rn = try!(line.parse::<RomanNumeral>());
            out_chars += rn.to_string().len();
        }

        assert!(in_chars >= out_chars);
        Ok(ProblemAnswer {
            actual: in_chars - out_chars,
            expected: EXPECTED_RESULT,
        })
    });
}

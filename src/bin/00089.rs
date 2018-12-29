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

use euler::dsc::roman_numeral::RomanNumeral;
use euler::util::error::*;
use euler::util::problem::*;

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
            let rn = line.parse::<RomanNumeral>()?;
            out_chars += rn.to_string().len();
        }

        assert!(in_chars >= out_chars);
        Ok(ProblemAnswer {
            actual: in_chars - out_chars,
            expected: EXPECTED_RESULT,
        })
    });
}

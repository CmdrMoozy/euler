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

// Using names.txt, a 46K text file containing over five-thousand first names,
// begin by sorting it into alphabetical order. Then working out the
// alphabetical value for each name, multiply this value by its alphabetical
// position in the list to obtain a name score.
//
// For example, when the list is sorted into alphabetical order, COLIN, which
// is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN
// would obtain a score of 938 x 53 = 49714.
//
// What is the total of all the name scores in the file?

#[macro_use]
extern crate error_chain;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const ASCII_UPPERCASE_A_BYTE: u8 = 65;
const NAMES_FILE: &'static str = include_str!("00022.txt");

const EXPECTED_RESULT: u64 = 871198282;

fn alphabetical_value(s: &str) -> Result<u64> {
    use std::ascii::AsciiExt;
    if !s.is_ascii() {
        bail!("Can't compute alphabetical value of non-ASCII string");
    }
    Ok(s.to_uppercase().bytes().fold(0 as u64,
                                     |sum, b| sum + ((b - ASCII_UPPERCASE_A_BYTE + 1) as u64)))
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut names: Vec<String> = try!(NAMES_FILE.split(',')
            .map(|name| match name.starts_with('"') && name.ends_with('"') {
                false => bail!("Corrupt problem input file"),
                true => Ok(String::from(&name[1..(name.len() - 1)])),
            })
            .collect::<Result<Vec<String>>>());
        names.sort();

        let result: Result<u64> = names.iter()
            .enumerate()
            .map(|name_pair| {
                alphabetical_value(name_pair.1.as_str()).map(|v| v * ((name_pair.0 + 1) as u64))
            })
            .fold(Ok(0 as u64), |acc, v| Ok(try!(acc) + try!(v)));

        Ok(ProblemAnswer {
            actual: try!(result),
            expected: EXPECTED_RESULT,
        })
    });
}

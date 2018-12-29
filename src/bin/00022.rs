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

use euler::util::error::*;
use euler::util::problem::*;
use failure::bail;

const ASCII_UPPERCASE_A_BYTE: u8 = 65;
const NAMES_FILE: &'static str = include_str!("00022.txt");

const EXPECTED_RESULT: u64 = 871198282;

fn alphabetical_value(s: &str) -> Result<u64> {
    if !s.is_ascii() {
        bail!("Can't compute alphabetical value of non-ASCII string");
    }
    Ok(s.to_uppercase().bytes().fold(0 as u64, |sum, b| {
        sum + ((b - ASCII_UPPERCASE_A_BYTE + 1) as u64)
    }))
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut names: Vec<String> = NAMES_FILE
            .split(',')
            .map(|name| match name.starts_with('"') && name.ends_with('"') {
                false => bail!("Corrupt problem input file"),
                true => Ok(String::from(&name[1..(name.len() - 1)])),
            })
            .collect::<Result<Vec<String>>>()?;
        names.sort();

        let result: Result<u64> = names
            .iter()
            .enumerate()
            .map(|name_pair| {
                alphabetical_value(name_pair.1.as_str()).map(|v| v * ((name_pair.0 + 1) as u64))
            })
            .fold(Ok(0 as u64), |acc, v| Ok(acc? + v?));

        Ok(ProblemAnswer {
            actual: result?,
            expected: EXPECTED_RESULT,
        })
    });
}

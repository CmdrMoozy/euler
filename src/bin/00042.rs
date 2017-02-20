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

// The nth term of the sequence of triangle numbers is given by, t(n) = 1/2 * n
// * (n + 1); so the first ten triangle numbers are:
//
//     1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
//
// By converting each letter in a word to a number corresponding to its
// alphabetical position and adding these values we form a word value. For
// example, the word value for SKY is 19 + 11 + 25 = 55 = t(10). If the word
// value is a triangle number then we shall call the word a triangle word.
//
// Using words.txt (right click and 'Save Link/Target As...'), a 16K text file
// containing nearly two-thousand common English words, how many are triangle
// words?

use std::collections::HashSet;

#[macro_use]
extern crate error_chain;

extern crate euler;
use self::euler::math::sequence;
use self::euler::util::error::*;
use self::euler::util::problem::*;

static WORDS_FILE: &'static str = include_str!("00042.txt");

const EXPECTED_RESULT: usize = 162;

fn get_word_score(word: &str) -> Result<u64> {
    if !word.chars().fold(true, |acc, c| acc && c.is_alphabetic()) {
        bail!("Encountered non-alphabetic character in word");
    }
    Ok(word.to_uppercase().bytes().map(|c| c - b'A' + 1).fold(0, |acc, v| acc + (v as u64)))
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        // Collect the score of each word in the file.
        let mut max_score: u64 = 0;
        let mut scores: Vec<u64> = vec![];
        for quoted_word in WORDS_FILE.split(',') {
            if !quoted_word.starts_with('"') || !quoted_word.ends_with('"') ||
               quoted_word.len() < 3 {
                bail!("Encountered invalid word in 00042.txt");
            }
            let score = try!(get_word_score(&quoted_word[1..quoted_word.len() - 1]));
            if score > max_score {
                max_score = score;
            }
            scores.push(score);
        }

        // Pregenerate a set of triangle numbers.
        let mut triangle_numbers: HashSet<u64> = HashSet::new();
        let mut n = 0;
        loop {
            let triangle_number = sequence::get_nth_triangle_number(n);
            if triangle_number > max_score {
                break;
            }
            triangle_numbers.insert(triangle_number);
            n += 1;
        }

        Ok(ProblemAnswer {
            actual: scores.iter().filter(|s| triangle_numbers.contains(s)).count(),
            expected: EXPECTED_RESULT,
        })
    });
}

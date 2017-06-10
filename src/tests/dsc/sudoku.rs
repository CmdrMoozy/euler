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

use dsc::sudoku::*;

const NO_NAME_INPUT: &'static str = include_str!("data/sudoku/no_name.txt");
const MISSING_NUMBER_INPUT: &'static str = include_str!("data/sudoku/missing_number.txt");
const MISSING_LINE_INPUT: &'static str = include_str!("data/sudoku/missing_line.txt");
const VALID_PUZZLES_INPUT: &'static str = include_str!("data/sudoku/valid_puzzles.txt");

const EXPECTED_VALID_PUZZLES: &'static [(&'static str, &'static [&'static [u8; 9]; 9])] =
    &[("Grid 01",
       &[&[0, 9, 0, 0, 7, 0, 0, 8, 0],
         &[0, 0, 0, 0, 0, 0, 0, 0, 0],
         &[3, 0, 1, 8, 0, 6, 2, 0, 5],
         &[0, 3, 8, 1, 0, 7, 6, 2, 0],
         &[2, 0, 0, 0, 0, 0, 0, 0, 1],
         &[0, 5, 6, 2, 0, 8, 9, 3, 0],
         &[6, 0, 4, 9, 0, 2, 5, 0, 3],
         &[0, 0, 0, 0, 0, 0, 0, 0, 0],
         &[0, 1, 0, 0, 8, 0, 0, 9, 0]]),
      ("Grid 02",
       &[&[2, 0, 0, 0, 0, 4, 3, 7, 0],
         &[0, 6, 3, 0, 0, 0, 0, 2, 0],
         &[0, 0, 0, 0, 0, 2, 1, 0, 4],
         &[0, 0, 5, 1, 0, 7, 0, 0, 0],
         &[8, 7, 0, 0, 0, 0, 0, 4, 1],
         &[0, 0, 0, 5, 0, 6, 7, 0, 0],
         &[3, 0, 2, 4, 0, 0, 0, 0, 0],
         &[0, 8, 0, 0, 0, 0, 4, 6, 0],
         &[0, 4, 9, 8, 0, 0, 0, 0, 3]])];

#[test]
fn test_no_name() {
    // Reading input data with no "name" row should result in an error.
    let puzzles = Puzzle::from_text(NO_NAME_INPUT);
    assert!(puzzles.is_err());
}

#[test]
fn test_missing_number() {
    // Reading input data with a missing number in one row should result in an
    // error.
    let puzzles = Puzzle::from_text(MISSING_NUMBER_INPUT);
    assert!(puzzles.is_err());
}

#[test]
fn test_missing_line() {
    // Reading input data with a missing number row should result in an error.
    let puzzles = Puzzle::from_text(MISSING_LINE_INPUT);
    assert!(puzzles.is_err());
}

#[test]
fn test_valid_puzzles() {
    // Reading valid puzzles should produce the expected result.
    let puzzles = Puzzle::from_text(VALID_PUZZLES_INPUT).unwrap();
    assert_eq!(EXPECTED_VALID_PUZZLES.len(), puzzles.len());
    for (idx, puzzle) in puzzles.iter().enumerate() {
        assert_eq!(EXPECTED_VALID_PUZZLES[idx].0, puzzle.get_name());
        assert_eq!(EXPECTED_VALID_PUZZLES[idx].1.len(), puzzle.get_size());
        for x in 0..EXPECTED_VALID_PUZZLES[idx].1.len() {
            for y in 0..EXPECTED_VALID_PUZZLES[idx].1[x].len() {
                assert_eq!(EXPECTED_VALID_PUZZLES[idx].1[x][y],
                           puzzle.get_value(x, y).unwrap_or(0));
            }
        }
    }
}

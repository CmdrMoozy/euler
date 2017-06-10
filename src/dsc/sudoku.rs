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

use util::error::*;

const PUZZLE_SIZE: usize = 9;
// Each puzzle should have one line per row of numbers, plus an extra line for
// the puzzle's name.
const LINES_PER_PUZZLE: usize = PUZZLE_SIZE + 1;

type PuzzleRow = [u8; PUZZLE_SIZE];
type PuzzleValues = [PuzzleRow; PUZZLE_SIZE];

fn parse_puzzle_row(line: &str) -> Result<PuzzleRow> {
    if line.len() != 9 {
        bail!("Each puzzle row must contain exactly nine digits");
    }

    let chars: Vec<char> = line.chars().collect();
    let mut row: PuzzleRow = [0; 9];
    for idx in 0..chars.len() {
        row[idx] = match chars[idx].to_digit(10) {
            Some(d) => d,
            None => bail!("Invalid puzzle value '{}'", chars[idx]),
        } as u8;
    }
    Ok(row)
}

fn parse_puzzle_values(text: &str) -> Result<Vec<(String, PuzzleValues)>> {
    let lines: Vec<&str> = text.lines().collect();
    if lines.len() % LINES_PER_PUZZLE != 0 {
        bail!("Expected exactly {} lines per puzzle, found {} lines",
              LINES_PER_PUZZLE,
              lines.len());
    }

    let mut puzzles: Vec<(String, PuzzleValues)> = vec![];
    for puzzle in 0..(lines.len() / LINES_PER_PUZZLE) {
        let puzzle_first_line: usize = puzzle * LINES_PER_PUZZLE;
        let puzzle_lines: &[&str] = &lines[puzzle_first_line..
                                     (puzzle_first_line + LINES_PER_PUZZLE)];

        let name: String = puzzle_lines[0].to_owned();
        let mut values: PuzzleValues = [[0; PUZZLE_SIZE]; PUZZLE_SIZE];
        for (y, line) in puzzle_lines.iter().skip(1).enumerate() {
            let row = parse_puzzle_row(line)?;
            for x in 0..PUZZLE_SIZE {
                values[x][y] = row[x];
            }
        }

        puzzles.push((name, values));
    }
    Ok(puzzles)
}

pub struct Puzzle {
    name: String,
    values: PuzzleValues,
}

impl Puzzle {
    fn new(name: String, values: PuzzleValues) -> Puzzle {
        Puzzle {
            name: name,
            values: values,
        }
    }

    pub fn from_text(text: &str) -> Result<Vec<Puzzle>> {
        let mut puzzles: Vec<Puzzle> = vec![];
        for (name, values) in parse_puzzle_values(text)?.into_iter() {
            puzzles.push(Puzzle::new(name, values));
        }
        Ok(puzzles)
    }

    pub fn get_name(&self) -> &str { self.name.as_str() }

    pub fn get_size(&self) -> usize { PUZZLE_SIZE }

    pub fn get_value(&self, x: usize, y: usize) -> Option<u8> {
        let value: u8 = self.values[x][y];
        if value != 0 { Some(value) } else { None }
    }
}

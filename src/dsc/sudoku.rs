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
const BOX_SIZE: usize = 3;
// Each puzzle should have one line per row of numbers, plus an extra line for
// the puzzle's name.
const LINES_PER_PUZZLE: usize = PUZZLE_SIZE + 1;

type PuzzleRow = [u8; PUZZLE_SIZE];
type PuzzleValues = [PuzzleRow; PUZZLE_SIZE];

#[derive(Clone, Copy)]
struct DigitState(u16);

impl DigitState {
    pub fn new() -> Self { Self::default() }

    pub fn is_closed(&self, digit: u8) -> Result<bool> {
        if digit < 1 || digit > 9 {
            bail!("Invalid digit '{}'", digit);
        }
        let mask: u16 = 1;
        let mask: u16 = mask << (digit - 1);
        Ok(self.0 & mask == 0)
    }

    pub fn set_closed(&mut self, digit: u8) -> Result<()> {
        if digit < 1 || digit > 9 {
            bail!("Invalid digit '{}'", digit);
        }
        let mask: u16 = 1;
        let mask: u16 = !(mask << (digit - 1));
        self.0 &= mask;
        Ok(())
    }

    pub fn get_open_digits(&self) -> Vec<u8> {
        (1_u8..10_u8).filter(|d| !self.is_closed(*d).unwrap()).collect()
    }

    /// Returns the single digit that is valid given this state. If zero or
    /// more than one digits are valid, None is returned instead.
    pub fn get_single_digit(&self) -> Option<u8> {
        let digits = self.get_open_digits();
        if digits.len() == 1 {
            Some(*digits.first().unwrap())
        } else {
            None
        }
    }
}

impl Default for DigitState {
    fn default() -> Self { DigitState(0xFFFF) }
}

struct PuzzleDigitStates([[DigitState; PUZZLE_SIZE]; PUZZLE_SIZE]);

impl PuzzleDigitStates {
    pub fn new(values: &PuzzleValues) -> Result<PuzzleDigitStates> {
        let mut states = PuzzleDigitStates([[DigitState::new(); PUZZLE_SIZE]; PUZZLE_SIZE]);
        for x in 0..PUZZLE_SIZE {
            for y in 0..PUZZLE_SIZE {
                let value = values[x][y];
                if value != 0 {
                    states.set_closed(x, y, values[x][y])?;
                }
            }
        }
        Ok(states)
    }

    pub fn set_closed(&mut self, x: usize, y: usize, digit: u8) -> Result<()> {
        // Mark this digit as closed for this cell's row and column...
        for i in 0..PUZZLE_SIZE {
            self.0[x][i].set_closed(digit)?;
            self.0[i][y].set_closed(digit)?;
        }

        // ... and for this cell's box.
        let box_x: usize = x / BOX_SIZE;
        let box_y: usize = y / BOX_SIZE;
        for i in (box_x * BOX_SIZE)..((box_x + 1) * BOX_SIZE) {
            for j in (box_y * BOX_SIZE)..((box_y + 1) * BOX_SIZE) {
                self.0[i][j].set_closed(digit)?;
            }
        }

        Ok(())
    }
}

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
    states: PuzzleDigitStates,
}

impl Puzzle {
    fn new(name: String, values: PuzzleValues) -> Result<Puzzle> {
        let states = PuzzleDigitStates::new(&values)?;
        Ok(Puzzle {
            name: name,
            values: values,
            states: states,
        })
    }

    pub fn from_text(text: &str) -> Result<Vec<Puzzle>> {
        let mut puzzles: Vec<Puzzle> = vec![];
        for (name, values) in parse_puzzle_values(text)?.into_iter() {
            puzzles.push(Puzzle::new(name, values)?);
        }
        Ok(puzzles)
    }

    /// Return the name associated with this puzzle.
    pub fn get_name(&self) -> &str { self.name.as_str() }

    /// Return the size (both the width and height) of this puzzle.
    pub fn get_size(&self) -> usize { PUZZLE_SIZE }

    /// Return the value in the given cell, or None if the given cell is empty.
    /// Cells in a puzzle are numbered according to a semi-standard x/y
    /// coordinate plane, where the origin is in the top left, while x and y
    /// increase while moving right or down, respectively.
    pub fn get_value(&self, x: usize, y: usize) -> Option<u8> {
        let value: u8 = self.values[x][y];
        if value != 0 { Some(value) } else { None }
    }

    /// Return the list of digits which are valid (accordingly to the row,
    /// column, and box constraints) to place in the given empty cell. If the
    /// cell is already filled in, an empty Vec is returned instead.
    pub fn get_open_digits(&self, x: usize, y: usize) -> Vec<u8> {
        self.states.0[x][y].get_open_digits()
    }

    /// Return the single digit which is valid to place in the given empty
    /// cell. If the cell is already filled in, or if more than one digit is
    /// possibly valid (purely by the row, column, and box constraints), then
    /// None is returned instead.
    pub fn get_single_digit(&self, x: usize, y: usize) -> Option<u8> {
        self.states.0[x][y].get_single_digit()
    }
}

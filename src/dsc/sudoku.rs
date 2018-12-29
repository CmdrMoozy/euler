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

use math::exact_cover::{Coordinate, ExactCover};
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
    pub fn new() -> Self {
        Self::default()
    }

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
        (1_u8..10_u8)
            .filter(|d| !self.is_closed(*d).unwrap())
            .collect()
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
    fn default() -> Self {
        DigitState(0xFFFF)
    }
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
        bail!(
            "Expected exactly {} lines per puzzle, found {} lines",
            LINES_PER_PUZZLE,
            lines.len()
        );
    }

    let mut puzzles: Vec<(String, PuzzleValues)> = vec![];
    for puzzle in 0..(lines.len() / LINES_PER_PUZZLE) {
        let puzzle_first_line: usize = puzzle * LINES_PER_PUZZLE;
        let puzzle_lines: &[&str] =
            &lines[puzzle_first_line..(puzzle_first_line + LINES_PER_PUZZLE)];

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

/// This function constructs a new ExactCover which can be used to represent
/// the given problem. This simply returns an ExactCover of the appropriate
/// size; it is up to the caller to then fill in the "1 nodes" in the returned
/// structure so it can be used to solve the problem.
fn construct_exact_cover(values: &PuzzleValues) -> ExactCover {
    let cols: usize = 324;
    let mut rows: usize = 0;

    for x in 0..PUZZLE_SIZE {
        for y in 0..PUZZLE_SIZE {
            if values[x][y] == 0 {
                rows += 9;
            } else {
                rows += 1;
            }
        }
    }

    ExactCover::new(cols, rows)
}

/// Returns the nth box, which contains the given cell in a puzzle. This
/// function doesn't do bounds checking, so the caller must be sure to pass
/// only valid coordinates.
fn box_of(x: usize, y: usize) -> usize {
    let i = y * PUZZLE_SIZE + x;
    #[cfg_attr(rustfmt, rustfmt_skip)]
    const LOOKUP_TABLE: &'static [usize] = &[
        0, 0, 0,   1, 1, 1,   2, 2, 2,
        0, 0, 0,   1, 1, 1,   2, 2, 2,
        0, 0, 0,   1, 1, 1,   2, 2, 2,

        3, 3, 3,   4, 4, 4,   5, 5, 5,
        3, 3, 3,   4, 4, 4,   5, 5, 5,
        3, 3, 3,   4, 4, 4,   5, 5, 5,

        6, 6, 6,   7, 7, 7,   8, 8, 8,
        6, 6, 6,   7, 7, 7,   8, 8, 8,
        6, 6, 6,   7, 7, 7,   8, 8, 8,
    ];
    LOOKUP_TABLE[i]
}

/// This function fills in "1 nodes" in the given ExactCover structure (which
/// is assumed to be of the right size), to represent the given sudoku puzzle
/// state.
///
/// A bit about how the problem is represented:
///
/// For cells which are filled in, we can express them in a single row. For
/// cells that are not filled in, we need to express them as nine different
/// rows (one for each possible value), to express that there are nine possible
/// solutions for that cell.
///
/// For each row, we have 324 columns. That's 4 * 81, or one set of 81 columns
/// per the cell, row, column, and box in the puzzle (respectively). So for
/// each cell in the puzzle, we put a "1 node" at:
///
/// 1. (i, row) where the cell is the ith = (y * PUZZLE_SIZE + x)th cell in the
/// puzzle, to indicate that the ith cell has a value in it.
/// 2. 81 + ((row * 9) + value - 1), to indicate that the rowth row has that
/// particular value in it.
/// 3. 162 + ((col * 9) + value - 1), to indicate that the colth column has
/// that particular value in it.
/// 4. 243 + ((box * 9) + value - 1), to indicate that the boxth box has that
/// particular value in it.
///
/// For cells which aren't filled in, we follow a similar process as the above,
/// but we do it *once per value, 1-9*.
fn populate_exact_cover(exact_cover: &mut ExactCover, values: &PuzzleValues) {
    let mut row: usize = 0;
    for y in 0..PUZZLE_SIZE {
        for x in 0..PUZZLE_SIZE {
            let i = (y * PUZZLE_SIZE) + x; // The cell at (x, y) is the ith cell.

            if values[x][y] == 0 {
                // This is a zero cell, so we need to setup 9 rows for it. For each possible
                // value, 1-9...
                for value in 1..10 {
                    exact_cover.set(i, row, true).unwrap();
                    exact_cover
                        .set(81 + (y * 9) + value - 1, row, true)
                        .unwrap();
                    exact_cover
                        .set(162 + (x * 9) + value - 1, row, true)
                        .unwrap();
                    exact_cover
                        .set(243 + (box_of(x, y) * 9) + value - 1, row, true)
                        .unwrap();
                    row += 1;
                }
            } else {
                // This is a filled-in cell, so we only need a single row for it.
                let value = values[x][y] as usize;
                exact_cover.set(i, row, true);
                exact_cover
                    .set(81 + (y * 9) + value - 1, row, true)
                    .unwrap();
                exact_cover
                    .set(162 + (x * 9) + value - 1, row, true)
                    .unwrap();
                exact_cover
                    .set(243 + (box_of(x, y) * 9) + value - 1, row, true)
                    .unwrap();
                row += 1;
            }
        }
    }
}

pub struct Puzzle {
    name: String,
    values: PuzzleValues,
    states: PuzzleDigitStates,
    solution: Option<PuzzleValues>,
}

impl Puzzle {
    fn new(name: String, values: PuzzleValues) -> Result<Puzzle> {
        let states = PuzzleDigitStates::new(&values)?;
        Ok(Puzzle {
            name: name,
            values: values,
            states: states,
            solution: None,
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
    pub fn get_name(&self) -> &str {
        self.name.as_str()
    }

    /// Return the size (both the width and height) of this puzzle.
    pub fn get_size(&self) -> usize {
        PUZZLE_SIZE
    }

    /// Return the value in the given cell, or None if the given cell is empty.
    /// Cells in a puzzle are numbered according to a semi-standard x/y
    /// coordinate plane, where the origin is in the top left, while x and y
    /// increase while moving right or down, respectively.
    pub fn get_value(&self, x: usize, y: usize) -> Option<u8> {
        let value: u8 = self.values[x][y];
        if value != 0 {
            Some(value)
        } else {
            None
        }
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

    /// This function returns the previously-computed full solution to this
    /// puzzle. It is possible that a valid puzzle will have multiple possible
    /// solutions: in this case, only the first solution that was found is
    /// returned. Note that this function will return None until solve() has
    /// been called.
    pub fn get_solution(&self) -> Option<&PuzzleValues> {
        self.solution.as_ref()
    }

    /// This function takes the input puzzle, and reduces the problem as much
    /// as is worthwhile using simple logic. This might result in a solution,
    /// but it also might only simplify the problem.
    ///
    /// NOTE: Currently, no extra problem reduction / simplification is
    /// implemented, because this structure is already "fast enough" relying
    /// solely on ExactCover. But, this is an easy place to add more
    /// optimization if it is needed in the future.
    fn reduce(&self) -> PuzzleValues {
        self.values.clone()
    }

    /// This function computes a full solution for the puzzle. This function
    /// must be called before get_solution() will return anything.
    pub fn solve(&mut self) {
        if self.solution.is_some() {
            return;
        }

        // Represent the puzzle as an exact cover problem, and get a solution for it.
        let values = self.reduce();
        let mut exact_cover = construct_exact_cover(&values);
        populate_exact_cover(&mut exact_cover, &values);
        exact_cover.solve(Some(1));
        // In the solution, we want to discard any node coordinates which are in a
        // column >= 81. These nodes are used to represent the one-value-per-{row,
        // column, box} constraints, but they are not useful to construct a solution
        // Puzzle.
        let solution: Option<Vec<Coordinate>> =
            exact_cover.get_solutions().get(0).map(|solution| {
                solution
                    .iter()
                    .filter(|coord| coord.col < 81)
                    .cloned()
                    .collect()
            });
        if solution.is_none() {
            return;
        }
        let mut solution = solution.unwrap();

        // Translate the exact cover solution to a set of puzzle values. The column of
        // the solution node is in the range of [0, 81), and it indicates that the node
        // represents the columnth value in the puzzle. So, this needs to be converted
        // to an (x, y) coordinate in the puzzle. The row of the solution node
        // indicates in some sense the selected solution value. Recall that when we
        // constructed the ExactCover, any filled-in cells in the puzzle produced 1
        // row, and any 0 cells produced 9 rows. The solution contains exactly one node
        // from each of these 1- or 9-row "groups". For filled-in cells we can just
        // copy the value, but for others the selected value is the offset from the
        // start of the 9-row group. So, we need to iterate over the solution nodes in
        // *column-order* (or, in puzzle cell order), and keep track of the start of
        // the row group.
        solution.sort_by_key(|coord| coord.col);
        let mut solution_values: PuzzleValues = [[0; PUZZLE_SIZE]; PUZZLE_SIZE];
        let mut from_row: usize = 0;
        for coord in solution {
            let x = coord.col % PUZZLE_SIZE;
            let y = coord.col / PUZZLE_SIZE;

            if values[x][y] != 0 {
                solution_values[x][y] = values[x][y];
                from_row += 1;
            } else {
                solution_values[x][y] = (coord.row + 1 - from_row) as u8;
                from_row += 9;
            }
        }
        self.solution = Some(solution_values);
    }
}

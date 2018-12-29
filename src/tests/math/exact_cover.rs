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

use crate::math::exact_cover::*;

#[test]
fn test_construction_properties() {
    const TEST_COLS: usize = 3;
    const TEST_ROWS: usize = 5;

    let ec = ExactCover::new(TEST_COLS, TEST_ROWS);
    assert_eq!(TEST_ROWS, ec.row_len());
    assert_eq!(TEST_COLS, ec.col_len());
    for x in 0..TEST_COLS {
        assert_eq!(Some(0), ec.col_count(x));

        for y in 0..TEST_ROWS {
            assert_eq!(Some(false), ec.get(x, y));
        }
    }
}

#[test]
fn test_empty_construction() {
    let ec = ExactCover::new(0, 0);
    assert_eq!(0, ec.row_len());
    assert_eq!(0, ec.col_len());
}

#[test]
fn test_set() {
    let mut ec = ExactCover::new(1, 1);

    assert_eq!(Some(false), ec.get(0, 0));
    assert_eq!(Some(0), ec.col_count(0));
    assert!(ec.set(0, 0, true).is_some());
    assert_eq!(Some(true), ec.get(0, 0));
    assert_eq!(Some(1), ec.col_count(0));

    assert!(ec.set(1, 1, true).is_none());
}

#[test]
fn test_solve() {
    // Taking a test vector from the Wikipedia page, we have a problem represented
    // like this:
    //
    //      1  2  3  4  5  6  7
    //
    // A    1  0  0  1  0  0  1
    // B    1  0  0  1  0  0  0
    // C    0  0  0  1  1  0  1
    // D    0  0  1  0  1  1  0
    // E    0  1  1  0  0  1  1
    // F    0  1  0  0  0  0  1
    //
    // Which has exactly one solution:
    //
    //      1  2  3  4  5  6  7
    //
    // B    1  0  0  1  0  0  0
    // D    0  0  1  0  1  1  0
    // F    0  1  0  0  0  0  1

    let mut ec = ExactCover::new(7, 6);

    ec.set(0, 0, true).unwrap();
    ec.set(3, 0, true).unwrap();
    ec.set(6, 0, true).unwrap();

    ec.set(0, 1, true).unwrap();
    ec.set(3, 1, true).unwrap();

    ec.set(3, 2, true).unwrap();
    ec.set(4, 2, true).unwrap();
    ec.set(6, 2, true).unwrap();

    ec.set(2, 3, true).unwrap();
    ec.set(4, 3, true).unwrap();
    ec.set(5, 3, true).unwrap();

    ec.set(1, 4, true).unwrap();
    ec.set(2, 4, true).unwrap();
    ec.set(5, 4, true).unwrap();
    ec.set(6, 4, true).unwrap();

    ec.set(1, 5, true).unwrap();
    ec.set(6, 5, true).unwrap();

    ec.solve(None);
    let mut solutions = ec.get_solutions().clone();
    assert_eq!(1, solutions.len());
    let mut solution = solutions.pop().unwrap();
    solution.sort();

    let expected_solution = vec![
        Coordinate { col: 0, row: 1 },
        Coordinate { col: 1, row: 5 },
        Coordinate { col: 2, row: 3 },
        Coordinate { col: 3, row: 1 },
        Coordinate { col: 4, row: 3 },
        Coordinate { col: 5, row: 3 },
        Coordinate { col: 6, row: 5 },
    ];
    assert_eq!(expected_solution, solution);
}

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

use math::exact_cover::*;

#[test]
fn test_construction_properties() {
    const TEST_COLS: usize = 3;
    const TEST_ROWS: usize = 5;

    let ec = ExactCover::new(TEST_COLS, TEST_ROWS);
    assert_eq!(TEST_ROWS, ec.row_len());
    assert_eq!(TEST_COLS, ec.col_len());
    for x in 0..TEST_COLS {
        assert_eq!(Some(0), ec.get_col_name(x));
        assert_eq!(Some(TEST_ROWS), ec.col_count(x));

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
    assert!(ec.set(0, 0, true).is_some());
    assert_eq!(Some(true), ec.get(0, 0));

    assert!(ec.set(1, 1, true).is_none());
}

#[test]
fn test_set_col_name() {
    let mut ec = ExactCover::new(1, 1);

    assert_eq!(Some(0), ec.get_col_name(0));
    assert!(ec.set_col_name(0, 123).is_some());
    assert_eq!(Some(123), ec.get_col_name(0));

    assert!(ec.set_col_name(1, 123).is_none());
}

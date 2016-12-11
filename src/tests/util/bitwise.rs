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

use ::util::bitwise::*;

#[test]
fn test_nlz() {
    static TEST_CASES: &'static [(u64, u64)] =
        &[(0, 64), (1, 63), (4294967296, 31), (18446744073709551615, 0)];

    for test_case in TEST_CASES {
        assert!(nlz(test_case.0) == test_case.1,
                "nlz({}) == {}",
                test_case.0,
                test_case.1);
    }
}

#[test]
fn test_lg() {
    static TEST_CASES: &'static [(u64, u64)] =
        &[(1, 0), (2, 1), (3, 1), (4, 2), (5, 2), (1275837, 20)];

    for test_case in TEST_CASES {
        assert!(lg(test_case.0) == test_case.1,
                "lg({}) == {}",
                test_case.0,
                test_case.1);
    }
}

#[test]
fn test_rmo_off() {
    static TEST_CASES: &'static [(u64, u64)] = &[(0, 0), (1, 0), (2, 0), (3, 2), (32768, 0),
                                                 (7, 6), (6, 4)];

    for test_case in TEST_CASES {
        assert!(rmo_off(test_case.0) == test_case.1,
                "rmo_off({}) == {}",
                test_case.0,
                test_case.1);
    }
}

#[test]
fn test_is_pow_two() {
    static TEST_CASES: &'static [(u64, bool)] = &[(1, true),
                                                  (2, true),
                                                  (4, true),
                                                  (32, true),
                                                  (8192, true),
                                                  (32768, true),
                                                  (131072, true),
                                                  (31, false),
                                                  (0, false),
                                                  (27834, false),
                                                  (2892, false),
                                                  (3226880, false),
                                                  (1234, false),
                                                  (1023, false)];

    for test_case in TEST_CASES {
        assert!(is_pow_two(test_case.0) == test_case.1,
                "is_pow_two({}) == {}",
                test_case.0,
                test_case.1);
    }
}

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

use ::math::division::*;

#[test]
fn test_signed_divide() {
    static TEST_CASES: &'static [(i64, i64, i64, i64)] = &[(0, 100, 0, 0),
                                                           (0, -100, 0, 0),
                                                           (100, 1, 100, 0),
                                                           (-100, 1, -100, 0),
                                                           (100, 3, 33, 1),
                                                           (100, -3, -33, 1),
                                                           (-100, 3, -33, -1),
                                                           (-100, -3, 33, -1)];

    for test_case in TEST_CASES {
        let (quotient, remainder) = divide(test_case.0, test_case.1);
        assert!(quotient == test_case.2,
                "{} div {} = {} == {}",
                test_case.0,
                test_case.1,
                quotient,
                test_case.2);
        assert!(remainder == test_case.3,
                "{} rem {} = {} == {}",
                test_case.0,
                test_case.1,
                remainder,
                test_case.3);
    }
}

#[test]
fn test_unsigned_divide() {
    static TEST_CASES: &'static [(u64, u64, u64, u64)] =
        &[(0, 100, 0, 0), (100, 1, 100, 0), (100, 3, 33, 1)];

    for test_case in TEST_CASES {
        let (quotient, remainder) = divide(test_case.0, test_case.1);
        assert!(quotient == test_case.2,
                "{} div {} = {} == {}",
                test_case.0,
                test_case.1,
                quotient,
                test_case.2);
        assert!(remainder == test_case.3,
                "{} rem {} = {} == {}",
                test_case.0,
                test_case.1,
                remainder,
                test_case.3);
    }
}

#[test]
fn test_aliquot_number_divisors() {
    // Note that d(0) is undefined, so these cases are 1-indexed essentially.
    static DIVISORS_OF_N: &'static [u64] =
        &[1, 2, 2, 3, 2, 4, 2, 4, 3, 4, 2, 6, 2, 4, 4, 5, 2, 6, 2, 6, 4, 4, 2, 8, 3, 4, 4, 6, 2,
          8, 2, 6, 4, 4, 4, 9, 2, 4, 4, 8, 2, 8, 2, 6, 6, 4, 2, 10, 3, 6, 4, 6, 2, 8, 4, 8, 4, 4,
          2, 12, 2, 4, 6, 7, 4, 8, 2, 6, 4, 8, 2, 12, 2, 4, 6, 6, 4, 8, 2, 10, 5, 4, 2, 12, 4, 4,
          4, 8, 2, 12, 4, 6, 4, 4, 4, 12, 2, 6, 6, 9, 2, 8, 2, 8];

    for test_case in DIVISORS_OF_N.iter().enumerate() {
        assert!(aliquot_number_divisors(test_case.0 as u64 + 1) == *test_case.1);
    }
}

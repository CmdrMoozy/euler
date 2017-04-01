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

use ::algorithm::*;

#[test]
fn test_is_permutation_of() {
    static TEST_CASES: &'static [(u64, u64, bool)] =
        &[(123, 321, true), (0, 0, true), (100, 1, false)];

    for test_case in TEST_CASES {
        assert!(is_permutation_of(&test_case.0, &test_case.1) == test_case.2);
        assert!(integer_is_permutation_of(test_case.0, test_case.1).unwrap() == test_case.2);
    }
}

#[test]
fn test_lower_bound() {
    static TEST_CASES: &'static [(&[u64], u64, usize)] =
        &[(&[], 123, 0), (&[1, 2, 3], 4, 3), (&[1, 2, 3], 0, 0), (&[1, 2, 2, 3], 2, 1)];

    for test_case in TEST_CASES {
        assert_eq!(test_case.2,
                   lower_bound(&Vec::from(test_case.0), &test_case.1));
    }
}

#[test]
fn test_upper_bound() {
    static TEST_CASES: &'static [(&[u64], u64, usize)] = &[(&[], 123, 0),
                                                           (&[1, 2, 3], 0, 0),
                                                           (&[1, 2, 3], 1, 1),
                                                           (&[1, 2, 2, 3], 1, 1),
                                                           (&[1, 2, 2, 3], 2, 3)];

    for test_case in TEST_CASES {
        assert_eq!(test_case.2,
                   upper_bound(&Vec::from(test_case.0), &test_case.1));
    }
}

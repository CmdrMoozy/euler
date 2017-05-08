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

use algorithm::sequence::*;

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
    static TEST_CASES: &'static [(&'static [u64], u64, usize)] =
        &[(&[], 123, 0), (&[1, 2, 3], 4, 3), (&[1, 2, 3], 0, 0), (&[1, 2, 2, 3], 2, 1)];

    for test_case in TEST_CASES {
        assert_eq!(test_case.2,
                   lower_bound(&Vec::from(test_case.0), &test_case.1));
    }
}

#[test]
fn test_upper_bound() {
    static TEST_CASES: &'static [(&'static [u64], u64, usize)] = &[(&[], 123, 0),
                                                                   (&[1, 2, 3], 0, 0),
                                                                   (&[1, 2, 3], 1, 1),
                                                                   (&[1, 2, 2, 3], 1, 1),
                                                                   (&[1, 2, 2, 3], 2, 3)];

    for test_case in TEST_CASES {
        assert_eq!(test_case.2,
                   upper_bound(&Vec::from(test_case.0), &test_case.1));
    }
}

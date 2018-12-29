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

use crate::util::bitwise::*;

#[test]
fn test_nlz() {
    static TEST_CASES: &'static [(u64, u64)] = &[
        (0, 64),
        (1, 63),
        (4294967296, 31),
        (18446744073709551615, 0),
    ];

    for test_case in TEST_CASES {
        assert!(
            nlz(test_case.0) == test_case.1,
            "nlz({}) == {}",
            test_case.0,
            test_case.1
        );
    }
}

#[test]
fn test_lg() {
    static TEST_CASES: &'static [(u64, u64)] =
        &[(1, 0), (2, 1), (3, 1), (4, 2), (5, 2), (1275837, 20)];

    for test_case in TEST_CASES {
        assert!(
            lg(test_case.0) == test_case.1,
            "lg({}) == {}",
            test_case.0,
            test_case.1
        );
    }
}

#[test]
fn test_reverse_bits() {
    assert_eq!(0x000000000000ffff, reverse_all_bits(0xffff000000000000));
    assert_eq!(0xffff000000000000, reverse_all_bits(0x000000000000ffff));
    assert_eq!(0x8d05ec5f8d05ec5f, reverse_all_bits(0xfa37a0b1fa37a0b1));

    assert_eq!(0x000000000000ffff, reverse_bits(0x000000000000ffff));
    assert_eq!(0x0000000000000055, reverse_bits(0x00000000000000aa));
    assert_eq!(
        reverse_all_bits(0xfa37a0b1fa37a0b1),
        reverse_bits(0xfa37a0b1fa37a0b1)
    );
}

#[test]
fn test_is_bitwise_palindromic() {
    assert!(is_bitwise_palindromic(0x909909909909));
    assert!(!is_bitwise_palindromic(0xa0aa0aa0aa0a));
}

#[test]
fn test_rmo_off() {
    static TEST_CASES: &'static [(u64, u64)] =
        &[(0, 0), (1, 0), (2, 0), (3, 2), (32768, 0), (7, 6), (6, 4)];

    for test_case in TEST_CASES {
        assert!(
            rmo_off(test_case.0) == test_case.1,
            "rmo_off({}) == {}",
            test_case.0,
            test_case.1
        );
    }
}

#[test]
fn test_is_pow_two() {
    static TEST_CASES: &'static [(u64, bool)] = &[
        (1, true),
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
        (1023, false),
    ];

    for test_case in TEST_CASES {
        assert!(
            is_pow_two(test_case.0) == test_case.1,
            "is_pow_two({}) == {}",
            test_case.0,
            test_case.1
        );
    }
}

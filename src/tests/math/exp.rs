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

use math::exp::*;

#[test]
fn test_checked_ipow() {
    for b in 1..16 {
        for e in 1..16 {
            assert_eq!(checked_ipow(b, e).unwrap(), b.pow(e as u32));
        }
    }

    assert!(checked_ipow(17, 17).is_none());
}

#[test]
fn test_ipowmod() {
    const MODULUS: u64 = 5;
    for b in 1_u64..6_u64 {
        for e in 1_u64..6_u64 {
            assert_eq!(b.pow(e as u32) % MODULUS, ipowmod(b, e, MODULUS));
        }
    }
}

#[test]
fn test_log10() {
    static TEST_CASES: &'static [(u64, u64)] = &[
        (0, 0),
        (9, 0),
        (10, 1),
        (11, 1),
        (99, 1),
        (100, 2),
        (101, 2),
        (999, 2),
        (1000, 3),
        (1001, 3),
        (9999, 3),
        (10000, 4),
        (10001, 4),
    ];

    for test_case in TEST_CASES {
        assert_eq!(test_case.1, log10(test_case.0));
    }
}

#[test]
fn test_isqrt() {
    #[cfg_attr(rustfmt, rustfmt_skip)]
    static TEST_CASES: &'static [(u64, u64)] = &[
        (0, 0), (1, 1), (2, 1), (3, 1), (4, 2), (5, 2), (8, 2), (9, 3), (10, 3),
        (15, 3), (16, 4), (17, 4), (24, 4), (25, 5), (26, 5), (35, 5), (36, 6),
        (37, 6), (48, 6), (49, 7), (50, 7), (63, 7), (64, 8), (65, 8), (80, 8),
        (81, 9), (82, 9), (99, 9), (100, 10), (101, 10), (2115, 45), (2116, 46),
        (2117, 46), (2208, 46), (2209, 47), (2210, 47), (2303, 47), (2304, 48),
        (2305, 48), (2400, 48), (2401, 49), (2402, 49), (2499, 49), (2500, 50),
        (2501, 50), (600851475143, 775146)];

    for test_case in TEST_CASES {
        assert!(
            isqrt(test_case.0) == test_case.1,
            "isqrt({}) == {}",
            test_case.0,
            test_case.1
        );
    }
}

#[test]
fn test_is_square() {
    #[cfg_attr(rustfmt, rustfmt_skip)]
    static SQUARES: &'static [u64] =
        &[4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289, 324, 361, 400,
          441, 484, 529, 576, 625, 676, 729, 784, 841, 900, 961, 1024, 1089, 1156, 1225, 1296,
          1369, 1444, 1521, 1600, 1681, 1764, 1849, 1936, 2025, 2116, 2209, 2304, 2401, 2500];

    assert!(is_square(0));
    assert!(is_square(1));
    assert!(!is_square(2));
    for s in SQUARES {
        assert!(!is_square(s - 1));
        assert!(is_square(*s));
        assert!(!is_square(s + 1));
    }
}

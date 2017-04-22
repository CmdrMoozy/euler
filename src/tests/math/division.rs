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

use ::math::division::*;
use math::prime::PrimeSieve;

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
fn test_gcd() {
    static TEST_CASES: &'static [(u64, u64, u64)] = &[(900, 736, 4),
                                                      (951, 474, 3),
                                                      (377, 540, 1),
                                                      (210, 818, 2),
                                                      (832, 17, 1),
                                                      (986, 799, 17),
                                                      (855, 469, 1),
                                                      (990, 604, 2),
                                                      (138, 827, 1),
                                                      (424, 203, 1),
                                                      (522, 813, 3),
                                                      (251, 26, 1),
                                                      (329, 191, 1),
                                                      (965, 435, 5),
                                                      (759, 400, 1),
                                                      (53, 549, 1),
                                                      (218, 678, 2),
                                                      (453, 767, 1),
                                                      (396, 594, 198),
                                                      (821, 615, 1),
                                                      (104, 410, 2),
                                                      (725, 153, 1),
                                                      (744, 764, 4),
                                                      (765, 436, 1),
                                                      (666, 86, 2)];

    for test_case in TEST_CASES {
        assert_eq!(test_case.2, gcd(test_case.0, test_case.1));
    }
}

#[test]
fn test_lcm() {
    static TEST_CASES: &'static [(u64, u64, u64)] = &[(900, 736, 165600),
                                                      (951, 474, 150258),
                                                      (377, 540, 203580),
                                                      (210, 818, 85890),
                                                      (832, 17, 14144),
                                                      (986, 799, 46342),
                                                      (855, 469, 400995),
                                                      (990, 604, 298980),
                                                      (138, 827, 114126),
                                                      (424, 203, 86072),
                                                      (522, 813, 141462),
                                                      (251, 26, 6526),
                                                      (329, 191, 62839),
                                                      (965, 435, 83955),
                                                      (759, 400, 303600),
                                                      (53, 549, 29097),
                                                      (218, 678, 73902),
                                                      (453, 767, 347451),
                                                      (396, 594, 1188),
                                                      (821, 615, 504915),
                                                      (104, 410, 21320),
                                                      (725, 153, 110925),
                                                      (744, 764, 142104),
                                                      (765, 436, 333540),
                                                      (666, 86, 28638)];

    for test_case in TEST_CASES {
        assert_eq!(test_case.2, lcm(test_case.0, test_case.1));
    }
}

#[test]
fn test_totient() {
    static TEST_CASES: &'static [(u64, u64)] =
        &[(1, 1), (2, 1), (3, 2), (4, 2), (5, 4), (6, 2), (7, 6), (8, 4), (9, 6), (10, 4),
          (11, 10), (12, 4), (13, 12), (14, 6), (15, 8), (16, 8), (17, 16), (18, 6), (19, 18),
          (20, 8), (21, 12), (22, 10), (23, 22), (24, 8), (25, 20), (26, 12), (27, 18), (28, 12),
          (29, 28), (30, 8), (31, 30), (32, 16), (33, 20), (34, 16), (35, 24), (36, 12), (37, 36),
          (38, 18), (39, 24), (40, 16), (41, 40), (42, 12), (43, 42), (44, 20), (45, 24),
          (46, 22), (47, 46), (48, 16), (49, 42), (50, 20), (51, 32), (52, 24), (53, 52),
          (54, 18), (55, 40), (56, 24), (57, 36), (58, 28), (59, 58), (60, 16), (61, 60),
          (62, 30), (63, 36), (64, 32), (65, 48), (66, 20), (67, 66), (68, 32), (69, 44),
          (70, 24), (71, 70), (72, 24), (73, 72), (74, 36), (75, 40), (76, 36), (77, 60),
          (78, 24), (79, 78), (80, 32), (81, 54), (82, 40), (83, 82), (84, 24), (85, 64),
          (86, 42), (87, 56), (88, 40), (89, 88), (90, 24), (91, 72), (92, 44), (93, 60),
          (94, 46), (95, 72), (96, 32), (97, 96), (98, 42), (99, 60)];

    for test_case in TEST_CASES {
        assert_eq!(test_case.1, totient(test_case.0));
    }
}

#[test]
fn test_repetend_length() {
    static TEST_CASES: &'static [(u64, u64)] = &[(2, 0), (3, 1), (4, 0), (5, 0), (6, 1), (7, 6),
                                                 (8, 0), (9, 1), (10, 0)];

    let sieve = PrimeSieve::new(100);
    for test_case in TEST_CASES {
        assert_eq!(test_case.1,
                   repetend_length(test_case.0, &sieve, None).unwrap());
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

#[test]
fn test_aliquot_sum_proper_divisors() {
    static TEST_CASES: &'static [(u64, u64)] =
        &[(1, 0), (2, 1), (3, 1), (4, 3), (5, 1), (6, 6), (7, 1), (8, 7), (9, 4), (10, 8),
          (11, 1), (12, 16), (13, 1), (14, 10), (15, 9), (16, 15), (17, 1), (18, 21), (19, 1),
          (20, 22), (21, 11), (22, 14), (23, 1), (24, 36), (25, 6), (26, 16), (27, 13), (28, 28),
          (29, 1), (30, 42), (31, 1), (32, 31), (33, 15), (34, 20), (35, 13), (36, 55), (37, 1),
          (38, 22), (39, 17), (40, 50), (41, 1), (42, 54), (43, 1), (44, 40), (45, 33), (46, 26),
          (47, 1), (48, 76), (49, 8), (50, 43), (51, 21), (52, 46), (53, 1), (54, 66), (55, 17),
          (56, 64), (57, 23), (58, 32), (59, 1), (60, 108), (61, 1), (62, 34), (63, 41), (64, 63),
          (65, 19), (66, 78), (67, 1), (68, 58), (69, 27), (70, 74), (71, 1), (72, 123), (73, 1),
          (74, 40), (75, 49), (76, 64), (77, 19), (78, 90), (79, 1), (80, 106)];

    for test_case in TEST_CASES {
        assert_eq!(test_case.1, aliquot_sum_proper_divisors(test_case.0));
        assert_eq!(test_case.0 + test_case.1, aliquot_sum_divisors(test_case.0));
    }
}

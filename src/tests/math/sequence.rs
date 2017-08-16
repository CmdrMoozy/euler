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

use gmp::mpz::Mpz;
use math::sequence::*;
use util::convert::*;

#[test]
fn test_get_nth_fibonacci_number() {
    #[cfg_attr(rustfmt, rustfmt_skip)]
    static SEQUENCE: &'static [u64] =
        &[0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181,
          6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040,
          1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169];
    for test_case in SEQUENCE.iter().enumerate() {
        assert!(
            mpz_to_u64(&get_nth_fibonacci_number(test_case.0 as u64)).unwrap() == *test_case.1,
            "fib({}) == {}",
            test_case.0,
            test_case.1
        );
    }
}

#[test]
fn test_get_nth_triangle_number() {
    #[cfg_attr(rustfmt, rustfmt_skip)]
    static SEQUENCE: &'static [u64] =
        &[0, 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78, 91, 105, 120, 136, 153, 171, 190, 210,
          231, 253, 276, 300, 325, 351, 378, 406, 435, 465, 496, 528, 561, 595, 630, 666, 703,
          741, 780, 820, 861, 903, 946, 990, 1035, 1081, 1128, 1176, 1225, 1275, 1326, 1378, 1431];
    for test_case in SEQUENCE.iter().enumerate() {
        assert!(
            get_nth_triangle_number(test_case.0 as u64) == *test_case.1,
            "triangle_number({}) == {}",
            test_case.0,
            test_case.1
        );
    }
}

#[test]
fn test_get_nth_pentagonal_number() {
    #[cfg_attr(rustfmt, rustfmt_skip)]
    static SEQUENCE: &'static [u64] =
        &[0, 1, 5, 12, 22, 35, 51, 70, 92, 117, 145, 176, 210, 247, 287, 330, 376, 425, 477, 532,
          590, 651, 715, 782, 852, 925, 1001, 1080, 1162, 1247, 1335, 1426, 1520, 1617, 1717,
          1820, 1926, 2035, 2147, 2262, 2380, 2501, 2625, 2752, 2882, 3015, 3151];
    for test_case in SEQUENCE.iter().enumerate() {
        assert!(
            get_nth_pentagonal_number(test_case.0 as u64) == *test_case.1,
            "pentagonal_number({}) = {}",
            test_case.0,
            test_case.1
        );
    }
}

#[test]
fn test_get_nth_hexagonal_number() {
    #[cfg_attr(rustfmt, rustfmt_skip)]
    static SEQUENCE: &'static [u64] =
        &[0, 1, 6, 15, 28, 45, 66, 91, 120, 153, 190, 231, 276, 325, 378, 435, 496, 561, 630, 703,
          780, 861, 946, 1035, 1128, 1225, 1326, 1431, 1540, 1653, 1770, 1891, 2016, 2145, 2278,
          2415, 2556, 2701, 2850, 3003, 3160, 3321, 3486, 3655, 3828, 4005, 4186, 4371, 4560];
    for test_case in SEQUENCE.iter().enumerate() {
        assert!(
            get_nth_hexagonal_number(test_case.0 as u64) == *test_case.1,
            "hexagonal_number({}) == {}",
            test_case.0,
            test_case.1
        );
    }
}

#[test]
fn test_sequence_search() {
    static TEST_CASES: &'static [(u64, u64, u64)] =
        &[(6764, 20, 6765), (6765, 20, 6765), (6766, 21, 10946)];
    for test_case in TEST_CASES {
        let (index, value) = sequence_search(0, Mpz::from(test_case.0), get_nth_fibonacci_number);
        assert!(index == test_case.1);
        assert!(mpz_to_u64(&value).unwrap() == test_case.2);
    }
}

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

use ::math::sequence::*;

#[test]
fn test_get_nth_fibonacci_number() {
    static SEQUENCE: &'static [u64] =
        &[0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181,
          6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040,
          1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169];
    for test_case in SEQUENCE.iter().enumerate() {
        assert!(get_nth_fibonacci_number(test_case.0 as u64) == *test_case.1,
                "fib({}) == {}",
                test_case.0,
                test_case.1);
    }
}

#[test]
fn test_get_nth_triangle_number() {
    static SEQUENCE: &'static [u64] =
        &[0, 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78, 91, 105, 120, 136, 153, 171, 190, 210,
          231, 253, 276, 300, 325, 351, 378, 406, 435, 465, 496, 528, 561, 595, 630, 666, 703,
          741, 780, 820, 861, 903, 946, 990, 1035, 1081, 1128, 1176, 1225, 1275, 1326, 1378, 1431];
    for test_case in SEQUENCE.iter().enumerate() {
        assert!(get_nth_triangle_number(test_case.0 as u64) == *test_case.1,
                "triangle_number({}) == {}",
                test_case.0,
                test_case.1);
    }
}

#[test]
fn test_sequence_search() {
    static TEST_CASES: &'static [(u64, u64, u64)] =
        &[(6764, 20, 6765), (6765, 20, 6765), (6766, 21, 10946)];
    for test_case in TEST_CASES {
        let (index, value) = sequence_search(0, test_case.0, get_nth_fibonacci_number);
        assert!(index == test_case.1);
        assert!(value == test_case.2);
    }
}

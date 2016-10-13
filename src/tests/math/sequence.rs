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

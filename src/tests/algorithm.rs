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
    }
}

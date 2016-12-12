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

use ::math::combinatorics::*;

#[test]
fn test_combinations() {
    // Test that the precondition stating that n >= r is enforced.
    assert!(combinations(10, 11).is_err());

    static TEST_CASES: &'static [(u64, u64, u64)] = &[(10, 8, 45),
                                                      (9, 3, 84),
                                                      (4, 1, 4),
                                                      (1, 1, 1),
                                                      (6, 1, 6),
                                                      (10, 6, 210),
                                                      (9, 5, 126),
                                                      (7, 2, 21),
                                                      (9, 7, 36),
                                                      (4, 3, 4),
                                                      (40, 20, 137846528820)];

    for test_case in TEST_CASES {
        assert!(combinations(test_case.0, test_case.1).ok().unwrap() == test_case.2,
                "combinations({}, {}) == {}",
                test_case.0,
                test_case.1,
                test_case.2);
    }
}

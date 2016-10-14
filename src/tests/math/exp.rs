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

use ::math::exp::*;

#[test]
fn test_isqrt() {
    static TEST_CASES: &'static [(u64, u64)] = &[(0, 0),
                                                 (1, 1),
                                                 (2, 1),
                                                 (3, 1),
                                                 (4, 2),
                                                 (5, 2),
                                                 (8, 2),
                                                 (9, 3),
                                                 (10, 3),
                                                 (15, 3),
                                                 (16, 4),
                                                 (17, 4),
                                                 (24, 4),
                                                 (25, 5),
                                                 (26, 5),
                                                 (35, 5),
                                                 (36, 6),
                                                 (37, 6),
                                                 (48, 6),
                                                 (49, 7),
                                                 (50, 7),
                                                 (63, 7),
                                                 (64, 8),
                                                 (65, 8),
                                                 (80, 8),
                                                 (81, 9),
                                                 (82, 9),
                                                 (99, 9),
                                                 (100, 10),
                                                 (101, 10),
                                                 (2115, 45),
                                                 (2116, 46),
                                                 (2117, 46),
                                                 (2208, 46),
                                                 (2209, 47),
                                                 (2210, 47),
                                                 (2303, 47),
                                                 (2304, 48),
                                                 (2305, 48),
                                                 (2400, 48),
                                                 (2401, 49),
                                                 (2402, 49),
                                                 (2499, 49),
                                                 (2500, 50),
                                                 (2501, 50),
                                                 (600851475143, 775146)];

    for test_case in TEST_CASES {
        assert!(isqrt(test_case.0) == test_case.1,
                "isqrt({}) == {}",
                test_case.0,
                test_case.1);
    }
}

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

use ::math::stats::*;

#[test]
fn test_iaverage() {
    static TEST_CASES: &'static [(&'static [u64], u64)] = &[(&[292120540, 3243950, 2749270],
                                                             99371253)];

    for test_case in TEST_CASES {
        assert_eq!(test_case.1, iaverage(test_case.0.iter().cloned()).unwrap());
    }
}

#[test]
fn test_istddev_population() {
    static TEST_CASES: &'static [(&'static [u64], u64)] = &[(&[272601155, 1327834, 1063480],
                                                             127941824)];

    for test_case in TEST_CASES {
        assert_eq!(test_case.1,
                   istddev_population(test_case.0.iter().cloned()).unwrap());
    }
}

#[test]
fn test_istddev_sample() {
    static TEST_CASES: &'static [(&'static [u64], u64)] = &[(&[272601155, 1327834, 1063480],
                                                             156696093)];

    for test_case in TEST_CASES {
        assert_eq!(test_case.1,
                   istddev_sample(test_case.0.iter().cloned()).unwrap());
    }
}

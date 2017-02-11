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

use std::cmp::Ordering;
use structs::fraction::Fraction;

#[test]
fn test_construction_invariant() {
    assert!(Fraction::new(0, 5).is_ok());
    assert!(Fraction::new(5, 0).is_err());

    static TEST_CASES: &'static [(u64, u64)] = &[(1, 2), (0, 5), (20, 10)];

    for test_case in TEST_CASES {
        let f = Fraction::new(test_case.0, test_case.1).unwrap();
        assert_eq!(test_case.0, f.numerator());
        assert_eq!(test_case.1, f.denominator());
    }
}

#[test]
fn test_reduction() {
    static TEST_CASES: &'static [(u64, u64, u64, u64)] =
        &[(0, 10, 0, 1), (123, 123, 1, 1), (4, 8, 1, 2)];

    for test_case in TEST_CASES {
        let original = Fraction::new(test_case.0, test_case.1).unwrap();
        let (reduced, was_reduced) = original.reduce();
        let expected = Fraction::new(test_case.2, test_case.3).unwrap();

        // Test that the "was reduced" function return value is what we expect (it
        // should be true if the numerator or denominator changed).
        assert_eq!(test_case.0 != test_case.2 || test_case.1 != test_case.3,
                   was_reduced);
        // Test that the original, reduced, and expected fractions are all equivalent
        // (but not necessarily identical).
        assert_eq!(expected, reduced);
        assert_eq!(original, reduced);
        // Test that the reduced output is *identical* to the expected reduced form.
        assert!(expected.is_identical(&reduced));
    }
}

#[test]
fn test_ordering() {
    static TEST_CASES: &'static [(u64, u64, u64, u64, Ordering)] =
        &[(0, 10, 0, 1, Ordering::Equal),
          (123, 123, 1, 1, Ordering::Equal),
          (4, 8, 1, 2, Ordering::Equal),
          (4, 8, 2, 10, Ordering::Greater),
          (10, 100, 1, 5, Ordering::Less)];

    for test_case in TEST_CASES {
        let a = Fraction::new(test_case.0, test_case.1).unwrap();
        let b = Fraction::new(test_case.2, test_case.3).unwrap();
        assert_eq!(a.cmp(&b), a.partial_cmp(&b).unwrap());
        assert_eq!(test_case.4, a.cmp(&b));
    }
}

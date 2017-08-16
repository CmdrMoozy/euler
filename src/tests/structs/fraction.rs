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
        assert_eq!(
            test_case.0 != test_case.2 || test_case.1 != test_case.3,
            was_reduced
        );
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
    static TEST_CASES: &'static [(u64, u64, u64, u64, Ordering)] = &[
        (0, 10, 0, 1, Ordering::Equal),
        (123, 123, 1, 1, Ordering::Equal),
        (4, 8, 1, 2, Ordering::Equal),
        (4, 8, 2, 10, Ordering::Greater),
        (10, 100, 1, 5, Ordering::Less),
    ];

    for test_case in TEST_CASES {
        let a = Fraction::new(test_case.0, test_case.1).unwrap();
        let b = Fraction::new(test_case.2, test_case.3).unwrap();
        assert_eq!(a.cmp(&b), a.partial_cmp(&b).unwrap());
        assert_eq!(test_case.4, a.cmp(&b));
    }
}

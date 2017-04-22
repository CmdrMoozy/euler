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

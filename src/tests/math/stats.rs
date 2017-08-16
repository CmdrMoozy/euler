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

use math::stats::*;

#[test]
fn test_iaverage() {
    static TEST_CASES: &'static [(&'static [u64], u64)] =
        &[(&[292120540, 3243950, 2749270], 99371253)];

    for test_case in TEST_CASES {
        assert_eq!(test_case.1, iaverage(test_case.0.iter().cloned()).unwrap());
    }
}

#[test]
fn test_istddev_population() {
    static TEST_CASES: &'static [(&'static [u64], u64)] =
        &[(&[272601155, 1327834, 1063480], 127941824)];

    for test_case in TEST_CASES {
        assert_eq!(
            test_case.1,
            istddev_population(test_case.0.iter().cloned()).unwrap()
        );
    }
}

#[test]
fn test_istddev_sample() {
    static TEST_CASES: &'static [(&'static [u64], u64)] =
        &[(&[272601155, 1327834, 1063480], 156696093)];

    for test_case in TEST_CASES {
        assert_eq!(
            test_case.1,
            istddev_sample(test_case.0.iter().cloned()).unwrap()
        );
    }
}

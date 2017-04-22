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

use ::math::geometry::*;

#[test]
fn test_get_pythagorean_triple() {
    for m in 1..6 {
        for n in 1..m {
            for k in 1..6 {
                let (a, b, c) = get_pythagorean_triple(m, n, k);
                assert_eq!(a * a + b * b, c * c);
            }
        }
    }
}

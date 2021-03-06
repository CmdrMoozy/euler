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

// Consider all integer combinations of a^b for 2 <= a <= 5 and 2 <= b <= 5:
//
//     2^2=4, 2^3=8, 2^4=16, 2^5=32
//     3^2=9, 3^3=27, 3^4=81, 3^5=243
//     4^2=16, 4^3=64, 4^4=256, 4^5=1024
//     5^2=25, 5^3=125, 5^4=625, 5^5=3125
//
// If they are then placed in numerical order, with any repeats removed, we get
// the following
// sequence of 15 distinct terms:
//
//     4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 243, 256, 625, 1024, 3125
//
// How many distinct terms are in the sequence generated by a^b for 2 <= a <=
// 100 and 2 <= b <=
// 100?

use euler::util::error::*;
use euler::util::problem::*;
use rug::ops::Pow;
use std::collections::HashSet;

const EXPECTED_RESULT: usize = 9183;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let mut result: HashSet<rug::Integer> = HashSet::new();
        for i in 2..101 {
            for j in 2..101 {
                result.insert(rug::Integer::from(i).pow(j));
            }
        }

        Ok(ProblemAnswer {
            actual: result.len(),
            expected: EXPECTED_RESULT,
        })
    });
}

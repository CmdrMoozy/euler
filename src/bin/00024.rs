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

// A permutation is an ordered arrangement of objects. For example, 3124 is one
// possible permutation of the digits 1, 2, 3 and 4. If all of the permutations
// are listed numerically or alphabetically, we call it lexicographic order.
// The lexicographic permutations of 0, 1 and 2 are:
//
// 012 021 102 120 201 210
//
// What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4,
// 5, 6, 7, 8 and 9?

use euler::algorithm::sequence;
use euler::util::error::*;
use euler::util::problem::*;

const EXPECTED_RESULT: &'static str = "2783915460";

fn main() {
    main_impl(|| -> Result<ProblemAnswer<String>> {
        let mut permutator = vec!['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'];

        // Permutate until we are at the millionth permutation.
        for _iteration in 1..1000000 {
            sequence::permutate_lt(&mut permutator);
        }

        Ok(ProblemAnswer {
            actual: permutator.iter().cloned().collect::<String>(),
            expected: EXPECTED_RESULT.to_owned(),
        })
    });
}

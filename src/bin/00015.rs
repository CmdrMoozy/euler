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

// Starting in the top left corner of a 2x2 grid, there are 6 routes (without
// backtracking) to the bottom right corner.
//
//   [... see 00015.gif ...]
//
// How many routes are there through a 20x20 grid?

use euler::math::combinatorics;
use euler::util::error::*;
use euler::util::problem::*;

const EXPECTED_RESULT: u64 = 137846528820;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        // It is well-defined that the number of paths (without backtracking) through
        // an m by n grid is: (m + n) combinations of n.
        Ok(ProblemAnswer {
            actual: combinatorics::combinations(40, 20)?,
            expected: EXPECTED_RESULT,
        })
    });
}

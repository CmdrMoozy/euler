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

// Starting with the number 1 and moving to the right in a clockwise direction
// a 5 by 5 spiral is formed as follows:
//
//   21 22 23 24 25
//   20  7  8  9 10
//   19  6  1  2 11
//   18  5  4  3 12
//   17 16 15 14 13
//
// It can be verified that the sum of the numbers on the diagonals is 101.
//
// What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral
// formed in the same way?

use euler::dsc::spiral;
use euler::util::error::*;
use euler::util::problem::*;

const EXPECTED_RESULT: u64 = 669171001;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut spiral = spiral::Spiral::new();
        let mut result: u64 = 1;
        let mut i: i64 = 1;
        while spiral::diagonal_size_to_edge_size(i) <= 1001 {
            for x in vec![-i, i] {
                for y in vec![-i, i] {
                    result += spiral.get_diagonal_value(&spiral::Address { x: x, y: y })?;
                }
            }

            i += 1;
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

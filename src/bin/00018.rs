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

// By starting at the top of the triangle below and moving to adjacent numbers
// on the row below, the maximum total from top to bottom is 23.
//
//        3
//       7 4
//      2 4 6
//     8 5 9 3
//
// That is, 3 + 7 + 4 + 9 = 23.
//
// Find the maximum total from top to bottom of the triangle below:
//
//                      75
//                     95 64
//                   17 47 82
//                  18 35 87 10
//                20 04 82 47 65
//               19 01 23 75 03 34
//             88 02 77 73 07 63 67
//            99 65 04 28 06 16 70 92
//          41 41 26 56 83 40 80 70 33
//         41 48 72 33 47 32 37 16 94 29
//       53 71 44 65 25 43 91 52 97 51 14
//      70 11 33 28 77 73 17 78 39 68 17 57
//    91 71 52 38 17 14 91 43 58 50 27 29 48
//   63 66 04 68 89 53 67 30 73 16 69 87 40 31
// 04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
//
// NOTE: As there are only 16384 routes, it is possible to solve this problem
// by trying every route. However, Problem 67, is the same challenge with a
// triangle containing one-hundred rows; it cannot be solved by brute force,
// and requires a clever method! ;o)

use euler::dsc::triangle::Triangle;
use euler::util::error::*;
use euler::util::problem::*;

const TRIANGLE_VALUES: &'static str = include_str!("00018.txt");

const EXPECTED_RESULT: u64 = 1074;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut triangle: Triangle<u64> = Triangle::new(TRIANGLE_VALUES.split('\n').count());
        for row_pair in TRIANGLE_VALUES.split('\n').enumerate() {
            for value_pair in row_pair.1.split(' ').enumerate() {
                triangle.set(row_pair.0, value_pair.0, value_pair.1.parse::<u64>()?)?;
            }
        }

        Ok(ProblemAnswer {
            actual: triangle.get_largest_path_sum()?,
            expected: EXPECTED_RESULT,
        })
    });
}

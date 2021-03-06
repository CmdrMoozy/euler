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

// The following iterative sequence is defined for the set of positive integers:
//
//   n -> n/2 (n is even)
//   n -> 3n + 1 (n is odd)
//
// Using the rule above and starting with 13, we generate the following
// sequence:
//
//  13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
//
// It can be seen that this sequence (starting at 13 and finishing at 1)
// contains 10 terms. Although it has not been proved yet (Collatz Problem), it
// is thought that all starting numbers finish at 1.
//
// Which starting number, under one million, produces the longest chain?
//
// NOTE: Once the chain starts the terms are allowed to go above one million.

use euler::util::bitwise;
use euler::util::error::*;
use euler::util::problem::*;

const MIN_NUMBER: u64 = 2;
const MAX_NUMBER: u64 = 1000000;

const EXPECTED_RESULT: u64 = 837799;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut length_cache: Vec<u64> = vec![0; MAX_NUMBER as usize];
        let mut answer_number: u64 = 0;
        let mut answer_length: u64 = 0;

        for starting_number in MIN_NUMBER..MAX_NUMBER {
            let mut current_length: u64 = 1;
            let mut current_number = starting_number;

            // Note that since we will have the length for 2 cached, and 2 -> 1 is the only
            // route to the terminal nmber, we don't need to do "while current_number > 1".
            loop {
                // If we already know the length for the remaining portion of the sequence,
                // stop here.
                if current_number < MAX_NUMBER && length_cache[current_number as usize] != 0 {
                    current_length += length_cache[current_number as usize];
                    length_cache[starting_number as usize] = current_length;
                    break;
                }

                // Optimize for powers of two, since the length of such sequences is trivial.
                if bitwise::is_pow_two(current_number) {
                    let length: u64 = bitwise::lg(current_number);
                    if current_number < MAX_NUMBER {
                        length_cache[current_number as usize] = length;
                    }
                    current_length += length;
                    break;
                }

                // Mutate the current number and proceed through the sequence.
                if current_number & 1 != 0 {
                    current_number = 3 * current_number + 1;
                } else {
                    current_number = current_number / 2;
                }
                current_length += 1;
            }

            if current_length > answer_length {
                answer_number = starting_number;
                answer_length = current_length;
            }
        }

        Ok(ProblemAnswer {
            actual: answer_number,
            expected: EXPECTED_RESULT,
        })
    });
}

// euler - A collection of ProjectEuler libraries, tools, and solutions.
// Copyright (C) 2013 Axel Rasmussen
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

extern crate euler;
use self::euler::util::bitwise;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const MIN_NUMBER: u64 = 2;
const MAX_NUMBER: u64 = 1000000;

const EXPECTED_RESULT: u64 = 837799;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut length_cache: [u64; MAX_NUMBER as usize] = [0; MAX_NUMBER as usize];
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

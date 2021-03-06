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

// Starting with 1 and spiralling anticlockwise in the following way, a square
// spiral with side length 7 is formed.
//
//    (37)36 35 34 33 32(31)
//     38(17)16 15 14(13)30
//     39 18 (5) 4 (3)12 29
//     40 19  6  1  2 11 28
//     41 20 (7) 8  9 10 27
//     42 21 22 23 24 25 26
//    (43)44 45 46 47 48 49
//
// It is interesting to note that the odd squares lie along the bottom right
// diagonal, but what is more interesting is that 8 out of the 13 numbers lying
// along both diagonals are prime; that is, a ratio of 8/13 = 62%.
//
// If one complete new layer is wrapped around the spiral above, a square
// spiral with side length 9 will be formed. If this process is continued, what
// is the side length of the square spiral for which the ratio of primes along
// both diagonals first falls below 10%?

use euler::dsc::spiral::{diagonal_size_to_edge_size, SpiralIterator};
use euler::math::prime::is_prime;
use euler::util::error::*;
use euler::util::problem::*;

// This value is sufficiently high enough for us to get the correct answer, and
// sufficiently low enough to find the answer very quickly.
const PRIMALITY_TEST_PRECISION: u64 = 50;

const EXPECTED_RESULT: usize = 26241;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let mut it = SpiralIterator::new();
        // Skip the center value, 1.
        it.next().unwrap()?;

        let mut primes: usize = 0;
        let mut iteration: usize = 0;
        loop {
            iteration += 1;

            for _ in 0..4 {
                let p = it.next().unwrap()?;
                if is_prime(p, PRIMALITY_TEST_PRECISION) {
                    primes += 1;
                }
            }

            // If < 10% of the total number of values we've checked have been prime, stop
            // here.
            let total_values = (iteration * 4) + 1;
            if 10 * primes < total_values {
                break;
            }
        }

        Ok(ProblemAnswer {
            actual: diagonal_size_to_edge_size(iteration as i64) as usize,
            expected: EXPECTED_RESULT,
        })
    });
}

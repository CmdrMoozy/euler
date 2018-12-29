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

// A number chain is created by continuously adding the square of the digits in
// a number to form a new number until it has been seen before.
//
// For example,
//
//     44 -> 32 -> 13 -> 10 -> 1 -> 1
//     85 -> 89 -> 145 -> 42 -> 20 -> 4 -> 16 -> 37 -> 58 -> 89
//
// Therefore any chain that arrives at 1 or 89 will become stuck in an endless
// loop. What is most amazing is that EVERY starting number will eventually
// arrive at 1 or 89.
//
// How many starting numbers below ten million will arrive at 89?

use euler::util::error::*;
use euler::util::problem::*;

const EXPECTED_RESULT: usize = 8581146;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let mut count: usize = 0;
        // Cache numbers which end at 89 to prevent recalculation.
        let mut ends_at_target: Vec<bool> = vec![false; 10000001];

        // Start at 2, since 1 has already arrived at 1...
        for n in 2..10000001 {
            let mut x: u64 = n;

            while x != 89 && x != 1 {
                let mut sum: u64 = 0;
                while x > 0 {
                    sum += (x % 10) * (x % 10);
                    x /= 10;
                }

                x = sum;
                if x <= 10000000 && ends_at_target[x as usize] {
                    x = 89;
                }
            }

            if x == 89 {
                ends_at_target[n as usize] = true;
                count += 1;
            }
        }

        Ok(ProblemAnswer {
            actual: count,
            expected: EXPECTED_RESULT,
        })
    });
}

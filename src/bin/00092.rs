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

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

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

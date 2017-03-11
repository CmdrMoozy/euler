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

// The prime 41 can be written as the sum of six consecutive primes:
//
//     41 = 2 + 3 + 5 + 7 + 11 + 13
//
// This is the longest sum of consecutive primes that adds to a prime below
// one-hundred.
//
// The longest sum of consecutive primes below one-thousand that adds to a
// prime, contains 21 terms, and is equal to 953.
//
// Which prime, below one-million, can be written as the sum of the most
// consecutive primes?

extern crate euler;
use self::euler::math::prime::PrimeSieve;
use self::euler::math::sieve::Sieve;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 997651;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        // It can be determined by adding the first n primes that the largest possible
        // set of consecutive primes added together to form a number less than
        // 1,000,000 is 546. Thus, this is our starting upper liimit.

        let sieve = PrimeSieve::new(1000000);
        let primes: Vec<u64> = sieve.iter().collect();
        let mut result: u64 = 0;

        for length in (1..547).rev() {
            // For each possible length, we try to see if the sum of that number of any
            // consecutive primes produces a prime.
            let mut start = 0;
            let mut end = start + length;
            while end <= sieve.get_size() {
                let sum: u64 = primes[start..end].iter().fold(0, |acc, p| acc + *p);
                if sum >= 1000000 {
                    break;
                }

                // If the resulting number is prime, we've found the one we wanted!
                if sieve.contains(sum).unwrap_or(false) {
                    result = sum;
                    break;
                }

                // Otherwise, increment the range we are working with.
                start += 1;
                end += 1;
            }

            if result != 0 {
                break;
            }
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

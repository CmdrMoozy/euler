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

// The arithmetic sequence, 1487, 4817, 8147, in which each of the terms
// increases by 3330, is unusual in two ways: (i) each of the three terms are
// prime, and, (ii) each of the 4-digit numbers are permutations of one
// another.
//
// There are no arithmetic sequences made up of three 1-, 2-, or 3-digit
// primes, exhibiting this property, by there is one other 4-digit increasing
// sequence.
//
// What 12-digit number do you form by concatenating the three terms in this
// sequence?

extern crate euler;
use self::euler::algorithm::is_permutation_of;
use self::euler::math::prime::PrimeSieve;
use self::euler::math::sieve::Sieve;
use self::euler::util::error::*;
use self::euler::util::problem::*;

static EXPECTED_RESULT: &'static str = "296962999629";

fn main() {
    main_impl(|| -> Result<ProblemAnswer<String>> {
        let sieve = PrimeSieve::new(10000);
        let mut result = vec![];

        // For each four-digit prime...
        for prime in sieve.iter().filter(|p| *p >= 1000 && *p <= 9999) {
            // For each arithmetic increase that would make sense...
            let mut addition: u64 = 1;
            while prime + addition * 2 < 10000 {
                // If the second number is prime...
                let second_prime = prime + addition;
                if sieve.contains(second_prime).unwrap_or(false) {
                    // If the third number is prime...
                    let third_prime = prime + addition * 2;
                    if sieve.contains(third_prime).unwrap_or(false) {
                        // If these primes are permutations of each other...
                        if is_permutation_of(&prime, &second_prime) &&
                           is_permutation_of(&prime, &third_prime) {
                            // If this isn't the sequence given in the problem description...
                            if prime != 1487 && second_prime != 1487 && third_prime != 1487 {
                                result.push(prime);
                                result.push(second_prime);
                                result.push(third_prime);
                                break;
                            }
                        }
                    }
                }

                addition += 1;
            }

            if !result.is_empty() {
                break;
            }
        }

        result.sort();
        Ok(ProblemAnswer {
            actual: result.iter().map(|prime| prime.to_string()).collect::<Vec<String>>().join(""),
            expected: EXPECTED_RESULT.to_owned(),
        })
    });
}

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
use self::euler::algorithm::sequence::integer_is_permutation_of;
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
                        if integer_is_permutation_of(prime, second_prime)? &&
                           integer_is_permutation_of(prime, third_prime)? {
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

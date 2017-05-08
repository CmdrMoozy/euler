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

// The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.
//
// Find the sum of all numbers, less than one million, which are palindromic in
// base 10 and base 2.
//
// (Please note that the palindromic number, in either base, may not include
// leading zeros.)

extern crate euler;
use self::euler::algorithm::sequence::is_palindrome;
use self::euler::util::bitwise::is_bitwise_palindromic;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 872187;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut sum: u64 = 0;
        for n in 1..1000000 {
            if is_bitwise_palindromic(n) && is_palindrome(&n) {
                sum += n;
            }
        }

        Ok(ProblemAnswer {
            actual: sum,
            expected: EXPECTED_RESULT,
        })
    });
}

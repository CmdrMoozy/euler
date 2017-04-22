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

// A paldinromic number reads the same both ways. The largest palindrome made
// from the product of two 2-digit numbers is 9009 = 91 x 99.
//
// Find the largest palindrome made from the product of two 3-digit numbers.

use std::collections::BTreeSet;
use std::string::String;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 906609;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        // Formulate a list of all of the products of two three-digit numbers.
        let mut products: BTreeSet<u64> = BTreeSet::new();
        for a in 100..1000 {
            for b in 100..(a + 1) {
                products.insert(a * b);
            }
        }

        // Starting with the largest number, search backwards until we find a
        // palindrome.
        let mut result: u64 = 0;
        for n in products.iter().rev() {
            let str_n: String = format!("{}", n);
            // Since this string only contains the characters 0-9, just reverse the bytes.
            let rev_str_n: String =
                String::from_utf8(str_n.as_bytes().iter().rev().cloned().collect())?;
            if str_n == rev_str_n {
                result = *n;
                break;
            }
        }

        Ok(ProblemAnswer {
            actual: result,
            expected: EXPECTED_RESULT,
        })
    });
}

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

// Consider the fraction, n/d, where n and d are positive integers. If n<d and
// HCF(n,d)=1, it is called a reduced proper fraction.
//
// If we list the set of reduced proper fractions for d <= 8 in ascending order
// of size, we get:
//
//     1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, _2/5_, 3/7, 1/2, 4/7, 3/5, 5/8,
//     2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
//
// It can be seen that 2/5 is the fraction immediately to the left of 3/7.
//
// By listing the set of reduced proper fractions for d <= 1,000,000 in
// ascending order of size, find the numerator of the fraction immediately to
// the left of 3/7.

use euler::structs::fraction::Fraction;
use euler::util::error::*;
use euler::util::problem::*;

// We will be searching, in a sorted list of all fractions where the
// denominator is <= DENOMINATOR_LIMIT, for a fraction immediately to the left
// of TARGET_N / TARGET_D.
const DENOMINATOR_LIMIT: u64 = 1000000;
const TARGET_N: u64 = 3;
const TARGET_D: u64 = 7;

const EXPECTED_RESULT: u64 = 428570;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let mut lower = Fraction::new(0, 1)?;
        let mut mediant = Fraction::new(0, 1)?;
        let upper = Fraction::new(TARGET_N, TARGET_D)?;

        while mediant.denominator() <= DENOMINATOR_LIMIT {
            lower = mediant;
            mediant = lower.mediant(&upper)?.0;
        }

        Ok(ProblemAnswer {
            actual: lower.numerator(),
            expected: EXPECTED_RESULT,
        })
    });
}

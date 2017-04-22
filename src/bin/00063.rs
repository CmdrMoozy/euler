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

// The 5-digit number, 16807 = 7^5, is also a fifth power. Similarly, the
// 9-digit number, 134217728 = 8^9, is a ninth power.
//
// How many n-digit positive integers exist which are also an nth power?

extern crate euler;
use self::euler::math::exp;
use self::euler::util::error::*;
use self::euler::util::problem::*;

// For this problem, we're searching for all b^e=n for positive integers n.
// This means we are trying to find values which satisfy:
//
//     floor(log(b^e)) + 1 = e
//
// We know that b^e is a positive integer. This implies that either b is
// nonnegative or e is even. We can exclude the case of negative b and even e,
// without loss of generality, since there exists some other b and e which
// produce an equivalent n. Thus, we only need to consider nonnegative b. We
// can also see that we can exclude the case of b = 0, since log(0^e) = log(0)
// which is undefined. This case will be counted as a solution to the problem
// separately.
const MINIMUM_BASE: u64 = 1;

// Since we are trying to find values satisfying floor(log(b^e)) + 1 = e, we
// can see that floor(log(b^e)) must be strictly less than e. Thus, we have:
//
//     floor(e * log(b)) < e
//
// Note that, if b >= 10, then log(b) >= 1, which means that we've violated the
// above restriction. Thus, b must be strictly less than 10.
const MAXIMUM_BASE: u64 = 9;

// We can also see that e must be nonnegative, since b^e for negative e
// produces a non-integer value of n. The value of e also cannot be equal to
// zero, since a "zero-digit positive integer" by definition doesn't exist.
const MINIMUM_EXP: u64 = 1;

const EXPECTED_RESULT: usize = 49;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        // Start our count at 1, since 0^1 = 0 which is a 1-digit number. This value is
        // not handled by our algorithm, since log(0) is undefined.
        let mut count: usize = 1;

        for b in MINIMUM_BASE..MAXIMUM_BASE + 1 {
            let mut e: u64 = MINIMUM_EXP;
            loop {
                let n = exp::checked_ipow(b, e);
                // If we overflowed, stop here.
                if n.is_none() {
                    break;
                }
                let n = n.unwrap();
                let digits = exp::log10(n) + 1;

                // If we've found a value for e such that the digits b^e exceeds e, we can stop
                // trying e's with this b. This is due to the fact that:
                //
                //     floor(log(b^e)) + 1 < e
                //     floor(log(b^e)) < e - 1
                //     floor(e * log(b)) < e - 1
                //     floor(e * log(b)) + 1 < e
                //
                // Since this is true, we can also show by induction that the identity holds
                // for e + 1 as well:
                //
                //     floor((e + 1) * log(b)) < (e + 1) - 1
                //     floor(e * log(b) + log(b)) < e
                //
                // Because floor(e * log(b)) + 1 < e, we can also see that floor(e * log(b) +
                // log(b)) < e as long as floor(e * log(b) + log(b)) <= floor(e * log(b)) + 1.
                // This is obviously true, as long as log(b) <= 1 (i.e., b <= 10).
                if e > digits {
                    break;
                }

                if e == digits {
                    count += 1;
                }

                e += 1;
            }
        }

        Ok(ProblemAnswer {
            actual: count,
            expected: EXPECTED_RESULT,
        })
    });
}

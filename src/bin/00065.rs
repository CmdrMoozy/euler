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

// The square root of 2 can be written as an infinite continued fraction.
//
// sqrt(2) = 1 +      1
//               -----------
//               2 +    1
//                   -------
//                   2 + ...
//
// The infinite continued fraction can be written, sqrt(2) = [1;(2)], (2)
// indicates that 2 repeats ad infinitum. In a similar way, sqrt(23) =
// [4;(1,3,1,8)].
//
// It turns out that the sequence of partial values of continued fractions for
// square roots provide the best rational approximations. Let us consider the
// convergents for sqrt(2):
//
//     3/2
//     7/5
//     17/12
//     41/29
//
// Hence the sequence of the first ten convergents for sqrt(2) are:
//
//     1, 3/2, 7/5, 17/12, 41/29, 99/70, 239/169, 577/408, 1393/985,
//     3363/2378, ...
//
// What is most surprising is that the important mathematical constant,
//
//     e = [2; 1, 2, 1, 1, 4, 1, 1, 6, 1, ... , 1, 2k, 1, ...].
//
// The first ten terms in the sequence of convergents for e are:
//
//     2, 3, 8/3, 11/4, 19/7, 87/32, 106/39, 193/71, 1264/465, 1457/536, ...
//
// The sum of the digits in the numerator of the 10th convergent is 1+4+5+7=17.
//
// Find the sum of the digits in the numerator of the 100th convergent of their
// continued fraction for e.

extern crate gmp;
use gmp::mpz::Mpz;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 272;

/// This function returns the nth continued fraction denominator for the
/// continued fraction representation of e, elsewhere referred to as b(n).
///
/// We are using the continued fraction: [ 2; (1, 2k, 1) ] for this calculation.
#[inline]
fn get_nth_b_n_denominator(n: u64) -> u64 {
    match n {
        0 => 2,
        _ => match n % 3 {
            2 => 2 * ((n + 1) / 3),
            _ => 1,
        },
    }
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        // By the Fundamental Recurrence formulas
        // (http://en.wikipedia.org/wiki/Fundamental_recurrence_formulas), we are given
        // the following:
        //
        // The nth convergent, x(n), = A(n) / B(n).
        //
        // Let A(n) and B(n) be defined by the recurrence relation:
        //
        //       A(0) = b(0)
        //       A(1) = b(1)b(0) + a(1)
        //     A(n+1) = b(n+1)A(n) + a(n+1)A(n-1)
        //
        //       B(0) = 1
        //       B(1) = b(1)b(0) + a(1)
        //     B(n+1) = b(n+1)B(n) + a(n+1)B(n-1)
        //
        // Where a(n) and b(n) represent the nth numerator and denominator of the
        // continued fraction, respectively. It can be seen that for the continued
        // fraction representation [...], where S(n) is the nth term of the
        // representation starting at S(0), that:
        //
        //    b(n) = S(n)
        //    a(n) = 1
        //
        // It should also be noted that, by the way continued fraction representations
        // are constructed, we know that the convergent x(n) for all n in Z is
        // automatically written in lowest terms (i.e., gcd(A(n), B(n)) = 1 for all
        // valid n).

        // The first two convergent numerators are 2(/1) and 3(/2).
        let mut previous_big_a = Mpz::from(2);
        let mut big_a = Mpz::from(3);

        // We want the numerator of the 100th convergent, so calculate the next A
        // (big_a) 99 times.
        for n in 1..99 {
            // A(n+1) = b(n+1)A(n) + a(n+1)A(n-1)
            let denominator = Mpz::from(get_nth_b_n_denominator(n + 1));
            let hold: Mpz = denominator * &big_a + previous_big_a;
            previous_big_a = big_a;
            big_a = hold;
        }

        // A (big_a) now contains the numerator of the 100th convergent. Add its digits
        // to get our answer.
        Ok(ProblemAnswer {
            actual: big_a
                .to_string()
                .chars()
                .fold(0_u64, |acc, c| acc + c.to_digit(10).unwrap() as u64),
            expected: EXPECTED_RESULT,
        })
    });
}

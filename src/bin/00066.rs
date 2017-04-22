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

// Consider quadratic Diophantine equations of the form:
//
//     x^2 - Dy^2 = 1
//
// For example, when D=13, the minimal solution in x is 649^2 - 13 x 180^2 = 1.
//
// It can be assumed that there are no solutions in positive integers when D is
// square.
//
// By finding minimal solutions in x for D = {2, 3, 5, 6, 7} we obtain the
// following:
//
//     3^2 - 2 x 2^2 = 1
//     2^2 - 3 x 1^2 = 1
//     9^2 - 5 x 4^2 = 1
//     5^2 - 6 x 2^2 = 1
//     8^2 - 7 x 3^2 = 1
//
// Hence, by considering minimal solutions in x for D <= 7, the largest x is
// obtained when D = 5.
//
// Find the value of D <= 1000 in minimal solutions of x for which the largest
// value of x is obtained.

extern crate gmp;
use gmp::mpz::Mpz;

extern crate euler;
use self::euler::math::exp;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 661;

/// This function will return the periodic continued fraction notation of
/// sqrt(D). E.g., for sqrt(11), which is [3; 3, 6, 3, 6, ...], we will return
/// a vector containing the elements 3, 3 and 6, in that order.
///
/// If the given number is a perfect square, then the vector returned will only
/// contain one element: sqrt(D).
///
/// Also, note that we will always return the entire period: e.g., for the
/// returned vector v, the continued fraction representation of sqrt(D) is
/// guaranteed to be, e.g., for a period length of 4:
///
///     [v(0), v(1), v(2), v(3), v(4), v(1), v(2), v(3), v(4), ...]
///
/// In order to compute this, we will use the algorithm described here:
///
/// http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/Fibonacci/cfINTRO.
/// html
fn get_continued_fraction(big_d: u64) -> Vec<u64> {
    let iroot = exp::isqrt(big_d);

    if iroot * iroot == big_d {
        return vec![iroot];
    }

    let mut v: Vec<u64> = Vec::new();
    let mut num: i64 = 0;
    let mut den: i64 = 1;
    loop {
        let nextn = (iroot as i64 + num) / den;
        v.push(nextn as u64);

        let hold: i64 = den;
        den = num - (den * nextn);
        num = hold;

        let hold = -den;
        den = (big_d as i64 - (den * den)) / num;
        num = hold;

        if den == 1 {
            v.push(iroot * 2);
            break;
        }
    }

    v
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        // To solve this problem, we will use H. W. Lengstra Jr.'s "Solving the Pell
        // Equation", which gives us that:
        //
        // Let h(i) / k(i) denote the sequence of convergents to the continued
        // fraction for sqrt(D). Then the pair (x1, y1) solving Pell's equation and
        // minimizing x satisfies x1 = h(i) and y1 = k(i) for some i.
        //
        // Notice that the generalized form of a continued fraction is:
        //
        //                             a(1)
        //     x = b(0) + -------------------------------
        //                                 a(2)
        //                b(1) + ------------------------
        //                                    a(3)
        //                       b(2) + -----------------
        //                                        a(4)
        //                              b(3) + ----------
        //                                     b(4) + ...
        //
        // And, finally, note that the recurrence relations for the convergents of
        // continued fractions in the form A(n) / B(n) are:
        //
        //     A(0) = b(0)                             B(0) = 1
        //     A(1) = b(1) * b(0) + a(1)               B(1) = b(1)
        //     A(n) = b(n) * A(n-1) +                  B(n) = b(n) * B(n-1) +
        //            a(n) * A(n-2)                           a(n) * B(n-2)
        //
        // This allows us to very easily generate the list of convergents for a given
        // value of D.

        // Loop through each D <= 1000, starting at 8 since we're given the solution
        // for D <= 7.

        let mut result_big_d: u64 = 5;
        let mut result_x = Mpz::from(9);

        let mut big_a_minus_1: Mpz;
        let mut big_a_minus_2: Mpz;
        let mut big_b_minus_1: Mpz;
        let mut big_b_minus_2: Mpz;

        for big_d in 19..1001 {
            // We need to skip any D which is a perfect square, since Pell's equation has
            // no solution for these values.
            if exp::is_square(big_d) {
                continue;
            }

            let cf = get_continued_fraction(big_d);

            // Add the first two convergents to our lists.
            big_a_minus_2 = Mpz::from(cf[0]);
            big_b_minus_2 = Mpz::from(1);
            big_a_minus_1 = Mpz::from(cf[0] * cf[1] + 1);
            big_b_minus_1 = Mpz::from(cf[1]);

            // Test if this first convergent is our solution.
            let tmp_a = &big_a_minus_2 * &big_a_minus_2;
            let tmp_b = &big_b_minus_2 * &big_b_minus_2;
            let tmp_b = &tmp_b * &Mpz::from(big_d);
            let tmp_a = &tmp_a - &tmp_b;
            if tmp_a == Mpz::from(1) {
                if big_a_minus_2 > result_x {
                    result_big_d = big_d;
                    result_x = big_a_minus_2;
                }
                continue;
            }

            // Keep testing & incrementing the convergent until we find the solution.
            let mut cfn: u64 = 2;
            loop {
                // Test the most recent convergent.
                let tmp_a = &big_a_minus_1 * &big_a_minus_1;
                let tmp_b = &big_b_minus_1 * &big_b_minus_1;
                let tmp_b = &tmp_b * &Mpz::from(big_d);
                let tmp_a = &tmp_a - &tmp_b;
                if tmp_a == Mpz::from(1) {
                    if big_a_minus_1 > result_x {
                        result_big_d = big_d;
                        result_x = big_a_minus_1;
                    }
                    break;
                }

                // Since this isn't the solution, compute the next one.
                let cfidx: u64 = (cfn - 1) % (cf.len() as u64 - 1) + 1;
                let tmp_a = &big_a_minus_1 * &Mpz::from(cf[cfidx as usize]) + &big_a_minus_2;
                let tmp_b = &big_b_minus_1 * &Mpz::from(cf[cfidx as usize]) + &big_b_minus_2;
                big_a_minus_2 = big_a_minus_1;
                big_a_minus_1 = tmp_a;
                big_b_minus_2 = big_b_minus_1;
                big_b_minus_1 = tmp_b;

                cfn += 1;
            }
        }

        Ok(ProblemAnswer {
            actual: result_big_d,
            expected: EXPECTED_RESULT,
        })
    });
}

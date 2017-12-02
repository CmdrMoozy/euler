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

// If a box contains twenty-one coloured discs, composed of fifteen blue discs
// and six red discs, and two discs were taken at random, it can be seen that
// the probability of taking two blue discs, P(BB) = (15/12) x (14/20) = 1/2.
//
// The next such arrangement, for which there is exactly 50% change of taking
// two blue discs at random, is a box containing eighty-five blue discs and
// thirty-five red discs.
//
// By finding the first arrangement to contain over 10^12 = 1,000,000,000,000
// discs in total, determine the number of blue discs that the box would
// contain.

extern crate rug;
use rug::ops::Pow;

extern crate libc;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const FLOAT_PRECISION: u32 = 256;

const EXPECTED_RESULT: usize = 756872327473;

fn float_from_int(v: i64) -> rug::Float {
    rug::Float::with_val_round(FLOAT_PRECISION, v, rug::float::Round::Nearest).0
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        // First note that, in general, we are trying to find integer solutions to the
        // following:
        //
        // [B * (B - 1)] / [N * (N - 1)] = 1/2
        //
        // I.e.,
        //
        // 2B(B-1) = N(N-1)
        //
        // Using some very basic algebra, as well as by completing the square to solve
        // for B in terms of N, we end up with:
        //
        // B^2 - B = (1/2) * N * (N - 1)
        // B^2 - B + (1/4) = (1/2) * N * (N - 1) + (1/4)
        // (B - (1/2))^2 = (1/2) * N * (N - 1) + (1/4)
        // B - (1/2) = +/- sqrt[ (1/2) * N * (N - 1) + (1/4) ]
        // B = +/- sqrt[ (1/2) * N * (N - 1) + (1/4) ] + (1/2)
        //
        // Furthermore, note that (in the context of our problem), negative values for
        // B don't make sense, so we can simply ignore those values of B, giving:
        //
        // B = sqrt[ (1/2) * N * (N - 1) + (1/4) ] + (1/2)
        //
        // At this point, all we need to do to solve this problem is to solve the
        // right-hand side of the equation over the integers, with N > 10^12.
        //
        // Note that, because B must be an integer, we also know that the right-hand
        // side of the given equation is in Z. Thus (=> means implies):
        //
        // sqrt[ (1/2) * N * (N - 1) + (1/4) ] + (1/2) is in Z
        // Let sqrt[ (1/2) * N * (N - 1) + (1/4) ] + (1/2) = Y, for Y in Z.
        //
        // With basic algebra, we come up with:
        //
        // (1/2) * N * (N - 1) + (1/4) = (Y - (1/2))^2
        // 4 * N * (N - 1) + 2 = 8 * (Y - (1/2))^2
        // 4N^2 - 4N + 2 = 8Y^2 - 8Y + 2
        // 8Y^2 - 8Y + 2 - 4N^2 + 4N - 2 = 0
        // 8Y^2 - 8Y + 2 - 4N^2 + 4N - 1 = 1
        // 2(4Y^2 - 4Y + 1) - (4N^2 - 4N + 1) = 1
        // 2(2Y - 1)^2 - (2N - 1)^2 = 1
        //
        // At this point, if we let X` = 2N - 1, and Y` = 2Y - 1, then we have:
        //
        // X`^2 - 2Y`^2 = -1
        //
        // I.e., the problem is reduced to the negative Pell's equation. For this
        // particular instance of the negative Pell's equation, the fundamental
        // solution is well known to be X` = 1, Y` = 1. Furthermore, the list of all
        // positive solutions are given by the recurrences:
        //
        // X`[n + 1] = 3 * X`[n] + 4 * Y`[n]
        // Y`[n + 1] = 2 * X`[n] + 3 * Y`[n]
        //
        // Returning back to the problem, we're looking for solutions with N > 10^12.
        // This means that we're looking for the first solution with X` > 2 * 10^12 -
        // 1. Let us search for that value first:

        let mut xprime = rug::Integer::from(1);
        let mut yprime = rug::Integer::from(1);

        let bound =
            (rug::Integer::from(10).pow(12) * rug::Integer::from(2)) - rug::Integer::from(1);

        while xprime < bound {
            let tmp_a = xprime.clone() * rug::Integer::from(3);
            let tmp_b = yprime.clone() * rug::Integer::from(4);
            let tmp_a = tmp_a + tmp_b;

            let tmp_b = xprime * rug::Integer::from(2);
            let tmp_c = yprime * rug::Integer::from(3);

            xprime = tmp_a;
            yprime = tmp_b + tmp_c;
        }

        // Now that we have the minimized X` solution, we need to get the corresponding
        // minimal N solution. Since X` = 2N - 1, we have:
        //
        // 2N = X` - 1
        // N = (1/2) * (X` - 1)
        //
        // Note that this must be an integer, since by definition of the solutions of
        // the negative Pell's equation we know that X` is odd.

        let xprime = (xprime - rug::Integer::from(1)) / rug::Integer::from(2);

        // Finally, it was proven above that B, the number of blue discs, can be
        // written in terms of N, the total number of discs. Namely:
        //
        // B = sqrt[ (1/2) * N * (N - 1) + (1/4) ] + (1/2)
        //
        // So we simply need to evaluate this expression and we have our answer!

        let big_n =
            rug::Float::with_val_round(FLOAT_PRECISION, xprime, rug::float::Round::Nearest).0;
        let mut big_b = (((big_n.clone() - float_from_int(1)) * big_n) / float_from_int(2))
            + (float_from_int(1) / float_from_int(4));
        big_b = big_b.sqrt() + (float_from_int(1) / float_from_int(2));
        big_b = big_b.ceil();

        Ok(ProblemAnswer {
            actual: big_b.to_integer().unwrap().to_u64().unwrap() as usize,
            expected: EXPECTED_RESULT,
        })
    });
}

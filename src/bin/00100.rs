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

extern crate gmp;
use gmp::mpf::Mpf;
use gmp::mpz::Mpz;

extern crate libc;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const MPF_PRECISION: usize = 256;

const EXPECTED_RESULT: usize = 756872327473;

fn mpf_from_int(v: i64) -> Mpf {
    let mut mpfv = Mpf::new(MPF_PRECISION);
    mpfv.set_from_si(v);
    mpfv
}

fn mpf_to_string(v: &mut Mpf, base: i32) -> String {
    let mut exponent: libc::c_long = 0;
    let s = v.get_str(0, base, &mut exponent);
    let exponent = exponent as usize;

    let int_part: String = s.chars().take(exponent).collect();
    let frac_part: String = s.chars().skip(exponent).collect();

    if frac_part.is_empty() {
        int_part
    } else {
        format!("{}.{}", int_part, frac_part)
    }
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

        let mut xprime = Mpz::from(1);
        let mut yprime = Mpz::from(1);

        let bound = (Mpz::ui_pow_ui(10, 12) * Mpz::from(2)) - Mpz::from(1);

        while xprime < bound {
            let tmp_a = xprime.clone() * Mpz::from(3);
            let tmp_b = yprime.clone() * Mpz::from(4);
            let tmp_a = tmp_a + tmp_b;

            let tmp_b = xprime * Mpz::from(2);
            let tmp_c = yprime * Mpz::from(3);

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

        let xprime = (xprime - Mpz::from(1)) / Mpz::from(2);

        // Finally, it was proven above that B, the number of blue discs, can be
        // written in terms of N, the total number of discs. Namely:
        //
        // B = sqrt[ (1/2) * N * (N - 1) + (1/4) ] + (1/2)
        //
        // So we simply need to evaluate this expression and we have our answer!

        let mut big_n = Mpf::new(MPF_PRECISION);
        big_n.set_z(&xprime);

        let mut big_b = (((big_n.clone() - mpf_from_int(1)) * big_n) / mpf_from_int(2)) +
                        (mpf_from_int(1) / mpf_from_int(4));
        big_b = big_b.sqrt() + (mpf_from_int(1) / mpf_from_int(2));
        big_b = big_b.ceil();

        Ok(ProblemAnswer {
            actual: mpf_to_string(&mut big_b, 10).parse::<usize>()?,
            expected: EXPECTED_RESULT,
        })
    });
}

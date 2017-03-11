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

// The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 1040571317.
//
// Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.

extern crate gmp;
use gmp::mpz::Mpz;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

static EXPECTED_RESULT: &'static str = "9110846700";

fn main() {
    main_impl(|| -> Result<ProblemAnswer<String>> {
        let mut sum: Vec<u64> = vec![0; 10];
        let modulus = Mpz::from(10);

        // Add the last ten digits of each number.
        for i in 1..1001 {
            let mut x = Mpz::from(i).pow(i);

            let mut j = 1;
            while x > Mpz::from(0) && j <= 10 {
                let digit: Option<u64> = (&x.modulus(&modulus)).into();
                sum[10 - j] += digit.unwrap();
                j += 1;
                x = x / 10;
            }
        }

        // Carry everything.
        for i in 1..10 {
            let idx = 10 - i;
            sum[idx - 1] += sum[idx] / 10;
            sum[idx] %= 10;
        }
        sum[0] %= 10;

        Ok(ProblemAnswer {
            actual: sum.iter().map(|d| d.to_string()).collect::<Vec<String>>().join(""),
            expected: EXPECTED_RESULT.to_owned(),
        })
    });
}

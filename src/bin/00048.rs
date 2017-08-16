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
            actual: sum.iter()
                .map(|d| d.to_string())
                .collect::<Vec<String>>()
                .join(""),
            expected: EXPECTED_RESULT.to_owned(),
        })
    });
}

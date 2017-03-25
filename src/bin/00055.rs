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

// If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.
//
// Not all numbers produce palindromes so quickly. For example,
//
//     349 + 943 = 1292,
//     1292 + 2921 = 4213
//     4213 + 3124 = 7337
//
// That is, 349 took three iterations to arrive at a palindrome.
//
// Although no one has proved it yet, it is thought that some numbers, like
// 196, never produce a palindrome. A number that never forms a palindrome
// through the reverse and add process is called a Lychrel number. Due to the
// theoretical nature of these numbers, and for the purpose of this problem, we
// shall assume that a number is Lychrel until proven otherwise. In addition
// you are given that for every number below ten-thousand, it will either (i)
// become a palindrome in less than fifty iterations, or, (ii) no one, with all
// the computing power that exists, has managed so far to map it to a
// palindrome. In fact, 10677 is the first number to be shown to require over
// fifty iterations before producing a palindrome: 4668731596684224866951378664
// (53 iterations, 28-digits).
//
// Surprisingly, there are palindromic numbers that are themselves Lychrel
// numbers; the first example is 4994.
//
// How many Lychrel numbers are there below ten-thousand?
//
// NOTE: Wording was modified slightly on 24 April 2007 to emphasise the
// theoretical nature of Lychrel numbers.

extern crate gmp;
use gmp::mpz::Mpz;

extern crate euler;
use self::euler::algorithm;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: usize = 249;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let mut lychrel_count: usize = 0;
        for start in 1..10000 {
            let mut current: Mpz = Mpz::from(start);
            let mut iterations: usize = 0;
            let mut is_palindrome: bool = false;
            while !is_palindrome && iterations <= 50 {
                let rev = Mpz::from_str_radix(current.to_str_radix(10)
                                                  .chars()
                                                  .rev()
                                                  .collect::<String>()
                                                  .as_str(),
                                              10)
                    .unwrap();
                current = current + rev;

                iterations += 1;
                is_palindrome = algorithm::is_palindrome(&current);
            }

            if !is_palindrome {
                lychrel_count += 1;
            }
        }

        Ok(ProblemAnswer {
            actual: lychrel_count,
            expected: EXPECTED_RESULT,
        })
    });
}
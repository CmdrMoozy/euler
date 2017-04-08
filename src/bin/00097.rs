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

// The first known prime found to exceed one million digits was discovered in
// 1999, and is a Mersenne prime of the form 2^6972593 - 1; it contains exactly
// 2,098,960 digits. Subsequently other Mersenne primes, of the form 2^p - 1,
// have been found which contain more digits.
//
// However, in 2004 there was found a massive non-Mersenne prime which contains
// 2,357,207 digits: 28433 x 2^7830457 + 1.
//
// Find the last ten digits of this prime number.

extern crate gmp;
use gmp::mpz::Mpz;

extern crate euler;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: u64 = 8739992577;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        // We need the last 10 digits of 28,433 * 2^7,830,457 + 1. We can just
        // calculate it directly, since GMP is fast enough.
        let prime = Mpz::from(28433);
        let prime = prime << 7830457;
        let prime = prime + 1;
        let last_ten_digits = prime.modulus(&Mpz::from(10000000000_u64));
        let last_ten_digits = try!(last_ten_digits.to_str_radix(10).parse::<u64>());

        Ok(ProblemAnswer {
            actual: last_ten_digits,
            expected: EXPECTED_RESULT,
        })
    });
}

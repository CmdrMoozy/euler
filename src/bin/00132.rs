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

use euler::math::prime::PrimeSieve;
use euler::util::error::*;
use euler::util::problem::*;
use log::info;
use rug::Integer;
use std::collections::BTreeSet;

// We're conjecturing that R(m) | R(n) for any m | n. Our target number is
// R(10^9), so we'll test for each factor of 10^9 - and this is the static list.
// This list excludes 1 (not a prime) and 10^9 itself (the whole goal is to
// find the list of factors without trying to factor this massive number
// itself). As a trivial optimization, 2 is also excluded because R(2) = 11
// which is itself a prime, which clearly divides R(10^9).
const REPUNIT_FACTORS: &'static [u64] = &[
    4, 5, 8, 10, 16, 20, 25, 32, 40, 50, 64, 80, 100, 125, 128, 160, 200, 250, 256, 320, 400, 500,
    512, 625, 640, 800, 1000, 1250, 1280, 1600, 2000, 2500, 2560, 3125, 3200, 4000, 5000, 6250,
    6400, 8000, 10000, 12500, 12800, 15625, 16000, 20000, 25000, 31250, 32000, 40000, 50000, 62500,
    64000, 78125, 80000, 100000, 125000, 156250, 160000, 200000, 250000, 312500, 320000, 390625,
    400000, 500000, 625000, 781250, 800000, 1000000, 1250000, 1562500, 1600000, 1953125, 2000000,
    2500000, 3125000, 3906250, 4000000, 5000000, 6250000, 7812500, 8000000, 10000000, 12500000,
    15625000, 20000000, 25000000, 31250000, 40000000, 50000000, 62500000, 100000000, 125000000,
    200000000, 250000000, 500000000,
];

// TODO: This limit only makes sense given prior knowledge of the solution. This
// should be replaced with a zero-knowledge implementation.
const SIEVE_LIMIT: u64 = 160001;

// The strategy below is to find the prime factors
const TRIAL_COUNT: usize = 40;

// The total number of primes we're really hoping to have found in the end.
const TARGET_PRIME_COUNT: usize = 40;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let sieve = PrimeSieve::new(SIEVE_LIMIT);
        let mut primes: BTreeSet<u64> = BTreeSet::new();
        primes.insert(11);

        for r in REPUNIT_FACTORS {
            // If we've found enough primes, stop.
            if primes.len() > TRIAL_COUNT {
                break;
            }

            info!("Testing R({})...", r);
            let mut r: Integer = Integer::u_pow_u(10, *r as u32).into();
            r -= 1;
            let r = r.div_exact_u(9);

            for p in sieve.iter() {
                // If we've found enough primes, stop.
                if primes.len() > TRIAL_COUNT {
                    break;
                }

                // If we've already found our target number of primes, and the
                // rest of the primes are now larger, we can skip all of them.
                if primes.len() >= TARGET_PRIME_COUNT && *primes.iter().next_back().unwrap() <= p {
                    break;
                }

                // We're conjecturing that R(10^9)'s prime factors all have an
                // exponent of 1, so if we've already got this prime in the list
                // don't bother testing it again.
                if primes.contains(&p) {
                    continue;
                }

                if r.is_divisible_u(p as u32) {
                    primes.insert(p);
                }
            }
        }

        let mut sum = 0_u64;
        for p in primes.iter().take(TARGET_PRIME_COUNT) {
            info!("{}", p);
            sum += p;
        }

        Ok(ProblemAnswer {
            actual: sum,
            expected: 843296,
        })
    });
}

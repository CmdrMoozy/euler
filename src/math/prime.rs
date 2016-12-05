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

use ::math::exp::{ipowmod, isqrt};
use rand::{self, Rng};
use std::iter::FilterMap;
use std::option::Option;
use ::structs::bit_array::*;

pub const DEFAULT_PRIMALITY_TEST_PRECISION: u64 = 15;

pub fn is_prime(n: u64, precision: u64) -> bool {
    assert!(precision >= 1);

    if n == 0 || n == 1 {
        // 0 and 1 are not prime.
        return false;
    } else if n == 2 || n == 3 {
        // 2 and 2 are prime.
        return true;
    } else if n % 2 == 0 {
        // Even numbers are NOT prime.
        return false;
    } else if n % 3 == 0 {
        // Numbers divisible by 3 are NOT prime.
        return false;
    }

    let mut rng = rand::thread_rng();
    for _ in 0..precision {
        // Generate a random number in the range [1, n).
        let a: u64 = rng.gen_range(1, n);

        // If a ^ (n - 1) % n != 1, then our number is definitely not prime.
        if ipowmod(a, n - 1, n) != 1 {
            return false;
        }
    }

    true
}

fn sieve(limit: u64) -> BitArray {
    let mut is_prime = BitArray::new((limit + 1) as usize, FillPolicy::Set);
    let root = isqrt(limit);

    is_prime.set(0, false);
    is_prime.set(1, false);

    for i in 2..(root + 1) {
        if is_prime.get(i as usize).unwrap() {
            for j in ((i * i)..(limit + 1)).step_by(i) {
                is_prime.set(j as usize, false);
            }
        }
    }

    is_prime
}

pub struct Sieve {
    limit: u64,
    is_prime: BitArray,
}

impl Sieve {
    pub fn new(limit: u64) -> Sieve {
        Sieve {
            limit: limit,
            is_prime: sieve(limit),
        }
    }

    pub fn get_limit(&self) -> u64 { self.limit }

    pub fn get_size(&self) -> usize { self.is_prime.iter().filter(|pair| pair.1).count() }

    pub fn contains(&self, n: u64) -> Option<bool> { self.is_prime.get(n as usize) }

    pub fn get_nth(&self, n: usize) -> Option<u64> {
        if n == 0 {
            return None;
        }
        self.is_prime.iter().filter(|pair| pair.1).nth(n - 1).map(|pair| pair.0 as u64)
    }

    pub fn iter(&self) -> FilterMap<Iter, fn((usize, bool)) -> Option<u64>> {
        fn filterer(pair: (usize, bool)) -> Option<u64> {
            match pair.1 {
                false => None,
                true => Some(pair.0 as u64),
            }
        }

        self.is_prime.iter().filter_map(filterer)
    }
}

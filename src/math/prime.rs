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

use crate::math::exp::{ipowmod, isqrt};
use crate::math::sieve::Sieve;
use crate::structs::bit_array::*;
use crate::util::error::*;
use failure::bail;
use rand::{self, Rng};
use std::cmp;
use std::collections::{hash_map, HashMap};
use std::iter::FilterMap;
use std::option::Option;

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

fn prime_sieve(limit: u64) -> BitArray {
    let mut is_prime = BitArray::new((limit + 1) as usize, FillPolicy::Set);
    let root = isqrt(limit);

    is_prime.set(0, false);
    is_prime.set(1, false);

    for i in 2..(root + 1) {
        if is_prime.get(i as usize).unwrap() {
            let mut j = i * i;
            while j <= limit {
                is_prime.set(j as usize, false);
                j += i;
            }
        }
    }

    is_prime
}

pub struct PrimeSieve {
    limit: u64,
    is_prime: BitArray,
}

impl PrimeSieve {
    pub fn new(limit: u64) -> PrimeSieve {
        PrimeSieve {
            limit: limit,
            is_prime: prime_sieve(limit),
        }
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

impl Sieve for PrimeSieve {
    type Item = u64;

    fn get_limit(&self) -> Self::Item {
        self.limit
    }

    fn get_size(&self) -> usize {
        self.is_prime.iter().filter(|pair| pair.1).count()
    }

    fn contains(&self, n: Self::Item) -> Option<bool> {
        self.is_prime.get(n as usize)
    }

    fn get_nth(&self, n: usize) -> Option<Self::Item> {
        if n == 0 {
            return None;
        }
        self.is_prime
            .iter()
            .filter(|pair| pair.1)
            .nth(n - 1)
            .map(|pair| pair.0 as u64)
    }
}

#[derive(Clone)]
pub struct Factorization {
    number: u64,
    factors: HashMap<u64, usize>,
}

impl Factorization {
    pub fn new(
        n: u64,
        sieve: &PrimeSieve,
        primality_test_precision: Option<u64>,
    ) -> Result<Factorization> {
        let mut f = Factorization {
            number: n,
            factors: HashMap::new(),
        };

        // The values 0 or 1 don't have prime factors, so just return an empty factors
        // list.
        if n == 0 || n == 1 {
            return Ok(f);
        }

        // If the number itself is prime, then it is its own prime factor.
        if match sieve.get_limit() >= n {
            true => sieve.contains(n).unwrap(),
            false => is_prime(
                n,
                primality_test_precision.unwrap_or(DEFAULT_PRIMALITY_TEST_PRECISION),
            ),
        } {
            f.factors.insert(n, 1);
            return Ok(f);
        }

        // Otherwise, the prime sieve must be large enough to check at least
        // ceil(sqrt(n)).
        if sieve.get_limit() <= isqrt(n) {
            bail!("Prime number sieve limit is too small to factor {}", n);
        }

        let mut remaining: u64 = n;
        for prime in sieve.iter() {
            if remaining == 1 {
                break;
            }

            while remaining % prime == 0 {
                let entry = f.factors.entry(prime).or_insert(0);
                *entry += 1;
                remaining /= prime;
            }
        }

        Ok(f)
    }

    pub fn new_from_iter<I>(
        mut iter: I,
        sieve: &PrimeSieve,
        primality_test_precision: Option<u64>,
    ) -> Result<Factorization>
    where
        I: Iterator<Item = u64>,
    {
        let mut f = Factorization::new(
            iter.next().unwrap_or(0),
            sieve,
            primality_test_precision.clone(),
        )?;
        for i in iter {
            f = f.product(&Factorization::new(
                i,
                sieve,
                primality_test_precision.clone(),
            )?);
        }
        Ok(f)
    }

    /// Reduces the rational number "numerator / denominator" by eliminating as
    /// many common factors as possible, returning the new numerator and
    /// denominator of the resulting fully reduced rational.
    pub fn reduce(
        numerator: Factorization,
        denominator: Factorization,
    ) -> (Factorization, Factorization) {
        let mut num_factors = numerator.factors;
        let mut den_factors = denominator.factors;

        for (factor, count) in num_factors.iter_mut() {
            let den_entry = den_factors.entry(*factor).or_insert(0);
            let common_count = cmp::min(*count, *den_entry);
            *den_entry -= common_count;
            *count -= common_count;
        }

        num_factors = num_factors.into_iter().filter(|pair| pair.1 > 0).collect();
        den_factors = den_factors.into_iter().filter(|pair| pair.1 > 0).collect();

        (
            Factorization {
                number: num_factors
                    .iter()
                    .map(|pair| pair.0.pow(*pair.1 as u32))
                    .fold(1, |acc, v| acc * v),
                factors: num_factors,
            },
            Factorization {
                number: den_factors
                    .iter()
                    .map(|pair| pair.0.pow(*pair.1 as u32))
                    .fold(1, |acc, v| acc * v),
                factors: den_factors,
            },
        )
    }

    /// Return the number which was factored for this Factorization.
    pub fn get_number(&self) -> u64 {
        self.number
    }

    /// Returns the number of distinct prime factors of this factorization's
    /// number.
    pub fn factor_count(&self) -> usize {
        self.factors.len()
    }

    /// Return the exponent for the given factor. If the given factor is not
    /// present at all, 0 is returned instead.
    pub fn get_factor(&self, f: u64) -> usize {
        *self.factors.get(&f).unwrap_or(&0)
    }

    /// Iterate over the prime factors of this factorization's number. Each
    /// entry is a mapping from prime factor to exponent (which is always >= 1).
    pub fn iter(&self) -> hash_map::Iter<u64, usize> {
        self.factors.iter()
    }

    /// Consumes this factorization, and returns a new factorization which
    /// contains all of the factors of this factorization multiplied by the
    /// other given factorization.
    pub fn product(self, other: &Factorization) -> Factorization {
        let mut f = Factorization {
            number: self.number,
            factors: self.factors,
        };

        for (factor, count) in other.iter() {
            let entry = f.factors.entry(*factor).or_insert(0);
            *entry += *count;
        }

        f
    }
}

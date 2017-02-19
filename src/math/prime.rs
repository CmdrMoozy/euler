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

use math::exp::{ipowmod, isqrt, log10};
use math::sieve::Sieve;
use rand::{self, Rng};
use std::cmp;
use std::collections::{hash_map, HashMap};
use std::collections::VecDeque;
use std::iter::FilterMap;
use std::option::Option;
use ::structs::bit_array::*;
use ::util::error::*;

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
            for j in ((i * i)..(limit + 1)).step_by(i) {
                is_prime.set(j as usize, false);
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

    fn get_limit(&self) -> Self::Item { self.limit }

    fn get_size(&self) -> usize { self.is_prime.iter().filter(|pair| pair.1).count() }

    fn contains(&self, n: Self::Item) -> Option<bool> { self.is_prime.get(n as usize) }

    fn get_nth(&self, n: usize) -> Option<Self::Item> {
        if n == 0 {
            return None;
        }
        self.is_prime.iter().filter(|pair| pair.1).nth(n - 1).map(|pair| pair.0 as u64)
    }
}

#[derive(Debug)]
struct DigitalRotationIterator {
    index: usize,
    digits: VecDeque<char>,
}

impl DigitalRotationIterator {
    pub fn new(n: u64) -> DigitalRotationIterator {
        DigitalRotationIterator {
            index: 0,
            digits: n.to_string().chars().collect(),
        }
    }

    pub fn iter_digits(&self) -> ::std::collections::vec_deque::Iter<char> { self.digits.iter() }
}

impl Iterator for DigitalRotationIterator {
    type Item = u64;

    fn next(&mut self) -> Option<Self::Item> {
        loop {
            if self.index == self.digits.len() {
                return None;
            }

            // Skip items with leading zeros.
            let item: Option<u64> = if self.digits[0] != '0' {
                Some(self.digits.iter().cloned().collect::<String>().parse::<u64>().unwrap())
            } else {
                None
            };

            // Increment our state.
            self.index += 1;
            let last_digit = self.digits.pop_back().unwrap();
            self.digits.push_front(last_digit);

            if item.is_some() {
                return item;
            }
        }
    }
}

pub struct CircularPrimeSieve {
    limit: u64,
    is_prime: BitArray,
}

impl CircularPrimeSieve {
    pub fn new(limit: u64) -> CircularPrimeSieve {
        // To test if an n-digit number is a circular prime, we need to know about all
        // of the
        // n-digit primes (so we can test all possible rotations of its digits).
        let mut bound: u64 = 10u64.pow(log10(limit) as u32);
        if bound < limit {
            bound *= 10;
        }

        let is_prime = PrimeSieve::new(bound);
        let mut is_circular_prime = is_prime.is_prime.clone();

        for p in is_prime.iter() {
            // If this prime is outside our limit, break now.
            if p > limit {
                break;
            }

            // If this is a single-digit prime, then it is circular by definition.
            if p < 10 {
                continue;
            }

            // If we have already eliminated this value, skip it.
            if !is_circular_prime.get(p as usize).unwrap() {
                continue;
            }


            // If this prime contains any of these digits, or else at least one of its
            // rotations has a trivial factorization.
            let it = DigitalRotationIterator::new(p);
            let has_divisible_digits = it.iter_digits()
                .map(|digit| {
                    *digit == '0' || *digit == '2' || *digit == '4' || *digit == '5' ||
                    *digit == '6' || *digit == '8'
                })
                .fold(false, |acc, dd| acc || dd);
            if has_divisible_digits {
                for rotation in it {
                    is_circular_prime.set(rotation as usize, false);
                }
                continue;
            }

            // Test if all of this prime's rotations are also prime. If we find one that
            // isn't, mark all of its rotations as non-prime.
            let cp = it.map(|rotation| is_prime.contains(rotation).unwrap())
                .fold(true, |acc, cp| acc && cp);
            if !cp {
                let it = DigitalRotationIterator::new(p);
                for rotation in it {
                    is_circular_prime.set(rotation as usize, false);
                }
            }
        }

        is_circular_prime.truncate((limit + 1) as usize);
        CircularPrimeSieve {
            limit: limit,
            is_prime: is_circular_prime,
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

impl Sieve for CircularPrimeSieve {
    type Item = u64;

    fn get_limit(&self) -> Self::Item { self.limit }

    fn get_size(&self) -> usize { self.is_prime.iter().filter(|pair| pair.1).count() }

    fn contains(&self, n: Self::Item) -> Option<bool> { self.is_prime.get(n as usize) }

    fn get_nth(&self, n: usize) -> Option<Self::Item> {
        if n == 0 {
            return None;
        }
        self.is_prime.iter().filter(|pair| pair.1).nth(n - 1).map(|pair| pair.0 as u64)
    }
}

#[derive(Clone)]
pub struct Factorization {
    number: u64,
    factors: HashMap<u64, usize>,
}

impl Factorization {
    pub fn new(n: u64,
               sieve: &PrimeSieve,
               primality_test_precision: Option<u64>)
               -> Result<Factorization> {
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
            false => {
                is_prime(n,
                         primality_test_precision.unwrap_or(DEFAULT_PRIMALITY_TEST_PRECISION))
            },
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

    pub fn new_from_iter<I>(mut iter: I,
                            sieve: &PrimeSieve,
                            primality_test_precision: Option<u64>)
                            -> Result<Factorization>
        where I: Iterator<Item = u64>
    {
        let mut f = try!(Factorization::new(iter.next().unwrap_or(0),
                                            sieve,
                                            primality_test_precision.clone()));
        for i in iter {
            f = f.product(&try!(Factorization::new(i, sieve, primality_test_precision.clone())));
        }
        Ok(f)
    }

    /// Reduces the rational number "numerator / denominator" by eliminating as
    /// many common factors as possible, returning the new numerator and
    /// denominator of the resulting fully reduced rational.
    pub fn reduce(numerator: Factorization,
                  denominator: Factorization)
                  -> (Factorization, Factorization) {
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

        (Factorization {
             number: num_factors.iter()
                 .map(|pair| pair.0.pow(*pair.1 as u32))
                 .fold(1, |acc, v| acc * v),
             factors: num_factors,
         },
         Factorization {
             number: den_factors.iter()
                 .map(|pair| pair.0.pow(*pair.1 as u32))
                 .fold(1, |acc, v| acc * v),
             factors: den_factors,
         })
    }

    /// Return the number which was factored for this Factorization.
    pub fn get_number(&self) -> u64 { self.number }

    /// Returns the number of distinct prime factors of this factorization's
    /// number.
    pub fn factor_count(&self) -> usize { self.factors.len() }

    /// Return the exponent for the given factor. If the given factor is not
    /// present at all, 0 is returned instead.
    pub fn get_factor(&self, f: u64) -> usize { *self.factors.get(&f).unwrap_or(&0) }

    /// Iterate over the prime factors of this factorization's number. Each
    /// entry is a mapping from prime factor to exponent (which is always >= 1).
    pub fn iter(&self) -> hash_map::Iter<u64, usize> { self.factors.iter() }

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

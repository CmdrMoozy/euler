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

use math::exp::log10;
use math::prime::PrimeSieve;
use math::sieve::Sieve;
use std::collections::VecDeque;
use std::iter::FilterMap;
use std::option::Option;
use ::structs::bit_array::*;

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
        let mut is_circular_prime = BitArray::new(bound as usize + 1, FillPolicy::Clear);
        for p in is_prime.iter() {
            is_circular_prime.set(p as usize, true);
        }

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

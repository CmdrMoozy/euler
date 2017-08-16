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

use gmp::mpz::*;
use std::option::Option;
use std::vec::Vec;

/// Returns the average of the given list of unsigned integers. If the average
/// is too large to fit in a u64, None is returned instead. If the given list
/// is empty, 0 is returned.
pub fn iaverage<I, V>(iter: I) -> Option<u64>
where
    I: Iterator<Item = V>,
    V: Into<u64>,
{
    let mut denominator: u64 = 0;
    let mut result = Mpz::from(0);
    for v in iter {
        denominator += 1;
        result = result + v.into();
    }
    if denominator == 0 {
        return Some(0);
    }
    result = result / denominator;
    (&result).into()
}

fn istddev_impl<I, V>(iter: I, is_population: bool) -> Option<u64>
where
    I: Iterator<Item = V>,
    V: Into<u64>,
{
    let items: Vec<u64> = iter.map(|v| v.into()).collect();
    if items.len() == 0 {
        return Some(0);
    }

    let a = iaverage(items.iter().cloned());
    if a.is_none() {
        return None;
    }
    let average: u64 = a.unwrap();

    let mut stddev: Mpz = Mpz::from(0);
    for item in &items {
        stddev = stddev + (Mpz::from(*item) - average).pow(2);
    }
    stddev = stddev / (match is_population {
        false => items.len() - 1,
        true => items.len(),
    } as u64);
    stddev = stddev.sqrt();
    (&stddev).into()
}

pub fn istddev_population<I, V>(iter: I) -> Option<u64>
where
    I: Iterator<Item = V>,
    V: Into<u64>,
{
    istddev_impl(iter, true)
}

pub fn istddev_sample<I, V>(iter: I) -> Option<u64>
where
    I: Iterator<Item = V>,
    V: Into<u64>,
{
    istddev_impl(iter, false)
}

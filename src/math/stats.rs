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

use gmp::mpz::*;
use std::option::Option;
use std::vec::Vec;

/// Returns the average of the given list of unsigned integers. If the average
/// is too large to fit in a u64, None is returned instead. If the given list
/// is empty, 0 is returned.
pub fn iaverage<I, V>(iter: I) -> Option<u64>
    where I: Iterator<Item = V>,
          V: Into<u64>
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
    where I: Iterator<Item = V>,
          V: Into<u64>
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
    stddev = stddev /
             (match is_population {
        false => items.len() - 1,
        true => items.len(),
    } as u64);
    stddev = stddev.sqrt();
    (&stddev).into()
}

pub fn istddev_population<I, V>(iter: I) -> Option<u64>
    where I: Iterator<Item = V>,
          V: Into<u64>
{
    istddev_impl(iter, true)
}

pub fn istddev_sample<I, V>(iter: I) -> Option<u64>
    where I: Iterator<Item = V>,
          V: Into<u64>
{
    istddev_impl(iter, false)
}

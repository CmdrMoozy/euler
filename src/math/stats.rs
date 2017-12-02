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

use rug;

/// Returns the average of the given list of unsigned integers. If the average
/// is too large to fit in a u64, None is returned instead. If the given list
/// is empty, 0 is returned.
pub fn iaverage<I, V>(iter: I) -> Option<u64>
where
    I: Iterator<Item = V>,
    V: Into<u64>,
{
    use rug::ops::DivRounding;

    let mut denominator: u64 = 0;
    let mut result = rug::Integer::new();
    for v in iter {
        denominator += 1;
        result += rug::Integer::from(v.into());
    }
    if denominator == 0 {
        return Some(0);
    }
    result.div_floor(rug::Integer::from(denominator)).to_u64()
}

fn istddev_impl<I, V>(iter: I, is_population: bool) -> Option<u64>
where
    I: Iterator<Item = V>,
    V: Into<u64>,
{
    use rug::ops::DivRounding;
    use rug::ops::Pow;

    let items: Vec<u64> = iter.map(|v| v.into()).collect();
    if items.len() == 0 {
        return Some(0);
    }

    let a = iaverage(items.iter().cloned());
    if a.is_none() {
        return None;
    }
    let average: u64 = a.unwrap();

    let mut stddev = rug::Integer::new();
    for item in &items {
        stddev += (rug::Integer::from(*item) - rug::Integer::from(average)).pow(2);
    }
    stddev
        .div_floor(rug::Integer::from(match is_population {
            false => items.len() - 1,
            true => items.len(),
        } as u64))
        .sqrt()
        .to_u64()
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

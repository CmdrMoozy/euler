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

use math::prime::{Factorization, PrimeSieve};
use std::cmp;
use util::error::*;

/// This function returns the number of ways r objects can be drawn from n
/// objects, assuming that order doesn't make any difference.
pub fn combinations(n: u64, r: u64) -> Result<u64> {
    // We cannot draw r objects from n objects of r > n.
    if r > n {
        bail!("Undefined combination '{} choose {}'", n, r);
    }

    // The number of ways r objects can be drawn from n objects, assuming order
    // doesn't matter, is:
    //
    //   n! / ((n-r)! * r!)
    //
    // Because factorials get large very fast, we are going to "cancel" factors as
    // much as possible. If we define pi(a..b) = a * a + 1 * ... * b (for a <= b),
    // and if we let x = max(n - r, r) and y = min(n - r, r), we only need to
    // compute:
    //
    //   pi(x+1..n) / pi(1..y)

    let x: u64 = cmp::max(n - r, r);
    let y: u64 = cmp::min(n - r, r);

    let sieve = PrimeSieve::new(n + 1);
    let num = Factorization::new_from_iter(x + 1..n + 1, &sieve, None)?;
    let den = Factorization::new_from_iter(1..y + 1, &sieve, None)?;

    let (num, den) = Factorization::reduce(num, den);
    Ok(
        num.iter()
            .map(|pair| pair.0.pow(*pair.1 as u32))
            .fold(1, |acc, v| acc * v)
            / den.iter()
                .map(|pair| pair.0.pow(*pair.1 as u32))
                .fold(1, |acc, v| acc * v),
    )
}

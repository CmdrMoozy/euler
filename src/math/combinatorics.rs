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

use math::prime::{Factorization, Sieve};
use std::cmp;
use ::util::error::*;

/// This function returns the number of ways r objects can be drawn from n
/// objects, assuming that order doesn't make any difference.
pub fn combinations(n: u64, r: u64) -> EulerResult<u64> {
    // We cannot draw r objects from n objects of r > n.
    if r > n {
        return Err(EulerError::new(ErrorKind::InvalidArgument {
            message: "Undefined combination.".to_owned(),
        }));
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

    let sieve = Sieve::new(n + 1);
    let num = try!(Factorization::new_from_iter(x + 1..n + 1, &sieve, None));
    let den = try!(Factorization::new_from_iter(1..y + 1, &sieve, None));

    let (num, den) = Factorization::reduce(num, den);
    Ok(num.iter().map(|pair| pair.0.pow(*pair.1 as u32)).fold(1, |acc, v| acc * v) /
       den.iter().map(|pair| pair.0.pow(*pair.1 as u32)).fold(1, |acc, v| acc * v))
}

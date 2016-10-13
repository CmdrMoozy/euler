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

/// This function computes the integer square root of the given number. That
/// is, isqrt(x) is equivalent to floor(sqrt(x)). Note that, because we do not
/// use any floating-point arithmetic for this result, it is faster than the
/// built-in sqrt() function.
///
/// We implement the algorithm using a simple binary search. Note, though, that
/// the initial midpoint chosen works better for large n than small n.
pub fn isqrt(n: u64) -> u64 {
    if n <= 1 {
        return n;
    }

    let mut a: u64 = 1;
    let mut b: u64 = (n >> 6) + 16;
    while {
        let m: u64 = (a + b) >> 1;
        if (m * m) > n {
            b = m - 1;
        } else {
            a = m + 1;
        }

        b >= a
    } {}

    a - 1
}

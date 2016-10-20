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

/// Returns a Pythagorean triple (a, b, c) which satisfies a^2 + b^2 = c^2,
/// given positive integers m, n, and k satisfying m > n, m and n are coprime,
/// and m and n are not both odd. Note that these conditions are not checked
/// explicitly; it is up to the caller to adhere to these preconditions, or the
/// returned triple will not be primitive (all entries in the result can be
/// divided by a common factor, and the result will be a primitive Pythagorean
/// triple).
///
/// This function implements Euclid's formula for generating all triples
/// uniquely. For details, see:
/// https://en.wikipedia.org/wiki/Pythagorean_triple#Generating_a_triple
pub fn get_pythagorean_triple(m: u64, n: u64, k: u64) -> (u64, u64, u64) {
    (k * (m * m - n * n), k * 2 * m * n, k * (m * m + n * n))
}

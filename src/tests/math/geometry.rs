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

use ::math::geometry::*;

#[test]
fn test_get_pythagorean_triple() {
    for m in 1..6 {
        for n in 1..m {
            for k in 1..6 {
                let (a, b, c) = get_pythagorean_triple(m, n, k);
                assert_eq!(a * a + b * b, c * c);
            }
        }
    }
}

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

use ::dsc::triangle::*;

#[test]
fn test_get_largest_path_sum_empty_triangle() {
    let triangle: Triangle<u64> = Triangle::new(0);
    assert_eq!(0, triangle.get_largest_path_sum().unwrap());
}

#[test]
fn test_get_largest_path_sum_single_cell() {
    let mut triangle: Triangle<u64> = Triangle::new(1);
    triangle.set(0, 0, 12345).unwrap();
    assert_eq!(12345, triangle.get_largest_path_sum().unwrap());
}

#[test]
fn test_get_largest_path_sum_multiple_rows() {
    let mut triangle: Triangle<u64> = Triangle::new(4);

    triangle.set(0, 0, 75).unwrap();
    triangle.set(1, 0, 95).unwrap();
    triangle.set(1, 1, 64).unwrap();
    triangle.set(2, 0, 17).unwrap();
    triangle.set(2, 1, 47).unwrap();
    triangle.set(2, 2, 82).unwrap();
    triangle.set(3, 0, 18).unwrap();
    triangle.set(3, 1, 35).unwrap();
    triangle.set(3, 2, 87).unwrap();
    triangle.set(3, 3, 10).unwrap();

    assert_eq!(308, triangle.get_largest_path_sum().unwrap());
}

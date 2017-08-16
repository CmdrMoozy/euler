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

use dsc::triangle::*;

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

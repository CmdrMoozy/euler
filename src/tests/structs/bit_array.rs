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

use ::structs::bit_array::*;

#[test]
fn test_construction() {
    let a = BitArray::new(80, FillPolicy::Set);
    assert_eq!(a.len(), 80);
    assert_eq!(a.len_bytes(), 10);
    assert_eq!(a.len_chunks(), 2);
    assert!(a.all());
}

#[test]
fn test_resize() {
    let mut a = BitArray::new(80, FillPolicy::Set);
    a.resize(40, FillPolicy::Clear);
    assert_eq!(a.len(), 40);
    assert_eq!(a.len_bytes(), 5);
    assert_eq!(a.len_chunks(), 1);
    assert!(a.none());
}

#[test]
fn test_set_all_and_reset_all() {
    let mut a = BitArray::new(80, FillPolicy::Clear);
    assert!(a.none());
    a.set_all();
    assert!(a.all());
    a.reset_all();
    assert!(a.none());
}

#[test]
fn test_negate_all() {
    let mut a = BitArray::new(80, FillPolicy::Clear);
    assert!(a.none());
    a.negate_all();
    assert!(a.all());
    a.negate_all();
    assert!(a.none());
}

#[test]
fn test_get_set_and_negate_all() {
    let mut a = BitArray::new(80, FillPolicy::Clear);
    for i in 0..80 {
        a.set(i, i & 1 != 0);
        assert_eq!(a.get(i).unwrap(), i & 1 != 0);
    }
    a.negate_all();
    for i in 0..80 {
        assert_eq!(a.get(i).unwrap(), i & 1 == 0);
    }
}

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

use structs::bit_array::*;

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

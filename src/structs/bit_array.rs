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


use math::division;
use std::iter::Iterator;
use std::vec::Vec;

pub enum FillPolicy {
    Clear,
    PreserveClear,
    PreserveSet,
    Set,
}

pub type Chunk = u64;

const CHUNK_BIT: usize = 64;
const ALL_CHUNK: Chunk = !(0 as Chunk);

/// Returns the index of the given bit as a (chunk index, bit offset) tuple.
fn bit_to_chunk_index(index: usize) -> (usize, usize) { division::divide(index, CHUNK_BIT) }

fn get_minimum_chunk_size(size: usize) -> usize {
    if size == 0 {
        return 0;
    }
    bit_to_chunk_index(size - 1).0 + 1
}

#[derive(Clone)]
pub struct BitArray {
    bits: usize,
    data: Vec<Chunk>,
}

impl BitArray {
    pub fn new(size: usize, policy: FillPolicy) -> BitArray {
        let mut arr = BitArray {
            bits: 0,
            data: Vec::new(),
        };
        arr.resize(size, policy);
        arr
    }

    pub fn len(&self) -> usize { self.bits }

    pub fn len_bytes(&self) -> usize { self.len() / 8 }

    pub fn len_chunks(&self) -> usize { self.data.len() }

    pub fn resize(&mut self, size: usize, policy: FillPolicy) {
        if size == 0 {
            self.bits = 0;
            self.data = Vec::new();
            return;
        }

        let new_chunk_size = get_minimum_chunk_size(size);
        let mut new_data: Vec<Chunk> = vec![0; new_chunk_size];

        let fill: Chunk = match policy {
            FillPolicy::Clear => 0,
            FillPolicy::PreserveClear => 0,
            _ => !(0 as Chunk),
        };

        for i in 0..new_chunk_size {
            *new_data.get_mut(i).unwrap() = match policy {
                FillPolicy::Clear => fill,
                FillPolicy::Set => fill,
                _ => {
                    let chunk = self.get_chunk(i).unwrap_or((0, 0));
                    (chunk.0 & chunk.1) | (fill & !chunk.1)
                },
            };
        }

        self.bits = size;
        self.data = new_data;
    }

    pub fn as_chunk_slice(&self) -> &[Chunk] { self.data.as_slice() }

    pub fn iter(&self) -> Iter { Iter::new(self) }

    /// Returns the chunk at the given position, along with a mask indicating
    /// which bits in the chunk are actually members of this bit array. If the
    /// given position is out of bounds, None is returned instead.
    pub fn get_chunk(&self, index: usize) -> Option<(Chunk, Chunk)> {
        let mut mask: Chunk = !(0 as Chunk);
        if index == self.data.len() - 1 {
            let rem_bits = self.bits % CHUNK_BIT;
            let last_chunk_bits = match rem_bits {
                0 => CHUNK_BIT,
                _ => rem_bits,
            };
            mask = mask << (CHUNK_BIT - last_chunk_bits) >> (CHUNK_BIT - last_chunk_bits);
        }

        self.data.get(index).map(|c| (*c, mask))
    }

    /// Access the bit at the given position, and return its value. If the
    /// given position is out-of-bounds, None is returned.
    pub fn get(&self, index: usize) -> Option<bool> {
        if index >= self.bits {
            return None;
        }
        let chunk_index = bit_to_chunk_index(index);
        Some(self.data.get(chunk_index.0).unwrap() & ((1 as Chunk) << chunk_index.1) != 0)
    }

    /// Sets the value of the bit at the given index to the given value. Panics
    /// if the given index is out of bounds.
    pub fn set(&mut self, index: usize, value: bool) {
        let chunk_index = bit_to_chunk_index(index);
        let mask: Chunk = (1 as Chunk) << chunk_index.1;
        let chunk: &mut Chunk = self.data.get_mut(chunk_index.0).unwrap();
        *chunk = match value {
            true => *chunk | mask,
            false => *chunk & !mask,
        }
    }

    /// Negate the value of the single bit at the given index. Like set(),
    /// panics if the given index is out of bounds.
    pub fn negate(&mut self, index: usize) {
        let value: bool = !self.get(index).unwrap();
        self.set(index, value);
    }

    pub fn set_all(&mut self) {
        for c in self.data.iter_mut() {
            *c = ALL_CHUNK;
        }
    }

    pub fn reset_all(&mut self) {
        for c in self.data.iter_mut() {
            *c = 0;
        }
    }

    pub fn negate_all(&mut self) {
        for c in self.data.iter_mut() {
            *c = !*c;
        }
    }

    /// Returns true if all bits are 1.
    pub fn all(&self) -> bool {
        for i in 0..self.data.len() {
            let chunk = self.get_chunk(i).unwrap();
            if (chunk.0 & chunk.1) != (ALL_CHUNK & chunk.1) {
                return false;
            }
        }
        true
    }

    /// Returns true if all bits are 0.
    pub fn none(&self) -> bool { !self.all() }
}

pub struct Iter<'a> {
    array: &'a BitArray,
    forward_index: usize,
    reverse_index: usize,
}

impl<'a> Iter<'a> {
    fn new(array: &'a BitArray) -> Iter<'a> {
        Iter {
            array: array,
            forward_index: 0,
            reverse_index: array.len(),
        }
    }
}

impl<'a> Iterator for Iter<'a> {
    type Item = (usize, bool);

    fn next(&mut self) -> Option<Self::Item> {
        let index = self.forward_index;
        let item = self.array.get(self.forward_index);
        self.forward_index += 1;
        item.map(|v| (index, v))
    }
}

impl<'a> DoubleEndedIterator for Iter<'a> {
    fn next_back(&mut self) -> Option<Self::Item> {
        if self.reverse_index == 0 {
            return None;
        }

        let index = self.reverse_index - 1;
        let item = self.array.get(self.reverse_index - 1);
        self.reverse_index -= 1;
        item.map(|v| (index, v))
    }
}

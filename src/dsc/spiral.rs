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

use std::collections::HashMap;
use util::error::*;

/// Represents the address of a single value in a Spiral. The center value,
/// which is always 1, is
/// considered to be at address (0, 0). The x address increases for values to
/// the right, and
/// decreases for values to the left. The y address increases for values above,
/// and decreases for
/// values below.
#[derive(Clone, Hash, PartialEq, Eq)]
pub struct Address {
    pub x: i64,
    pub y: i64,
}

/// Returns the size of the square spiral's edges (the number of values on the
/// outermost sides of the spiral) given the diagonal size of the spiral (the
/// number of values, excluding the origin, on the way to each corner of the
/// spiral). For example, if we call this function f, f(0) = 1, f(1) = 3, and
/// so forth.
pub fn diagonal_size_to_edge_size(diagonal_size: i64) -> i64 { 1 + (diagonal_size.abs() * 2) }

/// Spiral denotes a grid of numbers, where the center value is 1, and each
/// other address is filled
/// in with consecutive integers in clockwise order, starting with the cell
/// immediately to the
/// right of cell (0, 0) (the origin).
///
/// This data structure is lazy - that is, the spiral is functionally infinite,
/// but its contents
/// are only computed when retrieved. As such, accessor functions generally
/// require a mutable
/// borrow of the data structure itself, so the new values can be computed and
/// filled in.
pub struct Spiral {
    contents: HashMap<Address, u64>,
}

impl Spiral {
    pub fn new() -> Spiral { Spiral { contents: HashMap::new() } }

    pub fn get_diagonal_value(&mut self, addr: &Address) -> EulerResult<u64> {
        if addr.x.abs() != addr.y.abs() {
            return Err(EulerError::new(ErrorKind::InvalidArgument {
                message: "Non-diagonal address passed to diagonal_value_at.".to_owned(),
            }));
        }

        if addr.x == 0 && addr.y == 0 {
            return Ok(1);
        }

        if let Some(v) = self.contents.get(addr) {
            return Ok(*v);
        }

        // We need the size of the edges, because the value at this cell is the value
        // of the
        // previous cell along the same diagonal, plus the length of the sides
        // in-between.
        let edge_size = diagonal_size_to_edge_size(addr.x);

        // Compute the value of the cell on the diagonal in the *first quadrant* that's
        // one cell
        // closer to the origin than the desired value. From this cell, we need to add
        // some number
        // of extra side lengths (at least one) to get to the next-biggest spiral
        // perimeter which
        // contains the desired cell.
        let previous_diagonal = try!(self.get_diagonal_value(&Address {
            x: addr.x.abs() - 1,
            y: addr.y.abs() - 1,
        }));

        // Cache all the diagonal values at this new diagonal size, and then return the
        // relevant one.
        let diagonal: i64 = addr.x.abs();
        for new_diagonal in vec![(diagonal, -diagonal, 1),
                                 (-diagonal, -diagonal, 2),
                                 (-diagonal, diagonal, 3),
                                 (diagonal, diagonal, 4)] {
            let value: u64 = previous_diagonal + (edge_size as u64 - 1) * new_diagonal.2 as u64;
            self.contents.insert(Address {
                                     x: new_diagonal.0,
                                     y: new_diagonal.1,
                                 },
                                 value);
        }

        Ok(*self.contents.get(&addr).unwrap())
    }
}
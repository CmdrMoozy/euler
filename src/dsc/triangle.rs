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

use std::fmt::Debug;
use std::ops::Add;
use util::error::{ErrorKind, EulerError, EulerResult};

#[derive(Clone, Debug)]
pub struct Triangle<T: Add<T, Output = T> + Clone + Debug + Default + PartialOrd> {
    values: Vec<Vec<T>>,
}

impl<T: Add<T, Output = T> + Clone + Debug + Default + PartialOrd> Triangle<T> {
    pub fn new(height: usize) -> Triangle<T> {
        let mut values: Vec<Vec<T>> = vec![];
        for row in 0..height {
            // The nth triangle number T(n) (the total number of cells in a triangle of
            // height n) is: (n * (n + 1)) / 2. So, the number of cells solely in the
            // bottom row of a triangle of height n is: T(n) - T(n-1). Which is:
            //
            //   (n * (n + 1)) / 2 - ((n - 1) * ((n - 1) + 1)) / 2
            // = (n * (n + 1) - n * (n - 1)) / 2
            // = n * (n + 1 - n + 1) / 2
            // = n
            values.push(vec![T::default(); row + 1]);
        }

        Triangle { values: values }
    }

    pub fn get_height(&self) -> usize { self.values.len() }

    fn is_in_bounds(&self, row: usize, col: usize) -> bool {
        (row < self.get_height()) && (col <= row)
    }

    /// Returns the value stored in the Triangle cell at the given coordinates.
    /// The row is a 0-indexed offset from the top row of the triangle, and the
    /// col is a 0-indexed offset from the left-most cell of that row.
    pub fn get(&self, row: usize, col: usize) -> EulerResult<T> {
        match self.is_in_bounds(row, col) {
            false => {
                Err(EulerError::new(ErrorKind::InvalidArgument {
                    message: "Index out of bounds".to_owned(),
                }))
            },
            true => Ok(self.values[row][col].clone()),
        }
    }

    /// Sets the value stored in the Triangle cell at the given coordinates.
    /// The row is a 0-indexed offset from the top row of the triangle, and the
    /// col is a 0-indexed offset from the left-most cell of that row.
    pub fn set(&mut self, row: usize, col: usize, value: T) -> EulerResult<()> {
        match self.is_in_bounds(row, col) {
            false => {
                Err(EulerError::new(ErrorKind::InvalidArgument {
                    message: "Index out of bounds".to_owned(),
                }))
            },
            true => {
                self.values[row][col] = value;
                Ok(())
            },
        }
    }

    fn get_left_child_value(&self, row: usize, col: usize) -> EulerResult<T> {
        self.get(row + 1, col)
    }

    fn get_right_child_value(&self, row: usize, col: usize) -> EulerResult<T> {
        self.get(row + 1, col + 1)
    }

    /// This function returns the largest possible sum of a path through the
    /// cells of the triangle, from top to bottom. This function operates in
    /// O(h^2) time, where h is the height of the triangle.
    pub fn get_largest_path_sum(&self) -> EulerResult<T> {
        if self.get_height() == 0 {
            return Ok(T::default());
        }

        let mut triangle = self.clone();
        // For each row from the next-to-last to the first...
        for row in (0..(triangle.get_height() - 1)).rev() {
            // For each column in this row...
            for col in 0..(row + 1) {
                let current_value = try!(triangle.get(row, col));
                let left_child = try!(triangle.get_left_child_value(row, col));
                let right_child = try!(triangle.get_right_child_value(row, col));

                try!(triangle.set(row,
                                  col,
                                  current_value +
                                  match left_child < right_child {
                                      false => left_child,
                                      true => right_child,
                                  }));
            }
        }

        triangle.get(0, 0)
    }
}

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

use std::fmt::Debug;
use std::ops::Add;
use util::error::*;

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
    pub fn get(&self, row: usize, col: usize) -> Result<T> {
        match self.is_in_bounds(row, col) {
            false => bail!("Index out of bounds"),
            true => Ok(self.values[row][col].clone()),
        }
    }

    /// Sets the value stored in the Triangle cell at the given coordinates.
    /// The row is a 0-indexed offset from the top row of the triangle, and the
    /// col is a 0-indexed offset from the left-most cell of that row.
    pub fn set(&mut self, row: usize, col: usize, value: T) -> Result<()> {
        match self.is_in_bounds(row, col) {
            false => bail!("Index out of bounds"),
            true => {
                self.values[row][col] = value;
                Ok(())
            },
        }
    }

    fn get_left_child_value(&self, row: usize, col: usize) -> Result<T> { self.get(row + 1, col) }

    fn get_right_child_value(&self, row: usize, col: usize) -> Result<T> {
        self.get(row + 1, col + 1)
    }

    /// This function returns the largest possible sum of a path through the
    /// cells of the triangle, from top to bottom. This function operates in
    /// O(h^2) time, where h is the height of the triangle.
    pub fn get_largest_path_sum(&self) -> Result<T> {
        if self.get_height() == 0 {
            return Ok(T::default());
        }

        let mut triangle = self.clone();
        // For each row from the next-to-last to the first...
        for row in (0..(triangle.get_height() - 1)).rev() {
            // For each column in this row...
            for col in 0..(row + 1) {
                let current_value = triangle.get(row, col)?;
                let left_child = triangle.get_left_child_value(row, col)?;
                let right_child = triangle.get_right_child_value(row, col)?;

                triangle.set(row,
                         col,
                         current_value +
                         match left_child < right_child {
                             false => left_child,
                             true => right_child,
                         })?;
            }
        }

        triangle.get(0, 0)
    }
}

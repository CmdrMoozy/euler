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

// By counting carefully it can be seen that a rectangular grid measuring 3 by 2
// contains eighteen rectangles:
//
//      _ _ _    _ _ _    _ _ _
//     |x|_|_|  |x|x|_|  |x|x|x|
//     |_|_|_|  |_|_|_|  |_|_|_|
//
//        6        4        2
//      _ _ _    _ _ _    _ _ _
//     |x|_|_|  |x|x|_|  |x|x|x|
//     |x|_|_|  |x|x|_|  |x|x|x|
//
//        3        2        1
//
// Although there exists no rectangular grid that contains exactly two million
// rectangles, find the area of the grid with the nearest solution.

use euler::math::sequence::sequence_search;
use euler::util::error::*;
use euler::util::problem::*;
use lazy_static::lazy_static;
use std::{cmp, fmt};

#[derive(Clone, Copy)]
struct Grid {
    w: usize,
    h: usize,
}

impl Grid {
    fn new(w: usize, h: usize) -> Grid {
        Grid {
            w: cmp::min(w, h),
            h: cmp::max(w, h),
        }
    }

    fn area(&self) -> usize {
        self.w * self.h
    }
}

impl fmt::Display for Grid {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}x{}", self.w, self.h)
    }
}

fn count_rectangles(grid: Grid) -> usize {
    let mut count = 0_usize;
    for shape_w in 1..grid.w + 1 {
        for shape_h in 1..grid.h + 1 {
            count += (grid.w - shape_w + 1) * (grid.h - shape_h + 1);
        }
    }
    count
}

const TARGET: usize = 2000000;

fn target_distance(count: usize) -> usize {
    cmp::max(count, TARGET) - cmp::min(count, TARGET)
}

lazy_static! {
    // The largest dimension we need to worry about is a grid with width 1, and
    // the other dimension being such that we have as close to (but not less
    // than) 2,000,000 rectangles within it. Precompute this quickly using
    // binary search, to give us a bound for the real loop.
    //
    // Add one, because loop bounds are exclusive by default.
    static ref UPPER_BOUND: usize = sequence_search(1, TARGET, |h| count_rectangles(Grid::new(1, h))).0 + 1;
}

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
        let mut closest_grid = Grid::new(1, 1);
        let mut closest_count = 0_usize;
        for w in 1..(*UPPER_BOUND) {
            // Symmetric grids always have the same number of rectangles. So,
            // e.g., we don't need to evaluate both (2,3) and (3,2). So, start
            // this loop with the height equal to the width.
            for h in w..(*UPPER_BOUND) {
                let grid = Grid::new(w, h);
                let count = count_rectangles(grid);
                if target_distance(count) < target_distance(closest_count) {
                    closest_grid = grid;
                    closest_count = count;
                }
            }
        }

        Ok(ProblemAnswer {
            actual: closest_grid.area(),
            expected: 2772,
        })
    });
}

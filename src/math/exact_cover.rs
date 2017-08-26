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

use std::cmp;

/// Node represents a single node or cell in an exact cover problem.
#[derive(Clone)]
struct Node {
    /// A node is "uncovered" if it should be considered linked to the
    /// neighbors above and below it.
    pub is_uncovered: bool,
    /// A node contains true if it is "filled in", or false if it is not. The
    /// solution to exact cover problems is a list of rows such that combined
    /// their nodes "fill in" each column exactly once.
    pub data: bool,
}

impl Default for Node {
    fn default() -> Self {
        Node {
            is_uncovered: true,
            data: false,
        }
    }
}

/// Header denotes an entire column. This structure doesn't contain problem
/// data, but instead keeps track of some metadata the algorithm relies upon.
#[derive(Clone)]
struct Header {
    /// A header or column is "uncovered" if it should be considered linked to
    /// its left and right neighbors.
    pub is_uncovered: bool,
    /// Count is intended to contain the number of "1 nodes" currently
    /// uncovered in this column. This is updated during the cover() and
    /// uncover() operations.
    pub count: usize,
}

impl Header {
    pub fn new(rows: usize) -> Self {
        Header {
            is_uncovered: true,
            count: rows,
        }
    }
}

/// A Coordinate describes a single node in an ExactCover problem.
#[derive(Clone, Copy, Debug, Eq, Ord, PartialEq, PartialOrd)]
pub struct Coordinate {
    pub col: usize,
    pub row: usize,
}

impl Default for Coordinate {
    fn default() -> Self {
        Coordinate {
            col: usize::max_value(),
            row: usize::max_value(),
        }
    }
}

/// ExactCover implements a structure to solve exact cover problems.
///
/// We utilize Knuth's Algorithm DLX, described in his paper "P159 Dancing
/// links", which can be found here:
/// http://www-cs-faculty.stanford.edu/~uno/preprints.html
///
/// Notably, though, this implementation uses vectors instead of linked lists.
/// Generally this should be faster, but much less space efficient. More
/// importantly, perhaps, circularly-doubly-linked-lists are particularly hard
/// to represent without unsafe code in Rust.
///
/// More resources:
/// http://en.wikipedia.org/wiki/Exact_cover
/// http://en.wikipedia.org/wiki/Knuth%27s_Algorithm_X
/// http://en.wikipedia.org/wiki/Dancing_Links
pub struct ExactCover {
    cols: Vec<Header>,
    nodes: Vec<Vec<Node>>,
    solutions: Vec<Vec<Coordinate>>,
}

impl ExactCover {
    /// Construct a new ExactCover problem with the given number of rows and
    /// columns.
    pub fn new(cols: usize, rows: usize) -> ExactCover {
        ExactCover {
            cols: vec![Header::new(rows); cols],
            nodes: vec![vec![Node::default(); rows]; cols],
            solutions: vec![],
        }
    }

    /// This function returns the total number of rows this structure contains.
    pub fn row_len(&self) -> usize { self.nodes.first().map_or(0, |c| c.len()) }

    /// This function returns the total number of columns this structure
    /// contains.
    pub fn col_len(&self) -> usize { self.cols.len() }

    /// This function returns the data from the node in the given position. The
    /// return type is not None unless the given coordinate is out-of-bounds.
    pub fn get(&self, col: usize, row: usize) -> Option<bool> {
        match self.nodes.get(col) {
            None => None,
            Some(col) => match col.get(row) {
                None => None,
                Some(node) => Some(node.data),
            },
        }
    }

    /// This function sets the data in the node at the given coordinate to the
    /// given value. This function returns None only if the given coordinate is
    /// out-of-bounds.
    pub fn set(&mut self, col: usize, row: usize, data: bool) -> Option<()> {
        if let Some(col) = self.nodes.get_mut(col) {
            if let Some(node) = col.get_mut(row) {
                node.data = data;
                return Some(());
            }
        }
        None
    }

    /// This function returns the given column's count. That is, the number of
    /// uncovered "1 nodes" in that column. This function returns None only if
    /// the given column index is out-of-bounds.
    pub fn col_count(&self, col: usize) -> Option<usize> { self.cols.get(col).map(|c| c.count) }

    /// This function clears any previously-computed solutions, and solves the
    /// problem again. This function will find *all* possible solutions if
    /// maximum_solutions is None, but can also be told to stop after finding a
    /// given number of solutions (1 is a typical value).
    pub fn solve(&mut self, maximum_solutions: Option<usize>) {
        self.solutions.clear();
        if self.row_len() == 0 || self.col_len() == 0 {
            return;
        }
        self.search(0, vec![], maximum_solutions);
    }

    /// This function returns the previously computed solutions to this
    /// problem. The returned structure is a list of solutions, each of which
    /// is the full list of "1 nodes" which make up the exact cover problem.
    /// For any node in the returned list, *all other nodes in the same row*
    /// are also included, by definition.
    pub fn get_solutions(&self) -> &Vec<Vec<Coordinate>> { &self.solutions }

    /// This function adds the given solution to this structure's list of
    /// solutions.
    ///
    /// Interestingly, even though the given Vec has the same type as our list
    /// of solutions, it is incomplete. The given Vec should contain one node
    /// per row. However, the full solution is *the list of all "1 nodes" in
    /// the rows containing the given nodes*. So, we need to expand the given
    /// Vec before storing the solution.
    fn push_solution(&mut self, o: Vec<Coordinate>) {
        let mut solution: Vec<Coordinate> = vec![];
        for coordinate in o.into_iter() {
            for col in 0..self.col_len() {
                if self.nodes[col][coordinate.row].data {
                    solution.push(Coordinate {
                        col: col,
                        row: coordinate.row,
                    });
                }
            }
        }
        self.solutions.push(solution);
    }

    /// This is a helper function which selects the next column we should cover
    /// in search(). We try to pick the lowest-count column closest to the root
    /// node in the list, as per Knuth's "Dancing Links", pp. 6. This slightly
    /// complicated selection is done to reduce branching in search().
    fn select_column(&self) -> Option<usize> {
        self.cols
            .iter()
            .enumerate()
            .filter(|idx_col| idx_col.1.is_uncovered)
            .min_by_key(|idx_col| idx_col.1.count)
            .map(|idx_col| idx_col.0)
    }

    /// This function performs a "cover" operation on the given column. This
    /// means, we temporarily remove the column from the list of available
    /// columns, and we also cover any "1 nodes" on the same row as "1 nodes"
    /// in this column. If this column is already covered, or the given index
    /// is out-of-bounds, then no action is taken (although this most likely
    /// indicates a logic error in the implementation).
    fn cover(&mut self, col: usize) {
        // If the column is already covered, or doesn't exist, do nothing.
        if self.cols.get(col).map_or(true, |c| !c.is_uncovered) {
            return;
        }

        // Cover this column.
        self.cols[col].is_uncovered = false;

        // For each node in this column...
        for row in 0..self.row_len() {
            // If this node is covered, or isn't a "1 node", skip it.
            if !(self.nodes[col][row].is_uncovered && self.nodes[col][row].data) {
                continue;
            }

            // For each other node on this node's row...
            for other_col in 0..self.col_len() {
                // Skip the node in the original column, or nodes which are not "1 nodes".
                if other_col == col || !self.nodes[other_col][row].data {
                    continue;
                }

                // Cover this node, and update the column's count.
                self.nodes[other_col][row].is_uncovered = false;
                self.cols[other_col].count -= 1;
            }
        }
    }

    /// This function performs an "uncover" operation on the given column. This
    /// means, we add the column back to the list of available columns, and we
    /// also uncover any "1 nodes" on the same row as "1 nodes" in this column.
    /// If this column is already uncovered, or the given index is
    /// out-of-bounds, then no action is taken (although this most likely
    /// indicates a logic error in the implementation).
    fn uncover(&mut self, col: usize) {
        // If the column is already uncovered, or doesn't exist, do nothing.
        if self.cols.get(col).map_or(true, |c| c.is_uncovered) {
            return;
        }

        // For each node in this column...
        for row in (0..self.row_len()).rev() {
            // If this node is covered, or isn't a "1 node", skip it.
            if !(self.nodes[col][row].is_uncovered && self.nodes[col][row].data) {
                continue;
            }

            // For each other node on this node's row...
            for other_col in 0..self.col_len() {
                // Skip the node in the original column, or nodes which are not "1 nodes".
                if other_col == col || !self.nodes[other_col][row].data {
                    continue;
                }

                // Uncover this node, and update the column's count.
                self.nodes[other_col][row].is_uncovered = true;
                self.cols[other_col].count += 1;
            }
        }

        // Uncover this column.
        self.cols[col].is_uncovered = true;
    }

    /// This is the function which really implements the main body of Knuth's
    /// Algorithm DLX, which finds solutions to exact cover problems. See
    /// Knuth's "Dancing Links", pp. 5-8 for more details. Note that solutions
    /// we find are added directly to self.solutions, so that structure should
    /// generally be cleared before the initial call to this recursive function.
    ///
    /// Also, it's worth noting that the first non-recursive call to this
    /// function should be search(0, vec![], maximum_solutions).
    ///
    /// This function returns its current solution state, o, when it exits.
    /// This is used to pass information back up the recursive call stack, but
    /// the returned value is generally not useful for the initial
    /// non-recursive call.
    fn search(
        &mut self,
        k: usize,
        mut o: Vec<Coordinate>,
        maximum_solutions: Option<usize>,
    ) -> Vec<Coordinate> {
        // If we have found enough solutions, stop here.
        if let Some(max) = maximum_solutions {
            if self.solutions.len() >= max {
                return o;
            }
        }

        // Select a column, c, and cover it. If there was no uncovered column to
        // select, then we have found a solution, so return.
        let mut c = match self.select_column() {
            None => {
                // The current solution is described the first k elements of o.
                self.push_solution(o.iter().cloned().take(k).collect());
                return o;
            },
            Some(c) => c,
        };
        self.cover(c);

        for mut r in 0..self.nodes[c].len() {
            // If this node is covered, or isn't a "1 node", skip it.
            if !(self.nodes[c][r].is_uncovered && self.nodes[c][r].data) {
                continue;
            }

            // Add this coordinate to the current solution state.
            let new_len = cmp::max(k + 1, o.len());
            o.resize(new_len, Coordinate::default());
            o[k].col = c;
            o[k].row = r;

            // For each other node on this row, moving right...
            let mut other_c = (c + 1) % self.col_len();
            while other_c != c {
                // If this node is a "1 node"...
                if self.nodes[other_c][r].data {
                    // Cover the column this node belongs to.
                    self.cover(other_c);
                }

                other_c = (other_c + 1) % self.col_len();
            }

            // Search recursively.
            o = self.search(k + 1, o.clone(), maximum_solutions);

            // Set r and c to the solution coordinate in o[k].
            c = o[k].col;
            r = o[k].row;

            // For each other node on this row, moving left...
            let mut other_c = if c == 0 { self.col_len() - 1 } else { c - 1 };
            while other_c != c {
                // If this node is a "1 node"...
                if self.nodes[other_c][r].data {
                    // Uncover the column this node belongs to.
                    self.uncover(other_c);
                }

                other_c = if other_c == 0 {
                    self.col_len() - 1
                } else {
                    other_c - 1
                };
            }
        }

        self.uncover(c);
        o
    }
}

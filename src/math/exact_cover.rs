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

#[derive(Clone)]
struct Node {
    pub is_live: bool,
    pub data: bool,
}

impl Default for Node {
    fn default() -> Self {
        Node {
            is_live: true,
            data: false,
        }
    }
}

#[derive(Clone)]
struct Header {
    pub name: i64,
    pub count: usize,
}

impl Header {
    pub fn new(rows: usize) -> Self {
        Header {
            name: 0,
            count: rows,
        }
    }
}

pub struct ExactCover {
    cols: Vec<Header>,
    nodes: Vec<Vec<Node>>,
}

impl ExactCover {
    pub fn new(cols: usize, rows: usize) -> ExactCover {
        ExactCover {
            cols: vec![Header::new(rows); cols],
            nodes: vec![vec![Node::default(); rows]; cols],
        }
    }

    pub fn row_len(&self) -> usize { self.nodes.first().map_or(0, |c| c.len()) }

    pub fn col_len(&self) -> usize { self.cols.len() }

    pub fn get(&self, col: usize, row: usize) -> Option<bool> {
        match self.nodes.get(col) {
            None => None,
            Some(col) => match col.get(row) {
                None => None,
                Some(node) => Some(node.data),
            },
        }
    }

    pub fn set(&mut self, col: usize, row: usize, data: bool) -> Option<()> {
        if let Some(col) = self.nodes.get_mut(col) {
            if let Some(node) = col.get_mut(row) {
                node.data = data;
                return Some(());
            }
        }
        None
    }

    pub fn col_count(&self, col: usize) -> Option<usize> { self.cols.get(col).map(|c| c.count) }

    pub fn get_col_name(&self, col: usize) -> Option<i64> { self.cols.get(col).map(|c| c.name) }

    pub fn set_col_name(&mut self, col: usize, name: i64) -> Option<()> {
        if let Some(header) = self.cols.get_mut(col) {
            header.name = name;
            return Some(());
        }
        None
    }
}

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

use crate::structs::graph::{Direction, Graph, VertexId};
use crate::util::error::*;
use failure::bail;
use std::cmp;

#[derive(Clone, Debug)]
pub struct GridGraphWeights {
    weights: Vec<Vec<i64>>,
    minimum_weight: i64,
}

impl GridGraphWeights {
    /// Load a GridGraphWeights structure from the given text content, where
    /// each line is a row of weight values, and each line contains a
    /// comma-separated list of weights.
    pub fn new(input_text: &str) -> Result<GridGraphWeights> {
        let mut weights: Vec<Vec<i64>> = vec![];
        let mut minimum_weight: i64 = i64::max_value();
        let mut y: usize = 0;
        for line in input_text.lines() {
            let mut x: usize = 0;
            for weight in line.split(',') {
                let weight = weight.parse::<i64>()?;
                minimum_weight = cmp::min(minimum_weight, weight);

                while weights.len() <= x {
                    weights.push(vec![]);
                }
                weights[x].push(weight);
                assert!(weights[x].len() == y + 1);

                x += 1;
            }
            y += 1;
        }

        for col in &weights {
            if col.len() != y {
                bail!("Grid graph weight data contained unevenly sized columns");
            }
        }

        Ok(GridGraphWeights {
            weights: weights,
            minimum_weight: minimum_weight,
        })
    }

    pub fn get_width(&self) -> usize {
        self.weights.len()
    }
    pub fn get_height(&self) -> usize {
        self.weights.get(0).map_or(0, |col| col.len())
    }
    pub fn get_minimum_weight(&self) -> i64 {
        self.minimum_weight
    }

    pub fn get(&self, x: usize, y: usize) -> Option<i64> {
        match self.weights.get(x) {
            Some(col) => col.get(y).map(|weight| *weight),
            None => None,
        }
    }
}

pub struct GridGraph {
    graph: Graph,
    faux_start_vertex: VertexId,
    faux_end_vertex: VertexId,
    vertices: Vec<Vec<VertexId>>,
}

impl GridGraph {
    /// Construct a new GridGraph with the given weights. The directions
    /// indicate which directions of movement are allowed, horizontally or
    /// vertically, between nodes. Forward / Backward mean Right / Left and
    /// Down / Up for horizontal and vertical, respectively.
    pub fn new(
        weights: GridGraphWeights,
        horizontal_direction: Direction,
        vertical_direction: Direction,
        start: (usize, usize),
        end: (usize, usize),
    ) -> GridGraph {
        let mut graph = Graph::new();

        // We need to create a graph with one vertex for each weight, plus two extra
        // faux start / end vertices, which are used so we can translated the weights
        // to edges instead of vertices.
        let faux_start_vertex = graph.add_vertex();
        let faux_end_vertex = graph.add_vertex();
        let mut vertices: Vec<Vec<VertexId>> = vec![];
        for x in 0..weights.get_width() {
            vertices.push(vec![]);
            for _ in 0..weights.get_height() {
                vertices[x].push(graph.add_vertex());
            }
        }

        // Connect the vertices, using the directions given.
        for y in 0..weights.get_height() {
            for x in 0..weights.get_width() {
                // Make the horizontal connection.
                if x + 1 < weights.get_width() {
                    graph.connect(
                        vertices[x][y],
                        vertices[x + 1][y],
                        weights.get(x + 1, y).unwrap(),
                        horizontal_direction,
                    );
                }

                // Make the vertical connection.
                if y + 1 < weights.get_height() {
                    graph.connect(
                        vertices[x][y],
                        vertices[x][y + 1],
                        weights.get(x, y + 1).unwrap(),
                        vertical_direction,
                    );
                }
            }
        }

        // Connect the start and end nodes.
        graph.connect(
            faux_start_vertex,
            vertices[start.0][start.1],
            weights.get(start.0, start.1).unwrap(),
            Direction::Forward,
        );
        graph.connect(
            vertices[end.0][end.1],
            faux_end_vertex,
            0,
            Direction::Forward,
        );

        GridGraph {
            graph: graph,
            faux_start_vertex: faux_start_vertex,
            faux_end_vertex: faux_end_vertex,
            vertices: vertices,
        }
    }

    pub fn get_graph(&self) -> &Graph {
        &self.graph
    }

    pub fn get_start_vertex(&self) -> VertexId {
        self.faux_start_vertex
    }
    pub fn get_end_vertex(&self) -> VertexId {
        self.faux_end_vertex
    }

    pub fn get(&self, x: usize, y: usize) -> Option<VertexId> {
        match self.vertices.get(x) {
            Some(col) => col.get(y).map(|id| *id),
            None => None,
        }
    }
}

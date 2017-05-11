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

// In the 5 by 5 matrix below, the minimal path sum from the top left to bottom
// right, by only moving to the right and down, is indicated in bold red and is
// equal to 2427.
//
//     [ (131)  673   234   103    18  ]
//     [ (201) ( 96) (342)  965   150  ]
//     [  630   803  (746) (422)  111  ]
//     [  537   699   497  (121)  956  ]
//     [  805   732   524  ( 37) (331) ]
//
// Find the minimal path sum, in matrix.txt (right click and 'Save Link/Target
// As...'), a 31K text file containing an 80 by 80 matrix, from the top left to
// the bottom right by moving only right and down.

#[macro_use]
extern crate error_chain;

extern crate euler;
use self::euler::algorithm::graph::dijkstra;
use self::euler::dsc::grid_graph::{GridGraph, GridGraphWeights};
use self::euler::structs::graph::Direction;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const INPUT_MATRIX: &'static str = include_str!("00081.txt");

const EXPECTED_GRID_WIDTH: usize = 80;
const EXPECTED_GRID_HEIGHT: usize = 80;

const EXPECTED_RESULT: i64 = 427337;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<i64>> {
        let weights = GridGraphWeights::new(INPUT_MATRIX)?;
        if weights.get_width() != EXPECTED_GRID_WIDTH ||
           weights.get_height() != EXPECTED_GRID_HEIGHT {
            bail!("Loaded grid graph doesn't contain the expected number of rows or columns");
        }

        let graph = GridGraph::new(weights,
                                   Direction::Forward,
                                   Direction::Forward,
                                   (0, 0),
                                   (EXPECTED_GRID_WIDTH - 1, EXPECTED_GRID_HEIGHT - 1));

        Ok(ProblemAnswer {
            actual: dijkstra(graph.get_graph(),
                             graph.get_start_vertex(),
                             graph.get_end_vertex())
                .unwrap()
                .sum,
            expected: EXPECTED_RESULT,
        })
    });
}

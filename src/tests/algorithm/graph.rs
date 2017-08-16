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

use algorithm::graph::*;
use structs::graph::*;

const TEST_GRAPH_WIDTH: usize = 22;
const TEST_GRAPH_HEIGHT: usize = 22;

const TEST_GRAPH_START_X: usize = 2;
const TEST_GRAPH_START_Y: usize = 2;
const TEST_GRAPH_END_X: usize = 18;
const TEST_GRAPH_END_Y: usize = 18;

const TEST_GRAPH_EXPECTED_PATH_LENGTH: usize = 25;
const TEST_GRAPH_EXPECTED_PATH_SUM: i64 = 24;

struct TestGraph {
    pub graph: Graph,
    pub start_id: VertexId,
    pub end_id: VertexId,
}

impl TestGraph {
    pub fn new() -> Self { Self::default() }
}

impl Default for TestGraph {
    fn default() -> Self {
        // For testing purposes, we create a test graph which represents the following
        // grid, where each edge has a distance of 1. Movement is allowed in all
        // directions - horizontally, vertically, and diagonally. The optimal path
        // we're expecting to find is shown below as well.
        //
        // | | | | | | | | | | | | | | | | | | | | | |
        // | | | | | | | | | | | | | | | | | | | | | |
        // | | S | | | | | | | | | | | | | | | | | | |
        // | | | X | | | | | | | | | | | | | | | | | |
        // | | | | X | | | | | | | | | | | | | | | | |
        // | | | | | X | | | | | | | | | | | | | | | |
        // | | | | | | X | | | | | | | | | | | | | | |
        // | | | | | | | X X X X X X X X X | | | | | |
        // | | | | | | | | | | | | |       X | | | | |
        // | | | | | | | | | | | | |       | X | | | |
        // | | | | | | | | | | | | |       | | X | | |
        // | | | | | | | | | | | | |       | | X | | |
        // | | | | | | | | | | | | |       | | X | | |
        // | | | | |                       | | X | | |
        // | | | | |                       | | X | | |
        // | | | | |                       | | X | | |
        // | | | | | | | | | | | | | | | | | | X | | |
        // | | | | | | | | | | | | | | | | | | X | | |
        // | | | | | | | | | | | | | | | | | | E | | |
        // | | | | | | | | | | | | | | | | | | | | | |
        // | | | | | | | | | | | | | | | | | | | | | |
        // | | | | | | | | | | | | | | | | | | | | | |

        let mut graph = Graph::new();
        let mut vertices: Vec<Vec<Option<VertexId>>> = vec![];

        // Create all of the vertices for the test graph.
        for x in 0..TEST_GRAPH_WIDTH {
            vertices.push(vec![]);
            for y in 0..TEST_GRAPH_HEIGHT {
                if x >= 5 && x <= 15 && y >= 13 && y <= 15 {
                    // There are no passable nodes in the rectangular area in the range (5, 13) to
                    // (15, 15).
                    vertices[x].push(None);
                } else if x >= 13 && x <= 15 && y >= 8 && y <= 12 {
                    // There are no passable nodes in the rectangular area in the range (13, 8) to
                    // (15, 12).
                    vertices[x].push(None);
                } else {
                    vertices[x].push(Some(graph.add_vertex()));
                }
            }
        }

        // Add the edges between the vertices.
        for x in 0..TEST_GRAPH_WIDTH {
            for y in 0..TEST_GRAPH_HEIGHT {
                if let Some(vertex_id) = vertices[x][y] {
                    // Connect to the left neighbor, if any.
                    if x > 0 {
                        if let Some(neighbor_id) = vertices[x - 1][y] {
                            graph.connect(vertex_id, neighbor_id, 1, Direction::Both);
                        }
                    }

                    // Connect the below neighbor, if any.
                    if y > 0 {
                        if let Some(neighbor_id) = vertices[x][y - 1] {
                            graph.connect(vertex_id, neighbor_id, 1, Direction::Both);
                        }
                    }

                    // Connect to the left + below neighbor, if any.
                    if x > 0 && y > 0 {
                        if let Some(neighbor_id) = vertices[x - 1][y - 1] {
                            graph.connect(vertex_id, neighbor_id, 1, Direction::Both);
                        }
                    }
                }
            }
        }

        let start_id = vertices[TEST_GRAPH_START_X][TEST_GRAPH_START_Y]
            .clone()
            .unwrap();
        let end_id = vertices[TEST_GRAPH_END_X][TEST_GRAPH_END_Y]
            .clone()
            .unwrap();
        let result = TestGraph {
            graph: graph,
            start_id: start_id,
            end_id: end_id,
        };

        result
    }
}

#[test]
fn test_dijkstra() {
    let test_graph = TestGraph::new();
    let result = dijkstra(&test_graph.graph, test_graph.start_id, test_graph.end_id).unwrap();
    assert_eq!(TEST_GRAPH_EXPECTED_PATH_LENGTH, result.path.len());
    assert_eq!(TEST_GRAPH_EXPECTED_PATH_SUM, result.sum);
}

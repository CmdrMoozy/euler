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

use algorithm::graph::dijkstra;
use dsc::grid_graph::*;
use structs::graph::{Direction, VertexId};

const TEST_GRID_GRAPH: &'static str = include_str!("data/test_grid_graph.txt");

const TEST_GRID_GRAPH_VALUES: &'static [&'static [i64]] = &[
    &[131, 201, 630, 537, 805],
    &[673, 96, 803, 699, 732],
    &[234, 342, 746, 497, 524],
    &[103, 965, 422, 121, 37],
    &[18, 150, 111, 956, 331],
];

const EXPECTED_TEST_GRAPH_WIDTH: usize = 5;
const EXPECTED_TEST_GRAPH_HEIGHT: usize = 5;
const EXPECTED_TEST_GRAPH_MINIMUM_WEIGHT: i64 = 18;

const EXPECTED_MINIMAL_PATH_LENGTH: usize = 11;
const EXPECTED_MINIMAL_PATH_SUM: i64 = 2427;

#[test]
fn test_load_weights() {
    let weights = GridGraphWeights::new(TEST_GRID_GRAPH).unwrap();
    assert_eq!(EXPECTED_TEST_GRAPH_WIDTH, weights.get_width());
    assert_eq!(EXPECTED_TEST_GRAPH_HEIGHT, weights.get_height());
    assert_eq!(
        EXPECTED_TEST_GRAPH_MINIMUM_WEIGHT,
        weights.get_minimum_weight()
    );

    for x in 0..EXPECTED_TEST_GRAPH_WIDTH {
        for y in 0..EXPECTED_TEST_GRAPH_HEIGHT {
            assert_eq!(TEST_GRID_GRAPH_VALUES[x][y], weights.get(x, y).unwrap());
        }
    }
}

#[test]
fn test_grid_graph_pathfinding() {
    let weights = GridGraphWeights::new(TEST_GRID_GRAPH).unwrap();
    let graph = GridGraph::new(
        weights,
        Direction::Forward,
        Direction::Forward,
        (0, 0),
        (4, 4),
    );
    let search_result = dijkstra(
        graph.get_graph(),
        graph.get_start_vertex(),
        graph.get_end_vertex(),
    ).unwrap();
    assert_eq!(EXPECTED_MINIMAL_PATH_LENGTH, search_result.path.len());
    assert_eq!(EXPECTED_MINIMAL_PATH_SUM, search_result.sum);

    let mut expected_path: Vec<VertexId> = vec![
        (0, 0),
        (0, 1),
        (1, 1),
        (2, 1),
        (2, 2),
        (3, 2),
        (3, 3),
        (3, 4),
        (4, 4),
    ].into_iter()
        .map(|point| graph.get(point.0, point.1).unwrap())
        .collect();
    expected_path.insert(0, graph.get_start_vertex());
    expected_path.push(graph.get_end_vertex());
    assert_eq!(expected_path, search_result.path);
}

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

use crate::structs::graph::{Graph, SearchResult, VertexId};
use std::collections::HashMap;

#[derive(Clone, Copy, Eq, PartialEq)]
enum VisitState {
    Open,
    Closed,
}

struct VertexState {
    heuristic_score: i64,
    actual_score: i64,
    state: VisitState,
    previous: Option<VertexId>,
}

impl VertexState {
    pub fn with_initial_state(initial_state: VisitState) -> Self {
        VertexState {
            heuristic_score: i64::max_value(),
            actual_score: i64::max_value(),
            state: initial_state,
            previous: None,
        }
    }

    /// Set this state's absolute score. That is, update both the heuristic and
    /// actual score. This is useful, for example, in Dijkstra's algorithm,
    /// where we really only have a single score.
    pub fn set_absolute_score(&mut self, score: i64) {
        self.heuristic_score = score;
        self.actual_score = score;
    }
}

type VertexStateMap = HashMap<VertexId, VertexState>;

fn find_smallest_open(map: &VertexStateMap) -> Option<VertexId> {
    let mut current: Option<VertexId> = None;
    for entry in map {
        // If this vertex isn't in the open set, skip it.
        if entry.1.state != VisitState::Open {
            continue;
        }

        // If there is no smallest vertex yet, just use this one. Otherwise, use this
        // one if it is smaller than the current vertex.
        if current.is_none()
            || entry.1.heuristic_score < map[current.as_ref().unwrap()].heuristic_score
        {
            current = Some(*entry.0);
        }
    }
    current
}

pub fn dijkstra(graph: &Graph, start_id: VertexId, end_id: VertexId) -> Option<SearchResult> {
    // Create a state struct for each vertex, where each vertex is initially
    // unvisited (that is, "open"), and with a score of (effectively) infinity.
    let mut vertices: VertexStateMap = graph
        .all_vertices()
        .into_iter()
        .map(|id| (id, VertexState::with_initial_state(VisitState::Open)))
        .collect();

    // Set the start vertex's score to 0, and make it the current vertex.
    let mut current_id: VertexId = start_id;
    vertices.get_mut(&start_id).unwrap().set_absolute_score(0);

    loop {
        for neighbor_id in graph.get(current_id).get_neighbors().into_iter() {
            // If this neighbor has already been visited, skip it.
            if vertices.get(&neighbor_id).unwrap().state != VisitState::Open {
                continue;
            }

            // Calculate a tentative distance (current + edge) and update this neighbor's
            // distancei if the tentative distance is less than its current distance.
            let tentative: i64 = vertices.get(&current_id).unwrap().actual_score
                + graph.get(current_id).distance_to(neighbor_id).unwrap();
            if tentative < vertices.get(&neighbor_id).unwrap().actual_score {
                let neighbor: &mut VertexState = vertices.get_mut(&neighbor_id).unwrap();
                neighbor.set_absolute_score(tentative);
                neighbor.previous = Some(current_id);
            }
        }

        // Mark the current node as visited.
        vertices.get_mut(&current_id).unwrap().state = VisitState::Closed;

        // Stop if the end node has been visited.
        if vertices.get(&end_id).unwrap().state == VisitState::Closed {
            break;
        }

        // Find the unvisited node with the smallest score. Stop if there is no
        // smallest vertex, or if its score is "infinity".
        let smallest_id = find_smallest_open(&vertices);
        if smallest_id.is_none() {
            return None;
        }
        let smallest_id = smallest_id.unwrap();
        if vertices.get(&smallest_id).unwrap().actual_score == i64::max_value() {
            return None;
        }

        // Make the next smallest vertex the current vertex.
        current_id = smallest_id;
    }

    // Navigate the path back to the start from the end, and return the resulting
    // path.
    let mut result = SearchResult {
        path: vec![],
        sum: vertices.get(&end_id).unwrap().actual_score,
    };
    let mut current_path_id: VertexId = end_id;
    loop {
        result.path.push(current_path_id);
        let previous_id: Option<VertexId> = vertices.get(&current_path_id).unwrap().previous;
        if let Some(id) = previous_id {
            current_path_id = id;
        } else {
            break;
        }
    }
    result.path.reverse();
    Some(result)
}

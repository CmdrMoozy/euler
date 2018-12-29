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

use crate::structs::graph::*;

#[test]
fn test_add_vertex() {
    let mut graph = Graph::new();
    let id = graph.add_vertex();

    let all_vertices = graph.all_vertices();
    assert_eq!(1, all_vertices.len());
    assert_eq!(id, *all_vertices.first().unwrap());

    assert_eq!(id, graph.get(id).get_id());
}

#[test]
fn test_connect_forward() {
    let mut graph = Graph::new();
    let a_id = graph.add_vertex();
    let b_id = graph.add_vertex();
    graph.connect(a_id, b_id, 123, Direction::Forward);

    assert_eq!(123, graph.get(a_id).distance_to(b_id).unwrap());
    assert!(graph.get(b_id).distance_to(a_id).is_none());
}

#[test]
fn test_connect_backward() {
    let mut graph = Graph::new();
    let a_id = graph.add_vertex();
    let b_id = graph.add_vertex();
    graph.connect(a_id, b_id, 123, Direction::Backward);

    assert!(graph.get(a_id).distance_to(b_id).is_none());
    assert_eq!(123, graph.get(b_id).distance_to(a_id).unwrap());
}

#[test]
fn test_connect_both() {
    let mut graph = Graph::new();
    let a_id = graph.add_vertex();
    let b_id = graph.add_vertex();
    graph.connect(a_id, b_id, 123, Direction::Both);

    assert_eq!(123, graph.get(a_id).distance_to(b_id).unwrap());
    assert_eq!(123, graph.get(b_id).distance_to(a_id).unwrap());
}

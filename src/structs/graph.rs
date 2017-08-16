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

use std::cell::{Ref, RefCell};
use std::rc::Rc;

pub type VertexId = usize;

pub struct Vertex {
    id: VertexId,
    edges: Vec<Edge>,
}

impl Vertex {
    fn new(id: VertexId) -> Self {
        Vertex {
            id: id,
            edges: vec![],
        }
    }

    pub fn get_id(&self) -> VertexId { self.id }

    pub fn distance_to(&self, o: VertexId) -> Option<i64> {
        for e in &self.edges {
            if e.to.borrow().get_id() == o {
                return Some(e.distance);
            }
        }
        None
    }

    pub fn get_neighbors(&self) -> Vec<VertexId> {
        self.edges.iter().map(|e| e.to.borrow().id).collect()
    }

    pub fn is_connected_to(&self, o: VertexId) -> bool { self.distance_to(o).is_some() }

    fn add_edge(&mut self, edge: Edge) { self.edges.push(edge) }
}

#[derive(Clone)]
struct Edge {
    pub distance: i64,
    pub to: Rc<RefCell<Vertex>>,
}

#[derive(Clone, Copy, Eq, PartialEq)]
pub enum Direction {
    Forward,
    Backward,
    Both,
}

#[derive(Clone)]
pub struct Graph {
    vertices: Vec<Rc<RefCell<Vertex>>>,
}

impl Graph {
    pub fn new() -> Self { Self::default() }

    pub fn add_vertex(&mut self) -> VertexId {
        let id: VertexId = self.vertices.len();
        let v = Rc::new(RefCell::new(Vertex::new(id)));
        self.vertices.push(v);
        id
    }

    pub fn all_vertices(&self) -> Vec<VertexId> { (0..self.vertices.len()).collect() }

    pub fn get(&self, id: VertexId) -> Ref<Vertex> { self.vertices.get(id).unwrap().borrow() }

    pub fn connect(&self, from_id: VertexId, to_id: VertexId, distance: i64, direction: Direction) {
        let from = self.vertices.get(from_id).unwrap().clone();
        let to = self.vertices.get(to_id).unwrap().clone();

        if direction == Direction::Forward || direction == Direction::Both {
            from.borrow_mut().add_edge(Edge {
                distance: distance.clone(),
                to: to.clone(),
            });
        }

        if direction == Direction::Backward || direction == Direction::Both {
            to.borrow_mut().add_edge(Edge {
                distance: distance.clone(),
                to: from.clone(),
            });
        }
    }
}

impl Default for Graph {
    fn default() -> Self { Graph { vertices: vec![] } }
}

pub struct SearchResult {
    pub path: Vec<VertexId>,
    pub sum: i64,
}

/*
 * euler - A collection of ProjectEuler libraries, tools, and solutions.
 * Copyright (C) 2013 Axel Rasmussen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "dijkstra.h"

#include <stdexcept>
#include <unordered_map>
#include <utility>

namespace
{
struct VertexState
{
	const euler::graph::Vertex *vertex;
	int64_t distance;
	bool visited;
	VertexState *previous;

	explicit VertexState(const euler::graph::Vertex *v)
	        : vertex(v),
	          distance(INT64_MAX),
	          visited(false),
	          previous(nullptr)
	{
	}

	VertexState(const VertexState &) = default;
	VertexState &operator=(const VertexState &) = default;
};

typedef std::unordered_map<const euler::graph::Vertex *, VertexState>
        VertexStateMap_t;

euler::graph::Vertex *getOther(const euler::graph::Edge &e,
                               const euler::graph::Vertex &c)
{
	return &e.a == &c ? &e.b : &e.a;
}

VertexState *getState(const euler::graph::Vertex &v, VertexStateMap_t &map)
{
	auto it = map.find(&v);
	if(it == map.end())
		throw std::runtime_error("Vertex not present in state map.");
	return &it->second;
}

VertexState *findSmallestUnvisited(VertexStateMap_t &map)
{
	VertexState *smallest = nullptr;

	for(auto &&statePair : map)
	{
		// If this node has already been visited, skip it.
		if(statePair.second.visited)
			continue;

		// If there is no smallest vertex yet, just use this one.
		if(smallest == nullptr)
		{
			smallest = &statePair.second;
			continue;
		}

		// If this node is smaller than the current smallest, use it.
		if(statePair.second.distance < smallest->distance)
		{
			smallest = &statePair.second;
			continue;
		}
	}

	return smallest;
}
}

namespace euler
{
namespace graph
{
DijkstraResult::DijkstraResult() : path(), sum(0)
{
}

DijkstraResult dijkstra(const Graph &graph, const Vertex &start,
                        const Vertex &end)
{
	// Create a state for each vertex in the graph. This sets all vertices
	// as unvisited, and their distance as infinity.
	VertexStateMap_t vertices(graph.vertexCount());
	for(auto it = graph.verticesBegin(); it != graph.verticesEnd(); ++it)
	{
		vertices.insert(std::make_pair<const Vertex *, VertexState>(
		        it->get(), VertexState(it->get())));
	}

	// Get the state for the end node.
	VertexState *endState = getState(end, vertices);

	// Set the start's distance to 0, and make it the current vertex.
	VertexState *current = getState(start, vertices);
	current->distance = 0;

	for(;;)
	{
		// For each neighbor of the current node...
		for(const auto &edge : current->vertex->edges)
		{
			VertexState *neighbor = getState(
			        *getOther(edge, *current->vertex), vertices);

			// If this neighbor has already been visited, skip it.
			if(neighbor->visited)
				continue;

			// Calculate a tentative distance (current + edge) and
			// update this neighbor's distance if the tentative
			// distance is less than its current distance.
			int64_t tentative =
			        current->distance +
			        current->vertex->distanceTo(*neighbor->vertex);
			if(tentative < neighbor->distance)
			{
				neighbor->distance = tentative;
				neighbor->previous = current;
			}
		}

		// Mark the current node as visited.
		current->visited = true;

		// Stop if the end node has been visited.
		if(endState->visited)
			break;

		// Find the unvisited node with the smallest distance.
		// Stop if there is no smallest vertex, or if its
		// distance is infinity.
		VertexState *smallest = findSmallestUnvisited(vertices);
		if((smallest == nullptr) || (smallest->distance == INT64_MAX))
			break;

		// Make the smallest vertex the current vertex.
		current = smallest;
	}

	// Navigate the path back to the start from the end.
	DijkstraResult result;
	for(current = getState(end, vertices); current != nullptr;
	    current = current->previous)
	{
		result.path.push_back(*current->vertex);
	}
	result.sum = getState(end, vertices)->distance;
	return result;
}
}
}

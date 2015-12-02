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

#include "astar.h"

#include <unordered_map>
#include <utility>

namespace
{
enum class VisitedState
{
	NONE,
	OPEN,
	CLOSED
};

struct VertexState
{
	const euler::graph::Vertex *vertex;
	int64_t heuristicScore;
	int64_t actualScore;
	VisitedState state;
	VertexState *previous;

	explicit VertexState(const euler::graph::Vertex *v)
	        : vertex(v),
	          heuristicScore(INT64_MAX),
	          actualScore(INT64_MAX),
	          state(VisitedState::NONE),
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

bool openSetEmpty(const VertexStateMap_t &map)
{
	for(auto vertexPair : map)
	{
		if(vertexPair.second.state == VisitedState::OPEN)
			return false;
	}

	return true;
}

VertexState *findSmallestHeuristicOpen(VertexStateMap_t &map)
{
	VertexState *smallest = nullptr;

	for(auto &&statePair : map)
	{
		// If this vertex isn't in the open set, skip it.
		if(statePair.second.state != VisitedState::OPEN)
			continue;

		// If there is no smallest vertex yet, just use this one.
		if(smallest == nullptr)
		{
			smallest = &statePair.second;
			continue;
		}

		// If this vertex has a smaller heuristic score than the
		// current smallest, use it instead.
		if(statePair.second.heuristicScore < smallest->heuristicScore)
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
AStarResult::AStarResult() : path(), sum(0)
{
}

template <>
AStarResult astar<AdmissibleHeuristic>(const Graph &, const Vertex &,
                                       const Vertex &, AStarHeuristicFunction_t)
{
	return AStarResult();
}

template <>
AStarResult astar<ConsistentHeuristic>(const Graph &graph, const Vertex &start,
                                       const Vertex &end,
                                       AStarHeuristicFunction_t heuristicFn)
{
	// Create a state for each vertex in the graph. This sets all vertices
	// as being neither open nor closed, and it sets both their actual and
	// heuristic scores to infinity.
	VertexStateMap_t vertices(graph.vertexCount());
	for(auto it = graph.verticesBegin(); it != graph.verticesEnd(); ++it)
	{
		vertices.insert(std::make_pair<const Vertex *, VertexState>(
		        it->get(), VertexState(it->get())));
	}

	// Get the state for the end node.
	VertexState *endState = getState(end, vertices);

	// Set the start vertex's actual score to 0, and estimate its distance
	// from the end vertex. Additionally, make the start vertex "open".
	VertexState *startState = getState(start, vertices);
	startState->actualScore = 0;
	startState->heuristicScore = heuristicFn(start, end);
	startState->state = VisitedState::OPEN;

	while(!openSetEmpty(vertices))
	{
		// Find the open vertex with the lowest heuristic score.
		// If this vertex is the end vertex, then we're done.
		VertexState *current = findSmallestHeuristicOpen(vertices);
		if(current == endState)
			break;

		// Move the current vertex to the closed set.
		current->state = VisitedState::CLOSED;

		// For each neighbor of the current vertex...
		for(const auto &edge : current->vertex->edges)
		{
			VertexState *neighbor = getState(
			        *getOther(edge, *current->vertex), vertices);

			// If this neighbor is in the closed set, skip it.
			if(neighbor->state == VisitedState::CLOSED)
				continue;

			// Calculate and update this neighbor's actual score,
			// if applicable.
			int64_t tentativeActualScore =
			        current->actualScore + edge.get().weight;
			if((neighbor->state != VisitedState::OPEN) ||
			   (tentativeActualScore < neighbor->actualScore))
			{
				neighbor->previous = current;
				neighbor->actualScore = tentativeActualScore;
				neighbor->heuristicScore =
				        neighbor->actualScore +
				        heuristicFn(*neighbor->vertex, end);
				neighbor->state = VisitedState::OPEN;
			}
		}
	}

	// Navigate the path back to the start from the end.
	AStarResult result;
	VertexState *current;
	for(current = getState(end, vertices); current != nullptr;
	    current = current->previous)
	{
		result.path.push_back(*current->vertex);
	}
	result.sum = getState(end, vertices)->actualScore;
	return result;
}
}
}

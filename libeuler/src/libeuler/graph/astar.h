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

#ifndef INCLUDE_LIBEULER_GRAPH_ASTAR_H
#define INCLUDE_LIBEULER_GRAPH_ASTAR_H

#include <cstdint>
#include <functional>
#include <list>

#include "libeuler/graph/Graph.h"
#include "libeuler/graph/Vertex.h"

namespace euler
{
namespace graph
{
struct AStarResult
{
	std::list<std::reference_wrapper<const Vertex>> path;
	int64_t sum;

	AStarResult();
};

typedef std::function<int64_t(const Vertex &, const Vertex &)>
        AStarHeuristicFunction_t;

struct AdmissibleHeuristic
{
};

struct ConsistentHeuristic
{
};

template <typename HeuristicType>
AStarResult astar(const Graph &graph, const Vertex &start, const Vertex &end,
                  AStarHeuristicFunction_t heuristicFn);

template <>
AStarResult astar<AdmissibleHeuristic>(const Graph &graph, const Vertex &start,
                                       const Vertex &end,
                                       AStarHeuristicFunction_t heuristicFn);

template <>
AStarResult astar<ConsistentHeuristic>(const Graph &graph, const Vertex &start,
                                       const Vertex &end,
                                       AStarHeuristicFunction_t heuristicFn);
}
}

#endif

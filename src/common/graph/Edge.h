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

#ifndef INCLUDE_LIBEULER_GRAPH_EDGE_H
#define INCLUDE_LIBEULER_GRAPH_EDGE_H

#include <cstdint>
#include <functional>
#include <memory>
#include <set>

#include <bdrck/util/ScopeExit.hpp>

namespace euler
{
namespace graph
{
class Vertex;

enum EdgeDirection
{
	EDGE_DIRECTION_NONE = 0,

	EDGE_DIRECTION_FORWARD = (1u << 0),
	EDGE_DIRECTION_BACKWARD = (1u << 1),

	EDGE_DIRECTION_BOTH = EDGE_DIRECTION_FORWARD | EDGE_DIRECTION_BACKWARD
};

class Edge
{
public:
	Vertex &a;
	Vertex &b;
	int64_t weight;

	Edge(Vertex &va, Vertex &vb, int64_t w,
	     EdgeDirection direction = EDGE_DIRECTION_BOTH);

	Edge(const Edge &) = default;
	~Edge() = default;
	Edge &operator=(const Edge &) = default;

	bool operator==(const Edge &o) const;

private:
	std::shared_ptr<bdrck::util::ScopeExit> cleanup;
};

struct EdgeComparator
{
	EdgeComparator();

	bool operator()(const Edge &a, const Edge &b) const;
};

typedef std::set<std::reference_wrapper<Edge>, EdgeComparator> EdgeSet_t;
}
}

#endif

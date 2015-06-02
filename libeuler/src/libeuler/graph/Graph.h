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

#ifndef INCLUDE_LIBEULER_GRAPH_GRAPH_H
#define INCLUDE_LIBEULER_GRAPH_GRAPH_H

#include <cstddef>
#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

#include "libeuler/graph/Edge.h"
#include "libeuler/graph/Vertex.h"

namespace euler
{
namespace graph
{
class Graph
{
private:
	typedef std::vector<std::unique_ptr<Vertex>> VertexVector_t;
	typedef std::vector<std::unique_ptr<Edge>> EdgeVector_t;

public:
	typedef VertexVector_t::iterator VertexIterator_t;
	typedef VertexVector_t::const_iterator ConstVertexIterator_t;

	Graph();

	Graph(const Graph &) = delete;
	~Graph() = default;
	Graph &operator=(const Graph &) = delete;

	VertexIterator_t verticesBegin();
	VertexIterator_t verticesEnd();
	ConstVertexIterator_t verticesBegin() const;
	ConstVertexIterator_t verticesEnd() const;

	std::size_t vertexCount() const;

	Vertex &addVertex();
	void connect(Vertex &a, Vertex &b, int64_t w,
	             EdgeDirection direction = EDGE_DIRECTION_BOTH);

private:
	VertexVector_t vertices;
	EdgeVector_t edges;
};
}

namespace graph_utils
{
/*!
 * @param apos The first (x, y) position.
 * @param bpos The second (x, y) position.
 * @return The floor of the euclidean distance between the two points.
 */
int64_t euclideanDistance(const std::pair<std::size_t, std::size_t> &apos,
                          const std::pair<std::size_t, std::size_t> &bpos);
}
}

#endif

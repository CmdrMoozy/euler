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

#include "Graph.h"

#include <utility>

namespace euler
{
namespace graph
{
Graph::Graph() : vertices(), edges()
{
}

Graph::VertexIterator_t Graph::verticesBegin()
{
	return vertices.begin();
}

Graph::VertexIterator_t Graph::verticesEnd()
{
	return vertices.end();
}

Graph::ConstVertexIterator_t Graph::verticesBegin() const
{
	return vertices.cbegin();
}

Graph::ConstVertexIterator_t Graph::verticesEnd() const
{
	return vertices.cend();
}

std::size_t Graph::vertexCount() const
{
	return vertices.size();
}

Vertex &Graph::addVertex()
{
	std::unique_ptr<Vertex> vertex(new Vertex());
	vertices.push_back(std::move(vertex));
	return *vertices.back();
}

void Graph::connect(Vertex &a, Vertex &b, int64_t w)
{
	std::unique_ptr<Edge> edge(new Edge(a, b, w));
	edges.push_back(std::move(edge));
}
}
}

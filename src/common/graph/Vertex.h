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

#ifndef INCLUDE_LIBEULER_GRAPH_VERTEX_H
#define INCLUDE_LIBEULER_GRAPH_VERTEX_H

#include <cstdint>

#include "common/graph/Edge.h"

namespace euler
{
namespace graph
{
class Vertex
{
public:
	EdgeSet_t edges;

	Vertex();

	Vertex(const Vertex &) = default;
	~Vertex() = default;
	Vertex &operator=(const Vertex &) = default;

	bool connectedTo(const Vertex &o) const;
	bool removeConnection(const Vertex &o);

	int64_t distanceTo(const Vertex &o) const;
};
}
}

#endif
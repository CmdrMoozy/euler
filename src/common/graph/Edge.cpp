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

#include "Edge.h"

#include <stdexcept>

#include "common/graph/Vertex.h"

namespace euler
{
namespace graph
{
Edge::Edge(Vertex &va, Vertex &vb, int64_t w, EdgeDirection direction)
        : a(va), b(vb), weight(w), cleanup()
{
	if(a.connectedTo(b))
		throw std::runtime_error("Can't create duplicate edges.");

	if(direction & EDGE_DIRECTION_FORWARD)
		va.edges.insert(*this);

	if(direction & EDGE_DIRECTION_BACKWARD)
		vb.edges.insert(*this);

	Vertex *vaPtr = &va;
	Vertex *vbPtr = &vb;
	cleanup = std::make_shared<bdrck::util::ScopeExit>(
	        [vaPtr, vbPtr, direction]()
	        {
		        if(direction & EDGE_DIRECTION_FORWARD)
			        vaPtr->removeConnection(*vbPtr);

		        if(direction & EDGE_DIRECTION_BACKWARD)
			        vbPtr->removeConnection(*vaPtr);
		});
}

bool Edge::operator==(const Edge &o) const
{
	return &a == &o.a && &b == &o.b && weight == o.weight;
}

EdgeComparator::EdgeComparator()
{
}

bool EdgeComparator::operator()(const Edge &a, const Edge &b) const
{
	if(&a.a < &b.a)
		return true;
	else if(&a.a > &b.a)
		return false;

	if(&a.b < &b.b)
		return true;
	else if(&a.b > &b.b)
		return false;

	if(a.weight < b.weight)
		return true;
	else
		return false;
}
}
}

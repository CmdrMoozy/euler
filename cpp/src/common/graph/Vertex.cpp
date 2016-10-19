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

#include "Vertex.h"

#include <stdexcept>

namespace euler
{
namespace graph
{
Vertex::Vertex() : edges()
{
}

bool Vertex::connectedTo(const Vertex &o) const
{
	for(const auto &edge : edges)
	{
		if((&edge.get().a == &o) || (&edge.get().b == &o))
			return true;
	}

	return false;
}

bool Vertex::removeConnection(const Vertex &o)
{
	for(auto it = edges.begin(); it != edges.end(); ++it)
	{
		if((&it->get().a == &o) || (&it->get().b == &o))
		{
			edges.erase(it);
			return true;
		}
	}

	return false;
}

int64_t Vertex::distanceTo(const Vertex &o) const
{
	for(const auto &edge : edges)
	{
		if((&edge.get().a == &o) || (&edge.get().b == &o))
			return edge.get().weight;
	}

	throw std::runtime_error("Not connected with the given vertex.");
}
}
}

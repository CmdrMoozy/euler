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

#include "GridGraphUtils.h"

namespace euler
{
namespace grid_graph_utils
{
euler::graph::EdgeDirection
movementDirectionToEdgeDirection(uint64_t movementFlags,
                                 GridGraphMovementDirection forward,
                                 GridGraphMovementDirection backward)
{
	if((movementFlags & static_cast<uint64_t>(forward | backward)) ==
	   static_cast<uint64_t>(forward | backward))
	{
		return euler::graph::EDGE_DIRECTION_BOTH;
	}
	else if(movementFlags & static_cast<uint64_t>(forward))
	{
		return euler::graph::EDGE_DIRECTION_FORWARD;
	}
	else if(movementFlags & static_cast<uint64_t>(backward))
	{
		return euler::graph::EDGE_DIRECTION_BACKWARD;
	}
	else
	{
		return euler::graph::EDGE_DIRECTION_NONE;
	}
}

FauxTerminalVertex::FauxTerminalVertex(euler::graph::Vertex &v, std::size_t x,
                                       std::size_t y)
        : vertex(&v), position(std::make_pair(x, y))
{
}
}
}

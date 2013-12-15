/*
 * euler - A collection of ProjectEuler solutions, and supporting libraries and tools.
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

#ifndef INCLUDE_LIBEULER_GRAPH_GRID_VERTEX_H
#define INCLUDE_LIBEULER_GRAPH_GRID_VERTEX_H

#include <vector>
#include <cstdint>

/*!
 * \brief This class implements a vertex in a graph which also has an (x, y) position in a grid.
 */
class EGridVertex
{
	public:
		EGridVertex(int x, int y, uint64_t v);
		virtual ~EGridVertex();
		
		bool operator<(const EGridVertex &o) const;
		
		int getX() const;
		int getY() const;
		uint64_t getValue() const;
		std::vector<const EGridVertex *> getEdges() const;
		
		void addEdge(const EGridVertex *v);
		void clearEdges();
		
	private:
		int xOff;
		int yOff;
		
		uint64_t value;
		std::vector<const EGridVertex *> edges;
};

#endif

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

#ifndef INCLUDE_LIBEULER_GRAPH_GRID_GRAPH_H
#define INCLUDE_LIBEULER_GRAPH_GRID_GRAPH_H

#include <cstdint>
#include <map>

class EGridVertex;

/*!
 * \brief This class provides utilities for graphs constructed with EGridVertex's.
 */
class EGridGraph
{
	public:
		static uint64_t aStar(EGridVertex *s, EGridVertex *e, uint64_t m);
	
	private:
		static uint64_t aStarHeuristic(const EGridVertex *a,
			const EGridVertex *b, uint64_t m);
		static uint64_t aStarReconstruct(const std::map<const EGridVertex *,
			const EGridVertex *> &navigated, const EGridVertex *c);
};

#endif

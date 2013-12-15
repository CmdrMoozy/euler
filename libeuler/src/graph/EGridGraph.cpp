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

#include "EGridGraph.h"

#include <cmath>
#include <set>
#include <cstdlib>

#include "graph/EGridVertex.h"

/*!
 * This function performs the traditional A* search for the shortest path between the given start
 * and end nodes. We also require the minimum node value in the graph, which we use for our
 * heuristic function.
 *
 * \param s The starting vertex.
 * \param e The end (or goal) vertex.
 * \param m The minimum value of any vertex in the graph.
 * \return The sum of the shortest path through the graph, or UINT64_MAX if no path exists.
 */
uint64_t EGridGraph::aStar(EGridVertex *s, EGridVertex *e, uint64_t m)
{
	// Define some structures to store the search state.
	
	std::set<const EGridVertex *> closed;
	
	std::set<const EGridVertex *> open;
	open.insert(s);
	
	std::map<const EGridVertex *, const EGridVertex *> navigated;
	
	std::map<const EGridVertex *, uint64_t> gscore;
	gscore.insert(std::pair<EGridVertex *, uint64_t>(s, 0));
	
	std::map<const EGridVertex *, uint64_t> fscore;
	fscore.insert(std::pair<EGridVertex *, uint64_t>(s, EGridGraph::aStarHeuristic(s, e, m)));
	
	// Search for the shortest path.
	
	while(!open.empty())
	{
		// The current node is the open node with the lowest fscore.
		
		const EGridVertex *current = NULL;
		
		for(std::set<const EGridVertex *>::iterator it = open.begin();
			it != open.end(); ++it)
		{
			if(current == NULL)
			{
				current = *it;
			}
			else
			{
				if(fscore.at(*it) < fscore.at(current))
					current = *it;
			}
		}
		
		// If we've reached the end node, we're done.
		
		if(current == e)
			return EGridGraph::aStarReconstruct(navigated, e);
		
		// Remove this current node from the open list, and add it to the closed list.
		
		open.erase(current);
		closed.insert(current);
		
		// Iterate over this node's neighbors.
		
		std::vector<const EGridVertex *> edges = current->getEdges();
		
		for(std::vector<const EGridVertex *>::iterator it = edges.begin();
			it != edges.end(); ++it)
		{
			uint64_t tentg = gscore.at(current) + current->getValue() +
				(*it)->getValue();
			uint64_t tentf = tentg + EGridGraph::aStarHeuristic(*it, e, m);
			
			if( (closed.find(*it) != closed.end()) && (tentf >= fscore.at(*it)) )
				continue;
			
			if( (open.find(*it) == open.end()) || (tentf < fscore.at(*it)) )
			{
				navigated.insert(std::pair<const EGridVertex *,
					const EGridVertex *>(*it, current));
				
				gscore.insert(std::pair<const EGridVertex *, uint64_t>(*it, tentg));
				fscore.insert(std::pair<const EGridVertex *, uint64_t>(*it, tentf));
				
				if(open.find(*it) == open.end())
					open.insert(*it);
			}
		}
	}
	
	return UINT64_MAX;
}

/*!
 * This is a heuristic that estimates the cost of travelling between the vertices a and b. To do
 * this, we assume that all nodes in the graph have a cost equal to the minimum node cost in the
 * graph.
 *
 * This heuristic is, by definition, admissable. That is, it will never over-estimate the cost of
 * moving between the two vertices.
 *
 * Additionally, this heuristic is consistent (or monotone).
 *
 * \param a The first vertex.
 * \param b The second vertex.
 * \param m The minimum value of any vertex in the graph.
 * \return An approximate cost to move between the two given vertices.
 */
uint64_t EGridGraph::aStarHeuristic(const EGridVertex *a, const EGridVertex *b, uint64_t m)
{
	double x1 = static_cast<double>(a->getX());
	double y1 = static_cast<double>(a->getY());
	double x2 = static_cast<double>(b->getX());
	double y2 = static_cast<double>(b->getY());
	
	double d = sqrt( (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) );
	d = fabs(d);
	
	d *= static_cast<double>(m);
	
	return static_cast<uint64_t>(floor(d));
}

/*!
 * This function reconstructs a path that has been traveled through the graph. This uses a map of
 * navigated nodes, which maps a vertex with the vertex that was navigated through to get to that
 * vertex. I.e., navigated[a vertex] = (the vertex visited before the key vertex).
 *
 * \param navigated The map of vertex nagivations made to get to the current vertex.
 * \param c The current vertex.
 * \return The sum of the cost of all moves made to reach the current vertex.
 */
uint64_t EGridGraph::aStarReconstruct(const std::map<const EGridVertex *,
	const EGridVertex *> &navigated, const EGridVertex *c)
{
	std::map<const EGridVertex *, const EGridVertex *>::const_iterator it = navigated.find(c);
	
	if(it != navigated.cend())
		return c->getValue() + EGridGraph::aStarReconstruct(navigated, it->second);
	else
		return c->getValue();
}

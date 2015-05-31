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

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "libeuler/graph/dijkstra.h"
#include "libeuler/graph/Graph.h"
#include "libeuler/graph/Vertex.h"
#include "libeuler/util/EString.h"

/*
 * In the 5 by 5 matrix below, the minimal path sum from the top left to bottom
 * right, by only moving to the right and down, is indicated in bold red and is
 * equal to 2427.
 *
 *     [ (131)  673   234   103    18  ]
 *     [ (201) ( 96) (342)  965   150  ]
 *     [  630   803  (746) (422)  111  ]
 *     [  537   699   497  (121)  956  ]
 *     [  805   732   524  ( 37) (331) ]
 *
 * Find the minimal path sum, in matrix.txt (right click and 'Save Link/Target
 * As...'), a 31K text file containing an 80 by 80 matrix, from the top left
 * to the bottom right by moving only right and down.
 */

namespace
{
constexpr std::size_t GRID_WIDTH = 80;
constexpr std::size_t GRID_HEIGHT = 80;
}

int main(void)
{
	// Open the file containing the edge weights.
	std::ifstream file("matrix.txt");
	if(!file.is_open())
	{
		std::cout << "FATAL: Couldn't open matrix.txt for reading.\n";
		return EXIT_FAILURE;
	}

	// Load the edge weights from the file.
	int64_t weights[GRID_WIDTH][GRID_HEIGHT];
	std::string line;
	for(std::size_t x = 0; std::getline(file, line);)
	{
		std::vector<std::string> rowWeights = EString::split(line, ',');
		std::size_t y = 0;
		for(auto weight : rowWeights)
		{
			weights[x][y] =
			        static_cast<int64_t>(std::stoll(weight));
			++y;
		}
		++x;
	}

	// We need to create a graph with GRAPH_WIDTH * GRAPH_HEIGHT nodes,
	// plus two extra nodes (the start and end).
	euler::graph::Graph graph;
	euler::graph::Vertex *internalVertices[GRID_WIDTH][GRID_HEIGHT];
	euler::graph::Vertex &start = graph.addVertex();
	euler::graph::Vertex &end = graph.addVertex();
	for(std::size_t x = 0; x < GRID_WIDTH; ++x)
	{
		for(std::size_t y = 0; y < GRID_HEIGHT; ++y)
			internalVertices[x][y] = &graph.addVertex();
	}

	// Connect all of the internal nodes, so that from each node we can
	// move either to the right or down (as per the problem description).
	for(std::size_t x = 0; x < GRID_WIDTH; ++x)
	{
		for(std::size_t y = 0; y < GRID_HEIGHT; ++y)
		{
			// Create the "right" connection.
			if((x + 1) < GRID_WIDTH)
			{
				graph.connect(
				        *internalVertices[x][y],
				        *internalVertices[x + 1][y],
				        weights[x + 1][y],
				        euler::graph::EDGE_DIRECTION_FORWARD);
			}

			// Create the "down" connection.
			if((y + 1) < GRID_HEIGHT)
			{
				graph.connect(
				        *internalVertices[x][y],
				        *internalVertices[x][y + 1],
				        weights[x][y + 1],
				        euler::graph::EDGE_DIRECTION_FORWARD);
			}
		}
	}

	// Connect the start and end nodes.
	graph.connect(start, *internalVertices[0][0], weights[0][0],
	              euler::graph::EDGE_DIRECTION_FORWARD);
	graph.connect(*internalVertices[GRID_WIDTH - 1][GRID_HEIGHT - 1], end,
	              0, euler::graph::EDGE_DIRECTION_FORWARD);

	// Find the shortest path, and we're done!

	auto result = euler::graph::dijkstra(graph, start, end);
	std::cout << "The minimum path sum is: " << result.sum << "\n";
	assert(result.sum == 427337);

	return EXIT_SUCCESS;
}

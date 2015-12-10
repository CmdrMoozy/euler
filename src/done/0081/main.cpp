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
#include <functional>
#include <iostream>

#include "common/euler/GridGraphUtils.h"
#include "common/graph/astar.h"
#include "common/graph/Edge.h"

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

typedef euler::grid_graph_utils::GridGraphWeights<GRID_WIDTH, GRID_HEIGHT>
        GridGraphWeights_t;
typedef euler::grid_graph_utils::GridGraph<GRID_WIDTH, GRID_HEIGHT> GridGraph_t;
}

int main(void)
{
	// Load the weights from the input file, and build a graph from them.
	GridGraphWeights_t weights =
	        euler::grid_graph_utils::loadWeights<GRID_WIDTH, GRID_HEIGHT>(
	                "matrix.txt");
	GridGraph_t graph(
	        weights, euler::grid_graph_utils::GRID_GRAPH_MOVE_DOWN |
	                         euler::grid_graph_utils::GRID_GRAPH_MOVE_RIGHT,
	        0, GRID_HEIGHT, GRID_WIDTH + 1, 0, 1, 0);

	// Connect the faux start and end nodes.
	graph.graph->connect(*graph.fauxStart.vertex,
	                     *graph.gridVertices[0][GRID_HEIGHT - 1],
	                     weights.weights[0][GRID_HEIGHT - 1],
	                     euler::graph::EDGE_DIRECTION_FORWARD);
	graph.graph->connect(*graph.gridVertices[GRID_WIDTH - 1][0],
	                     *graph.fauxEnd.vertex, 0,
	                     euler::graph::EDGE_DIRECTION_FORWARD);

	// Find the shortest path, and we're done!

	euler::graph::AStarHeuristicFunction_t heuristicFn = [&weights, &graph](
	        const euler::graph::Vertex &a,
	        const euler::graph::Vertex &b) -> int64_t
	{
		auto apos =
		        euler::grid_graph_utils::getVertexPosition(graph, a);
		auto bpos =
		        euler::grid_graph_utils::getVertexPosition(graph, b);
		return euler::graph_utils::euclideanDistance(apos, bpos) *
		       weights.minimumWeight;
	};

	auto result = euler::graph::astar<euler::graph::ConsistentHeuristic>(
	        *graph.graph, *graph.fauxStart.vertex, *graph.fauxEnd.vertex,
	        heuristicFn);
	std::cout << "The minimum path sum is: " << result.sum << "\n";
	assert(result.sum == 427337);

	return EXIT_SUCCESS;
}

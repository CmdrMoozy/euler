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

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "libeuler/graph/astar.h"
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

struct GridWeights
{
	std::array<std::array<int64_t, GRID_HEIGHT>, GRID_WIDTH> weights;
	int64_t minimumWeight;
};

GridWeights loadWeights()
{
	GridWeights ret;

	// Open the file containing the edge weights.
	std::ifstream file("matrix.txt");
	if(!file.is_open())
	{
		throw std::runtime_error(
		        "FATAL: Couldn't open matrix.txt for reading.");
	}

	// Load the edge weights from the file.
	ret.minimumWeight = INT64_MAX;
	std::string line;
	for(std::size_t x = 0; std::getline(file, line);)
	{
		std::vector<std::string> rowWeights = EString::split(line, ',');
		std::size_t y = 0;
		for(auto weight : rowWeights)
		{
			ret.weights[x][y] =
			        static_cast<int64_t>(std::stoll(weight));
			ret.minimumWeight =
			        std::min(ret.minimumWeight, ret.weights[x][y]);
			++y;
		}
		++x;
	}

	return ret;
}

struct GridGraph
{
	std::shared_ptr<euler::graph::Graph> graph;
	std::unordered_map<const euler::graph::Vertex *,
	                   std::pair<std::size_t, std::size_t>> positionMap;

	euler::graph::Vertex *start;
	euler::graph::Vertex *end;

	euler::graph::Vertex *fauxStart;
	euler::graph::Vertex *fauxEnd;
};

GridGraph buildGraph(const GridWeights &weights)
{
	GridGraph ret;

	// We need to create a graph with GRAPH_WIDTH * GRAPH_HEIGHT vertices,
	// plus two extra vertices (the faux start and end, which are used so
	// that we can make each of the weights in the input file an edge
	// instead of a vertex).
	ret.graph = std::make_shared<euler::graph::Graph>();
	euler::graph::Vertex *internalVertices[GRID_WIDTH][GRID_HEIGHT];
	ret.fauxStart = &ret.graph->addVertex();
	ret.fauxEnd = &ret.graph->addVertex();
	for(std::size_t x = 0; x < GRID_WIDTH; ++x)
	{
		for(std::size_t y = 0; y < GRID_HEIGHT; ++y)
		{
			internalVertices[x][y] = &ret.graph->addVertex();
			ret.positionMap.insert(std::make_pair(
			        internalVertices[x][y], std::make_pair(x, y)));
		}
	}

	// Connect all of the internal nodes, so that from each ndoe we can
	// move either to the right or down (as per the problem description).
	for(std::size_t x = 0; x < GRID_WIDTH; ++x)
	{
		for(std::size_t y = 0; y < GRID_HEIGHT; ++y)
		{
			// Create the "right" connection.
			if((x + 1) < GRID_WIDTH)
			{
				ret.graph->connect(
				        *internalVertices[x][y],
				        *internalVertices[x + 1][y],
				        weights.weights[x + 1][y],
				        euler::graph::EDGE_DIRECTION_FORWARD);
			}

			// Create the "down" connection.
			if((y + 1) < GRID_HEIGHT)
			{
				ret.graph->connect(
				        *internalVertices[x][y],
				        *internalVertices[x][y + 1],
				        weights.weights[x][y + 1],
				        euler::graph::EDGE_DIRECTION_FORWARD);
			}
		}
	}

	// Connect the faux start and end vertices.
	ret.graph->connect(*ret.fauxStart, *internalVertices[0][0],
	                   weights.weights[0][0],
	                   euler::graph::EDGE_DIRECTION_FORWARD);
	ret.graph->connect(*internalVertices[GRID_WIDTH - 1][GRID_HEIGHT - 1],
	                   *ret.fauxEnd, 0,
	                   euler::graph::EDGE_DIRECTION_FORWARD);

	return ret;
}

std::pair<std::size_t, std::size_t> getPosition(const GridGraph &graph,
                                                const euler::graph::Vertex &v)
{
	if(&v == graph.fauxStart)
		return std::make_pair<std::size_t, std::size_t>(0, 0);

	if(&v == graph.fauxEnd)
		return std::make_pair(GRID_WIDTH, GRID_HEIGHT);

	auto posit = graph.positionMap.find(&v);
	assert(posit != graph.positionMap.end());
	return std::make_pair(posit->second.first + 1,
	                      posit->second.second + 1);
}

int64_t euclideanDistance(const std::pair<std::size_t, std::size_t> &apos,
                          const std::pair<std::size_t, std::size_t> &bpos)
{
	double distance = (bpos.first - apos.first) * (bpos.first * apos.first);
	distance += (bpos.second - apos.second) * (bpos.second * apos.second);
	return static_cast<int64_t>(floor(sqrt(distance)));
}
}

int main(void)
{
	// Load the weights from the input file, and build a graph from them.
	GridWeights weights = loadWeights();
	GridGraph graph = buildGraph(weights);

	// Find the shortest path, and we're done!

	euler::graph::AStarHeuristicFunction_t heuristicFn =
	        [&weights, &graph](const euler::graph::Vertex &a,
	                           const euler::graph::Vertex &b) -> int64_t
	{
		auto apos = getPosition(graph, a);
		auto bpos = getPosition(graph, b);
		return euclideanDistance(apos, bpos) * weights.minimumWeight;
	};

	auto result = euler::graph::astar<euler::graph::ConsistentHeuristic>(
	        *graph.graph, *graph.fauxStart, *graph.fauxEnd, heuristicFn);
	std::cout << "The minimum path sum is: " << result.sum << "\n";
	assert(result.sum == 427337);

	return EXIT_SUCCESS;
}

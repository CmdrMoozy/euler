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

#include <catch/catch.hpp>

#include <cstddef>
#include <cmath>
#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>

#include "common/graph/astar.h"
#include "common/graph/dijkstra.h"
#include "common/graph/Graph.h"
#include "common/graph/Vertex.h"

namespace
{
constexpr std::size_t TEST_GRAPH_WIDTH = 22;
constexpr std::size_t TEST_GRAPH_HEIGHT = 22;

constexpr std::size_t TEST_GRAPH_START_X = 2;
constexpr std::size_t TEST_GRAPH_START_Y = 2;
constexpr std::size_t TEST_GRAPH_END_X = 18;
constexpr std::size_t TEST_GRAPH_END_Y = 18;

constexpr std::size_t TEST_GRAPH_EXPECTED_LENGTH = 25;
constexpr std::size_t TEST_GRAPH_EXPECTED_DISTANCE = 24;

struct TestGraph
{
	std::shared_ptr<euler::graph::Graph> graph;
	euler::graph::Vertex *start;
	euler::graph::Vertex *end;

	std::unordered_map<const euler::graph::Vertex *,
	                   std::pair<std::size_t, std::size_t>> positionMap;
};

TestGraph createTestGraph()
{
	TestGraph test;
	test.graph = std::make_shared<euler::graph::Graph>();

	euler::graph::Vertex *vertices[TEST_GRAPH_WIDTH][TEST_GRAPH_HEIGHT];

	// Create the vertices for the test graph.
	for(std::size_t x = 0; x < TEST_GRAPH_WIDTH; ++x)
	{
		for(std::size_t y = 0; y < TEST_GRAPH_HEIGHT; ++y)
		{
			vertices[x][y] = nullptr;

			// There are no passable nodes in the rectangular area
			// in the range (5, 13) to (15, 15).
			if((x >= 5) && (x <= 15))
				if((y >= 13) && (y <= 15))
					continue;

			// There are no passable nodes in the rectangular area
			// in the range (13, 8) to (15, 12).
			if((x >= 13) && (x <= 15))
				if((y >= 8) && (y <= 12))
					continue;

			vertices[x][y] = &test.graph->addVertex();
			auto position = std::make_pair(x, y);
			test.positionMap.insert(
			        std::make_pair(vertices[x][y], position));
		}
	}

	// Create the edges for the test graph.
	for(std::size_t x = 0; x < TEST_GRAPH_WIDTH; ++x)
	{
		for(std::size_t y = 0; y < TEST_GRAPH_HEIGHT; ++y)
		{
			if(vertices[x][y] == nullptr)
				continue;

			// Connect to the left neighbor, if any.
			if((x > 0) && (vertices[x - 1][y] != nullptr))
			{
				test.graph->connect(*vertices[x][y],
				                    *vertices[x - 1][y], 1);
			}

			// Connect to the below neighbor, if any.
			if((y > 0) && (vertices[x][y - 1] != nullptr))
			{
				test.graph->connect(*vertices[x][y],
				                    *vertices[x][y - 1], 1);
			}

			// Connect to the left & below neighbor, if any.
			if((x > 0) && (y > 0) &&
			   (vertices[x - 1][y - 1] != nullptr))
			{
				test.graph->connect(*vertices[x][y],
				                    *vertices[x - 1][y - 1], 1);
			}
		}
	}

	test.start = vertices[TEST_GRAPH_START_X][TEST_GRAPH_START_Y];
	test.end = vertices[TEST_GRAPH_END_X][TEST_GRAPH_END_Y];

	return test;
}
}

TEST_CASE("Test Dijkstra path finding algorithm", "[Graph]")
{
	TestGraph test = createTestGraph();
	auto result =
	        euler::graph::dijkstra(*test.graph, *test.start, *test.end);
	CHECK(TEST_GRAPH_EXPECTED_LENGTH == result.path.size());
	CHECK(TEST_GRAPH_EXPECTED_DISTANCE == result.sum);
}

TEST_CASE("Test A* heuristic consistency", "[Graph]")
{
	TestGraph test = createTestGraph();

	euler::graph::AStarHeuristicFunction_t heuristicFn = [&test](
	        const euler::graph::Vertex &a,
	        const euler::graph::Vertex &b) -> int64_t
	{
		auto aposit = test.positionMap.find(&a);
		auto bposit = test.positionMap.find(&b);
		CHECK(aposit != test.positionMap.end());
		CHECK(bposit != test.positionMap.end());

		auto apos = aposit->second;
		auto bpos = bposit->second;

		double distance =
		        (bpos.first - apos.first) * (bpos.first - apos.first);
		distance += (bpos.second - apos.second) *
		            (bpos.second - apos.second);
		distance = sqrt(distance);
		return static_cast<int64_t>(floor(distance));
	};

	auto result = euler::graph::astar<euler::graph::ConsistentHeuristic>(
	        *test.graph, *test.start, *test.end, heuristicFn);
	CHECK(TEST_GRAPH_EXPECTED_LENGTH == result.path.size());
	CHECK(TEST_GRAPH_EXPECTED_DISTANCE == result.sum);
}

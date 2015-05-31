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

#include "GraphTest.h"

#include <cstddef>
#include <memory>

#include "libeuler/graph/dijkstra.h"
#include "libeuler/graph/Graph.h"
#include "libeuler/graph/Vertex.h"

// DEBUG
#include <iostream>

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

void testDijkstra()
{
	TestGraph test = createTestGraph();
	auto result =
	        euler::graph::dijkstra(*test.graph, *test.start, *test.end);
	vrfy::assert::assertEquals(TEST_GRAPH_EXPECTED_LENGTH,
	                           result.path.size());
	vrfy::assert::assertEquals<int64_t>(TEST_GRAPH_EXPECTED_DISTANCE,
	                                    result.sum);
}
}

namespace euler
{
namespace test
{
void GraphTest::test()
{
	testDijkstra();
}
}
}
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

#ifndef INCLUDE_LIBEULER_EULER_GRID_GRAPH_UTILS_H
#define INCLUDE_LIBEULER_EULER_GRID_GRAPH_UTILS_H

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// DEBUG
#include <cassert>

#include "libeuler/graph/Edge.h"
#include "libeuler/graph/Graph.h"
#include "libeuler/graph/Vertex.h"
#include "libeuler/util/EString.h"

namespace euler
{
namespace grid_graph_utils
{
/*!
 * \brief This structure contains the weight information for a grid graph.
 */
template <std::size_t Width, std::size_t Height> struct GridGraphWeights
{
	std::array<std::array<int64_t, Height>, Width> weights;
	int64_t minimumWeight;
};

/*!
 * Load a GridGraphWeights structure from a file. Each row of weights should
 * be separated by a newline, and each weight on that line should be separated
 * by a comma.
 *
 * If loading the weights from the file fails, an exception will be thrown
 * instead.
 *
 * @param path The file path to load a set of weights from.
 * @return A weights structure containing the file contents.
 */
template <std::size_t Width, std::size_t Height>
GridGraphWeights<Width, Height> loadWeights(const std::string &path)
{
	GridGraphWeights<Width, Height> ret;

	// Open the file containing the edge weights.
	std::ifstream file(path);
	if(!file.is_open())
	{
		throw std::runtime_error(
		        "FATAL: Couldn't open file for reading.");
	}

	// Load the edge weights from the file.
	ret.minimumWeight = INT64_MAX;
	std::string line;
	for(std::size_t y = 1; std::getline(file, line);)
	{
		if(y > Height)
		{
			throw std::runtime_error(
			        "Encountered too many lines of weight values.");
		}

		std::vector<std::string> rowWeights = EString::split(line, ',');
		if(rowWeights.size() != Width)
		{
			throw std::runtime_error("Encountered line with an "
			                         "invalid number of weights.");
		}
		for(std::size_t x = 0; x < rowWeights.size(); ++x)
		{
			int64_t wi =
			        static_cast<int64_t>(std::stoll(rowWeights[x]));
			ret.weights[x][Height - y] = wi;
			ret.minimumWeight = std::min(ret.minimumWeight, wi);
		}
		++y;
	}

	return ret;
}

/*!
 * \brief These flags denote the various grid movement directions.
 */
enum GridGraphMovementDirection
{
	GRID_GRAPH_MOVE_NONE = 0,

	GRID_GRAPH_MOVE_UP = (1u << 0),
	GRID_GRAPH_MOVE_DOWN = (1u << 1),
	GRID_GRAPH_MOVE_LEFT = (1u << 2),
	GRID_GRAPH_MOVE_RIGHT = (1u << 3),

	GRID_GRAPH_MOVE_ALL = GRID_GRAPH_MOVE_UP | GRID_GRAPH_MOVE_DOWN |
	                      GRID_GRAPH_MOVE_LEFT | GRID_GRAPH_MOVE_RIGHT
};

/*!
 * This function converts a set of grid graph movement flags to an edge
 * direction value. The forward and backward parameters should generally be
 * left/right or down/up. If both of these directions are in the given set of
 * movement flags, then EDGE_DIRECTION_BOTH is returned. Otherwise, either
 * EDGE_DIRECTION_FORWARD or EDGE_DIRECTION_BACKWARD is returned, depdnding on
 * which of the two given directions are in the given set of movement flags.
 *
 * @param movementFlags The set of all allowed movement flags.
 * @param forward The "forward" grid graph movement direction.
 * @param backward The "backward" grid graph movement direction.
 * @return An edge direction value matching the given inputs.
 */
euler::graph::EdgeDirection
movementDirectionToEdgeDirection(uint64_t movementFlags,
                                 GridGraphMovementDirection forward,
                                 GridGraphMovementDirection backward);

/*!
 * \brief Contains information about a faux terminal grid graph vertex.
 *
 * In a grid graph, we have a series of edge weights arranged in a table. We
 * need these weights to be associated with edges, not vertices. Additionally,
 * certain problem say that we can start by traversing one or multiple edges.
 *
 * Because of this, we create "faux" start and end vertices, which are then
 * connected with any edge weights that the problem states can be terminal.
 */
struct FauxTerminalVertex
{
	euler::graph::Vertex *vertex;
	std::pair<std::size_t, std::size_t> position;

	/*!
	 * @param v The faux terminal vertex.
	 * @param x This vertex's X position.
	 * @param y This vertex's Y position.
	 */
	FauxTerminalVertex(euler::graph::Vertex &v, std::size_t x,
	                   std::size_t y);
};

/*!
 * \brief Contains all information about a grid-based graph structure.
 */
template <std::size_t Width, std::size_t Height> struct GridGraph
{
	std::shared_ptr<euler::graph::Graph> graph;

	// The list of non-faux graph vertices; one vertex per weight.
	std::array<std::array<euler::graph::Vertex *, Height>, Width>
	        gridVertices;

	// A map which allows looking up a non-faux vertex's unadjusted
	// position in the graph.
	std::unordered_map<const euler::graph::Vertex *,
	                   std::pair<std::size_t, std::size_t>> positionMap;

	// The (X, Y) translation to apply to any non-faux vertex's position.
	// This is useful so the faux vertices can occupy real positions in
	// the graph. This is used by getVertexPosition(), which should
	// generally be used instead of accessing non-faux vertex position
	// data directly.
	const std::pair<std::size_t, std::size_t> gridVertexOffset;

	FauxTerminalVertex fauxStart;
	FauxTerminalVertex fauxEnd;

	/*!
	 * @param weights The set of weights to create the graph from.
	 * @param movementFlags The movement directions allowed for this graph.
	 * @param fauxStartX The X position of the faux start node.
	 * @param fauxStartY The Y position of the faux start node.
	 * @param fauxEndX The X position of the faux end node.
	 * @param fauxEndY The Y position of the faux end node.
	 * @param gridVertexOffsetX The X offset for non-faux vertices.
	 * @param gridVertexOffsetY The Y offset for non-faux vertices.
	 */
	GridGraph(const GridGraphWeights<Width, Height> &weights,
	          uint64_t movementFlags, const std::size_t fauxStartX,
	          const std::size_t fauxStartY, const std::size_t fauxEndX,
	          const std::size_t fauxEndY,
	          const std::size_t gridVertexOffsetX,
	          const std::size_t gridVertexOffsetY)
	        : graph(std::make_shared<euler::graph::Graph>()),
	          gridVertices(),
	          positionMap(),
	          gridVertexOffset(
	                  std::make_pair(gridVertexOffsetX, gridVertexOffsetY)),
	          fauxStart(graph->addVertex(), fauxStartX, fauxStartY),
	          fauxEnd(graph->addVertex(), fauxEndX, fauxEndY)
	{
		// We need to create a graph with Width * Height vertices,
		// plus two extra vertices (the faux start and end, which are
		// used so that we can make each of the weights in the input
		// file an edge instead of a vertex).
		for(std::size_t x = 0; x < Width; ++x)
		{
			for(std::size_t y = 1; y <= Height; ++y)
			{
				auto vertex = &graph->addVertex();
				gridVertices[x][Height - y] = vertex;
				positionMap.insert(std::make_pair(
				        vertex, std::make_pair(x, Height - y)));
			}
		}

		// Connect all of the internal vertices, according to the
		// movement flags given to us.
		euler::graph::EdgeDirection lrDirection =
		        movementDirectionToEdgeDirection(movementFlags,
		                                         GRID_GRAPH_MOVE_RIGHT,
		                                         GRID_GRAPH_MOVE_LEFT);
		euler::graph::EdgeDirection udDirection =
		        movementDirectionToEdgeDirection(movementFlags,
		                                         GRID_GRAPH_MOVE_UP,
		                                         GRID_GRAPH_MOVE_DOWN);
		for(std::size_t x = 0; x < Width; ++x)
		{
			for(std::size_t y = 0; y < Height; ++y)
			{
				// Create the right/left connections.
				if((x + 1) < Width)
				{
					graph->connect(
					        *gridVertices[x][y],
					        *gridVertices[x + 1][y],
					        weights.weights[x + 1][y],
					        lrDirection);
				}

				// Create the up/down connections.
				if((y + 1) < Height)
				{
					graph->connect(*gridVertices[x][y],
					               *gridVertices[x][y + 1],
					               weights.weights[x][y],
					               udDirection);
				}
			}
		}
	}
};

/*!
 * Retrieve the adjusted position of a vertex in the given grid graph. This
 * function works as expected for the faux start and end nodes, as well as any
 * non-faux vertices.
 *
 * @param graph The graph containing the vertex.
 * @param v The vertex to get a position for.
 * @return The (X, Y) position for the given vertex.
 */
template <std::size_t Width, std::size_t Height>
std::pair<std::size_t, std::size_t>
getVertexPosition(const GridGraph<Width, Height> &graph,
                  const euler::graph::Vertex &v)
{
	if(&v == graph.fauxStart.vertex)
		return graph.fauxStart.position;

	if(&v == graph.fauxEnd.vertex)
		return graph.fauxEnd.position;

	auto it = graph.positionMap.find(&v);
	if(it == graph.positionMap.end())
		throw std::runtime_error("Invalid graph vertex.");
	return std::make_pair(it->second.first + graph.gridVertexOffset.first,
	                      it->second.second +
	                              graph.gridVertexOffset.second);
}
}
}

#endif

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

#include "EGridVertex.h"

/*!
 * This is our default constructor, which creates a new EGridVertex which represents a vertex with
 * the given value and (x, y) position in the grid.
 *
 * \param x The X-component of this vertex's grid position.
 * \param y The Y-component of this vertex's grid position.
 * \param v The value (or cost) of this vertex.
 */
EGridVertex::EGridVertex(int x, int y, uint64_t v)
	: xOff(x), yOff(y), value(v)
{
}

/*!
 * This is our destructor, which cleans up & destroys this vertex object.
 */
EGridVertex::~EGridVertex()
{
}

/*!
 * This operator compares this vertex with the given other one. This is used, e.g., to place a list
 * of vertices in a std::set<> and have them sorted by cost. The two vertices are compared using
 * their two values.
 *
 * \param o The vertex to compare ourself to.
 * \return True if this is less than the given other vertex, or false otherwise.
 */
bool EGridVertex::operator<(const EGridVertex &o) const
{
	return getValue() < o.getValue();
}

/*!
 * This function returns the X-component of this vertex's position in the grid.
 *
 * \return Our x position.
 */
int EGridVertex::getX() const
{
	return xOff;
}

/*!
 * This function returns the Y-component of this vertex's position in the grid.
 *
 * \return Our y position.
 */
int EGridVertex::getY() const
{
	return yOff;
}

/*!
 * This function returns the value (or cost) of this vertex.
 *
 * \return Our value.
 */
uint64_t EGridVertex::getValue() const
{
	return value;
}

/*!
 * This function returns a copy of this vertex's list of edges (or adjacent vertices).
 *
 * \return Our list of adjacent vertices.
 */
std::vector<const EGridVertex *> EGridVertex::getEdges() const
{
	return edges;
}

/*!
 * This function adds the given vertex to this vertex's list of adjacent vertices.
 *
 * \param v The vertex we are now adjacent to.
 */
void EGridVertex::addEdge(const EGridVertex *v)
{
	edges.push_back(v);
}

/*!
 * This function clears the list of edges (or adjacent vertices).
 */
void EGridVertex::clearEdges()
{
	edges.clear();
}

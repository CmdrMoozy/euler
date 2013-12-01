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

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

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

#include <iostream>
#include <cassert>
#include <cstdint>
#include <string>
#include <fstream>

#include "libeuler/graph/EGridGraph.h"
#include "libeuler/graph/EGridVertex.h"
#include "libeuler/util/EString.h"

/*
 * In the 5 by 5 matrix below, the minimal path sum from the top left to bottom right, by only
 * moving to the right and down, is indicated in bold red and is equal to 2427.
 *
 *     [ (131)  673   234   103    18  ]
 *     [ (201) ( 96) (342)  965   150  ]
 *     [  630   803  (746) (422)  111  ]
 *     [  537   699   497  (121)  956  ]
 *     [  805   732   524  ( 37) (331) ]
 *
 * Find the minimal path sum, in matrix.txt (right click and 'Save Link/Target As...'), a 31K text
 * file containing an 80 by 80 matrix, from the top left to the bottom right by moving only right
 * and down.
 */

#define GRID_WIDTH 80
#define GRID_HEIGHT 80

int main(void)
{
	EGridVertex *grid[GRID_HEIGHT][GRID_WIDTH];
	
	int i, j;
	
	// Read the input file, and assemble the graph.
	
	std::string line;
	std::ifstream gridfile("matrix.txt");
	
	if(!gridfile.is_open())
	{
		std::cout << "FATAL: Couldn't open matrix.txt for reading.\n";
		return 1;
	}
	
	i = 0;
	
	uint64_t minCost = UINT64_MAX;
	
	while(std::getline(gridfile, line))
	{
		j = 0;
		std::vector<std::string> values = EString::split(line, ',');
		
		for(std::vector<std::string>::iterator it = values.begin(); it != values.end(); ++it)
		{
			uint64_t v = static_cast<uint64_t>(std::stoll(*it));
			
			if(v < minCost)
				minCost = v;
			
			grid[i][j] = new EGridVertex(j, i, v);
			
			++j;
		}
		
		++i;
	}
	
	for(i = 0; i < GRID_HEIGHT; ++i)
	{
		for(j = 0; j < GRID_WIDTH; ++j)
		{
			if( (i + 1) < GRID_HEIGHT )
				grid[i][j]->addEdge(grid[i + 1][j]);
			
			if( (j + 1) < GRID_WIDTH )
				grid[i][j]->addEdge(grid[i][j + 1]);
		}
	}
	
	// Compute the minimum path sum and we're done!
	
	uint64_t minimum = EGridGraph::aStar(grid[0][0], grid[GRID_HEIGHT - 1][GRID_WIDTH - 1], minCost);
	
	std::cout << "The minimum path sum is: " << minimum << "\n";
	assert(minimum == 427337);
	
	return 0;
}

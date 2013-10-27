#include <iostream>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <climits>

#include <libquadra/euler/QShortestPath.h>

/*
 * In the 5 by 5 matrix below, the minimal path sum from the top left to bottom right, by only moving
 * to the right and down, is indicated in bold red and is equal to 2427.
 *
 *     [ (131)  673   234   103    18  ]
 *     [ (201) ( 96) (342)  965   150  ]
 *     [  630   803  (746) (422)  111  ]
 *     [  537   699   497  (121)  956  ]
 *     [  805   732   524  ( 37) (331) ]
 *
 * Find the minimal path sum, in matrix.txt (right click and 'Save Link/Target As...'), a 31K text file
 * containing an 80 by 80 matrix, from the top left to the bottom right by moving only right and down.
 */

int main(void)
{
	int i, j;
	uint64_t min = ~(0ULL);
	QGraphNode *matrix[80][80];
	
	// Zero-out the matrix, initially.
	
	for(i = 0; i < 80; ++i)
		for(j = 0; j < 80; ++j)
			matrix[i][j] = NULL;
	
	// Open the data file.
	
	std::string line;
	char *cline;
	char *tok;
	std::ifstream file("matrix.txt");
	
	if(!file.is_open())
	{
		std::cout << "Unable to open matrix.txt.\n";
		return 1;
	}
	
	// Read the matrix from the file.
	
	i = 0;
	while(file.good())
	{
		std::getline(file, line);
		cline = new char[line.length() + 1];
		strcpy(cline, line.c_str());
		tok = strtok(cline, ",");
		j = 0;
		while(tok != NULL)
		{
			// Make sure bounds are good.
			if( (i >= 80) || (j >= 80) )
			{
				std::cout << "Invalid input file.\n";
				return 1;
			}
			
			uint64_t x = static_cast<uint64_t>(strtoll(tok, NULL, 10));
			
			if(x < min)
				min = x;
			
			QGraphNode *n = new QGraphNode();
			n->setValue(x);
			
			matrix[i][j++] = n;
			tok = strtok(NULL, ",");
		}
		
		++i;
		delete[] cline;
	};
	
	file.close();
	
	// Ensure matrix is filled completely.
	
	for(i = 0; i < 80; ++i)
	{
		for(j = 0; j < 80; ++j)
		{
			if(matrix[i][j] == NULL)
			{
				std::cout << "Invalid input file.\n";
				return 1;
			}
		}
	}
	
	
	
	return 0;
}

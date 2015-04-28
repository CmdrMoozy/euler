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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

#include "libeuler/euler/ETriangleStructure.h"

int main(void)
{
	int result;
	int i, j;
	int rowValues[100];
	std::string buf;
	ETriangleStructure t(100);
	std::ifstream in("triangle.txt");
	
	if(!in.is_open())
	{
		std::cerr << "Unable to open 'triangle.txt'!\n";
		return 1;
	}
	
	i = 0;
	while(in.good())
	{
		getline(in, buf);
		if(buf.length() <= 1)
			continue;
		
		std::istringstream iss(buf, std::istringstream::in);
		
		for(j = 0; j < (i + 1); j++)
			iss >> rowValues[j];
		
		t.setRowAt(i, rowValues);
		i++;
	}
	
	in.close();
	
	result = t.getLargestPathSum();
	std::cout << "The maximum total from top to bottom in our triangle is: " << result << "\n";
	
	assert(result == 7273);
	return 0;
}

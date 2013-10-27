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

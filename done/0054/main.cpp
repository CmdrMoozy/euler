#include <iostream>
#include <cassert>
#include <string>
#include <fstream>

#include "libeuler/euler/EPoker.h"

int main(void)
{
	int wins;
	EPoker a, b;
	std::string line;
	std::ifstream ifile("poker.txt");
	
	if(!ifile.is_open())
	{
		std::cout << "Failed to open input file 'poker.txt'!\n";
		return 1;
	}
	
	wins = 0;
	while(ifile.good())
	{
		std::getline(ifile, line);
		if(line.size() != 29)
			continue;
		
		if(!a.parse(line.substr(0, 14)))
		{
			std::cout << "Unable to parse first hand!\n";
			return 1;
		}
		
		if(!b.parse(line.substr(15, 14)))
		{
			std::cout << "Unable to parse second hand!\n";
			return 1;
		}
		
		if(a > b)
			++wins;
	}
	
	std::cout << "Player 1 won: " << wins << " hands.\n";
	assert(wins == 376);
	
	return 0;
}

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
#include <cassert>
#include <string>
#include <fstream>

#include "common/euler/EPoker.h"

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

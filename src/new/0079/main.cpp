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

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

/*
 * A common security method used for online banking is to ask the user
 * for three random characters from a passcode. For example, if the passcode
 * was 531278, they may ask for the 2nd, 3rd, and 5th characters; the
 * expected reply would be: 317.
 *
 * The text file, keylog.txt, contains fifty successful login attempts.
 *
 * Given that the three characters are always asked for in order, analyse
 * the file so as to determine the shortest possible secret passcode of
 * unknown length.
 */

int main(void)
{
	std::string line;
	std::ifstream ifile("keylog.txt");

	if(!ifile.is_open())
	{
		std::cout << "Failed to open input file 'keylog.txt'!\n";
		return 1;
	}

	while(ifile.good())
	{
		std::getline(ifile, line);
	}

	return 0;
}

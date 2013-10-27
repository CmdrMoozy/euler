#include <iostream>
#include <cassert>
#include <fstream>
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

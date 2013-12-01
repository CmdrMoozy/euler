#include "EString.h"

#include <sstream>

/*!
 * This is a very simple function which splits the given string into a vector of string components,
 * with the given delimiter.
 *
 * \param s The string to split.
 * \param d The delimeter character to split by.
 * \return A list of components inside the given string.
 */
std::vector<std::string> EString::split(const std::string &s, char d)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> tokens;
	
	while(std::getline(ss, item, d))
	{
		tokens.push_back(item);
	}
	
	return tokens;
}

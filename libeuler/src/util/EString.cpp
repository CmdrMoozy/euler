#include "EString.h"

#include <sstream>
#include <algorithm>
#include <cctype>
#include <functional>
#include <locale>

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

/*!
 * This function removes any characters matching std::isspace from the left-hand side of
 * the given string.
 *
 * \param s The string to trim.
 * \return The string we modified.
 */
std::string &EString::ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(
		std::ptr_fun<int, int>(std::isspace))));
	
	return s;
}

/*!
 * This function removes any characters matching std::isspace from the right-hand side of
 * the given string.
 *
 * \param s The string to trim.
 * \return The string we modified.
 */
std::string &EString::rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(
		std::isspace))).base(), s.end());
	
        return s;
}

/*!
 * This function removes any leading or trailing characters which match std::isspace from
 * the given string.
 *
 * \param s The string to trim.
 * \return The string we modified.
 */
std::string &EString::trim(std::string &s)
{
	return EString::ltrim(EString::rtrim(s));
}

/*!
 * This function makes all of the characters in the given string lowercase. Note that this
 * only works as intended on ASCII strings; for multibyte character strings, the behavior
 * of this function is undefined.
 *
 * \param s The string to lowercase.
 * \return The string we modified.
 */
std::string &EString::strtolower(std::string &s)
{
	struct lower {
		void operator()(char &c)
		{
			c = tolower((unsigned char) c);
		}
	};
	
	std::for_each(s.begin(), s.end(), lower());
	return s;
}

/*!
 * This function makes all of the characters in the given string uppercase. Note that this
 * only works as intended on ASCII strings; for multibyte character strings, the behavior
 * of this function is undefined.
 *
 * \param s The string to uppercase.
 * \return The string we modified.
 */
std::string &EString::strtoupper(std::string &s)
{
	struct upper {
		void operator()(char &c)
		{
			c = toupper((unsigned char) c);
		}
	};
	
	std::for_each(s.begin(), s.end(), upper());
	return s;
}

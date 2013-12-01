#ifndef INCLUDE_LIBEULER_UTIL_STRING_H
#define INCLUDE_LIBEULER_UTIL_STRING_H

#include <vector>
#include <string>

/*!
 * \brief This class implements some simple string utilities.
 */
class EString
{
	public:
		static std::vector<std::string> split(const std::string &s, char d);
};

#endif

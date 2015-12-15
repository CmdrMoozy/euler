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

#ifndef common_string_Util_HPP
#define common_string_Util_HPP

#include <sstream>
#include <string>
#include <vector>

namespace euler
{
namespace string
{
namespace util
{
/*!
 * A version of strdup() which is guaranteed to return a valid pointer. If the
 * copy could not be allocated, then an exception is thrown instead.
 *
 * \param s The string to duplicate.
 * \return The copy of the input string.
 */
char *strdup(char const *s);

template <typename Iterator>
std::string join(Iterator begin, Iterator end, std::string const &delimiter)
{
	std::ostringstream oss;
	for(auto it = begin; it != end; ++it)
	{
		auto next = it;
		++next;
		oss << *it;
		if(next != end)
			oss << delimiter;
	}
	return oss.str();
}

std::string join(std::vector<std::string> const &strings,
                 std::string const &delimiter);
}
}
}

#endif

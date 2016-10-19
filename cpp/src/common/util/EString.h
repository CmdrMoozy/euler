/*
 * euler - A collection of ProjectEuler solutions, and supporting libraries and
 *tools.
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

#ifndef INCLUDE_LIBEULER_UTIL_STRING_H
#define INCLUDE_LIBEULER_UTIL_STRING_H

#include <string>
#include <vector>

/*!
 * \brief This class implements some simple string utilities.
 */
class EString
{
public:
	static std::vector<std::string> split(const std::string &s, char d);

	static std::string &ltrim(std::string &s);
	static std::string &rtrim(std::string &s);
	static std::string &trim(std::string &s);

	static std::string &strtolower(std::string &s);
	static std::string &strtoupper(std::string &s);
};

#endif

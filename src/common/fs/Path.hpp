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

#ifndef common_fs_Path_HPP
#define common_fs_Path_HPP

#include <string>
#include <vector>

#include "common/string/Util.hpp"

namespace euler
{
namespace fs
{
namespace path
{
template <typename Iterator> std::string join(Iterator begin, Iterator end)
{
	return string::util::join(begin, end, "/");
}

std::string join(std::vector<std::string> const &components);

std::vector<std::string> glob(std::string const &pattern);
}
}
}

#endif

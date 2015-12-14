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

#ifndef common_string_RegEx_HPP
#define common_string_RegEx_HPP

#include <memory>
#include <string>
#include <vector>

namespace euler
{
namespace string
{
namespace detail
{
class RegExImpl;
}

struct RegExOptions
{
};

struct RegExResult
{
	bool matched;
	std::vector<std::string> matches;
};

class RegEx
{
public:
	RegEx(std::string const &pattern, RegExOptions const &options = {});

	RegEx(RegEx const &) = delete;
	RegEx(RegEx &&) = default;
	RegEx &operator=(RegEx const &) = delete;
	RegEx &operator=(RegEx &&) = default;

	~RegEx();

	RegExResult
	match(std::string const &text, std::string::size_type startPos = 0,
	      std::string::size_type endPos = std::string::npos) const;

private:
	std::unique_ptr<detail::RegExImpl> impl;
};
}
}

#endif

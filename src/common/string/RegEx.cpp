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

#include "RegEx.hpp"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <stdexcept>

#include <re2/re2.h>
#include <re2/stringpiece.h>

namespace euler
{
namespace string
{
namespace detail
{
class RegExImpl
{
public:
	RegExImpl(std::string const &pattern, RegExOptions const &)
	        : regex(pattern)
	{
		if(!regex.ok())
			throw std::runtime_error(regex.error());
	}

	RegExImpl(RegExImpl const &) = delete;
	RegExImpl(RegExImpl &&) = default;
	RegExImpl &operator=(RegExImpl const &) = delete;
	RegExImpl &operator=(RegExImpl &&) = default;

	~RegExImpl() = default;

	re2::RE2 &get()
	{
		return regex;
	}

private:
	re2::RE2 regex;
};
}

RegEx::RegEx(std::string const &pattern, RegExOptions const &options)
        : impl(new detail::RegExImpl(pattern, options))
{
}

RegEx::~RegEx()
{
}

RegExResult RegEx::match(std::string const &text,
                         std::string::size_type startPos,
                         std::string::size_type endPos) const
{
	assert(!!impl);

	if(endPos == std::string::npos)
		endPos = text.length();

	std::vector<re2::StringPiece> matches(static_cast<std::size_t>(
	        impl->get().NumberOfCapturingGroups() + 1));
	bool matched = impl->get().Match(
	        text, static_cast<int>(startPos), static_cast<int>(endPos),
	        re2::RE2::Anchor::UNANCHORED, matches.data(),
	        static_cast<int>(matches.size()));

	RegExResult result = {matched, {}};
	if(!matched)
		return result;
	std::transform(matches.begin(), matches.end(),
	               std::back_inserter(result.matches),
	               [](re2::StringPiece const &piece)
	               {
		               return piece.as_string();
		       });
	return result;
}
}
}

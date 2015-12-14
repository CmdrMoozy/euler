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

#include "Path.hpp"

#include <cerrno>
#include <cstddef>
#include <stdexcept>

#include <glob.h>

#include "common/util/Error.hpp"

namespace
{
struct GlobBuffer
{
	glob_t buffer;

	GlobBuffer(char const *pattern, int flags,
	           int (*errfunc)(char const *, int))
	        : buffer()
	{
		switch(glob(pattern, flags, errfunc, &buffer))
		{
		case 0:
		case GLOB_NOMATCH: // No matches isn't really an error.
			break;

		case GLOB_NOSPACE:
			euler::util::error::throwErrnoError(ENOMEM);

		case GLOB_ABORTED:
			euler::util::error::throwErrnoError(EIO);

		default:
			throw std::runtime_error("Unknown error.");
		}
	}

	~GlobBuffer()
	{
		globfree(&buffer);
	}
};
}

namespace euler
{
namespace fs
{
namespace path
{
std::string join(std::vector<std::string> const &components)
{
	return ::euler::fs::path::join(components.begin(), components.end());
}

std::vector<std::string> glob(std::string const &pattern)
{
	GlobBuffer buffer(pattern.c_str(), GLOB_ERR | GLOB_NOSORT, nullptr);
	std::vector<std::string> paths;
	for(std::size_t i = 0; i < buffer.buffer.gl_pathc; ++i)
		paths.emplace_back(buffer.buffer.gl_pathv[i]);
	return paths;
}
}
}
}

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

#include <cassert>
#include <cerrno>
#include <cstddef>
#include <memory>
#include <stdexcept>

#include <glob.h>
#include <libgen.h>
#include <unistd.h>
#include <linux/limits.h>

#include <bdrck/cwrap/String.hpp>
#include <bdrck/util/Error.hpp>

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
			bdrck::util::error::throwErrnoError(ENOMEM);

		case GLOB_ABORTED:
			bdrck::util::error::throwErrnoError(EIO);

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

std::string baseJoin(std::string const &base,
                     std::vector<std::string> const &components)
{
	std::vector<std::string> newComponents;
	newComponents.reserve(components.size() + 1);
	newComponents.emplace_back(base);
	newComponents.insert(newComponents.end(), components.begin(),
	                     components.end());
	return ::euler::fs::path::join(newComponents);
}

std::vector<std::string> glob(std::string const &pattern)
{
	GlobBuffer buffer(pattern.c_str(), GLOB_ERR | GLOB_NOSORT, nullptr);
	std::vector<std::string> paths;
	for(std::size_t i = 0; i < buffer.buffer.gl_pathc; ++i)
		paths.emplace_back(buffer.buffer.gl_pathv[i]);
	return paths;
}

std::string currentExecutable()
{
	char buffer[PATH_MAX];
	ssize_t ret = readlink("/proc/self/exe", buffer, PATH_MAX - 1);
	if(ret == -1)
		::bdrck::util::error::throwErrnoError();
	assert(static_cast<std::size_t>(ret) < (PATH_MAX - 1));
	buffer[ret] = '\0';
	return buffer;
}

std::string currentPath()
{
	std::unique_ptr<char, std::function<void(char *)>> duplicate(
	        ::bdrck::cwrap::string::strdup(currentExecutable().c_str()),
	        [](char *p)
	        {
		        free(p);
		});
	return dirname(duplicate.get());
}

std::string sourcePath(std::vector<std::string> const &components)
{
	return baseJoin(EULER_SOURCE_DIR, components);
}
std::string binaryPath(std::vector<std::string> const &components)
{
	return baseJoin(EULER_SOURCE_DIR, components);
}

std::string currentPath(std::vector<std::string> const &components)
{
	return baseJoin(currentPath(), components);
}
}
}
}

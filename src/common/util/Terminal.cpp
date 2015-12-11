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

#include "Terminal.hpp"

#include <cassert>
#include <cerrno>

#include <unistd.h>

#include "common/util/Error.hpp"

namespace euler
{
namespace util
{
namespace terminal
{
bool isInteractiveTerminal(StdStream stream)
{
	int fd = -1;
	switch(stream)
	{
	case StdStream::In:
		fd = STDIN_FILENO;
		break;
	case StdStream::Out:
		fd = STDOUT_FILENO;
		break;
	case StdStream::Err:
		fd = STDERR_FILENO;
		break;
	}
	assert(fd != -1);

	int r = isatty(fd);
	if(r == 0 && errno == EBADF)
		error::throwErrnoError();

	return r == 1;
}
}
}
}

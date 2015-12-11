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

#include "Error.hpp"

#include <cerrno>
#include <cstring>
#include <stdexcept>

namespace euler
{
namespace util
{
namespace error
{
[[noreturn]] void throwErrnoError(std::experimental::optional<int> error,
                                  std::string const &defaultMessage)
{
	if(!error)
		error = errno;
	char *message = std::strerror(*error);
	throw std::runtime_error(message != nullptr ? message
	                                            : defaultMessage.c_str());
}
}
}
}

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

#include <fstream>
#include <stdexcept>
#include <string>

#include "common/euler/EPoker.h"
#include "common/util/Path.hpp"
#include "common/util/Process.hpp"

namespace
{
constexpr int EXPECTED_RESULT = 376;

euler::util::process::ProblemResult<int> problem()
{
	int wins;
	EPoker a, b;
	std::string line;
	std::ifstream ifile(euler::util::path::currentPath({"poker.txt"}));

	if(!ifile.is_open())
	{
		throw std::runtime_error(
		        "Failed to open input file 'poker.txt'!");
	}

	wins = 0;
	while(ifile.good())
	{
		std::getline(ifile, line);
		if(line.size() != 29)
			continue;

		if(!a.parse(line.substr(0, 14)))
		{
			throw std::runtime_error("Unable to parse first hand!");
		}

		if(!b.parse(line.substr(15, 14)))
		{
			throw std::runtime_error(
			        "Unable to parse second hand!");
		}

		if(a > b)
			++wins;
	}

	return {wins, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

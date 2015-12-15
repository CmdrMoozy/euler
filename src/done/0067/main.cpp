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
#include <sstream>
#include <stdexcept>
#include <string>

#include "common/euler/ETriangleStructure.h"
#include "common/fs/Path.hpp"
#include "common/util/Process.hpp"

namespace
{
constexpr int EXPECTED_RESULT = 7273;

euler::util::process::ProblemResult<int> problem()
{
	int rowValues[100];
	std::string buf;
	ETriangleStructure t(100);
	std::ifstream in(euler::fs::path::currentPath({"triangle.txt"}));

	if(!in.is_open())
		throw std::runtime_error("Unable to open 'triangle.txt'!");

	std::size_t i = 0;
	while(in.good())
	{
		getline(in, buf);
		if(buf.length() <= 1)
			continue;

		std::istringstream iss(buf, std::istringstream::in);

		for(std::size_t j = 0; j < (i + 1); j++)
			iss >> rowValues[j];

		t.setRowAt(i, rowValues);
		i++;
	}

	in.close();

	return {t.getLargestPathSum(), EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

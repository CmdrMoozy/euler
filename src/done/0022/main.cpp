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

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "common/util/Process.hpp"

/*
 * Using names.txt, a 46K text file containing over five-thousand first names,
 * begin by sorting it into alphabetical order. Then working out the
 * alphabetical value for each name, multiply this value by its alphabetical
 * position in the list to obtain a name score.
 *
 * For example, when the list is sorted into alphabetical order, COLIN, which is
 * worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN
 * would obtain a score of 938 x 53 + 49714.
 *
 * What is the total of all the name scores in the file?
 */

namespace
{
constexpr uint64_t EXPECTED_RESULT = 871198282;

euler::util::process::ProblemResult<uint64_t> problem()
{
	/*
	 * This is a bit of a naieve solution... Basically we use a shell script
	 * to process the names list
	 * a bit, then we read all of them into a vector, which we then sort,
	 * and we add all the scores up.
	 * Despite this, this solution still executes quite rapidly.
	 */

	uint64_t total, name;
	std::string buf;
	std::vector<std::string> names;
	std::vector<std::string>::iterator it;
	std::ifstream in("names_processed.txt");

	if(!in.is_open())
	{
		throw std::runtime_error(
		        "Unable to open 'names_processed.txt'!");
	}

	while(in.good())
	{
		std::getline(in, buf);
		names.push_back(buf);
	}

	in.close();

	std::sort(names.begin(), names.end());

	total = 0;
	for(it = names.begin(); it < names.end(); it++)
	{
		name = 0;

		for(std::size_t i = 0; i < it->length(); i++)
		{
			name += static_cast<unsigned long int>(
			        it->at(i) - 'A' + static_cast<char>(1));
		}

		name *= static_cast<unsigned long int>(it - names.begin() + 1);
		total += name;
	}

	return {total, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

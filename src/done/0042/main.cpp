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

#include <cstdint>
#include <fstream>
#include <set>
#include <stdexcept>
#include <string>

#include "common/fs/Path.hpp"
#include "common/math/EMath.h"
#include "common/util/Process.hpp"

/*
 * The nth term of the sequence of triangle numbers is given by,
 * tn = 1/2 * n * (n+1); so the first ten triangle numbers are:
 *
 *     1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
 *
 * By converting each letter in a word to a number corresponding to its
 * alphabetical position and adding these values we form a word value. For
 * example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word
 * value is a triangle number then we shall call the word a triangle world.
 *
 * Using words.txt (right click and 'Save Link/Target As...'), a 16K text file
 * containing nearly two-thousand common English words, how many are triangle
 * words?
 */

namespace
{
constexpr uint64_t EXPECTED_RESULT = 162;

euler::util::process::ProblemResult<uint64_t> problem()
{
	std::string word;
	std::ifstream fin;
	uint64_t *triangleNumbers;
	std::multiset<uint64_t> scores;
	std::multiset<uint64_t>::iterator it;
	uint64_t i, v, maxScore, result;

	// Read in and score all of our words.

	fin.open(euler::fs::path::currentPath({"words-processed.txt"}));
	if(!fin.is_open())
	{
		throw std::runtime_error(
		        "Unable to open 'words-processed.txt'!");
	}

	while(fin.good())
	{
		getline(fin, word);

		for(v = 0, i = 0; i < word.length(); i++)
			v += static_cast<uint32_t>(word.at(i) - 'A' + 1);

		scores.insert(v);
	}

	fin.close();

	// Build a list of triangle numbers.

	maxScore = (*scores.rbegin());
	triangleNumbers = new uint64_t[maxScore + 1];

	i = 0;
	v = EMath::getTriangleNumberN(i);
	while(v <= maxScore)
	{
		triangleNumbers[v] = v;
		v = EMath::getTriangleNumberN(i++);
	}

	// Check each score to see if it is a triangle number.

	for(result = 0, it = scores.begin(); it != scores.end(); it++)
		if(triangleNumbers[(*it)] == (*it))
			result++;

	delete[] triangleNumbers;
	return {result, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

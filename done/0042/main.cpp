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

#include <iostream>
#include <cassert>
#include <set>
#include <fstream>
#include <string>
#include <cstdint>

#include "libeuler/math/EMath.h"

/*
 * The nth term of the sequence of triangle numbers is given by, tn = 1/2 * n * (n+1); so the first
 * ten triangle numbers are:
 *
 *     1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
 *
 * By converting each letter in a word to a number corresponding to its alphabetical position and adding
 * these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If
 * the word value is a triangle number then we shall call the word a triangle world.
 *
 * Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-
 * thousand common English words, how many are triangle words?
 */

int main(void)
{
	std::string word;
	std::ifstream fin;
	uint32_t *triangleNumbers;
	std::multiset<uint32_t> scores;
	std::multiset<uint32_t>::iterator it;
	uint32_t i, v, maxScore, result;

	// Read in and score all of our words.

	fin.open("words-processed.txt");
	if(!fin.is_open())
	{
		std::cout << "Unable to open 'words-processed.txt'!\n";
		return 1;
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
	triangleNumbers = new uint32_t[maxScore + 1];

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

	std::cout << "The number of triangle words in the text file is: " << result << "\n";

	delete[] triangleNumbers;
	assert(result == 162);
	return 0;
}

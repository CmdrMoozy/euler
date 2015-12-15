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

#include <cassert>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>

#include "common/fs/Path.hpp"
#include "common/types/ERomanNumeral.h"
#include "common/util/EString.h"
#include "common/util/Process.hpp"

/*
 * The rules for writing Roman numerals allow for many ways of writing each
 * number (see About Roman Numerals...). However, there is always a "best" way
 * of writing a particular number.
 *
 * For example, the following represent all of the legitimate ways of writing
 * the number sixteen:
 *
 *     IIIIIIIIIIIIIIII
 *     VIIIIIIIIIII
 *     VVIIIIII
 *     XIIIIII
 *     VVVI
 *     XVI
 *
 * The last example being considered the most efficient, as it uses the least
 * number of numerals.
 *
 * The 11K text file, roman.txt (right click and 'Save Link/Target As...'),
 * contains one thousand numbers written in valid, but not necessarily minimal,
 * Roman numerals; that is, they are arranged in descending units and obey the
 * subtractive pair rule (see About Roman Numerals... for the definitive rules
 * for this problem).
 *
 * Find the number of characters saved by writing each of these in their minimal
 * form.
 *
 * Note: You can assume that all the Roman numerals in the file contain no more
 * than four consecutive identical units.
 */

namespace
{
constexpr uint64_t EXPECTED_RESULT = 743;

euler::util::process::ProblemResult<uint64_t> problem()
{
	ERomanNumeral numeral;
	uint64_t inchars, outchars;

	// Open the input file with the list of roman numerals.

	std::string line;
	std::ifstream numeralfile(euler::fs::path::currentPath({"roman.txt"}));

	if(!numeralfile.is_open())
	{
		throw std::runtime_error(
		        "Couldn't open 'roman.txt' for reading.");
	}

	// Process each line of the file...

	inchars = 0;
	outchars = 0;

	while(std::getline(numeralfile, line))
	{
		// Make note of the input length.

		EString::trim(line);

		inchars += static_cast<uint64_t>(line.length());

		// Parse this line, and get the output length.

		if(!numeral.parse(line))
		{
			throw std::runtime_error(
			        "Invalid roman numeral in 'roman.txt'.");
		}

		std::string out = numeral.getStringValue();

		outchars += static_cast<uint64_t>(out.length());
	}

	// Print our answer!

	assert(inchars >= outchars);
	return {inchars - outchars, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

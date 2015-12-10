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
#include <cstdint>
#include <set>

#include "common/math/EMath.h"
#include "common/math/EPrimeSieve.h"

int main(void)
{
	// Range is 1 < n < 10^7 as given in the problem description.
	EPrimeSieve sieve(10000000);

	uint32_t t, result = 0;

	for(std::set<uint32_t>::reverse_iterator it = sieve.rbegin();
	    it != sieve.rend(); ++it)
	{
		std::cout << (*it) << "\n";
		t = EMath::totient((*it));

		if(EMath::isPermutationOf((*it), t))
		{
			result = (*it);
			break;
		}
	}

	std::cout << "Number with smallest ratio is: " << result << "\n";

	return 0;
}

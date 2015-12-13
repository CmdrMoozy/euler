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

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <string>

#include <mpfr.h>

#include "common/util/Process.hpp"

/*
 * Comparing two numbers written in index form like 2^11 and 3^7 is not
 * difficult, as any calculator would confirm that 2^11 = 2048 < 3^7 = 2187.
 *
 * However, confirming that 632382^518061 > 519432^525806 would be much more
 * difficult, as both numbers contain over three million digits.
 *
 * Using base_exp.txt, a 22K text file containing one thousand lines with a
 * base/exponent pair on each line, determine which line number has the
 * greatest numerical value.
 *
 * NOTE: The first two lines in the file represent the numbers in the example
 * given above.
 */

namespace
{
constexpr int EXPECTED_RESULT = 709;

/*!
 * This function compares two b^e values. We take advantage of the fact that
 * deciding if:
 *
 *     a^b > c^d is equivalent to deciding if:
 *     log(a^b) > log(c^d)
 *
 * This function is a typical three-state compare: it returns an integer greater
 * than, equal to or less than zero if a is greater than, equal to or less than
 * b, respectively.
 *
 * \param ba The base of the first value.
 * \param ea The exponent of the first value.
 * \param bb The base of the second value.
 * \param be The exponent of the second value.
 */
int compare(uint64_t ba, uint64_t ea, uint64_t bb, uint64_t be)
{
	int ret;
	mpfr_t a, b, tmp;

	mpfr_init2(a, static_cast<mpfr_prec_t>(128));
	mpfr_init2(b, static_cast<mpfr_prec_t>(128));
	mpfr_init2(tmp, static_cast<mpfr_prec_t>(128));

	// Set our mpfr values to the bases.

	mpfr_set_uj(a, ba, MPFR_RNDN);
	mpfr_set_uj(b, bb, MPFR_RNDN);

	// Take the logarithm of each.

	mpfr_log(a, a, MPFR_RNDN);
	mpfr_log(b, b, MPFR_RNDN);

	// Multiply the values by their respective exponents.

	mpfr_set_uj(tmp, ea, MPFR_RNDN);
	mpfr_mul(a, a, tmp, MPFR_RNDN);

	mpfr_set_uj(tmp, be, MPFR_RNDN);
	mpfr_mul(b, b, tmp, MPFR_RNDN);

	// Done!

	ret = mpfr_cmp(a, b);

	mpfr_clear(a);
	mpfr_clear(b);
	mpfr_clear(tmp);

	return ret;
}

euler::util::process::ProblemResult<int> problem()
{
	std::string line;
	std::ifstream ifile;
	int ln = 0, maxl = 0;
	uint64_t maxb = 1, maxe = 1;

	ifile.open("base_exp.txt", std::ifstream::in);
	if(!ifile.is_open())
		throw std::runtime_error("Unable to open base_exp.txt!");

	while(ifile.good())
	{
		std::getline(ifile, line);
		++ln;

		if(line.length() > 0)
		{
			// Parse this particular line.

			std::string bs, es;
			uint64_t b = 0, e = 0;
			size_t idx;

			idx = line.find(",");

			if(idx == std::string::npos)
			{
				throw std::runtime_error(
				        "Invalid line in input file.");
			}

			bs = line.substr(0, idx);
			es = line.substr(idx + 1, line.length() - (idx + 1));

			b = static_cast<uint64_t>(
			        strtoll(bs.c_str(), NULL, 10));
			e = static_cast<uint64_t>(
			        strtoll(es.c_str(), NULL, 10));

			if((b == 0) || (e == 0))
			{
				throw std::runtime_error(
				        "Invalid line in input file.");
			}

			// Compare this line's value with our previous
			// maximum value.

			if(compare(maxb, maxe, b, e) < 0)
			{
				maxb = b;
				maxe = e;
				maxl = ln;
			}
		}
	}

	return {maxl, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

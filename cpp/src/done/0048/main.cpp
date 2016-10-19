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
#include <sstream>
#include <string>

#include <gmp.h>
#include <gmpxx.h>

#include "common/util/Process.hpp"

/*
 * The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
 *
 * Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
 */

namespace
{
constexpr char EXPECTED_RESULT[] = "9110846700";

euler::util::process::ProblemResult<std::string> problem()
{
	mpz_class power, m;
	uint32_t sum[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	// Add the last ten digits of each number.
	for(uint32_t i = 1; i <= 1000; i++)
	{
		mpz_ui_pow_ui(power.get_mpz_t(), i, i);

		uint32_t j = 1;
		while((power > 0) && (j <= 10))
		{
			m = (power % 10);
			sum[10 - (j++)] += m.get_ui();
			power /= 10;
		}
	}

	// Carry everything.
	for(uint32_t i = 9; i > 0; i--)
	{
		sum[i - 1] += sum[i] / 10;
		sum[i] %= 10;
	}
	sum[0] %= 10;

	std::ostringstream oss;
	for(std::size_t i = 0; i < 10; ++i)
		oss << sum[i];
	return {oss.str(), EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

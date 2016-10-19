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

#include "common/util/EDate.h"
#include "common/util/Process.hpp"

/*
 * You are given the following information, but you may prefer to do some
 * reasearch for yourself.
 *
 * - 1 Jan 1900 was a Monday.
 * - Thirty days has September,
 *   April, June and November.
 *   All the rest have thirty-one,
 *   Saving February alone,
 *   Which has twenty-eight, rain or shine
 *   And on leap years, twenty-nine.
 * - A leap year occurs on any year evenly divisible by 4, but not on a century
 *   unless it is divisble by 400.
 *
 * How many Sundays fell on the first of the month during the twentieth century
 * (1 Jan 1901 to 31 Dec 2000)?
 */

namespace
{
constexpr int EXPECTED_RESULT = 171;

euler::util::process::ProblemResult<int> problem()
{
	int s;
	EDate d(1900, 1, 1, EDate::Monday);
	EDate e(2000, 12, 31);

	// Fast-forward to the start of our interval, 1901/01/01.
	d.addDays(EDate::getDaysInYear(1900));

	// Progress to our first Sunday.
	while(d.getDayOfWeek() != EDate::Sunday)
		d.addDays(1);

	// Keep looping from here until we have found every Sunday!
	s = 0;
	do
	{
		if(d.getDay() == 1)
			s++;

		d.addWeeks(1);
	} while(d < e);

	return {s, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

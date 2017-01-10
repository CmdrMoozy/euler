// euler - A collection of ProjectEuler libraries, tools, and solutions.
// Copyright (C) 2013 Axel Rasmussen
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// You are given the following information, but you may prefer to do some
// research for yourself.
//
// - 1 Jan 1900 was a Monday.
// - Thirday days has September,
//   April, June and November.
//   All the rest have thirty-one,
//   Saving February alone,
//   Which has twenty-eight, rain or shine
//   And on leap years, twenty-nine.
// - A leap year occurs on any year evenly divisible by 4, but not on a century
//   unless it is divisible by 400.
//
// How many Sundays fell on the first of the month during the twentieth century
// (1 Jan 1901 to 31 Dec 2000)?

extern crate euler;
use self::euler::dsc::date::*;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: usize = 171;

fn main() {
    main_impl(|| -> EulerResult<ProblemAnswer<usize>> {
        let mut current_date = Date::new(1900, 1, 1, Some(DayOfWeek::Monday));
        let end_date = Date::new(2000, 12, 31, None);

        // Fast-forward to the start of our interval, 1901-01-01.
        current_date.add_years(1);

        // Progress to the first Sunday in that year.
        while current_date.get_day_of_week().unwrap() != DayOfWeek::Sunday {
            current_date.add_days(1);
        }

        // Iterate over each sunday in the year.
        let mut sundays: usize = 0;
        while current_date < end_date {
            // If this date is the first of its month, this is a Sunday we want to count.
            if current_date.get_raw_date().2 == 1 {
                sundays += 1;
            }

            current_date.add_weeks(1);
        }

        Ok(ProblemAnswer {
            actual: sundays,
            expected: EXPECTED_RESULT,
        })
    });
}

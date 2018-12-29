// Copyright 2013 Axel Rasmussen
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

use euler::dsc::date::*;
use euler::util::error::*;
use euler::util::problem::*;

const EXPECTED_RESULT: usize = 171;

fn main() {
    main_impl(|| -> Result<ProblemAnswer<usize>> {
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

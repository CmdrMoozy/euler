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

use std::cmp::Ordering;

fn days_in_year(year: i64) -> u64 {
    match year % 100 {
        0 => {
            match year % 400 {
                0 => 366,
                _ => 365,
            }
        },
        _ => {
            match year % 4 {
                0 => 366,
                _ => 365,
            }
        },
    }
}

fn days_in_month(year: i64, month: i64) -> u64 {
    match month {
        2 => {
            match days_in_year(year) {
                365 => 28,
                _ => 29,
            }
        },
        4 => 30,
        6 => 30,
        9 => 30,
        11 => 30,
        _ => 31,
    }
}

#[derive(Clone, Debug, PartialEq)]
pub enum DayOfWeek {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
}

/// This structure provides some rudimentary mechanisms to perform math with
/// dates. This struct lives in the "euler" crate's Domain Specific Code module
/// because although it is used for some ProjectEuler solutions, in general the
/// chrono crate should be used instead (unless the entire point of a problem
/// is to figure out how date math works).
#[derive(Clone, Debug)]
pub struct Date {
    year: i64,
    month: i64,
    day: i64,
    dow: Option<DayOfWeek>,
}

impl Date {
    pub fn new(year: i64, month: i64, day: i64, dow: Option<DayOfWeek>) -> Date {
        Date {
            year: year,
            month: month,
            day: day,
            dow: dow,
        }
    }

    /// Returns this Date's internal representation, as integer year, month,
    /// and day values (respectively).
    pub fn get_raw_date(&self) -> (i64, i64, i64) { (self.year, self.month, self.day) }

    pub fn get_day_of_week(&self) -> Option<DayOfWeek> { self.dow.clone() }

    pub fn add_days(&mut self, days: u64) {
        for _ in 0..days {
            self.day += 1;

            if let Some(dow) = self.dow.clone() {
                self.dow = Some(match dow {
                    DayOfWeek::Sunday => DayOfWeek::Monday,
                    DayOfWeek::Monday => DayOfWeek::Tuesday,
                    DayOfWeek::Tuesday => DayOfWeek::Wednesday,
                    DayOfWeek::Wednesday => DayOfWeek::Thursday,
                    DayOfWeek::Thursday => DayOfWeek::Friday,
                    DayOfWeek::Friday => DayOfWeek::Saturday,
                    DayOfWeek::Saturday => DayOfWeek::Sunday,
                })
            }

            if self.day > days_in_month(self.year, self.month) as i64 {
                self.day = 1;
                self.month += 1;
            }

            if self.month > 12 {
                self.month = 1;
                self.year += 1;
            }
        }
    }

    pub fn add_weeks(&mut self, weeks: u64) { self.add_days(weeks * 7); }

    pub fn add_months(&mut self, months: u64) {
        for _ in 0..months {
            let y: i64 = self.year;
            let m: i64 = self.month;
            self.add_days(days_in_month(y, m));
        }
    }

    pub fn add_years(&mut self, years: u64) { self.add_months(12 * years) }
}

impl PartialEq for Date {
    fn eq(&self, other: &Date) -> bool {
        self.year == other.year && self.month == other.month && self.day == other.day
    }
}

impl PartialOrd for Date {
    fn partial_cmp(&self, other: &Date) -> Option<Ordering> {
        if self.year > other.year {
            Some(Ordering::Greater)
        } else if self.year < other.year {
            Some(Ordering::Less)
        } else {
            if self.month > other.month {
                Some(Ordering::Greater)
            } else if self.month < other.month {
                Some(Ordering::Less)
            } else {
                if self.day > other.day {
                    Some(Ordering::Greater)
                } else if self.day < other.day {
                    Some(Ordering::Less)
                } else {
                    Some(Ordering::Equal)
                }
            }
        }
    }
}

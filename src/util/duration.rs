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

use std::cmp::{Ord, Ordering, PartialOrd};
use std::convert::From;
use std::fmt;
use std::iter::Sum;
use std::ops::Deref;
use std::option::Option;
use std::time;

const NANOS_PER_SECOND: u64 = 1000000000;

#[derive(Clone, Eq, PartialEq)]
pub struct Duration {
    duration: time::Duration,
}

impl Duration {
    pub fn from_total_nanos(nanos: u64) -> Duration {
        Duration {
            duration: time::Duration::new(nanos / NANOS_PER_SECOND,
                                          (nanos % NANOS_PER_SECOND) as u32),
        }
    }

    pub fn total_nanos(&self) -> u64 {
        self.duration.as_secs() * NANOS_PER_SECOND + (self.duration.subsec_nanos() as u64)
    }
}

impl From<time::Duration> for Duration {
    fn from(duration: time::Duration) -> Duration { Duration { duration: duration } }
}

impl Deref for Duration {
    type Target = time::Duration;

    fn deref(&self) -> &time::Duration { &self.duration }
}

impl PartialOrd for Duration {
    fn partial_cmp(&self, other: &Duration) -> Option<Ordering> {
        Some(self.duration.cmp(&other.duration))
    }
}

impl Ord for Duration {
    fn cmp(&self, other: &Duration) -> Ordering { self.duration.cmp(&other.duration) }
}

impl<'a> Sum<&'a Duration> for Duration {
    fn sum<I>(iter: I) -> Duration
        where I: Iterator<Item = &'a Duration>
    {
        Duration::from(iter.map(|d| d.duration).fold(time::Duration::new(0, 0), |acc, d| acc + d))
    }
}

impl fmt::Display for Duration {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let milliseconds: u32 = self.duration.subsec_nanos() / 1000000;
        let submillisecond_nanos: u32 = self.duration.subsec_nanos() % 1000000;

        write!(f,
               "{}s+{}ms+{}ns",
               self.duration.as_secs(),
               milliseconds,
               submillisecond_nanos)
    }
}

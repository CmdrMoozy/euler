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

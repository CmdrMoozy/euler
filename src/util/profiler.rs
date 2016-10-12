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
//

use std::string::String;
use std::time::{Duration, Instant};

pub struct Profiler {
    start: Instant,
    log_on_drop: bool,
    log_prefix: String,
}

impl Profiler {
    pub fn new(log_on_drop: bool, log_prefix: &str) -> Profiler {
        Profiler {
            start: Instant::now(),
            log_on_drop: log_on_drop,
            log_prefix: log_prefix.to_owned(),
        }
    }

    pub fn get_elapsed(&self) -> Duration { Instant::now().duration_since(self.start) }

    pub fn log_elapsed(&self) {
        let elapsed = self.get_elapsed();
        info!("{}Elapsed time: {}s+{}ns",
              self.log_prefix,
              elapsed.as_secs(),
              elapsed.subsec_nanos());
    }
}

impl Drop for Profiler {
    fn drop(&mut self) {
        if self.log_on_drop {
            self.log_elapsed();
        }
    }
}

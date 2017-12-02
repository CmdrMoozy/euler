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

use std::string::String;
use std::time;
use util::duration;

pub struct Profiler {
    start: time::Instant,
    log_on_drop: bool,
    log_prefix: String,
}

impl Profiler {
    pub fn new(log_on_drop: bool, log_prefix: &str) -> Profiler {
        Profiler {
            start: time::Instant::now(),
            log_on_drop: log_on_drop,
            log_prefix: log_prefix.to_owned(),
        }
    }

    pub fn get_elapsed(&self) -> duration::Duration {
        duration::Duration::from(time::Instant::now().duration_since(self.start))
    }

    pub fn log_elapsed(&self) {
        let elapsed = self.get_elapsed();
        info!("{}Elapsed time: {}", self.log_prefix, elapsed);
    }
}

impl Drop for Profiler {
    fn drop(&mut self) {
        if self.log_on_drop {
            self.log_elapsed();
        }
    }
}

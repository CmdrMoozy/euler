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


use bdrck_log;
use std::fmt::{self, Debug, Display};
use std::process;
use util::error::*;

pub const EXIT_SUCCESS: i32 = 0;
pub const EXIT_FAILURE: i32 = 1;

#[derive(Debug, Eq, PartialEq)]
pub struct ProblemAnswer<R: Debug + Display + Eq + PartialEq> {
    pub actual: R,
    pub expected: R,
}

impl<R> ProblemAnswer<R>
    where R: Debug + Display + Eq + PartialEq
{
    pub fn is_correct(&self) -> bool { self.actual == self.expected }
}

impl<R> fmt::Display for ProblemAnswer<R>
    where R: Debug + Display + Eq + PartialEq
{
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f,
               "Actual result: {} / Expected result: {}",
               self.actual,
               self.expected)
    }
}

pub fn main_impl<R, F: FnOnce() -> Result<ProblemAnswer<R>>>(problem_impl: F) -> !
    where R: Debug + Display + Eq + PartialEq
{
    bdrck_log::init_debug_logger().unwrap();
    process::exit(match problem_impl() {
        Err(e) => {
            info!("{}", e);
            EXIT_FAILURE
        },
        Ok(r) => {
            info!("{}", r);
            match r.is_correct() {
                true => EXIT_SUCCESS,
                false => EXIT_FAILURE,
            }
        },
    });
}

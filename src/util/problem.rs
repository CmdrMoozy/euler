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

use bdrck_log;
use std::fmt::{self, Debug, Display};
use std::process;

use super::error::*;

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

pub fn main_impl<R, F: FnOnce() -> EulerResult<ProblemAnswer<R>>>(problem_impl: F) -> !
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

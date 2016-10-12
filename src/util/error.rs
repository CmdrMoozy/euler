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

use backtrace::Backtrace;
use std::error::Error;
use std::fmt;
use std::result::Result;

// #[derive(Clone, Debug, Eq, PartialEq)]
// pub enum ErrorKind {
// }

#[derive(Debug)]
pub struct EulerError {
    backtrace: Backtrace,
}

impl EulerError {
    pub fn new() -> EulerError { EulerError { backtrace: Backtrace::new() } }
}

// impl PartialEq for EulerError {
// fn eq(&self, other: &EulerError) -> bool { self.kind == other.kind }
// }
//
// impl Eq for EulerError {}

impl Error for EulerError {
    fn description(&self) -> &str { "Generic Euler error." }
}

impl fmt::Display for EulerError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result { f.write_str(self.description()) }
}

pub type EulerResult<T> = Result<T, EulerError>;

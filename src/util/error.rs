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
use std::convert::From;
use std::error::Error;
use std::fmt;
use std::io;
use std::num;
use std::result::Result;
use std::string::String;

#[derive(Clone, Debug, Eq, PartialEq)]
pub enum ErrorKind {
    InvalidArgument { message: String },
    IoError { cause: String },
}

#[derive(Debug)]
pub struct EulerError {
    backtrace: Backtrace,
    kind: ErrorKind,
}

impl EulerError {
    pub fn new(kind: ErrorKind) -> EulerError {
        EulerError {
            backtrace: Backtrace::new(),
            kind: kind,
        }
    }
}

impl PartialEq for EulerError {
    fn eq(&self, other: &EulerError) -> bool { self.kind == other.kind }
}

impl Eq for EulerError {}

impl From<io::Error> for EulerError {
    fn from(e: io::Error) -> EulerError {
        EulerError::new(ErrorKind::IoError { cause: format!("{}", e) })
    }
}

impl From<num::ParseIntError> for EulerError {
    fn from(e: num::ParseIntError) -> EulerError {
        EulerError::new(ErrorKind::InvalidArgument { message: format!("{}", e) })
    }
}

impl Error for EulerError {
    fn description(&self) -> &str {
        match self.kind {
            ErrorKind::InvalidArgument { message: _ } => "Invalid argument",
            ErrorKind::IoError { cause: _ } => "Input/output error",
        }
    }
}

impl fmt::Display for EulerError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self.kind {
            ErrorKind::InvalidArgument { message: ref m } => {
                write!(f, "{}: {}", self.description(), m)
            },
            ErrorKind::IoError { cause: ref c } => write!(f, "{}: {}", self.description(), c),
        }
    }
}

pub type EulerResult<T> = Result<T, EulerError>;

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

extern crate atomic;
extern crate bdrck_log;
extern crate bdrck_params;
#[macro_use]
extern crate error_chain;
extern crate glob;
extern crate gmp;
extern crate itoa;
#[macro_use]
extern crate lazy_static;
#[macro_use]
extern crate log;
extern crate num;
extern crate num_cpus;
extern crate pdqsort;
extern crate rand;
extern crate regex;
extern crate rust_mpfr as mpfr;

pub mod algorithm;
pub mod dsc;
pub mod math;
pub mod structs;
pub mod util;

#[cfg(test)]
mod tests;

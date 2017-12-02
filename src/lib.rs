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

extern crate atomic;
extern crate bdrck;
#[macro_use]
extern crate error_chain;
extern crate glob;
extern crate itoa;
#[macro_use]
extern crate lazy_static;
extern crate libc;
extern crate num;
extern crate num_cpus;
extern crate pdqsort;
extern crate rand;
extern crate regex;
extern crate rug;

pub mod algorithm;
pub mod dsc;
pub mod math;
pub mod structs;
pub mod util;

#[cfg(test)]
mod tests;

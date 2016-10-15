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

pub mod exp;
pub mod prime;
pub mod sequence;

use std::ops::{Div, Rem};

/// This function divides the given dividend by the given divisor, and returns
/// a tuple of the resulting quoteient and remainder.
pub fn divide<T: Copy + Div<Output = T> + Rem<Output = T>>(dividend: T, divisor: T) -> (T, T) {
    (dividend / divisor, dividend % divisor)
}

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

// A permutation is an ordered arrangement of objects. For example, 3124 is one
// possible permutation of the digits 1, 2, 3 and 4. If all of the permutations
// are listed numerically or alphabetically, we call it lexicographic order.
// The lexicographic permutations of 0, 1 and 2 are:
//
// 012 021 102 120 201 210
//
// What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4,
// 5, 6, 7, 8 and 9?

extern crate euler;
use self::euler::algorithm;
use self::euler::util::error::*;
use self::euler::util::problem::*;

const EXPECTED_RESULT: &'static str = "2783915460";

fn main() {
    main_impl(|| -> Result<ProblemAnswer<String>> {
        let mut permutator = vec!['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'];

        // Permutate until we are at the millionth permutation.
        for _iteration in 1..1000000 {
            algorithm::permutate(&mut permutator);
        }

        Ok(ProblemAnswer {
            actual: permutator.iter().cloned().collect::<String>(),
            expected: EXPECTED_RESULT.to_owned(),
        })
    });
}

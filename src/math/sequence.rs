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

/// This function returns the nth Fibonacci number.
///
/// The Fibonacci sequence is defined such that F(0) = 0, F(1) = 1, and F(n) =
/// F(n-1) + F(n-2). For this function, however, we use a closed-form solution
/// to the Fibonacci sequence, so we can avoid unnecessary recursion.
///
/// Note that precision is only guaranteed up to n = 5000.
pub fn get_nth_fibonacci_number(n: u64) -> u64 {
    // We use the closed-form solution called "Binet's Formula," defined here:
    // http://en.wikipedia.org/wiki/Fibonacci_number#Relation_to_the_golden_ratio
    //
    // The formula is: F(n) = (p^n - (1 - p)^n) / sqrt(5) where p is phi, the
    // Golden Ratio: p = (1 + sqrt(5)) / 2

    let sqrt_five: f64 = (5.0_f64).sqrt();
    let phi: f64 = (1.0 + sqrt_five) / 2.0;
    let psi: f64 = (1.0 - sqrt_five) / 2.0;
    let fib: f64 = (phi.powf(n as f64) - psi.powf(n as f64)) / sqrt_five;
    fib as u64
}

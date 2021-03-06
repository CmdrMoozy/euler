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

// Pentagonal numbers are generated by the formula, P(n) = (n(3n - 1)) / 2. The
// first ten pentagonal numbers are:
//
//     1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...
//
// It can be seen that P(4) + P(7) = 22 + 70 = 92 = P(8). However, their
// difference, 70 - 22 = 48, is not pentagonal.
//
// Find the pair of pentagonal numbers, P(j) and P(k), for which their sum and
// difference is pentagonal and D = |P(k) - P(j)| is minimised; what is the
// value of D?

use atomic::{Atomic, Ordering};
use euler::math::exp::isqrt;
use euler::math::sequence::{get_nth_pentagonal_number, is_pentagonal_number};
use euler::util::error::*;
use euler::util::problem::*;
use std::mem;
use std::sync::Arc;
use std::thread;

type AtomicU64 = Atomic<u64>;

const EXPECTED_RESULT: u64 = 1912;

struct Context {
    pub d: AtomicU64,
    pub result: AtomicU64,
}

/// This function attempts to solve the system of equations produced by setting
/// (x` + y`) and (x` - y`) equal to the factors a and b (where a > b; if b >
/// a, the factors are swapped), and returns the resulting x and y values
/// (respectively) if the solutions are both a) integers and b) positive.
///
/// This function, rather than using something like Gaussian elimination to
/// solve the system, instead just gives the values of x and y directly. This
/// is because the coefficients in the systems are always the same; it is only
/// what the system is equal to that changes, so we can get a closed form
/// solution by solving:
///
///     x` + y` = a
///     x` - y` = b
///
/// By solving this system of equations, we can see that x` = (a + b) / 2 and
/// y` = (a - b) / 2. We then set the values x` and y` represent equal to these
/// values, and solve for the respective variable to arrive at the final
/// solution.
///
/// If no valid solution exists, None is returned instead.
fn solve(mut a: i64, mut b: i64) -> Option<(i64, i64)> {
    // Ensure a > b.
    if a < b {
        mem::swap(&mut a, &mut b);
    }

    // Solve for x` and y` using the closed-form solutions.
    let x_prime = a + b;
    let y_prime = a - b;
    if x_prime & 1 > 0 || y_prime & 1 > 0 {
        return None;
    }
    let mut x_prime = x_prime / 2;
    let mut y_prime = y_prime / 2;

    // Now, solve for x and y respectively...

    x_prime -= 1;
    y_prime += 1;

    // We only care about solutions where both x and y are positive integers (note
    // we negate x_prime later).
    if x_prime >= 0 || y_prime <= 0 {
        return None;
    }

    // Divide by two (if we can't do this evenly, stop here.
    if x_prime & 1 > 0 || y_prime & 1 > 0 {
        return None;
    }
    let x_prime = x_prime / 2;
    let y_prime = y_prime / 2;

    // Now, check that we can divide by three evenly, and perform this final
    // division (and negation), and then we can return the result.
    if x_prime % 3 != 0 || y_prime % 3 != 0 {
        return None;
    }
    Some((-x_prime / 3, y_prime / 3))
}

fn consumer(context: Arc<Context>) {
    loop {
        let d: u64 = context.d.fetch_add(1, Ordering::SeqCst);
        let p_d: u64 = get_nth_pentagonal_number(d);
        let factor: i64 = p_d as i64 * -24;

        // Search for factors simply by trial division.
        for a in 1..isqrt(factor.abs() as u64) {
            let a: i64 = a as i64;

            // See if we can stop searching for solutions here.
            let existing_result = context.result.load(Ordering::SeqCst);
            if existing_result > 0 && existing_result <= d {
                return;
            }

            // See if this is a factor...
            if factor % a == 0 {
                // See if this factor produces a valid solution...
                if let Some((x, y)) = solve(a, factor / a) {
                    // Test if the solution produces a pentagonal sum...
                    let p_x = get_nth_pentagonal_number(x as u64);
                    let p_y = get_nth_pentagonal_number(y as u64);
                    if is_pentagonal_number((p_x + p_y) as u64) {
                        context.result.store(d, Ordering::SeqCst);
                        return;
                    }
                }
            }
        }
    }
}

/// A naieve approach would be to iterate over each pentagonal number, and then
/// see if there are any two other pentagonal numbers whose difference is the
/// given number.
///
/// This requires, in order to be exhaustive, that one checks up to P(n) such
/// that 3*n + 1 > P(d), which (for this particular problem) equates to around
/// four billion loop iterations.
///
/// The approach below is to iterate over each pentagonal number, as before,
/// but then to express that pentagonal number as the difference of pentagonal
/// numbers, and to solve the resulting bivariate Diophantine quadratics.
///
/// Consider the difference P(d), which is equal to P(y) - P(x). Thus:
///
///      P(d) = (y(3y - 1))/2 - (x(3x - 1))/2
///     2P(d) = 3y^2 - y - 3x^2 + x
///
/// Next, consider the arbitrary quadratic Diophantine equation in two
/// variables, giving the coefficients in our equation names:
///
///     Ax^2 + Bxy + Cy^2 + Dx + Ey + F = 0
///
/// We multiply our entire equation by 4*A (= 12) in order to complete the
/// square with only integers remaining:
///
///     36y^2 - 12y - 36x^2 + 12x = 24P(d)
///
/// Next, we complete the square on the first two terms by adding and
/// subtracting 1:
///
///     36y^2 - 12y + 1 - 36x^2 + 12x - 1 = 24P(d)
///          (6y - 1)^2 - 36x^2 + 12x - 1 = 24P(d)
///
/// Next, multiply by -1 so we can complete the square with the remaining two
/// terms:
///
///     -(6y - 1)^2 + 36x^2 - 12x + 1 = -24P(d)
///         -(6y - 1)^2 + (-6x + 1)^2 = -24P(d)
///
/// Next, let y` = 6y - 1 and let x` = -6x + 1, which allows us to rewrite the
/// equation as:
///
///            x`^2 - y`^2 = -24P(d)
///     (x` + y`)(x` - y`) = -24P(d)
///
/// At this point, we simply iterate over every pair of factors of -24P(d), and
/// we solve where (x` + y`) is equal to the larger factor, and (y` - y`) is
/// equal to the smaller factor. If any of these solutions are such that both x
/// and y are positive integers, then we have found the indices of the two
/// pentagonal numbers P(x) and P(y) such that P(y) - P(x) = P(d).
///
/// Next, we can very rapidly test if P(x) + P(y) is itself pentagonal, giving
/// us our desired solution.
fn main() {
    main_impl(|| -> Result<ProblemAnswer<u64>> {
        let context: Arc<Context> = Arc::new(Context {
            d: AtomicU64::new(1),
            result: AtomicU64::new(0),
        });

        // Launch one thread per core to solve the problem.
        let mut handles: Vec<thread::JoinHandle<()>> = vec![];
        for _ in 0..num_cpus::get() {
            let context = context.clone();
            handles.push(thread::spawn(move || {
                consumer(context);
            }));
        }

        // Wait for all of our threads to halt.
        for handle in handles.into_iter() {
            handle.join().unwrap();
        }

        Ok(ProblemAnswer {
            actual: context.result.load(Ordering::SeqCst),
            expected: EXPECTED_RESULT,
        })
    });
}

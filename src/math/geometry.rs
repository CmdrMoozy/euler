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

/// Returns a Pythagorean triple (a, b, c) which satisfies a^2 + b^2 = c^2,
/// given positive integers m, n, and k satisfying m > n, m and n are coprime,
/// and m and n are not both odd. Note that these conditions are not checked
/// explicitly; it is up to the caller to adhere to these preconditions, or the
/// returned triple will not be primitive (all entries in the result can be
/// divided by a common factor, and the result will be a primitive Pythagorean
/// triple).
///
/// This function implements Euclid's formula for generating all triples
/// uniquely. For details, see:
/// https://en.wikipedia.org/wiki/Pythagorean_triple#Generating_a_triple
pub fn get_pythagorean_triple(m: u64, n: u64, k: u64) -> (u64, u64, u64) {
    (k * (m * m - n * n), k * 2 * m * n, k * (m * m + n * n))
}

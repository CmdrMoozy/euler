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

use ::math::prime::*;

#[test]
fn test_prime_number_sieve_functionality() {
    const SIEVE_LIMIT: u64 = 10000;
    const PRIME_TEST_PRECISION: u64 = 50;

    let sieve = Sieve::new(SIEVE_LIMIT);
    assert_eq!(SIEVE_LIMIT, sieve.get_limit());
    for prime in sieve.iter() {
        assert!(is_prime(prime, PRIME_TEST_PRECISION),
                "{} should pass a primality test",
                prime);
    }

    assert_eq!(1229, sieve.get_size());
    assert_eq!(2, sieve.get_nth(1).unwrap_or(0));
    assert_eq!(9973, sieve.get_nth(1229).unwrap_or(0));
    assert!(sieve.get_nth(1230).is_none());
}

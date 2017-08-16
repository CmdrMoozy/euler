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

use math::prime::*;
use math::sieve::Sieve;

#[test]
fn test_prime_number_sieve_functionality() {
    const SIEVE_LIMIT: u64 = 10000;
    const PRIME_TEST_PRECISION: u64 = 50;

    let sieve = PrimeSieve::new(SIEVE_LIMIT);
    assert_eq!(SIEVE_LIMIT, sieve.get_limit());
    for prime in sieve.iter() {
        assert!(
            is_prime(prime, PRIME_TEST_PRECISION),
            "{} should pass a primality test",
            prime
        );
    }

    assert_eq!(1229, sieve.get_size());
    assert_eq!(2, sieve.get_nth(1).unwrap_or(0));
    assert_eq!(9973, sieve.get_nth(1229).unwrap_or(0));
    assert!(sieve.get_nth(1230).is_none());
}

#[test]
fn test_factorization_functionality() {
    const SIEVE_LIMIT: u64 = 150;
    const PRIME_TEST_PRECISION: u64 = 50;

    let sieve = PrimeSieve::new(SIEVE_LIMIT);

    static TEST_CASES: &'static [(u64, &'static [(u64, usize)])] =
        &[(56, &[(2, 3), (7, 1)]), (150, &[(2, 1), (3, 1), (5, 2)])];

    for test_case in TEST_CASES {
        let f = Factorization::new(test_case.0, &sieve, Some(PRIME_TEST_PRECISION))
            .ok()
            .unwrap();
        assert!(f.get_number() == test_case.0);
        assert!(f.iter().count() == f.factor_count());
        assert!(
            f.factor_count() == test_case.1.len(),
            "{} has {} distinct prime factors",
            test_case.0,
            test_case.1.len()
        );
        for (factor, count) in test_case.1.iter().map(|pair| *pair) {
            assert!(
                f.get_factor(factor) == count,
                "{}^{} divides {}",
                factor,
                count,
                test_case.0
            );
        }
    }
}

#[test]
fn test_factorization_product() {
    const SIEVE_LIMIT: u64 = 150;
    const PRIME_TEST_PRECISION: u64 = 50;

    let sieve = PrimeSieve::new(SIEVE_LIMIT);

    let a = Factorization::new(56, &sieve, Some(PRIME_TEST_PRECISION))
        .ok()
        .unwrap();
    let b = Factorization::new(150, &sieve, Some(PRIME_TEST_PRECISION))
        .ok()
        .unwrap();
    let result = a.product(&b);

    static EXPECTED_FACTORS: &'static [(u64, usize)] = &[(2, 4), (3, 1), (5, 2), (7, 1)];

    assert!(result.factor_count() == EXPECTED_FACTORS.len());
    for factor in EXPECTED_FACTORS {
        assert!(
            result.get_factor(factor.0) == factor.1,
            "{}^{} divides {}",
            factor.0,
            factor.1,
            56 * 150
        );
    }
}

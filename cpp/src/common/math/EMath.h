/*
 * euler - A collection of ProjectEuler libraries, tools, and solutions.
 * Copyright (C) 2013 Axel Rasmussen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INCLUDE_LIBEULER_MATH_MATH_DEPRECATED_H
#define INCLUDE_LIBEULER_MATH_MATH_DEPRECATED_H

#include <cstddef>
#include <cstdint>

#ifdef _WIN32
// Disable all warnings for gmp.h and gmpxx.h on win32, since they generate
// warnings.
#pragma warning(push, 0)
#endif

#include <gmp.h>
#include <gmpxx.h>

#ifdef _WIN32
// Be sure to enable warnings again.
#pragma warning(pop)
#endif

#include "common/EExceptions.h"

// Forward Declarations
class EFactorization;

/*!
 * \brief This class provides math utility functions.
 */
class EMath
{
public:
#if(defined _WIN32 || defined __APPLE__)
	static mpz_class int64ToBigInteger(uint64_t n);
	static mpf_class int64ToBigFloat(uint64_t n, mp_bitcnt_t p);
#endif

	static uint64_t getTriangleNumberN(uint64_t n);
	static uint64_t getPentagonalNumberN(uint64_t n);
	static bool isPentagonal(uint64_t x);
	static uint64_t getHexagonalNumberN(uint64_t n);
	static uint64_t getHeptagonalNumberN(uint64_t n);
	static uint64_t getOctagonalNumberN(uint64_t n);

	static mpz_class getFibonacciNumberN(uint32_t n);

	static bool isPrime_UI(uint64_t n, int p = 15);
	static bool isPrime(const mpz_class &n, int p = 15);

	static bool areCoprime(uint32_t a, uint32_t b);
	static uint32_t totient(uint32_t n);
	static uint32_t repetendLength(uint32_t n, EFactorization &f);

	static uint64_t leastCommonMultiple(uint64_t a, uint64_t b);

	static uint32_t logBaseTen(uint64_t n);
	static bool isSquare(uint64_t n);
	static uint64_t icbrt(uint64_t n);
	static bool isCube(uint64_t n);
	static bool isMultipleThree(uint64_t n);

	static bool isPermutationOf(uint64_t a, uint64_t b);

	static uint64_t permutations(int n, int r);

	static uint64_t getPythagoreanTripleA(uint64_t m, uint64_t n,
	                                      uint64_t k);
	static uint64_t getPythagoreanTripleB(uint64_t m, uint64_t n,
	                                      uint64_t k);
	static uint64_t getPythagoreanTripleC(uint64_t m, uint64_t n,
	                                      uint64_t k);

private:
	static uint64_t mid(uint64_t l, uint64_t r);
	static uint64_t binaryFibonacciSearch(uint32_t l, uint32_t u,
	                                      const mpz_class &t);
};

#endif

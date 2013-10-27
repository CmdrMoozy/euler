#ifndef INCLUDE_LIBEULER_MATH_MATH_H
#define INCLUDE_LIBEULER_MATH_MATH_H

#include <cstdint>

#ifdef _WIN32
	// Disable all warnings for gmp.h and gmpxx.h on win32, since they generate warnings.
	#pragma warning(push, 0)
#endif

#include <gmp.h>
#include <gmpxx.h>

#ifdef _WIN32
	// Be sure to enable warnings again.
	#pragma warning(pop)
#endif

#include "../EExceptions.h"

// Forward Declarations
class EFactorization;

/*!
 * \brief This class provides math utility functions.
 */
class EMath
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
	
#if (defined _WIN32 || defined __APPLE__)
		static mpz_class int64ToBigInteger(uint64_t n);
		static mpf_class int64ToBigFloat(uint64_t n, mp_bitcnt_t p);
#endif
		
		static uint64_t getTriangleNumberN(uint64_t n);
		static uint64_t getPentagonalNumberN(uint64_t n);
		static bool isPentagonal(uint64_t x);
		static uint64_t getHexagonalNumberN(uint64_t n);
		static uint64_t getHeptagonalNumberN(uint64_t n);
		static uint64_t getOctagonalNumberN(uint64_t n);
		
		static uint64_t getFibonacciNumberN_UI(uint32_t n);
		static mpz_class getFibonacciNumberN(uint32_t n);
		static uint64_t fibonacciSearch(uint32_t s, const mpz_class &t);
		
		static bool isPrime_UI(uint64_t n, int p = 15);
		static bool isPrime(const mpz_class &n, int p = 15);
		
		static bool areCoprime(uint32_t a, uint32_t b);
		static uint32_t totient(uint32_t n);
		static uint32_t repetendLength(uint32_t n, EFactorization &f);
		
		static uint64_t greatestCommonDivisor(uint64_t u, uint64_t v);
		static uint64_t leastCommonMultiple(uint64_t a, uint64_t b);
		static uint64_t aliquotNumberDivisors(uint32_t n);
		static uint64_t aliquotSumDivisors(uint64_t n);
		static uint64_t aliquotSumProperDivisors(uint64_t n);
		
		static uint64_t integerPow(uint64_t b, uint64_t e);
		static uint64_t modularIntegerPow(uint64_t b, uint64_t e, uint64_t m);
		static uint32_t logBaseTen(uint64_t n);
		static uint64_t isqrt(uint64_t n);
		static bool isSquare(uint64_t n);
		static uint64_t icbrt(uint64_t n);
		static bool isCube(uint64_t n);
		static bool isMultipleThree(uint64_t n);
		
		static bool isPermutationOf(uint64_t a, uint64_t b);
		
		static uint64_t permutations(int n, int r) throw(EValueRangeException &);
		static uint64_t combinations(int n, int r) throw(EValueRangeException &);
		
		static uint64_t getPythagoreanTripleA(uint64_t m, uint64_t n, uint64_t k);
		static uint64_t getPythagoreanTripleB(uint64_t m, uint64_t n, uint64_t k);
		static uint64_t getPythagoreanTripleC(uint64_t m, uint64_t n, uint64_t k);
	
	private:
		static uint64_t mid(uint64_t l, uint64_t r);
		static uint64_t binaryFibonacciSearch(uint32_t l, uint32_t u, const mpz_class &t);
};

#endif

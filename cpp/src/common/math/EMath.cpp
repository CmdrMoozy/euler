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

#include "EMath.h"

#include <cmath>
#include <cstdlib>
#include <map>
#include <stdexcept>

#include "common/EDefines.h"
#include "common/math/Math.hpp"
#include "common/util/EBitwise.h"

#if(defined _WIN32 || defined __APPLE__)
/*!
 * This is a convenience function, that will return a GMP mpz object whose value
 *is that of
 * the given 64-bit integer.
 *
 * \param n The value we are going to set.
 * \return A GMP object whose value is equal to the one given.
 */
mpz_class EMath::int64ToBigInteger(uint64_t n)
{
	mpz_class r = 0;

	r += static_cast<uint32_t>(n >> 32);
	mpz_mul_2exp(r.get_mpz_t(), r.get_mpz_t(), 32);
	r += static_cast<uint32_t>((n << 32) >> 32);

	return r;
}

/*!
 * This is a convenience function, that will return a GMP mpf object whose value
 *is that of
 * the given 64-bit integer.
 *
 * \param n The value we are going to set.
 * \param p The precision desired for the new object.
 * \return A GMP object whose value is equal to the one given.
 */
mpf_class EMath::int64ToBigFloat(uint64_t n, mp_bitcnt_t p)
{
	mpf_class r(0, p);

	r += static_cast<uint32_t>(n >> 32);
	mpf_mul_2exp(r.get_mpf_t(), r.get_mpf_t(), 32);
	r += static_cast<uint32_t>((n << 32) >> 32);

	return r;
}
#endif

/*!
 * This function returns the nth heptagonal number.
 *
 * \param n The nth heptagonal number will be generated.
 * \return The value of the nth heptagonal number.
 */
uint64_t EMath::getHeptagonalNumberN(uint64_t n)
{
	// The heptagonal number Hn is given by Hn = n(5n-3)/2
	return ((n * (5 * n - 3)) >> 1);
}

/*!
 * This function returns the nth octagonal number.
 *
 * \param n The nth octagonal number will be generated.
 * \return The value of the nth octagonal number.
 */
uint64_t EMath::getOctagonalNumberN(uint64_t n)
{
	// The octagonal number On is given by On = n(3n - 2)
	return (n * (3 * n - 2));
}

/*!
 * This function returns the nth Fibonacci number.
 *
 * The Fibonacci sequence is defined such that F(0) = 0, F(1) = 1, and F(n) =
 *F(n-1) + F(n-2).
 * For this function, however, we use a closed-form solution to the Fibonacci
 *sequence, so we can
 * avoid unnecessary recursion.
 *
 * Note that precision is only guaranteed up to n = 5000.
 *
 * \param n The nth Fibonacci number will be generated.
 * \return The value of the nth Fibonacci number.
 */
mpz_class EMath::getFibonacciNumberN(uint32_t n)
{
	/*
	 * We use the closed-form solution called "Binet's Formula," defined
	 *here:
	 *   http://en.wikipedia.org/wiki/Fibonacci_number#Relation_to_the_golden_ratio
	 *
	 * The formula is:
	 *     F(n) = (p^n - (1 - p)^n) / sqrt(5)
	 *
	 * Where p is phi, the Golden Ratio:
	 *     p = (1 + sqrt(5)) / 2
	 */

	// Since we are dealing with irrational square roots, we want a VERY
	// HIGH level of precision.
	mpf_class sf(5.0, 4000);
	mpf_class p(0.0, 4000);
	mpf_class pn(0.0, 4000), opn(0.0, 4000);
	mpf_class ret(0.0, 4000);

	mpf_sqrt(sf.get_mpf_t(), sf.get_mpf_t());

	p = sf;
	p += 1.0;
	p /= 2.0;

	mpf_pow_ui(pn.get_mpf_t(), p.get_mpf_t(), n);

	opn = 1 - p;
	mpf_pow_ui(opn.get_mpf_t(), opn.get_mpf_t(), n);

	ret = (pn - opn) / sf;
	ret += 0.5;
	mpf_floor(ret.get_mpf_t(), ret.get_mpf_t());

	return mpz_class(ret);
}

/*!
 * This is a convenience function for isPrime(), which just wraps the given
 *primitive value in an mpz_class
 * object.
 *
 * \param n The value to test for primality.
 * \param p The precision with which to perform our test.
 * \return True if the number is probably prime, or false otherwise.
 */
bool EMath::isPrime_UI(uint64_t n, int p)
{
#ifdef _WIN32
	return EMath::isPrime(EMath::int64ToBigInteger(n), p);
#elif defined __APPLE__
	return EMath::isPrime(EMath::int64ToBigInteger(n), p);
#else
	return EMath::isPrime(mpz_class(n), p);
#endif
}

/*!
 * This function tests probabalistically whether or not the given number is
 *probably prime. It
 * takes a precision argument -- a precision of 15 is fairly normal, a precision
 *of 100 is VERY
 * precise.
 *
 * \param n The value to test for primality.
 * \param p The precision with which to perform our test.
 * \return True if the number is probably prime, or false otherwise.
 */
bool EMath::isPrime(const mpz_class &n, int p)
{
	int i;
	mpz_class a, tA;
	gmp_randstate_t randState;

	// If we were given an invalid precision, just use the default of 15.
	p = (p < 1 ? 15 : p);

	// 0 is NOT prime.
	if(n == 0)
		return false;

	// 1 is NOT prime.
	if(n == 1)
		return false;

	// 2 and 3 are prime.
	if((n == 2) || (n == 3))
		return true;

	// Even numbers are NOT prime.
	if((n % 2) == 0)
		return false;

	// Numbers divisible by 3 are NOT prime.
	if((n % 3) == 0)
		return false;

	gmp_randinit_mt(randState);
	for(i = 0; i < p; i++)
	{
		// a = rand [1, value - 1]
		tA = n - 2;
		mpz_urandomm(a.get_mpz_t(), randState, tA.get_mpz_t());
		a += 1;

		// if (a ^ (value - 1) % value) != 1 then our number is not
		// prime.
		tA += 1;
		mpz_powm(tA.get_mpz_t(), a.get_mpz_t(), tA.get_mpz_t(),
		         n.get_mpz_t());
		if(tA != 1)
		{
			gmp_randclear(randState);
			return false;
		}
	}
	gmp_randclear(randState);

	return true;
}

/*!
 * This function returns the least common multiple of a and b. To make it easy,
 * we reduce this problem to being able to find the greatest common divisor,
 * which we can already do using the fast Euclidean algorithm.
 *
 * More information:
 *     http://en.wikipedia.org/wiki/Least_common_multiple#Reduction_by_the_greatest_common_divisor
 *
 * Note that this function fails if both a and b are 0.
 *
 * \param a The first integer input.
 * \param b The second integer input.
 * \return The least common multiple of a and b.
 */
uint64_t EMath::leastCommonMultiple(uint64_t a, uint64_t b)
{
	uint64_t gcd = euler::math::gcd(a, b);

	if(gcd == 0)
		return 0;

	return ((a * b) / gcd);
}

/*!
 * This function tests if the given number is a multiple of three. We use a very
 *simple finite
 * state machine and only bitwish shifts and ANDs, so this should in theory be
 *faster than using
 * naive techniques such as the modulus division operator.
 *
 * \param n The number to test.
 * \return True if n is a multiple of three, or false otherwise.
 */
bool EMath::isMultipleThree(uint64_t n)
{
	int r = 0;

	while(n != 0)
	{
		if(n & 1)
		{ // Low-bit is a 1.

			switch(r)
			{
			case 0:
				r = 1;
				break;

			case 1:
				r = 0;
				break;
			};
		}
		else
		{ // Low-bit is a 0.

			switch(r)
			{
			case 1:
				r = 2;
				break;

			case 2:
				r = 1;
				break;
			};
		}

		// Move to the next digit
		n >>= 1;
	}

	// Return result.

	return (r == 0);
}

/*!
 * This function tests if b is a permutation of a (i.e., b contains exactly the
 *same digits as a,
 * ignoring zeros). Zero digits are ignored since they can simply be
 *"permutated" to the front of
 * the number, and leading zeros do not change value.
 *
 * \param a The first number to test.
 * \param b The second number to test.
 * \return True if b is a permutation of a, or false otherwise.
 */
bool EMath::isPermutationOf(uint64_t a, uint64_t b)
{
	int digits[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	while(a > 0)
	{
		++digits[a % 10];
		a /= 10;
	}

	while(b > 0)
	{
		--digits[b % 10];
		b /= 10;
	}

	for(int i = 1; i <= 9; ++i)
		if(digits[i] != 0)
			return false;

	return true;
}

/*!
 * This functions returns the number of ways r objects can be drawn from n
 *objects,
 * assuming that order matters.
 *
 * \param n The number of available choices.
 * \param r The number of selections we will make.
 * \return n permutations of r.
 */
uint64_t EMath::permutations(int n, int r)
{
	uint64_t result;
	uint32_t i;

	/*
	 * We can only do r permutations of n if:
	 *
	 *   - r <= n
	 *   - n >= 0
	 *   - r >= 0
	 */
	if((r > n) || (n < 0) || (r < 0))
        throw std::runtime_error("Undefined premutation");

	/*
	 * The number of permutations of r objects from n objects is:
	 *     n! / (n-r)!
	 */

	/*
	 * Because factorials get very large very fast, we are going to "cancel"
	 *in order
	 * to get the correct answer. Because factorials necessarily contain the
	 *same numbers
	 * being multipled, we only need to multiply in the range of [n, n-r).
	 *
	 * I.e., for n = 5 and r = 3, we would have:
	 *       5! / (5 - 3)!
	 *     = 5! / 2!
	 *     = (5 * 4 * 3 * 2 * 1) / (2 * 1)
	 *     = 5 * 4 * 3
	 */

	result = 1;
	for(i = static_cast<uint32_t>(n); i > static_cast<uint32_t>(n - r); i--)
		result *= i;

	return result;
}

/*!
 * This function is part of Euclid's formula for generating Pythagorean triples.
 *Given
 * values m, n and k, this will provide the A value of our triple.
 *
 * More infomration about Euclid's formula:
 *     http://en.wikipedia.org/wiki/Pythagorean_triple#Generating_a_triple
 *
 * \param m A positive integer greater than n.
 * \param n A positive integer less than m.
 * \param k The multiple for this triple.
 * \return The A component of our triple.
 */
uint64_t EMath::getPythagoreanTripleA(uint64_t m, uint64_t n, uint64_t k)
{
	return (k * ((m * m) - (n * n)));
}

/*!
 * This function is part of Euclid's formula for generating Pythagorean triples.
 *Given
 * values m, n and k, this will provide the B value of our triple.
 *
 * More infomration about Euclid's formula:
 *     http://en.wikipedia.org/wiki/Pythagorean_triple#Generating_a_triple
 *
 * \param m A positive integer greater than n.
 * \param n A positive integer less than m.
 * \param k The multiple for this triple.
 * \return The B component of our triple.
 */
uint64_t EMath::getPythagoreanTripleB(uint64_t m, uint64_t n, uint64_t k)
{
	return (k * (2 * m * n));
}

/*!
 * This function is part of Euclid's formula for generating Pythagorean triples.
 *Given
 * values m, n and k, this will provide the C value of our triple.
 *
 * More infomration about Euclid's formula:
 *     http://en.wikipedia.org/wiki/Pythagorean_triple#Generating_a_triple
 *
 * \param m A positive integer greater than n.
 * \param n A positive integer less than m.
 * \param k The multiple for this triple.
 * \return The C component of our triple.
 */
uint64_t EMath::getPythagoreanTripleC(uint64_t m, uint64_t n, uint64_t k)
{
	return (k * ((m * m) + (n * n)));
}

/*!
 * This is a utility function for binary searches; it returns the index nearest
 *to the middle of the
 * indices l and r.
 *
 * \param l The left index.
 * \param r The right index.
 * \return The index in the middle of l and r.
 */
uint64_t EMath::mid(uint64_t l, uint64_t r)
{
	return ((l + r) / 2);
}

/*!
 * This function performs a binary search on the Fibonacci sequence. Both the
 *lower and upper indices
 * passed to this functions, along with the value returned by it, are indexes in
 *the Fibonacci sequence.
 * The goal of this function is to find the smallest number in the Fibonacci
 *sequence that exceeds the
 * given target number t.
 *
 * It is assumed that F(l) is <= the target number, and F(u) is >= the target
 *number.
 *
 * \param l The lower-bound index number in the sequence.
 * \param u The upper-bound index number in the sequence.
 * \param t The target number.
 * \return The sequence index of the smallest number that exceeds the given
 *target number.
 */
uint64_t EMath::binaryFibonacciSearch(uint32_t l, uint32_t u,
                                      const mpz_class &t)
{
	uint32_t m = static_cast<uint32_t>(mid(l, u));
	mpz_class v = EMath::getFibonacciNumberN(m);

	if(l == m)
	{
		if(v < t)
		{
			do
			{
				v = EMath::getFibonacciNumberN(++m);
			} while(v < t);

			return m;
		}
		else if(v > t)
		{
			do
			{
				v = EMath::getFibonacciNumberN(--m);
			} while(v >= t);

			return (m + 1);
		}
		else
			return m;
	}

	if(v < t)
		return EMath::binaryFibonacciSearch(m, u, t);
	else if(v > t)
		return EMath::binaryFibonacciSearch(l, m, t);
	else
		return m;
}

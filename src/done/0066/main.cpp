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

#include <cstddef>
#include <cstdint>
#include <vector>

#include <gmp.h>

#include "common/math/EMath.h"
#include "common/math/Math.hpp"
#include "common/util/Process.hpp"

/*
 * Consider quadratic Diophantine equations of the form:
 *
 *     x^2 - Dy^2 = 1
 *
 * For example, when D=13, the minimal solution in x is 649^2 - 13 x 180^2 = 1.
 *
 * It can be assumed that there are no solutions in positive integers when D is
 * square.
 *
 * By finding minimal solutions in x for D = {2, 3, 5, 6, 7} we obtain the
 * following:
 *
 *     3^2 - 2 x 2^2 = 1
 *     2^2 - 3 x 1^2 = 1
 *     9^2 - 5 x 4^2 = 1
 *     5^2 - 6 x 2^2 = 1
 *     8^2 - 7 x 3^2 = 1
 *
 * Hence, by considering minimal solutions in x for D <= 7, the largest x is
 * obtained when D = 5.
 *
 * Find the value of D <= 1000 in minimal solutions of x for which the largest
 * value of x is obtained.
 */

namespace
{
constexpr uint64_t EXPECTED_RESULT = 661;

/*!
 * This function will return the periodic continued fraction notation of
 * sqrt(D). E.g., for sqrt(11), which is [3; 3, 6, 3, 6, ...], we will return
 * a vector containing the elements 3, 3 and 6, in that order.
 *
 * If the given number is a perfect square, then the vector returned will only
 * contain one element: sqrt(D).
 *
 * Also, note that we will always return the entire period: e.g., for the
 * returned vector v, the continued fraction representation of sqrt(D) is
 * guaranteed to be, e.g., for a period length of 4:
 *
 *     [v(0), v(1), v(2), v(3), v(4), v(1), v(2), v(3), v(4), ...]
 *
 * In order to compute this, we will use the algorithm described here:
 *
 *     http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/Fibonacci/cfINTRO.html
 *
 * \param D the number to compute the continued fraction representation of.
 * \return The continued fraction representation of D.
 */
std::vector<uint64_t> getContinuedFraction(uint64_t D)
{
	std::vector<uint64_t> v;
	uint64_t iroot = euler::math::isqrt(D);

	if(iroot * iroot == D)
	{
		v.push_back(iroot);
		return v;
	}

	uint64_t num = 0, den = 1;
	while(true)
	{
		uint64_t hold;
		uint64_t nextn = (iroot + num) / den;
		v.push_back(nextn);

		hold = den;
		den = num - (den * nextn);
		num = hold;

		hold = -den;
		den = (D - (den * den)) / num;
		num = hold;

		if(den == 1)
		{
			v.push_back(iroot << 1);
			break;
		}
	}

	return v;
}

euler::util::process::ProblemResult<uint64_t> problem()
{
	/*
	 * To solve this problem, we will use H. W. Lenstra Jr.'s "Solving the
	 * Pell Equation," which gives us that:
	 *
	 *     Let h(i) / k(i) denote the sequence of convergents to the
	 *     continued fraction for sqrt(D). Then the pair (x1, y1) solving
	 *     Pell's equation and minimizing x satisfies x1 = h(i) and
	 *     y1 = k(i) for some i.
	 *
	 * Notice that the generalized form of a continued fraction is:
	 *
	 *                              a(1)
	 *     x = b(0) + -------------------------------
	 *                                a(2)
	 *                b(1) + ------------------------
	 *                                   a(3)
	 *                       b(2) + -----------------
	 *                                     a(4)
	 *                              b(3) + ----------
	 *                                     b(4) + ...
	 *
	 * And, finally, note that the recurrence relations for the convergents
	 * of continued fractions in the form A(n) / B(n) are:
	 *
	 *     A(0) = b(0)                              B(0) = 1
	 *     A(1) = b(1) * b(0) + a(1)                B(1) = b(1)
	 *     A(n) = b(n) * A(n-1) + a(n) * A(n-2)     B(n) = b(n) * B(n-1) +
	 *                                                       a(n) * B(n-2)
	 *
	 * This allows us to very easily generate the list of convergents for a
	 * given value of D.
	 */

	mpz_t Am1, Am2;
	mpz_t Bm1, Bm2;
	mpz_t resultx;
	mpz_t tmpA, tmpB;

	mpz_inits(Am1, Am2, Bm1, Bm2, resultx, tmpA, tmpB, NULL);

	uint64_t D, resultD, cfn;

	// Loop through each D <= 1000, starting at 8 since we're given the
	// solution for D <= 7;

	resultD = 5;
	mpz_set_ui(resultx, 9);

	for(D = 19; D <= 1000; ++D)
	{
		// We need to skip any D which is a perfect square, since Pell's
		// equation has no solution for these values.

		if(EMath::isSquare(D))
			continue;

		// Compute the continued fraction representation of this D.

		std::vector<uint64_t> cf = getContinuedFraction(D);

		// Add the first two convergents to our lists.

		mpz_set_si(Am2, static_cast<long int>(cf[0]));
		mpz_set_ui(Bm2, 1);

		mpz_set_si(Am1, static_cast<long int>((cf[0] * cf[1]) + 1));
		mpz_set_si(Bm1, static_cast<long int>(cf[1]));

		// Test if this first convergent is our solution.

		mpz_mul(tmpA, Am2, Am2);
		mpz_mul(tmpB, Bm2, Bm2);
		mpz_mul_ui(tmpB, tmpB, D);
		mpz_sub(tmpA, tmpA, tmpB);

		if(mpz_cmp_ui(tmpA, 1) == 0)
		{
			if(mpz_cmp(Am2, resultx) > 0)
			{
				resultD = D;
				mpz_set(resultx, Am2);
			}

			continue;
		}

		// Keep testing & incrementing the convergent until we find the
		// solution.

		cfn = 2;

		while(true)
		{
			// Test the most recent convergent.

			mpz_mul(tmpA, Am1, Am1);
			mpz_mul(tmpB, Bm1, Bm1);
			mpz_mul_ui(tmpB, tmpB, D);
			mpz_sub(tmpA, tmpA, tmpB);

			if(mpz_cmp_ui(tmpA, 1) == 0)
			{
				if(mpz_cmp(Am1, resultx) > 0)
				{
					resultD = D;
					mpz_set(resultx, Am1);
				}

				break;
			}

			// Since this isn't the solution, compute the next one.

			uint64_t cfidx = ((cfn - 1) % (cf.size() - 1)) + 1;

			mpz_mul_ui(tmpA, Am1, cf[cfidx]);
			mpz_add(tmpA, tmpA, Am2);

			mpz_mul_ui(tmpB, Bm1, cf[cfidx]);
			mpz_add(tmpB, tmpB, Bm2);

			mpz_set(Am2, Am1);
			mpz_set(Am1, tmpA);

			mpz_set(Bm2, Bm1);
			mpz_set(Bm1, tmpB);

			++cfn;
		}
	}

	// We've gone through all possible D values - print out our final
	// solution!

	mpz_clears(Am1, Am2, Bm1, Bm2, resultx, tmpA, tmpB, NULL);
	return {resultD, EXPECTED_RESULT};
}
}

EULER_PROBLEM_ENTRYPOINT

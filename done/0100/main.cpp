#include <iostream>
#include <cassert>
#include <cstdint>

#include <gmp.h>
#include <mpfr.h>

/*
 * If a box contains twenty-one coloured discs, composed of fifteen blue discs and six red
 * discs, and two discs were taken at random, it can be seen that the probability of
 * taking two blue discs, P(BB) = (15/12) x (14/20) = 1/2.
 *
 * The next such arrangement, for which there is exactly 50% change of taking two blue
 * discs at random, is a box containing eighty-five blue discs and thirty-five red discs.
 *
 * By finding the first arrangement to contain over 10^12 = 1,000,000,000,000 discs in
 * total, determine the number of blue discs that the box would contain.
 */

int main(void)
{
	/*
	 * First note that, in general, we are trying to find integer solutions to the
	 * following:
	 *
	 *     [B * (B - 1)] / [N * (N - 1)] = 1/2
	 *
	 * I.e.,
	 *
	 *     2B(B-1) = N(N-1)
	 *
	 * Using some very basic algebra, as well as by completing the square to solve for
	 * B in terms of N, we end up with:
	 *
	 *     B^2 - B = (1/2) * N * (N - 1)
	 *     B^2 - B + (1/4) = (1/2) * N * (N - 1) + (1/4)
	 *     (B - (1/2))^2 = (1/2) * N * (N - 1) + (1/4)
	 *     B - (1/2) = +/- sqrt[ (1/2) * N * (N - 1) + (1/4) ]
	 *     B = +/- sqrt[ (1/2) * N * (N - 1) + (1/4) ] + (1/2)
	 *
	 * Furthermore, note that (in the context of our problem), negative values for B
	 * don't make sense, so we can simply ignore those values of B, giving:
	 *
	 *     B = sqrt[ (1/2) * N * (N - 1) + (1/4) ] + (1/2)
	 *
	 * At this point, all we need to do to solve this problem is to solve the
	 * right-hand side of the equation over the integers, with N > 10^12.
	 *
	 * Note that, because B must be an integer, we also know that the right-hand side
	 * of the given equation is in Z. Thus (=> means implies):
	 *
	 *     sqrt[ (1/2) * N * (N - 1) + (1/4) ] + (1/2) is in Z
	 *     Let sqrt[ (1/2) * N * (N - 1) + (1/4) ] + (1/2) = Y, with Y is in Z.
	 *
	 * With basic algebra, we come up with:
	 *
	 *     (1/2) * N * (N - 1) + (1/4) = (Y - (1/2))^2
	 *     4 * N * (N - 1) + 2 = 8 * (Y - (1/2))^2
	 *     4N^2 - 4N + 2 = 8Y^2 - 8Y + 2
	 *     8Y^2 - 8Y + 2 - 4N^2 + 4N - 2 = 0
	 *     8Y^2 - 8Y + 2 - 4N^2 + 4N - 1 = 1
	 *     2(4Y^2 - 4Y + 1) - (4N^2 - 4N + 1) = 1
	 *     2(2Y - 1)^2 - (2N - 1)^2 = 1
	 *
	 * At this point, if we let X` = 2N - 1, and Y` = 2Y - 1, then we have:
	 *
	 *     X`^2 - 2Y`^2 = -1
	 *
	 * I.e., the problem is reduced to the negative Pell's equation. For this
	 * particular instance of the negative Pell's equation, the fundamental solution
	 * is well known to be X` = 1, Y` = 1. Furthermore, the list of all positive
	 * solutions are given by the recurrences:
	 *
	 *     X`[n + 1] = 3 * X`[n] + 4 * Y`[n]
	 *     Y`[n + 1] = 2 * X`[n] + 3 * Y`[n]
	 *
	 * Returning back to the problem, we're looking for solutions with N > 10^12. This
	 * means that we're looking for the first solution with X` > 2 * 10^12 - 1. Let us
	 * search for that value first:
	 */
	
	mpz_t xprime, yprime, bound, tmpA, tmpB, tmpC;
	
	mpz_init_set_ui(xprime, 1);
	mpz_init_set_ui(yprime, 1);
	
	mpz_init_set_ui(bound, 10);
	mpz_pow_ui(bound, bound, 12);
	mpz_mul_ui(bound, bound, 2);
	mpz_sub_ui(bound, bound, 1);
	
	mpz_init(tmpA);
	mpz_init(tmpB);
	mpz_init(tmpC);
	
	while(mpz_cmp(xprime, bound) < 0)
	{
		mpz_mul_ui(tmpA, xprime, 3);
		mpz_mul_ui(tmpB, yprime, 4);
		mpz_add(tmpA, tmpA, tmpB);
		
		mpz_mul_ui(tmpB, xprime, 2);
		mpz_mul_ui(tmpC, yprime, 3);
		
		mpz_set(xprime, tmpA);
		
		mpz_add(yprime, tmpB, tmpC);
	}
	
	/*
	 * Now that we have the minimized X` solution, we need to get the corresponding
	 * minimal N solution. Since X` = 2N - 1, we have:
	 *
	 *     2N = X` - 1
	 *     N = (1/2) * (X` - 1)
	 *
	 * Note that this must be an integer, since by definition of the solutions of the
	 * negative Pell's equation we know that X` is odd.
	 */
	
	mpz_sub_ui(xprime, xprime, 1);
	mpz_divexact_ui(xprime, xprime, 2);
	
	/*
	 * Finally, it was proven above that B, the number of blue discs, can be written
	 * in terms of N, the total number of discs. Namely:
	 *
	 *     B = sqrt[ (1/2) * N * (N - 1) + (1/4) ] + (1/2)
	 *
	 * So we simply need to evaluate this expression and we have our answer!
	 */
	
	mpfr_t N, B, ftmpA;
	
	mpfr_init2(N, static_cast<mpfr_prec_t>(256));
	mpfr_set_z(N, xprime, MPFR_RNDA);
	
	mpfr_init2(B, static_cast<mpfr_prec_t>(256));
	
	mpfr_init2(ftmpA, static_cast<mpfr_prec_t>(256));
	
	mpz_clear(xprime);
	mpz_clear(yprime);
	mpz_clear(bound);
	mpz_clear(tmpA);
	mpz_clear(tmpB);
	mpz_clear(tmpC);
	
	mpfr_sub_ui(B, N, 1, MPFR_RNDA);
	mpfr_mul(B, B, N, MPFR_RNDA);
	mpfr_div_ui(B, B, 2, MPFR_RNDA);
	
	mpfr_set_ui(ftmpA, 1, MPFR_RNDA);
	mpfr_div_ui(ftmpA, ftmpA, 4, MPFR_RNDA);
	mpfr_add(B, B, ftmpA, MPFR_RNDA);
	
	mpfr_sqrt(B, B, MPFR_RNDA);
	
	mpfr_set_ui(ftmpA, 1, MPFR_RNDA);
	mpfr_div_ui(ftmpA, ftmpA, 2, MPFR_RNDA);
	mpfr_add(B, B, ftmpA, MPFR_RNDA);
	
	uintmax_t result = mpfr_get_uj(B, MPFR_RNDA);
	
	mpfr_clear(N);
	mpfr_clear(B);
	
	std::cout << "The number of blue discs is: " << result << "\n";
	assert(result == 756872327473);
	
	return 0;
}

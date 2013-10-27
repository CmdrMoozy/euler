#include <iostream>
#include <cassert>

#include "libeuler/types/EFraction.h"
#include "libeuler/EExceptions.h"
#include "libeuler/EDefines.h"

/*
 * We will be searching, in a sorted list of all fractions where the denominator is <=
 * DENOMINATOR_LIMIT, for the fraction immedately to the left of TARGET_N / TARGET_D.
 */
#define DENOMINATOR_LIMIT 1000000
#define TARGET_N 3
#define TARGET_D 7

/*
 * Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d)=1,
 * it is called a reduced proper fraction.
 *
 * If we list the set of reduced proper fractions for d <= 8 in ascending order of size, we
 * get:
 *
 *     1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, _2/5_, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4,
 *     4/5, 5/6, 6/7, 7/8
 *
 * It can be seen that 2/5 is the fraction immediately to the left of 3/7.
 *
 * By listing the set of reduced proper fractions for d <= 1,000,000 in ascending order of
 * size, find the numerator of the fraction immediately to the left of 3/7.
 */

int main(void)
{
	try
	{
		EFraction lower(0, 1), mediant(0, 1), upper(TARGET_N, TARGET_D);
		
		while(mediant.getDenominator() <= DENOMINATOR_LIMIT)
		{
			lower = mediant;
			mediant.mediant(upper);
			mediant.reduce();
		} 
		
		std::cout << "The fraction immediately less than 3/7 is: " << lower << ".\n";
		assert(lower.getNumerator() == 428570);
	}
	catch(EValueRangeException &e)
	{
		EDIE_LOGIC(e)
	}
}

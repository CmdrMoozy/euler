#ifndef INCLUDE_LIBEULER_EULER_CIRCULAR_PRIME_SIEVE_H
#define INCLUDE_LIBEULER_EULER_CIRCULAR_PRIME_SIEVE_H

#include "../math/EPrimeSieve.h"

/*!
 * \brief This is an extension of our sieve which searches for circular primes only.
 *
 * It behaves in exactly the same way, except after the primes are generated it proceeds
 * to filter out all non-circular primes.
 */
class ECircularPrimeSieve : public EPrimeSieve
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
	
		ECircularPrimeSieve();
	
	protected:
		virtual void generatePrimes();
	
	private:
		/*!
		 * This enum represents the category of a given prime, whether it hasn't been tested yet,
		 * is definitely Circular, or definitely NotCircular. It is used only internally.
		 */
		enum PrimeCategory
		{
			Untested,
			Circular,
			NotCircular
		};
};

#endif

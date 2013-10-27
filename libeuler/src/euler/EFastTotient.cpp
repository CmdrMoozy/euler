#include "EFastTotient.h"

#include "math/EMath.h"
#include "math/EPrimeSieve.h"

#ifdef LIBEULER_DEBUG
	#include <iostream>
	
	#include "EDefines.h"
	#include "EExceptions.h"
#endif

#ifdef LIBEULER_DEBUG
/*!
 * This function implements our test suite for this class. It uses non-abort()'ing
 * assertions, and merely prints the result to stdout.
 */
void EFastTotient::doTestSuite()
{
	bool success;
	
	std::cout << "\tTesting 'EFastTotient'...\t\t";
	try
	{
		success = true;
		
		EPrimeSieve s;
		EFastTotient t(&s, 5000);
		
		for(uint32_t i = 1; i < 5000; ++i)
			EASSERT(EMath::totient(i) == t.totient(i));
	}
	catch(EAssertionException &e)
	{
		ELUNUSED(e)
		success = false;
	}
	
	// Print out our results.
	if(success)
		std::cout << "[ OK ]\n";
	else
		std::cout << "[FAIL]\n";
}
#endif

EFastTotient::EFastTotient(EPrimeSieve *s, uint32_t l)
{
	sieve = s;
	setLimit(l);
}

EFastTotient::~EFastTotient()
{
}

uint32_t EFastTotient::getLimit() const
{
	return sieve->getLimit();
}

void EFastTotient::setLimit(uint32_t l)
{
	sieve->setLimit(l);
}

uint32_t EFastTotient::totient(uint32_t n)
{
	// Handle some cases exactly.
	
	if(n == 0) return 0;
	if(n == 1) return 1;
	
	// This can be very slow; callers are encouraged to set an upper limit BEFORE calling this function.
	
	if( n > getLimit() )
		sieve->setLimit(n);
	
	/*
	 * Because the totient is multiplicative, we are going to calculate it based upon the given number's prime
	 * factorization. This is so we don't need to calculate the GCD of nearly as many numbers, as well as the
	 * fact that the totient of a prime p is exactly p-1, so we do not need to really "calculate" it.
	 */
	
	uint32_t t = 0, h, p, e;
	
	for(std::set<uint32_t>::iterator it = sieve->begin(); it != sieve->end(); ++it)
	{
		if(n == 1) break;
		
		e = 0;
		p = (*it);
		
		while( (n % (*it)) == 0 )
		{
			n /= (*it);
			++e;
		}
		
		if(e > 0)
		{
			h = EMath::integerPow(p, e - 1) * (p - 1);
			t = (t == 0) ? h : t * h;
		}
	}
	
	return t;
}

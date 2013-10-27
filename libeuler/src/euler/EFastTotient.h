#ifndef INCLUDE_LIBEULER_EULER_FAST_TOTIENT_H
#define INCLUDE_LIBEULER_EULER_FAST_TOTIENT_H

#include <cstdint>

class EPrimeSieve;

class EFastTotient
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
		
		EFastTotient(EPrimeSieve *s, uint32_t l = 0);
		virtual ~EFastTotient();
		
		uint32_t getLimit() const;
		void setLimit(uint32_t l);
		
		uint32_t totient(uint32_t n);
		
	private:
		EPrimeSieve *sieve;
};

#endif

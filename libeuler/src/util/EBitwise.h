#ifndef INCLUDE_LIBEULER_UTIL_BITWISE_H
#define INCLUDE_LIBEULER_UTIL_BITWISE_H

#include <cstdint>

/*!
 * \brief This class provides bitwise utility functions.
 */
class EBitwise
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
	
		/*
		To test:
		
		rotl64
		rotr64
	
		rmoOff
		rmzOn
		isPowTwoLessOne
		rmoIsolate
		rmzIsolate
		trailZMask
		trailOMask
		trailRMOZMask
		trailRMZOMask
		rmoPropR
		rmzPropR
		rmosOff
		rmzsOn
		nextSNOOB
		
		nlz32
		nlz64
		*/
	
		static bool isPowerOfTwo(uint32_t v) __attribute__ ((deprecated));
		static uint32_t lgPowerOfTwo(uint32_t v) __attribute__ ((deprecated));
		static uint32_t lg(uint32_t v) __attribute__ ((deprecated));
		
		static uint32_t lg32(uint32_t v);
		static uint32_t lg64(uint64_t v);
		
		static uint32_t reverseAllBits(uint32_t v);
		static uint32_t reverseBits(uint32_t v);
	
		static bool isPalindromic(uint32_t v);
	
		static uint32_t rotateLeft(uint32_t n, int p) __attribute__ ((deprecated));
		static uint32_t rotateRight(uint32_t n, int p) __attribute__ ((deprecated));
	
		static uint32_t rotl32(uint32_t n, int p);
		static uint32_t rotr32(uint32_t n, int p);
		static uint64_t rotl64(uint64_t n, int p);
		static uint64_t rotr64(uint64_t n, int p);
	
		static uint64_t modPowTwo(uint64_t n, unsigned int s);
		static uint64_t modPowTwoLessOne(uint64_t n, unsigned int s);
	
		/*
		 * Hacker's Delight Functions!
		 */
		
		static uint64_t rmoOff(uint64_t x);
		static uint64_t rmzOn(uint64_t x);
		static bool isPowTwo(uint64_t n);
		static bool isPowTwoLessOne(uint64_t n);
		static uint64_t rmoIsolate(uint64_t x);
		static uint64_t rmzIsolate(uint64_t x);
		static uint64_t trailZMask(uint64_t x);
		static uint64_t trailOMask(uint64_t x);
		static uint64_t trailRMOZMask(uint64_t x);
		static uint64_t trailRMZOMask(uint64_t x);
		static uint64_t rmoPropR(uint64_t x);
		static uint64_t rmzPropR(uint64_t x);
		static uint64_t rmosOff(uint64_t x);
		static uint64_t rmzsOn(uint64_t x);
		static int opop(uint64_t x);
		
		static int nlz32(uint32_t x);
		static int nlz64(uint64_t x);
};

#endif

#ifndef INCLUDE_LIBEULER_MATH_PRIME_SIEVE_H
#define INCLUDE_LIBEULER_MATH_PRIME_SIEVE_H

#include <set>
#include <cstdint>

/*!
 * \brief This class is a sieve that generates prime numbers.
 *
 * It is a very simple, and not very optimized implementation of the Sieve of Atkin.
 */
class EPrimeSieve
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
	
		EPrimeSieve(uint32_t l = 0);
		virtual ~EPrimeSieve();
	
		uint32_t getLimit() const;
		void setLimit(uint32_t nL);
	
		uint32_t getSize() const;
	
		bool contains(uint32_t i) const;
		bool erase(uint32_t i);
	
		std::set<uint32_t>::iterator find(uint32_t n);
	
		std::set<uint32_t>::iterator begin();
		std::set<uint32_t>::const_iterator begin() const;
		std::set<uint32_t>::iterator end();
		std::set<uint32_t>::const_iterator end() const;
		std::set<uint32_t>::reverse_iterator rbegin();
		std::set<uint32_t>::const_reverse_iterator rbegin() const;
		std::set<uint32_t>::reverse_iterator rend();
		std::set<uint32_t>::const_reverse_iterator rend() const;
		
		std::set<uint32_t>::iterator lowerBound(const uint32_t &n) const;
		std::set<uint32_t>::iterator upperBound(const uint32_t &n) const;
	
	protected:
		virtual void generatePrimes();
	
	private:
		uint32_t limit;
		std::set<uint32_t> primes;
};


#endif

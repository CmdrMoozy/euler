#ifndef INCLUDE_LIBEULER_MATH_FACTORIZATION_H
#define INCLUDE_LIBEULER_MATH_FACTORIZATION_H

#include <map>
#include <set>
#include <cstdint>

// Forward Declarations
class EPrimeSieve;

/*!
 * \brief This class facilitates the factoring or numbers.
 *
 * It provides a way to get the prime factorization, or the TOTAL factorization, along with some
 * other utility functions.
 */
class EFactorization
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
	
		EFactorization(uint32_t n = 0);
		virtual ~EFactorization();
	
		uint32_t getNumber();
		void setNumber(uint32_t n);
	
		int getPrimeFactorsCount();
		int getAllFactorsCount();
		const std::map<uint32_t, uint32_t> &getPrimeFactors();
	
		const std::set<uint32_t> &getAllFactors();
	
	private:
		EPrimeSieve *sieve;
		uint32_t number;
		bool primesGenerated, allGenerated;
		std::map<uint32_t, uint32_t> primeFactors;
		std::set<uint32_t> allFactors;
	
		void generatePrimeFactors();
		void generateAllFactors();
};

#endif

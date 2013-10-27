#ifndef INCLUDE_LIBEULER_TYPES_BIG_INTEGER_H
#define INCLUDE_LIBEULER_TYPES_BIG_INTEGER_H

#include <cstdint>
#include <iosfwd>

#include <gmp.h>
#include <gmpxx.h>

// Forward declarations.
class EBigInteger;
std::ostream &operator<<(std::ostream &o, const EBigInteger &i);

/*!
 * \brief This class implements an arbitrary-precision integer using GMP.
 *
 * It provides some functionality that GMP's mpz_class type either doesn't provide, or doesn't
 * make easy to use syntactically.
 */
class EBigInteger
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
		
		EBigInteger();
		EBigInteger(const EBigInteger &o);
		EBigInteger(const mpz_class &v);
		explicit EBigInteger(int64_t v);
		EBigInteger(uint64_t v);
		virtual ~EBigInteger();
	
		EBigInteger &operator=(const EBigInteger &o);
	
		bool operator==(const EBigInteger &o) const;
		bool operator!=(const EBigInteger &o) const;
		bool operator<(const EBigInteger &o) const;
		bool operator<=(const EBigInteger &o) const;
		bool operator>(const EBigInteger &o) const;
		bool operator>=(const EBigInteger &o) const;
		
		EBigInteger operator-() const;
		
		EBigInteger operator+(const EBigInteger &o) const;
		EBigInteger operator-(const EBigInteger &o) const;
		EBigInteger operator*(const EBigInteger &o) const;
		EBigInteger operator/(const EBigInteger &o) const;
		EBigInteger operator%(const EBigInteger &o) const;
		
		EBigInteger &operator+=(const EBigInteger &o);
		EBigInteger &operator-=(const EBigInteger &o);
		EBigInteger &operator*=(const EBigInteger &o);
		EBigInteger &operator/=(const EBigInteger &o);
		EBigInteger &operator%=(const EBigInteger &o);
		
		EBigInteger &operator++();
		EBigInteger operator++(int);
		EBigInteger &operator--();
		EBigInteger operator--(int);
		
		EBigInteger operator~() const;
		EBigInteger operator&(const EBigInteger &o) const;
		EBigInteger operator|(const EBigInteger &o) const;
		EBigInteger operator^(const EBigInteger &o) const;
		EBigInteger operator<<(const EBigInteger &o) const;
		EBigInteger operator>>(const EBigInteger &o) const;
		
		EBigInteger &operator&=(const EBigInteger &o);
		EBigInteger &operator|=(const EBigInteger &o);
		EBigInteger &operator^=(const EBigInteger &o);
		EBigInteger &operator<<=(const EBigInteger &o);
		EBigInteger &operator>>=(const EBigInteger &o);
		
		EBigInteger abs() const;
		int sgn() const;
		
		EBigInteger pow(const EBigInteger &e) const;
		EBigInteger powMod(const EBigInteger &e, const EBigInteger &m) const;
		EBigInteger lcm(const EBigInteger &o) const;
		
		void nextPrime();
		
		std::string toString() const;
		int64_t toInt() const;
		uint64_t toUInt() const;
		mpz_class &toMPZ();
	
	private:
		mpz_class value;
};

#endif

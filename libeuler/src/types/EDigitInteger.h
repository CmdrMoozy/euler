#ifndef INCLUDE_LIBEULER_TYPES_DIGIT_INTEGER_H
#define INCLUDE_LIBEULER_TYPES_DIGIT_INTEGER_H

#include <cstdint>
#include <string>
#include <iostream>

#ifdef _WIN32
	// Disable all warnings for gmp.h and gmpxx.h on win32, since they generate warnings.
	#pragma warning(push, 0)
#endif

#include <gmp.h>
#include <gmpxx.h>

#ifdef _WIN32
	// Be sure to enable warnings again.
	#pragma warning(pop)
#endif

#include "../structs/EHashMap.h"
#include "../EExceptions.h"

#ifdef LIBEULER_DEBUG
	#include <ctime>
#endif

// Forward declarations.
class EDigitInteger;
std::ostream &operator<<(std::ostream &out, const EDigitInteger &i);

/*
 * These two hardcoded parameters define our default EHashMap capacity and desired load factor
 * for EDigitInteger objects. A default capacity of 7 (i.e., 128) and a desired load factor of
 * 1:1 for keys(digits):capacity should work fine.
 */
#define EDIGITINTEGER_DEFAULT_CAPACITY 7
#define EDIGITINTEGER_LOAD_FACTOR 1.0

/*!
 * \brief This class stores integers of arbitrary size as a series of digits.
 *
 * This allows for non-standard checks that involve individual digits, such as whether or not
 * the number is a palindrome. This class is a subclass of EHashMap, where the "keys" are the
 * indices of the digits in our number, and the "values" are the values of the digits themselves.
 *
 * It should be noted that, although this class provides some rudimentary mathematical functions
 * (mostly +, -, *, / and %) they are going to be MUCH slower than the same operations on primitive
 * types (or even the same operation on GMP types). As such, if you are going to be performing
 * lots of math, you should do it with some other type and then initialize a new EDigitInteger using
 * that value.
 */
class EDigitInteger : public EHashMap<int, int>
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
	
		EDigitInteger();
		EDigitInteger(const EDigitInteger &o);
		explicit EDigitInteger(uint64_t v);
		explicit EDigitInteger(const mpz_class &v);
		virtual ~EDigitInteger();
	
		EDigitInteger &operator=(const EDigitInteger &o);
		EDigitInteger &operator=(const std::string &v) throw(EStringFormatException &);
		EDigitInteger &operator=(uint64_t v);
		EDigitInteger &operator=(const mpz_class &v);
	
		bool operator==(const EDigitInteger &o) const;
		bool operator!=(const EDigitInteger &o) const;
		bool operator<(const EDigitInteger &o) const;
		bool operator>(const EDigitInteger &o) const;
		bool operator<=(const EDigitInteger &o) const;
		bool operator>=(const EDigitInteger &o) const;
	
		EDigitInteger operator-() const;
		
		EDigitInteger &operator+=(const EDigitInteger &o);
		EDigitInteger &operator-=(const EDigitInteger &o);
		EDigitInteger &operator*=(const EDigitInteger &o);
		EDigitInteger &operator/=(const EDigitInteger &o) throw(EDivideByZeroException &);
		EDigitInteger &operator%=(const EDigitInteger &o) throw(EDivideByZeroException &);
		
		EDigitInteger operator+(const EDigitInteger &o) const;
		EDigitInteger operator-(const EDigitInteger &o) const;
		EDigitInteger operator*(const EDigitInteger &o) const;
		EDigitInteger operator/(const EDigitInteger &o) const throw(EDivideByZeroException &);
		EDigitInteger operator%(const EDigitInteger &o) const throw(EDivideByZeroException &);
	
		EDigitInteger &operator++();
		EDigitInteger operator++(int i);
		EDigitInteger &operator--();
		EDigitInteger operator--(int i);
		
		bool isPositive() const;
		void setPositive(bool p);
		int digitCount() const;
		
		int sumOfDigits() const;
		
		bool isPalindrome() const;
		bool isPandigital() const;
		
		bool isDigitallyEquivalent(const EDigitInteger &o) const;
		
		virtual bool put(const int &k, const int &v) throw(EValueRangeException &);
		virtual bool erase(const int &k);
		
		void rightDigitalShift(int p);
		bool rightDigitalRotate(int p);
		void leftDigitalShift(int p);
		bool leftDigitalRotate(int p);
		
		void sortDigitsAscending();
		bool sortDigitsDescending();
		bool permutateDigits();
		bool reversePermutateDigits();
		
		bool reverseDigits(int l = 0, int r = -1);
		
		uint64_t rangeToInteger(int l, int r) const throw(EOutOfBoundsException &);
		uint64_t toInteger() const;
		mpz_class rangeToBigInteger(int l, int r) const throw(EOutOfBoundsException &);
		mpz_class toBigInteger() const;
		std::string rangeToString(int l, int r) const throw(EOutOfBoundsException &);
		std::string toString() const;
		
	private:
		bool positive;
		
		bool volatileSetDigitAt(int k, int v);
		bool removeLeadingZeros();
		
		void carry();
		void borrow() throw(EUnderflowException &);
	
		void setZero();
		
		bool unsignedEqualTo(const EDigitInteger &o) const;
		bool unsignedNotEqualTo(const EDigitInteger &o) const;
		bool unsignedLessThan(const EDigitInteger &o) const;
		bool unsignedGreaterThan(const EDigitInteger &o) const;
		bool unsignedLessThanEqualTo(const EDigitInteger &o) const;
		bool unsignedGreaterThanEqualTo(const EDigitInteger &o) const;
		
		void unsignedAdd(const EDigitInteger &i);
		void unsignedSubtract(const EDigitInteger &i);
		void unsignedMultiply(const EDigitInteger &i);
		void unsignedDivide(const EDigitInteger &i, bool m = false) throw(EDivideByZeroException &);
		
		void quicksortAsc(int l, int r);
		void quicksortDesc(int l, int r);
};

#endif

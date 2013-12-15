/*
 * euler - A collection of ProjectEuler solutions, and supporting libraries and tools.
 * Copyright (C) 2013 Axel Rasmussen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "EDigitInteger.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <sstream>
#include <algorithm>

#include "EDefines.h"

#ifdef _WIN32
	// We need EMath on Win32 for int64ToBigInteger().
	#include "math/EMath.h"
#endif

#ifdef LIBEULER_DEBUG
	#include <cassert>
	
	#include "util/EArray.h"
#endif

#ifdef LIBEULER_DEBUG
/*!
 * This function implements our test suite for this class. It uses non-abort()'ing
 * assertions, and merely prints the result to stdout.
 */
void EDigitInteger::doTestSuite()
{
	bool success;
			
	std::cout << "\tTesting 'EDigitInteger'...\t\t";
	try
	{
		success = true;
		
		uint64_t i;
		int j, k;
		EDigitInteger a, b, c;
		
		// Test our various assignment operators and rangeTo* functions.
		
		// Test our default constructor.
		EASSERT(a.toInteger() == 0)
		EASSERT(a.isPositive())
		EASSERT(b.toInteger() == 0)
		EASSERT(b.isPositive())
		EASSERT(c.toInteger() == 0)
		EASSERT(c.isPositive())
		
		// Test our string assignment operator.
		
		a = "+123456789";
		
		EASSERT(a.isPositive())
		EASSERT(a.toInteger() == 123456789)
		EASSERT(a.toBigInteger() == 123456789)
		EASSERT(a.toString() == "123456789")
		
		a = "-12345";
		
		EASSERT(!a.isPositive())
		EASSERT(a.toInteger() == 12345)
		EASSERT(a.toBigInteger() == 12345)
		EASSERT(a.toString() == "-12345")
		
		EASSERT(a.rangeToString(0, 3) == "2345")
		
		a = "12345678910";
		
		EASSERT(a.isPositive())
		EASSERT(a.toInteger() == 12345678910)

#ifndef _WIN32
		EASSERT(a.toBigInteger() == 12345678910)
#else
		EASSERT(a.toBigInteger() == EMath::int64ToBigInteger(12345678910))
#endif
		
		EASSERT(a.toString() == "12345678910")
		
		// Test rangeTo* functions
		
		EASSERT(a.rangeToInteger(0, 5) == 678910)
		EASSERT(a.rangeToBigInteger(0, 5) == 678910)
		EASSERT(a.rangeToString(0, 5) == "678910")
		
		EASSERT(a.rangeToInteger(6, 9) == 2345)
		EASSERT(a.rangeToBigInteger(6, 9) == 2345)
		EASSERT(a.rangeToString(6, 9) == "2345")
		
		// Test integer assignment operator.
		a = static_cast<uint64_t>(1);
		EASSERT(a.toInteger() == 1)
		
		a = static_cast<uint64_t>(12345678910);
		EASSERT(a.toInteger() == 12345678910)
		
		a = static_cast<uint64_t>(123456);
		EASSERT(a.toInteger() == 123456)
		
		// Test big-integer assignment operator.
		mpz_class bigint = 1278483892;
		a = bigint;
		EASSERT(a.toBigInteger() == bigint)
		
		// Test copy constructor.
		
		EDigitInteger copy(a);
		EASSERT(a == copy)
		EASSERT(a.toInteger() == copy.toInteger())
		
		// Test unary negation operator.
		
		b = -a;
		EASSERT(b != a)
		a.setPositive(false);
		EASSERT(b == a)
		
		// Test copy assignment operator.
		
		a = "123456";
		b = a;
		
		EASSERT(a == b)
		EASSERT(a.toInteger() == b.toInteger())
		
		// Test post/pre-fix inc/de-crement operators.
		
		for(i = 0, a = 0; i < 1000; ++i, ++a)
			EASSERT(a.toInteger() == i)
		
		for(i = 0, a = 0; i < 1000; ++i, a++)
			EASSERT(a.toInteger() == i)
		
		for(i = 1000, a = 1000; i > 0; --i, --a)
			EASSERT(a.toInteger() == i)
		
		for(i = 1000, a = 1000; i > 0; --i, a--)
			EASSERT(a.toInteger() == i)
		
		
		// Test our comparison operators.
		
		srand( static_cast<unsigned int>(time(NULL)) );
		for(i = 0; i < 1000; ++i)
		{
			// Set a.
			j = rand();
			a = j;
			if(j&1)
			{
				j *= -1;
				a.setPositive(false);
				EASSERT(!a.isPositive())
			}
			else
			{
				EASSERT(a.isPositive())
			}
			
			// Set b.
			k = rand();
			b = k;
			if(k&1)
			{
				k *= -1;
				b.setPositive(false);
				EASSERT(!b.isPositive())
			}
			else
			{
				EASSERT(b.isPositive())
			}
			
			// ==
			if(j == k)
			{
				EASSERT(a == b)
			}
			else
			{
				EASSERT(!(a == b))
			}
			
			// !=
			if(j != k)
			{
				EASSERT(a != b)
			}
			else
			{
				EASSERT(!(a != b))
			}
			
			// <
			if(j < k)
			{
				EASSERT(a < b)
			}
			else
			{
				EASSERT(!(a < b))
			}
			
			// >
			if(j > k)
			{
				EASSERT(a > b)
			}
			else
			{
				EASSERT(!(a > b))
			}
			
			// <=
			if(j <= k)
			{
				EASSERT(a <= b)
			}
			else
			{
				EASSERT(!(a <= b))
			}
			
			// >=
			if(j >= k)
			{
				EASSERT(a >= b)
			}
			else
			{
				EASSERT(!(a >= b))
			}
		}
		
		// Test our arithmetic operators (+, -, *, / and %).
		
		// Addition
		
		a = 123456;
		a += EDigitInteger(123456);
		EASSERT(a.toInteger() == 246912)
		EASSERT(a.isPositive())
		
		a = 1000;
		a.setPositive(false);
		a += EDigitInteger(1000000);
		EASSERT(a.toInteger() == 999000)
		EASSERT(a.isPositive())
		
		a = 999;
		b = 1999;
		b.setPositive(false);
		a += b;
		EASSERT(a.toInteger() == 1000)
		EASSERT(!a.isPositive())
		
		// Subtraction
		
		a = 12345;
		a -= EDigitInteger(2345);
		EASSERT(a.toInteger() == 10000)
		EASSERT(a.isPositive())
		
		a = 100;
		a -= EDigitInteger(1000);
		EASSERT(a.toInteger() == 900)
		EASSERT(!a.isPositive())
		
		a = 100;
		b = 900;
		b.setPositive(false);
		a -= b;
		EASSERT(a.toInteger() == 1000)
		EASSERT(a.isPositive())
		
		// Multiplication
		
		a = 123;
		a *= EDigitInteger(456);
		EASSERT(a.toInteger() == 56088)
		EASSERT(a.isPositive())
		
		a = 999;
		a.setPositive(false);
		a *= EDigitInteger(0);
		EASSERT(a.toInteger() == 0)
		EASSERT(a.isPositive())
		
		a = 983243;
		a.setPositive(false);
		a *= EDigitInteger(5);
		EASSERT(a.toInteger() == 4916215)
		EASSERT(!a.isPositive())
		
		a = 321;
		a.setPositive(false);
		b = 987;
		b.setPositive(false);
		a *= b;
		EASSERT(a.toInteger() == 316827)
		EASSERT(a.isPositive())
		
		// rightDigitalShift
		
		a = 726398567;
		a.rightDigitalShift(3);
		EASSERT(a.toInteger() == 726398)
		EASSERT(a.digitCount() == 6)
		a.rightDigitalShift(1);
		EASSERT(a.toInteger() == 72639)
		EASSERT(a.digitCount() == 5)
		a.rightDigitalShift(-2);
		EASSERT(a.toInteger() == 7263900)
		EASSERT(a.digitCount() == 7)
		a.rightDigitalShift(0);
		EASSERT(a.toInteger() == 7263900)
		EASSERT(a.digitCount() == 7)
		a.rightDigitalShift(10);
		EASSERT(a.toInteger() == 0)
		EASSERT(a.digitCount() == 1)
		
		
		// rightDigitalRotate
		
		a = 12437070894;
		a.rightDigitalRotate(11);
		EASSERT(a.toInteger() == 12437070894)
		EASSERT(a.digitCount() == 11)
		a.rightDigitalRotate(0);
		EASSERT(a.toInteger() == 12437070894)
		EASSERT(a.digitCount() == 11)
		a.rightDigitalRotate(-3);
		EASSERT(a.toInteger() == 37070894124)
		EASSERT(a.digitCount() == 11)
		a.rightDigitalRotate(5);
		EASSERT(a.toInteger() == 94124370708)
		EASSERT(a.digitCount() == 11)
		a.rightDigitalRotate(1);
		EASSERT(a.toInteger() == 89412437070)
		EASSERT(a.digitCount() == 11)
		a.rightDigitalRotate(1);
		EASSERT(a.toInteger() == 8941243707)
		EASSERT(a.digitCount() == 10)
		
		// leftDigitalShift
		
		a = 82736;
		a.leftDigitalShift(3);
		EASSERT(a.toInteger() == 82736000)
		EASSERT(a.digitCount() == 8)
		a.leftDigitalShift(-3);
		EASSERT(a.toInteger() == 82736)
		EASSERT(a.digitCount() == 5)
		a.leftDigitalShift(1);
		EASSERT(a.toInteger() == 827360)
		EASSERT(a.digitCount() == 6)
		a.leftDigitalShift(0);
		EASSERT(a.toInteger() == 827360)
		EASSERT(a.digitCount() == 6)
		a.leftDigitalShift(5);
		EASSERT(a.toInteger() == 82736000000)
		EASSERT(a.digitCount() == 11)
		
		// leftDigitalRotate
		
		a = 17892372809;
		a.leftDigitalRotate(-5);
		EASSERT(a.toInteger() == 72809178923)
		EASSERT(a.digitCount() == 11)
		a.leftDigitalRotate(11);
		EASSERT(a.toInteger() == 72809178923)
		EASSERT(a.digitCount() == 11)
		a.leftDigitalRotate(1);
		EASSERT(a.toInteger() == 28091789237)
		EASSERT(a.digitCount() == 11)
		a.leftDigitalRotate(0);
		EASSERT(a.toInteger() == 28091789237)
		EASSERT(a.digitCount() == 11)
		a.leftDigitalRotate(5);
		EASSERT(a.toInteger() == 78923728091)
		EASSERT(a.digitCount() == 11)
		a.leftDigitalRotate(8);
		EASSERT(a.toInteger() == 9178923728)
		EASSERT(a.digitCount() == 10)
		
		// Division
		
		a = 1234;
		a /= EDigitInteger(123);
		EASSERT(a.toInteger() == 10)
		EASSERT(a.isPositive())
		
		a = 9999;
		a /= EDigitInteger(1);
		EASSERT(a.toInteger() == 9999)
		EASSERT(a.isPositive())
		
		a = 182374;
		b = 2829;
		b.setPositive(false);
		a /= b;
		EASSERT(a.toInteger() == 64)
		EASSERT(!a.isPositive())
		
		a = 321;
		a.setPositive(false);
		b = 123;
		b.setPositive(false);
		a /= b;
		EASSERT(a.toInteger() == 2)
		EASSERT(a.isPositive())
		
		try
		{
			a = 100;
			a /= EDigitInteger(0);
			throw EAssertionException("Expected EDivideByZeroException to be thrown!");
		}
		catch(EDivideByZeroException &e)
		{
			ELUNUSED(e)
		}
		
		a = 31278;
		a.setPositive(false);
		b = 27;
		b.setPositive(false);
		a /= b;
		EASSERT(a.toInteger() == 1158)
		EASSERT(a.isPositive())
		
		// Modulus Divison
		
		a = 18937237;
		b = 23;
		a %= b;
		EASSERT(a.toInteger() == 3)
		EASSERT(a.isPositive())
		
		a = 18937237;
		a.setPositive(false);
		b = 1;
		a %= b;
		EASSERT(a.toInteger() == 0)
		EASSERT(a.isPositive())
		
		try
		{
			a = 2787;
			b = 0;
			a %= b;
			throw EAssertionException("Expected EDivideByZeroException to be thrown!");
		}
		catch(EDivideByZeroException &e)
		{
			ELUNUSED(e)
		}
		
		a = 27823;
		b = 378;
		b.setPositive(false);
		a %= b;
		EASSERT(a.toInteger() == 229)
		EASSERT(a.isPositive())
		
		a = 31278;
		a.setPositive(false);
		b = 27;
		b.setPositive(false);
		a %= b;
		EASSERT(a.toInteger() == 12)
		EASSERT(!a.isPositive())
		
		// sumOfDigits
		
		a = 2378274987;
		EASSERT(a.sumOfDigits() == 57)
		
		a = 2378274987;
		a.setPositive(false);
		EASSERT(a.sumOfDigits() == 57)
		
		a = 2378274000;
		EASSERT(a.sumOfDigits() == 33)
		
		// isPalindrome
		
		a = 237824782;
		EASSERT(!a.isPalindrome())
		
		a = 112232211;
		EASSERT(a.isPalindrome())
		
		a = 112232211;
		a.setPositive(false);
		EASSERT(a.isPalindrome())
		
		// isPandigital
		
		a = 12345;
		a.setPositive(false);
		EASSERT(a.isPandigital())
		
		a = 1;
		EASSERT(a.isPandigital())
		
		a = 123456789;
		EASSERT(a.isPandigital())
		
		a = 1234567891;
		EASSERT(!a.isPandigital())
		
		a = 5;
		EASSERT(!a.isPandigital())
		
		// isDigitallyEquivalent
		
		a = 12345;
		b = 54312;
		EASSERT(a.isDigitallyEquivalent(b))
		
		a = 11;
		b = 1;
		EASSERT(!a.isDigitallyEquivalent(b))
		
		a = 27837;
		b = 37287;
		a.setPositive(false);
		EASSERT(a.isDigitallyEquivalent(b))
		
		// reverseDigits
		
		a = 2173843782;
		a.reverseDigits();
		EASSERT(a.toInteger() == 2873483712)
		
		a = 10;
		a.reverseDigits();
		EASSERT(a.toInteger() == 1)
		
		a = 2003;
		a.setPositive(false);
		a.reverseDigits();
		EASSERT(a.toInteger() == 3002)
		EASSERT(!a.isPositive())
		
		a = 123456789;
		a.reverseDigits(1, 7);
		EASSERT(a.toInteger() == 187654329)
		
		// permutateDigits
		
		EArray<int> array(9);
		a = 987654321;
		array.at(0) = 1;
		array.at(1) = 2;
		array.at(2) = 3;
		array.at(3) = 4;
		array.at(4) = 5;
		array.at(5) = 6;
		array.at(6) = 7;
		array.at(7) = 8;
		array.at(8) = 9;
		
		do
		{
			for(i = 0; static_cast<int>(i) < a.digitCount(); ++i)
			{
				EASSERT(a.get(static_cast<int>(i)) == array.at(static_cast<int>(i)))
			}
		} while( array.permutate() && a.permutateDigits() );
		
		// reversePermutateDigits
		
		a = 123456789;
		array.at(0) = 9;
		array.at(1) = 8;
		array.at(2) = 7;
		array.at(3) = 6;
		array.at(4) = 5;
		array.at(5) = 4;
		array.at(6) = 3;
		array.at(7) = 2;
		array.at(8) = 1;
		
		do
		{
			for(i = 0; static_cast<int>(i) < a.digitCount(); ++i)
			{
				EASSERT(a.get(static_cast<int>(i)) == array.at(static_cast<int>(i)))
			}
		} while( array.reversePermutate() && a.reversePermutateDigits() );
		
		// sortDigitsAscending
		
		a = 219287365939;
		a.sortDigitsAscending();
		
		for(i = 0; static_cast<int>(i) < (a.digitCount() - 1); ++i)
			EASSERT(a.get(static_cast<int>(i)) <= a.get(static_cast<int>(i+1)))
		
		// sortDigitsDescending
		
		a = 219287365939;
		a.sortDigitsDescending();
		
		for(i = 0; static_cast<int>(i) < (a.digitCount() - 1); ++i)
			EASSERT(a.get(static_cast<int>(i)) >= a.get(static_cast<int>(i+1)))
	}
	catch(EAssertionException &e)
	{
		ELUNUSED(e)
		success = false;
	}
	catch(EException &e)
	{
		EDIE_LOGIC(e)
	}
	
	// Print out our results.
	if(success)
		std::cout << "[ OK ]\n";
	else
		std::cout << "[FAIL]\n";
}
#endif

/*!
 * This is our default constructor, which initializes a new object with a default capacity,
 * load factor, value and sign.
 */
EDigitInteger::EDigitInteger()
	: EHashMap<int, int>(EDIGITINTEGER_DEFAULT_CAPACITY, EDIGITINTEGER_LOAD_FACTOR)
{
	setZero();
	
#ifdef LIBEULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
}

/*!
 * This is our copy constructor, which initializes a new object that has the same value as
 * the given other object.
 *
 * \param o The other object we will be equal to.
 */
EDigitInteger::EDigitInteger(const EDigitInteger &o)
	: EHashMap<int, int>(o)
{
	// Our constructor takes care of our digit list, so just set our other properties...
	setPositive(o.isPositive());
	
#ifdef LIBEULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
}

/*!
 * This is a convenience constructor, which initializes a new object that has the same value
 * as the given primitive integer type.
 *
 * \param v The value we will be equal to.
 */
EDigitInteger::EDigitInteger(uint64_t v)
	: EHashMap<int, int>(EDIGITINTEGER_DEFAULT_CAPACITY, EDIGITINTEGER_LOAD_FACTOR)
{
	(*this) = v;
}

/*!
 * This is a convenience constructor, which initializes a new object that has the same value
 * as the given GMP big integer type.
 *
 * \param v The value we will be equal to.
 */
EDigitInteger::EDigitInteger(const mpz_class &v)
	: EHashMap<int, int>(EDIGITINTEGER_DEFAULT_CAPACITY, EDIGITINTEGER_LOAD_FACTOR)
{
	(*this) = v;
}

/*!
 * This is our default destructor, which cleans up & destroys our object.
 */
EDigitInteger::~EDigitInteger()
{
}

/*!
 * This is an assignment operator, which sets our value equal to that of the given other object.
 *
 * \param o The other object to set ourself equal to.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator=(const EDigitInteger &o)
{
	// Use our superclass's assignment operator...
	EHashMap<int, int>::operator=(o);
	
	// Set our other properties...
	setPositive(o.isPositive());
	
#ifdef LIBEULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
	
	return (*this);
}

/*!
 * This is an assignment operator, which sets our value equal to that of the given string. The
 * expected format for this string is one of:
 *
 *     "1234",
 *     "-1234",
 *  or "+1234"
 *
 * If the format is something else, then an exception will be thrown.
 *
 * \param v A string-representation of the value we will be equal to.
 * \exception EStringFormatException This exception is thrown if the string provided is in an invalid format.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator=(const std::string &v)
	throw(EStringFormatException &)
{
	try
	{
		const char *cv = v.c_str();
		bool signSet;
		char buf[2];
		size_t i;
		int digit;
		
		buf[1] = '\0';
		
		// Make our value zero initially.
		setZero();
		
		digit = 0;
		signSet = false;
		for(i = strlen(cv); i > 0; i--)
		{ // Loop backwards so the values will be in the right place in our internal array.
			i -= 1;
			
			if(cv[i] == '+')
			{
				// If we encounter a '+' try to set our sign positive, unless it has already been set.
				if(signSet)
				{
					throw EStringFormatException("Invalid input string!");
				}
				else
				{
					setPositive(true);
					signSet = true;
				}
			}
			else if(cv[i] == '-')
			{
				// If we encounter a '-' try to set our sign negative, unless it has already been set.
				if(signSet)
				{
					throw EStringFormatException("Invalid input string!");
				}
				else
				{
					setPositive(false);
					signSet = true;
				}
			}
			else if(isdigit(cv[i]))
			{
				// If we encounter a digit, try to insert it into our number. Also assume positive if the sign hasn't been set.
				if(!signSet && (i == 0))
				{
					setPositive(true);
					signSet = true;
				}
				
				try
				{
					buf[0] = cv[i];
					volatileSetDigitAt(digit++, atoi(buf));
				}
				catch(EValueRangeException &e)
				{ // This should never be thrown, since our buffer is only 2 characters long.
#ifdef LIBEULER_DEBUG
					EDIE_LOGIC(e)
#else
					ELUNUSED(e)
#endif
				}
			}
			else
			{
				throw EStringFormatException("Invalid input string!");
			}
			
			i += 1;
		}
		
		// Ditch any leading zeros we may have picked up.
		removeLeadingZeros();
	}
	catch(EStringFormatException &e)
	{
		setZero();
		throw e;
	}
	
#ifdef LIBEULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
	
	// Make sure that, if our value is 0, we are positive.
	try
	{
		if(getKeys() == 1)
			if(get(0) == 0)
				setPositive(true);
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	return (*this);
}

/*!
 * This is one of our assignment operators, which sets our value to be equal to that of the given primitive
 * integer type. Since v is an unsigned type, our resulting value will be positive.
 *
 * \param v The value we will have.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator=(uint64_t v)
{
#if (defined _WIN32 || defined __APPLE__)
	return this->operator=(EMath::int64ToBigInteger(v));
#else
	return this->operator=(mpz_class(v));
#endif
}

/*!
 * This is one of our assignment operators, which sets our value to be equal to that of the given GMP
 * big integer object. This treats v as unsigned, so our resulting value will be positive.
 *
 * \param v The value we will have.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator=(const mpz_class &v)
{
	mpz_class vc = v, m;
	int i;
	
	// Zero-out our value initially.
	setZero();
	
	// Set our value.
	try
	{
		i = 0;
		while(vc > 0)
		{
			m = (vc % 10);
			volatileSetDigitAt(i++, m.get_ui());
			vc /= 10;
		}
		
		// Ditch any leading zeros we may have picked up.
		removeLeadingZeros();
	}
	catch(EValueRangeException &e)
	{ // The digits in another Int50 should not be out-of-range, because by design our class will not allow it.
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
#ifdef LIBEULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
	
	// Make sure that, if our value is 0, we are positive.
	try
	{
		if(getKeys() == 1)
			if(get(0) == 0)
				setPositive(true);
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	return (*this);
}

/*!
 * This is one of our comparison operators, which tests if our value is equal to
 * that of the given other object. You can use the explicit constructors that take other types to
 * compare our object to other values.
 *
 * \param o The other object to compare ourself to.
 * \return True if our objects are equal, or false otherwise.
 */
bool EDigitInteger::operator==(const EDigitInteger &o) const
{
	if(isPositive() != o.isPositive())
		return false;
	
	return unsignedEqualTo(o);
}

/*!
 * This is one of our comparison operators, which tests if our value is not equal to
 * that of the given other object. You can use the explicit constructors that take other types to
 * compare our object to other values.
 *
 * \param o The other object to compare ourself to.
 * \return True if our objects are not equal, or false otherwise.
 */
bool EDigitInteger::operator!=(const EDigitInteger &o) const
{
	return !operator==(o);
}

/*!
 * This is one of our comparison operators, which tests if our value is less than
 * that of the given other object. You can use the explicit constructors that take other types to
 * compare our object to other values.
 *
 * \param o The other object to compare ourself to.
 * \return True if our object is less than the other, or false otherwise.
 */
bool EDigitInteger::operator<(const EDigitInteger &o) const
{
	bool magnitude;
	
	// Try to test if we are less than the other using our signs.
	if(isPositive() != o.isPositive())
	{ // If our signs are different...
		
		if(!o.isPositive())
			return false; // O is negative, so we must be positive (and greater).
		else
			return true; // Otherwise, the reverse is true.
	}
	
	// Check our relative magnitudes, since our sign is the same.
	magnitude = unsignedLessThan(o);
	if(isPositive())
		return magnitude;
	else // If we are negative, then a bigger "absolute value" means a SMALLER number...
		return (!magnitude);
}

/*!
 * This is one of our comparison operators, which tests if our value is greater than
 * that of the given other object. You can use the explicit constructors that take other types to
 * compare our object to other values.
 *
 * \param o The other object to compare ourself to.
 * \return True if our object is greater than the other, or false otherwise.
 */
bool EDigitInteger::operator>(const EDigitInteger &o) const
{
	return ( !((*this) < o) && ((*this) != o) );
}

/*!
 * This is one of our comparison operators, which tests if our value is less than or equal to
 * that of the given other object. You can use the explicit constructors that take other types to
 * compare our object to other values.
 *
 * \param o The other object to compare ourself to.
 * \return True if our object is less than or equal to the other, or false otherwise.
 */
bool EDigitInteger::operator<=(const EDigitInteger &o) const
{
	return ( ((*this) < o) || ((*this) == o) );
}

/*!
 * This is one of our comparison operators, which tests if our value is greater than or equal to
 * that of the given other object. You can use the explicit constructors that take other types to
 * compare our object to other values.
 *
 * \param o The other object to compare ourself to.
 * \return True if our object is greater than or equal to the other, or false otherwise.
 */
bool EDigitInteger::operator>=(const EDigitInteger &o) const
{
	return ( ((*this) > o) || ((*this) == o) );
}

/*!
 * This is our unary minus / additive inverse operator. It returns a copy of our object with the sign
 * reversed.
 *
 * \return A copy of our object with the opposite sign.
 */
EDigitInteger EDigitInteger::operator-() const
{
	EDigitInteger r( (*this) );
	r.setPositive(!r.isPositive());
	return r;
}

/*!
 * This operator adds the value of the given other object to our value, and makes it so our object
 * contains the result.
 *
 * \param o The object to add to ourself.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator+=(const EDigitInteger &o)
{
	bool msign = isPositive(), osign = o.isPositive();
	
	/*
	 * If our absolute value INCREASES (i.e., our currently positive number becomes MORE positive, or
	 * our currently negative number becomes MORE negative), we just need to do an unsigned add of the
	 * two numbers, keeping the sign the same.
	 *
	 * If, on the other hand, our absolute value DECREASES (i.e., our currently positive number becomes
	 * LESS positive, or our currently negative number becomes LESS negative), we need to do an unsigned
	 * subtract of the smaller of our two numbers from the larger one. If "this" is the SMALLER one, then
	 * we also need to flip the sign on the result (because we crossed 0 and went back the other way).
	 */
	
	if(msign == osign)
	{
		/*
		 * If we are doing a negative ADD another negative, or a positive ADD another positive,
		 * then our absolute value is INCREASING. Therefore, as stated above, we just need to 
		 * do an unsigned add, without touching the sign.
		 */
		unsignedAdd(o);
	}
	else
	{
		/*
		 * Otherwise, if we are doing a negative ADD a positive, or a positive ADD a negative,
		 * then our absolute value is DECREASING. Therefore, as stated above, we need to do an
		 * unsigned subtract of the SMALLER number from the LARGER number, and if "this" is the
		 * SMALLER number, we need to flip the sign of the result.
		 */
		if( unsignedEqualTo(o) )
		{
			// If our numbers are the same, then our result is simply 0.
			setZero();
			return (*this);
		}
		
		// Otherwise, make sure we are the larger number, then subtract.
		if( unsignedLessThan(o) )
		{
			EDigitInteger tmp(o);
			swapValues(tmp);
			
			msign = !msign;
			unsignedSubtract(tmp);
			setPositive(msign);
		}
		else
		{
			unsignedSubtract(o);
		}
	}
	
	removeLeadingZeros();
	
#ifdef LIBEULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
	
	// Make sure that, if our value is 0, we are positive.
	try
	{
		if(getKeys() == 1)
			if(get(0) == 0)
				setPositive(true);
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	return (*this);
}

/*!
 * This operator subtracts the value of the given other object from our value, and makes it so our object
 * contains the result.
 *
 * \param o The object to subtract from ourself.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator-=(const EDigitInteger &o)
{
	/*
	  a - b
	= -( (-a) + b )
	*/
	
	// Flip our sign and then add.
	setPositive(!isPositive());
	this->operator+=(o);
	removeLeadingZeros();
	setPositive(!isPositive());
	
	// Make sure that, if our value is 0, we are positive.
	try
	{
		if(getKeys() == 1)
			if(get(0) == 0)
				setPositive(true);
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	return (*this);
}

/*!
 * This operator multiplies our value by the value of the given other object, and makes it so our object
 * contains the result.
 *
 * \param o The object to multiply ourself by.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator*=(const EDigitInteger &o)
{
	// The result is positive if either both inputs are positive or both are negative.
	bool sign = (isPositive() == o.isPositive());
	
	// Do our multiplication.
	unsignedMultiply(o);
	removeLeadingZeros();
	setPositive(sign);
	
#ifdef LIBEULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
	
	// Make sure that, if our value is 0, we are positive.
	try
	{
		if(getKeys() == 1)
			if(get(0) == 0)
				setPositive(true);
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	return (*this);
}

/*!
 * This operator divides our value by the value of the given other object, and makes it so our object
 * contains the result. Note that any remainder encountered is simply discarded.
 *
 * \param o The object to divide ourself by.
 * \exception EDivideByZeroException This exception is thrown if the other value provided is zero.
 * \return A reference to this, to the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator/=(const EDigitInteger &o)
	throw(EDivideByZeroException &)
{
	// The result is positive if either both inputs are positive or both are negative.
	bool sign = (isPositive() == o.isPositive());
	
	// Do our divide.
	unsignedDivide(o);
	removeLeadingZeros();
	setPositive(sign);
	
#ifdef LIBEULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
	
	// Make sure that, if our value is 0, we are positive.
	try
	{
		if(getKeys() == 1)
			if(get(0) == 0)
				setPositive(true);
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	return (*this);
}

/*!
 * This operator performs a modulo operation of our value by the given other value, and makes it so our
 * object contains the result. That is, the result will be the remainder of our value divided by the given
 * other value. Note that, in accordance with the C99 standard, the result will have the same sign as the
 * dividend (i.e., our sign doesn't change).
 *
 * \param o The object to divide ourself by.
 * \exception EDivideByZeroException This exception is thrown if the other value provided is zero.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator%=(const EDigitInteger &o)
	throw(EDivideByZeroException &)
{
	bool sign = isPositive();
	unsignedDivide(o, true);
	removeLeadingZeros();
	setPositive(sign);
	
#ifdef LIBEULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
	
	// Make sure that, if our value is 0, we are positive.
	try
	{
		if(getKeys() == 1)
			if(get(0) == 0)
				setPositive(true);
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	return (*this);
}

/*!
 * This is our addition operator, which returns by value a new object that has the sum of our value and the
 * value of the given other object.
 *
 * \param o The other object to add to our value.
 * \return A new object containing the result.
 */
EDigitInteger EDigitInteger::operator+(const EDigitInteger &o) const
{
	EDigitInteger r( (*this) );
	r += o;
	return r;
}

/*!
 * This is our subtraction operator, which returns by value a new object that has the difference of our value
 * and the value of the given other object.
 *
 * \param o The other object to subtract from our value.
 * \return A new object containing the result.
 */
EDigitInteger EDigitInteger::operator-(const EDigitInteger &o) const
{
	EDigitInteger r( (*this) );
	r -= o;
	return r;
}

/*!
 * This is our multiplication operator, which returns by value a new object that has the product of our value
 * and the value of the given other object.
 *
 * \param o The other object to multiply our value by.
 * \return A new object containing the result.
 */
EDigitInteger EDigitInteger::operator*(const EDigitInteger &o) const
{
	EDigitInteger r( (*this) );
	r *= o;
	return r;
}

/*!
 * This is our division operator, which returns by value a new object that has the quotient of our value and the
 * value of the given other object. Note that any remainder encountered is simply discarded.
 *
 * \param o The other object to divide our value by.
 * \exception EDivideByZeroException This exception is thrown if the other value provided is zero.
 * \return A new object containing the result.
 */
EDigitInteger EDigitInteger::operator/(const EDigitInteger &o) const
	throw(EDivideByZeroException &)
{
	EDigitInteger r( (*this) );
	r /= o;
	return r;
}

/*!
 * This is our modulus division operator, which returns by value a new object that has the remainder of our value
 * divided by the given other value. Note that, in accordance with the C99 standard, the result will have the same
 * sign as the dividend (i.e., the sign of the left-hand operand).
 *
 * \param o The object to divide ourself by.
 * \exception EDivideByZeroException This exception is thrown if the other value provided is zero.
 * \return A new object containing the result.
 */
EDigitInteger EDigitInteger::operator%(const EDigitInteger &o) const
	throw(EDivideByZeroException &)
{
	EDigitInteger r( (*this) );
	r %= o;
	return r;
}

/*!
 * This is our prefix increment operator, which will increase our current object's value by 1.
 *
 * \return A reference to this.
 */
EDigitInteger &EDigitInteger::operator++()
{
	return ( (*this) += EDigitInteger(1) );
}

/*!
 * This is our postfix increment operator, which will increase our current object's value by 1.
 *
 * \param i This parameter is unused; it is simply there to differentiate between post- versus prefix.
 * \return A copy of our original value, so the change occurs after the expression is evaluated.
 */
EDigitInteger EDigitInteger::operator++(int EUNUSED(i))
{
	EDigitInteger r;
	r = (*this);
	( (*this) += EDigitInteger(1) );
	return r;
}

/*!
 * This is our prefix decrement operator, which will decrease our current object's value by 1.
 *
 * \return A reference to this.
 */
EDigitInteger &EDigitInteger::operator--()
{
	return ( (*this) -= EDigitInteger(1) );
}

/*!
 * This is our postfix decrement operator, which will decrease our current object's value by 1.
 *
 * \param i This parameter is unused; it is simply there to differentiate between post- versus prefix.
 * \return A copy of our original value, so the change occurs after the expression is evaluated.
 */
EDigitInteger EDigitInteger::operator--(int EUNUSED(i))
{
	EDigitInteger r;
	r = (*this);
	( (*this) -= EDigitInteger(1) );
	return r;
}

/*!
 * This functino just returns whether or not our number is currently positive or not.
 *
 * \return True if our number is positive, or false otherwise.
 */
bool EDigitInteger::isPositive() const
{
	return positive;
}

/*!
 * This function sets whether or not our number is currently positive or not by passing
 * true or false, respectively.
 *
 * \param p Our new sign.
 */
void EDigitInteger::setPositive(bool p)
{
	positive = p;
}

/*!
 * This function returns the same value as getKeys(), since we are a subclass of EHashMap,
 * but its name is a bit more logical than that of our parent class's function.
 *
 * \return The nubmer of digits in our number.
 */
int EDigitInteger::digitCount() const
{
	return getKeys();
}

/*!
 * This function returns a sum of all of our digits, ignoring sign. This function operates
 * in O(n) time over our digits.
 *
 * \return The sum of our digits.
 */
int EDigitInteger::sumOfDigits() const
{
	int i;
	int total = 0;
	
	try
	{
		for(i = total = 0; i < getKeys(); ++i)
			total += get(i);
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	return total;
}

/*!
 * This function tests if our number is a palindrome (that is, it is equivalent both forwards
 * and backwards). This function ignores our sign. This function operates in O(n) time over
 * our digits.
 *
 * \return True if our number is a palindrome, or false otherwise.
 */
bool EDigitInteger::isPalindrome() const
{
	int a, b;
	
	try
	{
		for(a = 0, b = (getKeys() - 1); a < b; ++a, --b)
			if(get(a) != get(b))
				return false;
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	return true;
}

/*!
 * This function tests if our number is pandigital or not. That is, for an n-digit number, to be
 * pandigital it must contain all of the digits from 1 to n. This function operates in O(n) time
 * over our digits, and doesn't need to sort or copy our number. Because numbers with more than 9
 * digits cannot be definition be pandigital (in base 10), we only even have to check very small
 * numbers.
 *
 * \return True if our number is pandigital, or false otherwise.
 */
bool EDigitInteger::isPandigital() const
{
	int digits[10] = {0,0,0,0,0,0,0,0,0,0};
	
	// 10-digit and larger numbers cannot be pandigital in base 10.
	if(getKeys() >= 10)
		return false;
	
	// Look at each of our digits.
	
	try
	{
		for(int i = 0; i < getKeys(); ++i)
			++digits[get(i)];
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	// Ensure that the digits we SHOULD contain are exactly one, and the digits we SHOULDN'T are still zero.
	
	if(digits[0] != 0) return false;
	
	for(int i = 1; i <= getKeys(); ++i)
	{
		if(digits[i] != 1)
			return false;
	}
	
	for(int i = getKeys() + 1; i < 10; ++i)
	{
		if(digits[i] != 0)
			return false;
	}
	
	// Must be pandigital if we've gotten this far.
	
	return true;
}

/*!
 * This function tests if our number and the given other number are digitally equivalent. That is, this function
 * will test if our numbers contain exactly the same digits (but not necessarily in the same order). Note that this
 * function will not even test numbers that contain different numbers of digits, and otherwise will operate in O(n)
 * time across the digits in each number.
 *
 * \param o The other object to compare ourself to.
 * \return True if our numbers are digitally equivalent, or false otherwise.
 */
bool EDigitInteger::isDigitallyEquivalent(const EDigitInteger &o) const
{
	int i;
	int digits[10] = {0,0,0,0,0,0,0,0,0,0};
	
	// If we have a different number of digits, return false immediately.
	if(getKeys() != o.getKeys())
		return false;
	
	try
	{
		// Add both of our numbers' digits to our cache.
		for(i = 0; i < getKeys(); ++i)
		{
			digits[get(i)]++;
			digits[o.get(i)]--;
		}
		
		// Loop through the counter and if we find an inconsistency, return false.
		for(i = 0; i < 10; ++i)
			if(digits[i] != 0)
				return false;
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	return true;
}

/*!
 * This function inserts the given digit (v) at the given position in our number (k). If a digit is already
 * present at that position, then it is replaced. If the position is past the end of our number, then zeros
 * are automatically filled in between the end of our number and your new digit.
 *
 * \param k The position to insert the new digit at.
 * \param v The value of the digit to insert.
 * \exception EValueRangeException This exception is thrown if 0 <= v <= 9 is not true.
 * \return True if a new digit was inserted, or false if a digit was replaced.
 */
bool EDigitInteger::put(const int &k, const int &v)
	throw(EValueRangeException &)
{
	bool r;
	
	// Only accept digits that really are single-digit values, and are positive (negative digits make no sense).
	if( (v > 9) || (v < 0) )
		throw EValueRangeException("The specified digit value was out of range!");
	
	// Set our digit.
	r = volatileSetDigitAt(k, v);
	removeLeadingZeros();
	return r;
}

/*!
 * This function reimplements the erase() function on our superclass. It behaves the same way, except if you
 * erase an "interior digit" (i.e., any digit except the highest digit in our number), then it shifts everything
 * else down so as to maintain number continuity (a number with a hole in it doesn't make much sense).
 *
 * \param k The position of the digit that is to be removed.
 * \return True if a digit was removed, or false otherwise.
 */
bool EDigitInteger::erase(const int &k)
{
	int i;
	bool r;
	
	// If the position is out-of-range or if it is the last digit in our number, just remove it and return.
	if(k >= getKeys())
		return false;
	else if(k == (getKeys() - 1))
	{
		r = EHashMap<int, int>::erase(k);
		
		if(getKeys() < 1)
			put(0, 0);
		
#ifdef LIBEULER_DEBUG
		// Make sure our number still has at least 1 digit.
		EASSERT(getKeys() >= 1);
#endif
		
		return r;
	}
	
	try
	{
		// Otherwise, shift everything down and then pop the top digit.
		for(i = k; i < (getKeys() - 1); ++i)
			put(i, get(i+1));
		
		r = EHashMap<int, int>::erase(getKeys() - 1);
		
		if(getKeys() < 1)
			put(0, 0);
		
#ifdef LIBEULER_DEBUG
		// Make sure our number still has at least 1 digit.
		EASSERT(getKeys() >= 1);
#endif
		
		return r;
	}
	catch(EValueRangeException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
#ifdef LIBEULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
	
	return false;
}

/*!
 * This function shifts our digits the given number of places to the right, discarding digits
 * that are shifted off the end. A call of rightDigitalShift(1) is equivalent to DIVIDING our
 * number by 10 and discarding the remainder.
 *
 * \param p The number of places to shift our number.
 */
void EDigitInteger::rightDigitalShift(int p)
{
	int i;
	int d = getKeys();
	
	// A shift of 0 places has no effect.
	if(p == 0)
		return;
	
	// Treat negative right-shifts as positive left-shifts.
	if(p < 0)
	{
		leftDigitalShift(EABS(p));
		return;
	}
	
	// If we're shifting all the way off the end of our number, just return now.
	if(p > d)
	{
		setZero();
		return;
	}
	
	try
	{
		// Shift everything.
		for(i = 0; i < d; ++i)
			if(p <= i)
				put(i - p, get(i));
		
		// Get rid of the remaining digits at the high end of our number.
		i = getKeys() - p;
		while(EHashMap<int, int>::erase(i++));
	}
	catch(EValueRangeException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
#ifdef LIBEULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
}

/*!
 * This function performs a right digit-wise rotation of our number by a given number of places. Note that
 * the return value's definition of "losing data" is if our result has leading zeros. These are removed (since
 * they do not change the value of the number) and the appropriate value is returned.
 *
 * \param p The number of places to rotate.
 * \return True if our rotation was done without losing data, or false otherwise.
 */
bool EDigitInteger::rightDigitalRotate(int p)
{
	int i, d;
	int *hold;
	bool r;
	
	// Treat negative right-rotations as positive left-rotations.
	if(p < 0)
		return leftDigitalRotate(EABS(p));
	
	// Don't do any full rotations.
	p %= digitCount();
	
	// Rotation 0 places has no effect.
	if(p == 0)
		return true;
	
	// Allocate some buffer memory for our rotation.
	hold = new int[p];
	
	try
	{
		// Add the p low digits to our buffer.
		for(i = 0; i < p; ++i)
			hold[p - i - 1] = get(i);
		
		
		// Shift right p places.
		rightDigitalShift(p);
		
		// Place the digits from our buffer back onto the top of our number.
		d = digitCount();
		for(i = 0; i < p; ++i)
			put(d + (p - i - 1), hold[i]);
	}
	catch(EValueRangeException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	// Clean up our buffer.
	delete[] hold;
	
	r = removeLeadingZeros();
	
#ifdef LIBEULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
	
	return r;
}

/*!
 * This function shifts our digits the given number of places to the left, filling in the new
 * empty spaces at the right with 0's. A call of rightDigitalShift(1) is equivalent to MULTIPLYING
 * our number by 10.
 *
 * \param p The number of places to shift our number.
 */
void EDigitInteger::leftDigitalShift(int p)
{
	int i;
	int d = getKeys();
	
	// A shift of 0 places has no effect.
	if(p == 0)
		return;
	
	// Treat negative left-shifts as positive right-shifts.
	if(p < 0)
	{
		rightDigitalShift(EABS(p));
		return;
	}
	
	try
	{
		// Shift everything.
		for(i = d; i > 0; --i)
			put((i-1)+p, get(i-1));
		
		// Fill in the new, empty space at the front with 0's.
		for(i = 0; i < p; ++i)
			put(i, 0);
	}
	catch(EValueRangeException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
#ifdef LIBEULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
}

/*!
 * This function performs a left digit-wise rotation of our number by a given number of places. Note that
 * the return value's definition of "losing data" is if our result has leading zeros. These are removed (since
 * they do not change the value of the number) and the appropriate value is returned.
 *
 * \param p The number of places to rotate.
 * \return True if our rotation was done without losing data, or false otherwise.
 */
bool EDigitInteger::leftDigitalRotate(int p)
{
	int i;
	int d;
	int *hold;
	bool r;
	
	// Treat negative right-rotations as positive left-rotations.
	if(p < 0)
		return rightDigitalRotate(EABS(p));
	
	// Don't do any full rotations.
	p %= getKeys();
	
	// Rotation 0 places has no effect.
	if(p == 0)
		return true;
	
	// Allocate some buffer memory for our rotation.
	hold = new int[p];
	
	try
	{
		// Add the p high digits to our buffer.
		d = digitCount();
		for(i = 0; i < p; ++i)
		{
			hold[i] = get(d - 1 - i);
			erase(d - 1 - i);
		}
		
		// Shift left p places.
		leftDigitalShift(p);
		
		// Place the digits from our buffer back onto the bottom of our number.
		for(i = 0; i < p; ++i)
			put(i, hold[p - 1 - i]);
	}
	catch(EValueRangeException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	// Clean up our buffer.
	delete[] hold;
	
	r = removeLeadingZeros();

#ifdef LIBEUADRA_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
	
	return r;
}

/*!
 * This function sorts the digits of our integer in ascending order. It should be noted that
 * this function will NEVER have to remove leading zeros, since they will be at the low digits of
 * our number.
 */
void EDigitInteger::sortDigitsAscending()
{
	quicksortAsc(0, digitCount() - 1);
}

/*!
 * This function sorts the digits of our integer in descending order. This function will also
 * remove any resulting leading zeros.
 *
 * \return True if no leading zeros were removed, or false otherwise.
 */
bool EDigitInteger::sortDigitsDescending()
{
	quicksortDesc(0, digitCount() - 1);
	return removeLeadingZeros();
}

/*!
 * This is an implementation of Knuth's "Algorithm L," which permutates a given array of elements
 * in lexicographic order. Note that because they are in lexicographic order, an array sorted in
 * ascending order is the "first" permutation.
 *
 * More information:
 *     http://en.wikipedia.org/wiki/Permutation#Systematic_generation_of_all_permutations
 *     http://blog.bjrn.se/2008/04/lexicographic-permutations-using.html
 *
 * Note that this function removes leading zeros after the permutation is performed, so it may not
 * work as expected with numbers that contain zero digits. If you just want to permutate numbers,
 * EArrayUtilities::permutate() may work better.
 *
 * \return True if there are more permutations, or false if this is the last one.
 */
bool EDigitInteger::permutateDigits()
{
	int hold;
	int k, l, i;
	
	try
	{
		/*
		 * Step 1: Find the largest index k such that a[k] < a[k + 1]. If no such index
		 *         exists, the permutation is the last permutation.
		 */
		
		k = -1;
		for(i = (digitCount() - 2); i >= 0; --i)
		{
			if(get(i) < get(i + 1))
			{
				k = i;
				break;
			}
		}
		
		if(k == -1) return false;
		
		/*
		 * Step 2: Find the largest index l such that a[k] < a[l]. Since k + 1 is such
		 *         an index, l is well defined and satisfies k < l.
		 */
		
		l = -1;
		for(i = (digitCount() - 1); k < i; --i)
		{
			if(get(k) < get(i))
			{
				l = i;
				break;
			}
		}
		
		if(l == -1) return false;
		
		/*
		 * Step 3: Swap a[k] and a[l].
		 */
		
		hold = get(k);
		volatileSetDigitAt(k, get(l));
		volatileSetDigitAt(l, hold);
		
		/*
		 * Step 4: Reverse the sequence from a[k + 1] up to and including the final element a[n].
		 */
		
		reverseDigits(k + 1, digitCount() - 1);
	}
	catch(EException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	removeLeadingZeros();
	return true;
}

/*!
 * This function is equivalent to permutate(), except it generates permutations in REVERSE lexicographic
 * order, instead of forwards. Accordingly, our "first" permutation is when our list is sorted in
 * descending order.
 *
 * Note that this function removes leading zeros after the permutation is performed, so it may not
 * work as expected with numbers that contain zero digits. If you just want to permutate numbers,
 * EArrayUtilities::reversePermutate() may work better.
 *
 * \return True if there are more permutations, or false if this is the last one.
 */
bool EDigitInteger::reversePermutateDigits()
{
	int hold;
	int k, l, i;
	
	try
	{
		/*
		 * Step 1: Find the largest index k such that a[k] < a[k - 1]. If no such index
		 *         exists, the permutation is the last permutation.
		 */
		
		k = -1;
		for(i = (digitCount() - 2); i >= 0; --i)
		{
			if(get(i) > get(i + 1))
			{
				k = i;
				break;
			}
		}
		
		if(k == -1) return false;
		
		/*
		 * Step 2: Find the largest index l such that a[k] < a[l]. Since k + 1 is such
		 *         an index, l is well defined and satisfies k < l.
		 */
		
		l = -1;
		for(i = (digitCount() - 1); k < i; --i)
		{
			if(get(k) > get(i))
			{
				l = i;
				break;
			}
		}
		
		if(l == -1) return false;
		
		/*
		 * Step 3: Swap a[k] and a[l].
		 */
		
		hold = get(k);
		volatileSetDigitAt(k, get(l));
		volatileSetDigitAt(l, hold);
		
		/*
		 * Step 4: Reverse the sequence from a[k + 1] up to and including the final element a[n].
		 */
		
		reverseDigits(k + 1, digitCount() - 1);
	}
	catch(EException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	removeLeadingZeros();
	return true;
}

/*!
 * This function reverses the order of the digits in our number. Note that the return value's definition of
 * "losing data" is if our result has leading zeros. These are removed (since they do not change the value of
 * our number) and the appropriate value is returned.
 *
 * \return True if the operation was done without losing data, or false otherwise.
 */
bool EDigitInteger::reverseDigits(int l, int r)
{
	int hold;
	int a, b;
	bool ret;
	
	l = (l < 0) ? 0 : l;
	r = (r == -1) ? (getKeys() - 1) : r;
	r = (r <= l) ? (getKeys() - 1) : r;
	r = (r >= getKeys()) ? (getKeys() - 1) : r;
	
	try
	{
		for(a = l, b = r; a < b; ++a, --b)
		{
			hold = get(a);
			volatileSetDigitAt(a, get(b));
			volatileSetDigitAt(b, hold);
		}
	}
	catch(EValueRangeException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	ret = removeLeadingZeros();
	
#ifdef LIBEULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(getKeys() >= 1);
#endif
	
	return ret;
}

/*!
 * This function returns a certain range in our number as a 64-bit unsigned integer. Note that if
 * the range specified contains leading zeros they will simply be discarded.
 *
 * \param l The left-most bound (inclusive).
 * \param r The right-most bound (inclusive).
 * \exception EOutOfBoundsException This exception is thrown if the range [l,r] is out-of-bounds.
 * \return The specified range as a 64-bit unsigned integer.
 */
uint64_t EDigitInteger::rangeToInteger(int l, int r) const
	throw(EOutOfBoundsException &)
{
	int i;
	uint64_t ret = 0;
	
	if( (l < 0) || (r >= getKeys()) )
		throw EOutOfBoundsException("Range is out-of-bounds.");
	
	for(i = r; i >= l; --i)
	{
		ret *= 10;
		ret += get(i);
	}
	
	return ret;
}

/*!
 * This is a convenience function, which is equivalent to running rangeToInteger() on our entire
 * number.
 *
 * \return Our entire number, represented as a 64-bit unsigned integer.
 */
uint64_t EDigitInteger::toInteger() const
{
	return rangeToInteger(0, getKeys() - 1);
}

/*!
 * This function returns a certain range in our number as a GMP big integer. Note that if the
 * range specified contains leading zeros they will simply be discarded.
 *
 * \param l The left-most bound (inclusive).
 * \param r The right-most bound (inclusive).
 * \exception EOutOfBoundsException This exception is thrown if the range [l,r] is out-of-bounds.
 * \return The specified range as a GMP big integer.
 */
mpz_class EDigitInteger::rangeToBigInteger(int l, int r) const
	throw(EOutOfBoundsException &)
{
	int i;
	mpz_class ret = 0;
	
	if( (l < 0) || (r >= getKeys()) )
		throw EOutOfBoundsException("Range is out-of-bounds.");
	
	for(i = r; i >= l; --i)
	{
		ret *= 10;
		ret += get(i);
	}
	
	return ret;
}

/*!
 * This is a convenience function, which is equivalent to running rangeToBigInteger() on our entire
 * number.
 *
 * \return Our entire number, represented as a GMP big integer object.
 */
mpz_class EDigitInteger::toBigInteger() const
{
	return rangeToBigInteger(0, getKeys() - 1);
}

/*!
 * This function returns a certain range in our number as a string. Note that if the range specified
 * contains leading zeros they will simply be discarded. Note that since this function is returning just
 * a portion of our string, it doesn't bother prepending a sign character. If you want that, you should
 * call toString() which will, or do it yourself.
 *
 * \param l The left-most bound (inclusive).
 * \param r The right-most bound (inclusive).
 * \exception EOutOfBoundsException This exception is thrown if the range [l,r] is out-of-bounds.
 * \return The specified range as a std::string.
 */
std::string EDigitInteger::rangeToString(int l, int r) const
	throw(EOutOfBoundsException &)
{
	int i;
	std::ostringstream oss;
	
	if( (l < 0) || (r >= getKeys()) )
		throw EOutOfBoundsException("Range is out-of-bounds.");
	
	for(i = r; i >= l; --i)
		oss << get(i);
	
	return oss.str();
}

/*!
 * This is a convenience function, which is equivalent to running rangeToString() on our entire
 * number. Note that this function DOES take the sign into account - if our number is negative, then
 * a '-' is prepended to the output number.
 *
 * \return Our entire number, represented as a string.
 */
std::string EDigitInteger::toString() const
{
	std::string r = rangeToString(0, getKeys() - 1);
	
	if(!isPositive())
		r.insert(0, "-");
	
	return r;
}

/*!
 * This function behaves the same as our public put() function, except it does not do range checking
 * on the value provided, so it can be used to, e.g., store intermediate values while performing an
 * addition or subtraction operation.
 *
 * \param i The position of the digit to set.
 * \param v The value of the new digit.
 * \return True if a new digit was inserted, or false if a digit was just updated.
 */
bool EDigitInteger::volatileSetDigitAt(int k, int v)
{
	int i;
	
	// Fill in digits between the previous end of our number and the specified digit with 0's.
	for(i = getKeys(); i < k; ++i)
		EHashMap<int, int>::put(i, 0);
	
	// Actually insert the new value.
	return EHashMap<int, int>::put(k, v);
}

/*!
 * This is a convenience function that removes the leading zeros from our number. It returns true if
 * leading zeros were removed, or false otherwise.
 *
 * \return True if leading zeros were removed, or false otherwise.
 */
bool EDigitInteger::removeLeadingZeros()
{
	bool r;
	int i;
	
	// Don't operate on numbers with 1 or fewer digits.
	if(getKeys() <= 1)
		return false;
	
	// Remove leading 0's from our number.
	r = false;
	try
	{
		for(i = (getKeys() - 1); i > 0; --i)
		{
			if(get(i) == 0)
			{
				r = true;
				erase(i);
			}
			else
				break;
		}
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	return r;
}

/*!
 * This utility function carries all of our digits, starting from the low digits, so it will be
 * "normalized" (that is, 0 <= digit <= 9 is always true), i.e. after an addition operation.
 */
void EDigitInteger::carry()
{
	int j;
	
	for(j = 0; containsKey(j); ++j)
	{
		while(get(j) > 9)
		{
			volatileSetDigitAt(j, get(j) - 10);
			
			try
			{
				volatileSetDigitAt(j+1, get(j+1) + 1);
			}
			catch(EOutOfBoundsException &)
			{
				volatileSetDigitAt(j+1, 1);
			}
		}
	}
	
#ifdef LIBEULER_DEBUG
	for(j = 0; j < digitCount(); ++j)
		EASSERT( (0 <= get(j)) && (get(j) <= 9) )
#endif
}

/*!
 * This utility function borrows all of our digits, starting from the low digits, so it will be
 * "normalized" (that is, 0 <= digit <= 9 is always true), i.e. after a subtraction operation.
 */
void EDigitInteger::borrow()
	throw(EUnderflowException &)
{
	int j;
	
	for(j = 0; containsKey(j+1); ++j)
	{
		while(get(j) < 0)
		{
			volatileSetDigitAt(j, get(j) + 10);
			volatileSetDigitAt(j+1, get(j+1) - 1);
		}
	}
	
	// We could possibly have reduced the number of digits in our number, leaving leading zeros...
	removeLeadingZeros();
	
	// If our leading digit is still negative, an error has occurred.
	if(get(digitCount() - 1) < 0)
		throw EUnderflowException("No more digits to borrow from!");
	
#ifdef LIBEULER_DEBUG
	for(j = 0; j < digitCount(); ++j)
		EASSERT( (0 <= get(j)) && (get(j) <= 9) )
#endif
}

/*!
 * This function sets our object's value to [positive] zero, clearing all of its existing digits
 * and other properties.
 */
void EDigitInteger::setZero()
{
	clear();
	volatileSetDigitAt(0, 0);
	setPositive(true);
}

/*!
 * This function tests if our value is equal to that of the given other object, ignoring the signs on
 * both.
 *
 * \param o The object to compare ourself to.
 * \return True if we are equal ignoring sign, or false otherwise.
 */
bool EDigitInteger::unsignedEqualTo(const EDigitInteger &o) const
{
	int i;
	
	// If our numbers contain varying numbers of digits, return immediately.
	if(getKeys() != o.getKeys())
		return false;
	
	try
	{
		// Test each digit until we find something that doesn't match.
		for(i = 0; i < getKeys(); ++i)
			if(get(i) != o.get(i))
				return false;
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	return true;
}

/*!
 * This function tests if our value is not equal to that of the given other object, ignoring the signs on
 * both.
 *
 * \param o The object to compare ourself to.
 * \return True if we are not equal ignoring sign, or false otherwise.
 */
bool EDigitInteger::unsignedNotEqualTo(const EDigitInteger &o) const
{
	return (!unsignedEqualTo(o));
}

/*!
 * This function tests if our value is less than the value of the given other object, ignoring signs.
 *
 * \param o The object to compare ourself to.
 * \return True if we are less than the other object, or false otherwise.
 */
bool EDigitInteger::unsignedLessThan(const EDigitInteger &o) const
{
	int i;
	
	// See if we can determine a return value based purely on the number of digits.
	if(getKeys() > o.getKeys())
		return false; // We have more digits, so we are greater.
	else if(getKeys() < o.getKeys())
		return true; // We have fewer digits, so we are less.
	
	try
	{
		// Test each of our digits to try and find an answer.
		for(i = (getKeys() - 1); i >= 0; --i)
			if(get(i) > o.get(i))
				return false; // Our digit is greater, so our number is greater.
			else if(get(i) < o.get(i))
				return true; // Our digit is less, so our number is less.
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	
	// We must be equal.
	return false;
}

/*!
 * This function tests if our value is greater than the value of the given other object, ignoring signs.
 *
 * \param o The object to compare ourself to.
 * \return True if we are greater than the other object, or false otherwise.
 */
bool EDigitInteger::unsignedGreaterThan(const EDigitInteger &o) const
{
	return (!unsignedLessThan(o) && !unsignedEqualTo(o));
}

/*!
 * This function tests if our value is less than or equal to that of the given other object, ignoring signs.
 *
 * \param o The object to compare ourself to.
 * \return True if we are less than or equal to the other object, or false otherwise.
 */
bool EDigitInteger::unsignedLessThanEqualTo(const EDigitInteger &o) const
{
	return (unsignedLessThan(o) || unsignedEqualTo(o));
}

/*!
 * This function tests if our value is greater than or equal to that of the given other object, ignoring signs.
 *
 * \param o The object to compare ourself to.
 * \return True if we are greater than or equal to the other object, or false otherwise.
 */
bool EDigitInteger::unsignedGreaterThanEqualTo(const EDigitInteger &o) const
{
	return (!unsignedLessThan(o));
}

/*!
 * This function does an unsigned add of the given other number to our current number. It doesn't factor
 * in which is positive and which is negative; it just adds magnitudes. It is up to the caller to handle
 * signs correctly. This function operates in O(n) time across our digits.
 *
 * \param i The other value to add to our value.
 */
void EDigitInteger::unsignedAdd(const EDigitInteger &i)
{
	int j;
	
	try
	{
		// Insert zeros at the front of our number until we are at least as big as the other.
		if(i.getKeys() > getKeys())
			volatileSetDigitAt(i.getKeys(), 0);
		
		// Do a digit-by-digit add, carrying as we go...
		for(j = 0; j < i.getKeys(); ++j)
			volatileSetDigitAt(j, get(j) + i.get(j));
		
		carry();
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This function does an unsigned subtract of the given other number from our current number. It doesn't
 * factor in which is positive and which is negative; it just subtracts one magnitude from the other. It
 * is up to the caller to handle signs correctly, and to MAKE SURE WE ARE >= THE OTHER VALUE. This function
 * operates in O(n) time across our digits.
 *
 * \param i The other value to subtract from our value.
 */
void EDigitInteger::unsignedSubtract(const EDigitInteger &i)
{
	int j;
	
#ifdef LIBEULER_DEBUG
	EASSERT( unsignedGreaterThanEqualTo(i) )
#endif
	
	// If we are equal, just return now.
	if( this->unsignedEqualTo(i) )
	{
		setZero();
		return;
	}
	
	try
	{
		// Do a digit-by-digit subtract, carrying as we go...
		for(j = 0; j < digitCount(); ++j)
		{
			// Only subtract if we are in-bounds on the other number.
			if(j < i.getKeys())
				volatileSetDigitAt(j, get(j) - i.get(j));
		}
		
		borrow();
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	catch(EUnderflowException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This function does an unsigned multiply of our value by the given other number. It doesn't factor in
 * which is positive and which is negative; it just multiplies the magnitudes. It is up to the caller to
 * handle/set signs correctly.
 *
 * \param i The other value to multiply our value by.
 */
void EDigitInteger::unsignedMultiply(const EDigitInteger &i)
{
	int a, b;
	EDigitInteger result;
	
	// Try to eliminate some easy possibilities.
	
	if(i.unsignedEqualTo(EDigitInteger(0)))
	{
		setZero();
		return;
	}
	
	if(i.unsignedEqualTo(EDigitInteger(1)))
		return;
	
	try
	{
		// Zero-out our results object.
		result.setZero();
		
		// Loop through each digit in both numbers...
		for(b = 0; b < i.getKeys(); ++b)
		{ // "b" represents the digit in the number we're multiplying by.
			for(a = 0; a < getKeys(); ++a)
			{ // "a" represents the digit in our current number.
				if( (b+a) >= result.getKeys() )
					result.volatileSetDigitAt(b+a, 0);
				
				// Multiply our current digits and add the result to our results array.
				result.volatileSetDigitAt(b+a, result.get(b+a) + (get(a) * i.get(b)));
			}
		}
		
		// Set our value to the result.
		result.carry();
		(*this) = result;
	}
	catch(EValueRangeException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This function performs an unsigned divide of our value by the given other value, optionally returning either
 * the result of the division or the remainder (i.e., modulus division). It doesn't factor in who is positive
 * and who is negative, so it is up to the caller to make sure that signs are set/handled correctly.
 *
 * \param i The other value to divide ourself by.
 * \param m Whether or not to do modulus division - true means we return the remainder, false means we return the division result.
 * \exception EDivideByZeroException This exception is thrown if the given other value is 0.
 */
void EDigitInteger::unsignedDivide(const EDigitInteger &i, bool m)
	throw(EDivideByZeroException &)
{
	EDigitInteger a, b, result;
	int aDigits, bDigits, j;
	bool sign = isPositive();
	
	if(i == EDigitInteger(0))
		throw EDivideByZeroException("Divide by zero!");
	
	try
	{
		// Try to eliminate some easy possibilities before we attempt an actual divide.
		
		if( unsignedLessThan(i) )
		{
			if(m)
			{
				return;
			}
			else
			{
				setZero();
				return;
			}
		}
		
		if( unsignedEqualTo(i) )
		{
			if(m)
			{
				setZero();
				return;
			}
			else
			{
				(*this) = 1;
				return;
			}
		}
		
		if( i.unsignedEqualTo(EDigitInteger(1)) )
		{
			if(m)
			{
				setZero();
				return;
			}
			else
			{
				return;
			}
		}
		
		/*
		 * An easy way to implement division is just to subtract the divisor from the dividend
		 * over and over again until the dividend is less than the divisor, and return the number
		 * of subtractions performed.
		 *
		 * This is very inefficient, however, for example in the case of a very large number divided
		 * by one - that would require O(n) divisions, where n is the dividend, and would go very
		 * slowly.
		 *
		 * Instead, we're going to right-shift (i.e., multiply by 10) our divisor until it is close
		 * to the dividend, and then multiply the divisor by a number such that the leading digits
		 * will be as close as possible, to eliminate a lot of the subtraction operations that will
		 * be performed.
		 */
		
		// Initialize a and b.
		
		a = (*this);
		a.setPositive(true);
		
		b = i;
		b.setPositive(true);
		
		aDigits = a.getKeys();
		bDigits = b.getKeys();
		
		// Initialize this - which will ultimately be our result.
		setZero();
		
		// This is our main loop for division, that goes a lot faster than just a naieve subtraction.
		result = 1;
		while(bDigits < aDigits)
		{
			// If b has only 1 fewer digits but a larger or equal leading digit, break out of the loop.
			if( (bDigits == (aDigits - 1)) && (b.get(bDigits - 1) >= a.get(aDigits - 1)) )
				break;
			
#ifdef LIBEULER_DEBUG
			// Make sure we aren't left-shifting by a negative value (i.e., right shifting).
			assert( (aDigits - bDigits) >= 0 );
#endif
			
			// Shift our number (multiply by power of 10) so it has a smaller number of digits.
			if( a.get(aDigits - 1) >= b.get(bDigits - 1) )
			{
				
				b.leftDigitalShift(aDigits - bDigits);
				result.leftDigitalShift(aDigits - bDigits);
			}
			else
			{
				b.leftDigitalShift(aDigits - bDigits - 1);
				result.leftDigitalShift(aDigits - bDigits - 1);
			}
			
			// Try multiplying by the largest possible number to optimize even more.
			for(j = 9; j > 0; --j)
			{
				if( (b * EDigitInteger(j)) <= a )
				{
					b *= EDigitInteger(j);
					result *= EDigitInteger(j);
					break;
				}
			}
			
			// Subtract this multiple and add it to our result.
			a -= b;
			(*this) += result;
			
			// Reset our variables for the next iteration of this loop.
			b = i;
			b.setPositive(true);
			bDigits = b.getKeys();
			aDigits = a.getKeys();
			result = 1;
		}
		
		// We've optimized just about as much as we can; finish up just doing a naieve subtraction.
		b = i;
		b.setPositive(true);
		while(a >= b)
		{
			a -= b;
			++(*this);
		}
		
		// If this was supposed to be a modulus operation, set our value to the remainder.
		if(m) (*this) = a;
		
		// Since this is an unsigned divide, set our sign back to its original value.
		setPositive(sign);
	}
	catch(EOutOfBoundsException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This is our behind-the-scenes ascending quicksort function.
 *
 * \param l The left index.
 * \param r The right index.
 */
void EDigitInteger::quicksortAsc(int l, int r)
{
	int pivot, hold;
	int i, j;
	
	try
	{
		/*
		 * Choose a pivot value. In this case, we just select the value in the center-ish of our
		 * array, but this could in theory be chosen a bit more intelligently.
		 */
		pivot = get((l + r) / 2);
		
		// Initialize our loop indices...
		i = l;
		j = r;
		
		// Keep looping until we have swapped all of the values to the correct side of the pivot.
		while(i <= j)
		{
			// Move right until we find a value that is >= our pivot.
			while(get(i) < pivot)
				++i;
			
			// Move left until we find a value that is <= our pivot.
			while(get(j) > pivot)
				--j;
			
			// If our left index is still left of our right index, then swap the two nodes.
			if(i < j)
			{
				hold = get(i);
				volatileSetDigitAt(i, get(j));
				volatileSetDigitAt(j, hold);
			}
			
			// Move our indices one more place for the next iteration of the loop.
			if(i <= j)
			{
				++i;
				--j;
			}
		}
		
		// If our left-most chunk is of size >= 1, then recurse on it.
		if(l < j)
			quicksortAsc(l, j);
		
		// If our right-most chunk is of size <= 1, then recurse on it.
		if(i < r)
			quicksortAsc(i, r);
	}
	catch(EException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This is our behind-the-scenes descending quicksort function.
 *
 * \param l The left index.
 * \param r The right index.
 */
void EDigitInteger::quicksortDesc(int l, int r)
{
	int pivot, hold;
	int i, j;
	
	try
	{
		/*
		 * Choose a pivot value. In this case, we just select the value in the center-ish of our
		 * array, but this could in theory be chosen a bit more intelligently.
		 */
		pivot = get((l + r) / 2);
		
		// Initialize our loop indices...
		i = l;
		j = r;
		
		// Keep looping until we have swapped all of the values to the correct side of the pivot.
		while(i <= j)
		{
			// Move right until we find a value that is <= our pivot.
			while(get(i) > pivot)
				++i;
			
			// Move left until we find a value that is >= our pivot.
			while(get(j) < pivot)
				--j;
			
			// If our left index is still left of our right index, then swap the two nodes.
			if(i < j)
			{
				hold = get(i);
				volatileSetDigitAt(i, get(j));
				volatileSetDigitAt(j, hold);
			}
			
			// Move our indices one more place for the next iteration of the loop.
			if(i <= j)
			{
				++i;
				--j;
			}
		}
		
		// If our left-most chunk is of size >= 1, then recurse on it.
		if(l < j)
			quicksortDesc(l, j);
		
		// If our right-most chunk is of size >= 1, then recurse on it.
		if(i < r)
			quicksortDesc(i, r);
	}
	catch(EException &e)
	{
#ifdef LIBEULER_DEBUG
		EDIE_LOGIC(e)
#else
		ELUNUSED(e)
#endif
	}
}

/*!
 * This is our output stream operator, which allows our objects to be easily printed to
 * a standard C++ ostream object. The value printed is effectively the same as that returned
 * by our class's toString() member function.
 *
 * \param out The output stream to which we will write.
 * \param i The EDigitInteger object we will be writing.
 * \return A reference to the output stream, so the operator can be chained.
 */
std::ostream &operator<<(std::ostream &out, const EDigitInteger &i)
{
	out << i.toString();
	return out;
}

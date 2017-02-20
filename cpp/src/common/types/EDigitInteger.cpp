/*
 * euler - A collection of ProjectEuler libraries, tools, and solutions.
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

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>

#include "common/EDefines.h"

#ifdef _WIN32
// We need EMath on Win32 for int64ToBigInteger().
#include "common/math/EMath.h"
#endif

/*!
 * This is our default constructor, which initializes a new object with a
 * default value and sign.
 */
EDigitInteger::EDigitInteger() : digits(), positive(true)
{
	setZero();

#ifdef EULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(digitCount() >= 1);
#endif
}

/*!
 * This is a convenience constructor, which initializes a new object that has
 * the same value as the given primitive integer type.
 *
 * \param v The value we will be equal to.
 */
EDigitInteger::EDigitInteger(uint64_t v) : digits(), positive(true)
{
	(*this) = v;
}

/*!
 * This is a convenience constructor, which initializes a new object that has
 * the same value as the given GMP big integer type.
 *
 * \param v The value we will be equal to.
 */
EDigitInteger::EDigitInteger(const mpz_class &v) : digits(), positive(true)
{
	(*this) = v;
}

/*!
 * This is an assignment operator, which sets our value equal to that of the
 * given string. The expected format for this string is one of:
 *
 *     "1234",
 *     "-1234",
 *  or "+1234"
 *
 * If the format is something else, then an exception will be thrown.
 *
 * \param v A string-representation of the value we will be equal to.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator=(const std::string &v)
{
	try
	{
		const char *cv = v.c_str();
		bool signSet;
		char buf[2];
		size_t i;
		std::size_t digit;

		buf[1] = '\0';

		// Make our value zero initially.
		setZero();

		digit = 0;
		signSet = false;
		for(i = strlen(cv); i > 0; i--)
		{ // Loop backwards so the values will be in the right place in
			// our internal array.
			i -= 1;

			if(cv[i] == '+')
			{
				// If we encounter a '+' try to set our sign
				// positive, unless it has already been set.
				if(signSet)
				{
					throw EException(
					        "Invalid input string!");
				}
				else
				{
					setPositive(true);
					signSet = true;
				}
			}
			else if(cv[i] == '-')
			{
				// If we encounter a '-' try to set our sign
				// negative, unless it has already been set.
				if(signSet)
				{
					throw EException(
					        "Invalid input string!");
				}
				else
				{
					setPositive(false);
					signSet = true;
				}
			}
			else if(isdigit(cv[i]))
			{
				// If we encounter a digit, try to insert it
				// into our number. Also assume positive if the
				// sign hasn't been set.
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
				catch(EValueRangeException &)
				{ // This should never be thrown, since our
					// buffer is only 2 characters long.
					assert(false);
				}
			}
			else
			{
				throw EException("Invalid input string!");
			}

			i += 1;
		}

		// Ditch any leading zeros we may have picked up.
		removeLeadingZeros();
	}
	catch(EException &e)
	{
		setZero();
		throw e;
	}

#ifdef EULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(digitCount() >= 1);
#endif

	// Make sure that, if our value is 0, we are positive.
	try
	{
		if(digitCount() == 1)
			if(get(0) == 0)
				setPositive(true);
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	return (*this);
}

/*!
 * This is one of our assignment operators, which sets our value to be equal to
 * that of the given primitive integer type. Since v is an unsigned type, our
 * resulting value will be positive.
 *
 * \param v The value we will have.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator=(uint64_t v)
{
#if(defined _WIN32 || defined __APPLE__)
	return this->operator=(EMath::int64ToBigInteger(v));
#else
	return this->operator=(mpz_class(v));
#endif
}

/*!
 * This is one of our assignment operators, which sets our value to be equal to
 * that of the given GMP big integer object. This treats v as unsigned, so our
 * resulting value will be positive.
 *
 * \param v The value we will have.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator=(const mpz_class &v)
{
	mpz_class vc = v, m;
	std::size_t i;

	// Zero-out our value initially.
	setZero();

	// Set our value.
	try
	{
		i = 0;
		while(vc > 0)
		{
			m = (vc % 10);
			volatileSetDigitAt(i, static_cast<int>(m.get_ui()));
			assert(get(i) == static_cast<int>(m.get_ui()));
			vc /= 10;
			++i;
		}

		// Ditch any leading zeros we may have picked up.
		removeLeadingZeros();
	}
	catch(EValueRangeException &)
	{ // The digits in another Int50 should not be out-of-range, because by
		// design our class will not allow it.
		assert(false);
	}

#ifdef EULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(digitCount() >= 1);
#endif

	// Make sure that, if our value is 0, we are positive.
	try
	{
		if(digitCount() == 1)
			if(get(0) == 0)
				setPositive(true);
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	return (*this);
}

/*!
 * This is one of our comparison operators, which tests if our value is equal to
 * that of the given other object. You can use the explicit constructors that
 * take other types to compare our object to other values.
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
 * This is one of our comparison operators, which tests if our value is not
 * equal to that of the given other object. You can use the explicit
 * constructors that take other types to compare our object to other values.
 *
 * \param o The other object to compare ourself to.
 * \return True if our objects are not equal, or false otherwise.
 */
bool EDigitInteger::operator!=(const EDigitInteger &o) const
{
	return !operator==(o);
}

/*!
 * This is one of our comparison operators, which tests if our value is less
 * than that of the given other object. You can use the explicit constructors
 * that take other types to compare our object to other values.
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
			return false; // O is negative, so we must be positive
		                      // (and greater).
		else
			return true; // Otherwise, the reverse is true.
	}

	// Check our relative magnitudes, since our sign is the same.
	magnitude = unsignedLessThan(o);
	if(isPositive())
		return magnitude;
	else // If we are negative, then a bigger "absolute value" means a
		// SMALLER number...
		return (!magnitude);
}

/*!
 * This is one of our comparison operators, which tests if our value is greater
 * than that of the given other object. You can use the explicit constructors
 * that take other types to compare our object to other values.
 *
 * \param o The other object to compare ourself to.
 * \return True if our object is greater than the other, or false otherwise.
 */
bool EDigitInteger::operator>(const EDigitInteger &o) const
{
	return (!((*this) < o) && ((*this) != o));
}

/*!
 * This is one of our comparison operators, which tests if our value is less
 * than or equal to that of the given other object. You can use the explicit
 * constructors that take other types to compare our object to other values.
 *
 * \param o The other object to compare ourself to.
 * \return True if our object is less than or equal to the other, or false.
 */
bool EDigitInteger::operator<=(const EDigitInteger &o) const
{
	return (((*this) < o) || ((*this) == o));
}

/*!
 * This is one of our comparison operators, which tests if our value is greater
 * than or equal to that of the given other object. You can use the explicit
 * constructors that take other types to compare our object to other values.
 *
 * \param o The other object to compare ourself to.
 * \return True if our object is greater than or equal to the other, or false.
 */
bool EDigitInteger::operator>=(const EDigitInteger &o) const
{
	return (((*this) > o) || ((*this) == o));
}

/*!
 * This is our unary minus / additive inverse operator. It returns a copy of our
 * object with the sign reversed.
 *
 * \return A copy of our object with the opposite sign.
 */
EDigitInteger EDigitInteger::operator-() const
{
	EDigitInteger r((*this));
	r.setPositive(!r.isPositive());
	return r;
}

/*!
 * This operator adds the value of the given other object to our value, and
 * makes it so our object contains the result.
 *
 * \param o The object to add to ourself.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator+=(const EDigitInteger &o)
{
	bool mySign = isPositive(), otherSign = o.isPositive();

	/*
	 * If our absolute value INCREASES (i.e., our currently positive number
	 * becomes MORE positive, or our currently negative number becomes MORE
	 * negative), we just need to do an unsigned add of the two numbers,
	 * keeping the sign the same.
	 *
	 * If, on the other hand, our absolute value DECREASES (i.e., our
	 * currently positive number becomes LESS positive, or our currently
	 * negative number becomes LESS negative), we need to do an unsigned
	 * subtract of the smaller of our two numbers from the larger one. If
	 * "this" is the SMALLER one, then we also need to flip the sign on
	 * the result (because we crossed 0 an went back the other way).
	 */

	if(mySign == otherSign)
	{
		/*
		 * If we are doing a negative ADD another negative, or a
		 * positive ADD another positive, then our absolute value is
		 * INCREASING. Therefore, as stated above, we just need to
		 * do an unsigned add, without touching the sign.
		 */
		unsignedAdd(o);
	}
	else
	{
		/*
		 * Otherwise, if we are doing a negative ADD a positive, or a
		 * positive ADD a negative, then our absolute value is
		 * DECREASING. Therefore, as stated above, we need to do an
		 * unsigned subtract of the SMALLER number from the LARGER
		 * number, and if "this" is the SMALLER number, we need to flip
		 * the sign of the result.
		 */
		if(unsignedEqualTo(o))
		{
			// If our numbers are the same, then our result is
			// simply 0.
			setZero();
			return *this;
		}

		// Otherwise, make sure we are the larger number, then subtract.
		if(unsignedLessThan(o))
		{
			EDigitInteger tmp(*this);
			*this = o;
			mySign = otherSign;
			unsignedSubtract(tmp);
			setPositive(mySign);
		}
		else
		{
			unsignedSubtract(o);
		}
	}

	removeLeadingZeros();
	// Make sure our number still has at least one digit.
	assert(digitCount() >= 1);

	// Make sure that, if our value is 0, we are positive.
	if((digitCount() == 1) && (get(0) == 0))
		setPositive(true);

	return *this;
}

/*!
 * This operator subtracts the value of the given other object from our value,
 * and makes it so our object contains the result.
 *
 * \param o The object to subtract from ourself.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator-=(const EDigitInteger &o)
{
	/*
	 * We implement subtraction using the following identity:
	 * a - b = -( (-a) + b )
	 */

	setPositive(!isPositive());
	*this += o;
	if((digitCount() > 1) || (get(0) != 0))
		setPositive(!isPositive());

	return (*this);
}

/*!
 * This operator multiplies our value by the value of the given other object,
 * and makes it so our object contains the result.
 *
 * \param o The object to multiply ourself by.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator*=(const EDigitInteger &o)
{
	// The result is positive if either both inputs are positive or both are
	// negative.
	bool sign = (isPositive() == o.isPositive());

	// Do our multiplication.
	unsignedMultiply(o);
	removeLeadingZeros();
	setPositive(sign);

#ifdef EULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(digitCount() >= 1);
#endif

	// Make sure that, if our value is 0, we are positive.
	try
	{
		if(digitCount() == 1)
			if(get(0) == 0)
				setPositive(true);
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	return (*this);
}

/*!
 * This operator divides our value by the value of the given other object, and
 * makes it so our object contains the result. Note that any remainder
 * encountered is simply discarded.
 *
 * \param o The object to divide ourself by.
 * \return A reference to this, to the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator/=(const EDigitInteger &o)
{
	// The result is positive if either both inputs are positive or both are
	// negative.
	bool sign = (isPositive() == o.isPositive());

	// Do our divide.
	unsignedDivide(o);
	removeLeadingZeros();
	setPositive(sign);

#ifdef EULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(digitCount() >= 1);
#endif

	// Make sure that, if our value is 0, we are positive.
	try
	{
		if(digitCount() == 1)
			if(get(0) == 0)
				setPositive(true);
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	return (*this);
}

/*!
 * This operator performs a modulo operation of our value by the given other
 * value, and makes it so our object contains the result. That is, the result
 * will be the remainder of our value divided by the given other value. Note
 * that, in accordance with the C99 standard, the result will have the same
 * sign as the dividend (i.e., our sign doesn't change).
 *
 * \param o The object to divide ourself by.
 * \return A reference to this, so the operator can be chained.
 */
EDigitInteger &EDigitInteger::operator%=(const EDigitInteger &o)
{
	bool sign = isPositive();
	unsignedDivide(o, true);
	removeLeadingZeros();
	setPositive(sign);

#ifdef EULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(digitCount() >= 1);
#endif

	// Make sure that, if our value is 0, we are positive.
	try
	{
		if(digitCount() == 1)
			if(get(0) == 0)
				setPositive(true);
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	return (*this);
}

/*!
 * This is our addition operator, which returns by value a new object that has
 * the sum of our value and the value of the given other object.
 *
 * \param o The other object to add to our value.
 * \return A new object containing the result.
 */
EDigitInteger EDigitInteger::operator+(const EDigitInteger &o) const
{
	EDigitInteger r((*this));
	r += o;
	return r;
}

/*!
 * This is our subtraction operator, which returns by value a new object that
 * has the difference of our value and the value of the given other object.
 *
 * \param o The other object to subtract from our value.
 * \return A new object containing the result.
 */
EDigitInteger EDigitInteger::operator-(const EDigitInteger &o) const
{
	EDigitInteger r((*this));
	r -= o;
	return r;
}

/*!
 * This is our multiplication operator, which returns by value a new object that
 * has the product of our value and the value of the given other object.
 *
 * \param o The other object to multiply our value by.
 * \return A new object containing the result.
 */
EDigitInteger EDigitInteger::operator*(const EDigitInteger &o) const
{
	EDigitInteger r((*this));
	r *= o;
	return r;
}

/*!
 * This is our division operator, which returns by value a new object that has
 * the quotient of our value and the value of the given other object. Note that
 * any remainder encountered is simply discarded.
 *
 * \param o The other object to divide our value by.
 * \return A new object containing the result.
 */
EDigitInteger EDigitInteger::operator/(const EDigitInteger &o) const
{
	EDigitInteger r((*this));
	r /= o;
	return r;
}

/*!
 * This is our modulus division operator, which returns by value a new object
 * that has the remainder of our value divided by the given other value. Note
 * that, in accordance with the C99 standard, the result will have the same
 * sign as the dividend (i.e., the sign of the left-hand operand).
 *
 * \param o The object to divide ourself by.
 * \return A new object containing the result.
 */
EDigitInteger EDigitInteger::operator%(const EDigitInteger &o) const
{
	EDigitInteger r((*this));
	r %= o;
	return r;
}

/*!
 * This is our prefix increment operator, which will increase our current
 * object's value by 1.
 *
 * \return A reference to this.
 */
EDigitInteger &EDigitInteger::operator++()
{
	return ((*this) += EDigitInteger(1));
}

/*!
 * This is our postfix increment operator, which will increase our current
 * object's value by 1.
 *
 * \param UNUSED_i Unused; used to differentiate post versus prefix.
 * \return A copy of this; change occurs after the expression is evaluated.
 */
EDigitInteger EDigitInteger::operator++(int EUNUSED(i))
{
	EDigitInteger r;
	r = (*this);
	((*this) += EDigitInteger(1));
	return r;
}

/*!
 * This is our prefix decrement operator, which will decrease our current
 * object's value by 1.
 *
 * \return A reference to this.
 */
EDigitInteger &EDigitInteger::operator--()
{
	return ((*this) -= EDigitInteger(1));
}

/*!
 * This is our postfix decrement operator, which will decrease our current
 * object's value by 1.
 *
 * \param UNUSED_i Unused; used to differentiate post versus prefix.
 * \return A copy of this; change occurs after the expression is evaluated.
 */
EDigitInteger EDigitInteger::operator--(int EUNUSED(i))
{
	EDigitInteger r;
	r = (*this);
	((*this) -= EDigitInteger(1));
	return r;
}

/*!
 * This functino just returns whether or not our number is currently positive or
 * not.
 *
 * \return True if our number is positive, or false otherwise.
 */
bool EDigitInteger::isPositive() const
{
	return positive;
}

/*!
 * This function sets whether or not our number is currently positive or not by
 * passing true or false, respectively.
 *
 * \param p Our new sign.
 */
void EDigitInteger::setPositive(bool p)
{
	positive = p;
}

/*!
 * \return The nubmer of digits in our number.
 */
std::size_t EDigitInteger::digitCount() const
{
	return digits.size();
}

/*!
 * Tests if this integer has an nth digit (i.e., if the number of digits in
 * this integer is strictly greater than i).
 *
 * \param i The 0-indexed digit position.
 * \return Whether or not this integer has an nth digit.
 */
bool EDigitInteger::hasNthDigit(std::size_t i) const
{
	return i < digitCount();
}

int EDigitInteger::get(std::size_t i) const
{
	return digits.at(i);
}

/*!
 * This function returns a sum of all of our digits, ignoring sign. This
 * function operates in O(n) time over our digits.
 *
 * \return The sum of our digits.
 */
int EDigitInteger::sumOfDigits() const
{
	int total = 0;

	try
	{
		for(std::size_t i = 0; i < digitCount(); ++i)
			total += get(i);
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	return total;
}

/*!
 * This function tests if our number is a palindrome (that is, it is equivalent
 * both forwards and backwards). This function ignores our sign. This function
 * operates in O(n) time over our digits.
 *
 * \return True if our number is a palindrome, or false otherwise.
 */
bool EDigitInteger::isPalindrome() const
{
	if(digitCount() <= 1)
		return true;

	try
	{
		for(std::size_t a = 0, b = (digitCount() - 1); a < b; ++a, --b)
		{
			if(get(a) != get(b))
				return false;
		}
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	return true;
}

/*!
 * This function tests if our number is pandigital or not. That is, for an
 * n-digit number, to be pandigital it must contain all of the digits from 1
 * to n. This function operates in O(n) time over our digits, and doesn't need
 * to sort or copy our number. Because numbers with more than 9 digits cannot
 * be definition be pandigital (in base 10), we only even have to check very
 * small numbers.
 *
 * \return True if our number is pandigital, or false otherwise.
 */
bool EDigitInteger::isPandigital() const
{
	int digitCounts[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	// 10-digit and larger numbers cannot be pandigital in base 10.
	if(digitCount() >= 10)
		return false;

	// Look at each of our digits.

	try
	{
		for(std::size_t i = 0; i < digitCount(); ++i)
			++digitCounts[get(i)];
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	// Ensure that the digits we SHOULD contain are exactly one, and the
	// digits we SHOULDN'T are still zero.

	if(digitCounts[0] != 0)
		return false;

	for(std::size_t i = 1; i <= digitCount(); ++i)
	{
		if(digitCounts[i] != 1)
			return false;
	}

	for(std::size_t i = digitCount() + 1; i < 10; ++i)
	{
		if(digitCounts[i] != 0)
			return false;
	}

	// Must be pandigital if we've gotten this far.

	return true;
}

/*!
 * This function tests if our number and the given other number are digitally
 * equivalent. That is, this function will test if our numbers contain exactly
 * the same digits (but not necessarily in the same order). Note that this
 * function will not even test numbers that contain different numbers of digits,
 * and otherwise will operate in O(n) time across the digits in each number.
 *
 * \param o The other object to compare ourself to.
 * \return True if our numbers are digitally equivalent, or false otherwise.
 */
bool EDigitInteger::isDigitallyEquivalent(const EDigitInteger &o) const
{
	int digitCounts[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	// If we have a different number of digits, return false immediately.
	if(digitCount() != o.digitCount())
		return false;

	try
	{
		// Add both of our numbers' digits to our cache.
		for(std::size_t i = 0; i < digitCount(); ++i)
		{
			digitCounts[get(i)]++;
			digitCounts[o.get(i)]--;
		}

		// Loop through the counter and if we find an inconsistency,
		// return false.
		for(std::size_t i = 0; i < 10; ++i)
			if(digitCounts[i] != 0)
				return false;
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	return true;
}

/*!
 * This function inserts the given digit (v) at the given position in our number
 * (k). If a digit is already present at that position, then it is replaced. If
 * the position is past the end of our number, then zeros are automatically
 * filled in between the end of our number and your new digit.
 *
 * \param i The position to insert the new digit at.
 * \param v The value of the digit to insert.
 * \return True if a new digit was inserted, or false if a digit was replaced.
 */
bool EDigitInteger::put(std::size_t i, int v)
{
	bool r;

	// Only accept digits that really are single-digit values, and are
	// positive (negative digits make no sense).
	if((v > 9) || (v < 0))
		throw EValueRangeException(
		        "The specified digit value was out of range!");

	// Set our digit.
	r = volatileSetDigitAt(i, v);
	removeLeadingZeros();
	return r;
}

/*!
 * This function reimplements the erase() function on our superclass. It behaves
 * the same way, except if you erase an "interior digit" (i.e., any digit except
 * the highest digit in our number), then it shifts everything else down so as
 * to maintain number continuity (a number with a hole in it doesn't make much
 * sense).
 *
 * \param i The position of the digit that is to be removed.
 * \return True if a digit was removed, or false otherwise.
 */
bool EDigitInteger::erase(std::size_t i)
{
	if(i >= digitCount())
		return false;

	if(digitCount() == 1)
		return false;

	// Shift any digits higher than the specified digit to the right by
	// one, overwriting the digit being removed.
	for(std::size_t idx = i; idx < (digitCount() - 1); ++idx)
		put(idx, get(idx + 1));

	// Remove the topmost digit, now that everything has been shifted.
	digits.erase(digitCount() - 1);

	return true;
}

/*!
 * This function shifts our digits the given number of places to the right,
 * discarding digits that are shifted off the end. A call of
 * rightDigitalShift(1) is equivalent to DIVIDING our number by 10 and
 * discarding the remainder.
 *
 * \param p The number of places to shift our number.
 */
void EDigitInteger::rightDigitalShift(int p)
{
	std::size_t d = digitCount();

	// A shift of 0 places has no effect.
	if(p == 0)
		return;

	// Treat negative right-shifts as positive left-shifts.
	if(p < 0)
	{
		leftDigitalShift(std::abs(p));
		return;
	}

	// If we're shifting all the way off the end of our number, just return
	// now.
	if(static_cast<std::size_t>(p) > d)
	{
		setZero();
		return;
	}

	try
	{
		// Shift everything.
		for(std::size_t i = 0; i < d; ++i)
		{
			if(static_cast<std::size_t>(p) <= i)
				put(i - static_cast<std::size_t>(p), get(i));
		}

		// Get rid of the remaining digits at the high end of our
		// number.
		std::size_t i = digitCount() - static_cast<std::size_t>(p);
		while(digits.erase(i++) > 0)
			;
	}
	catch(EValueRangeException &)
	{
		assert(false);
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

#ifdef EULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(digitCount() >= 1);
#endif
}

/*!
 * This function performs a right digit-wise rotation of our number by a given
 * number of places. Note that the return value's definition of "losing data"
 * is if our result has leading zeros. These are removed (since they do not
 * change the value of the number) and the appropriate value is returned.
 *
 * \param p The number of places to rotate.
 * \return True if our rotation was done without losing data, or false.
 */
bool EDigitInteger::rightDigitalRotate(int p)
{
	int *hold;
	bool r;

	// Treat negative right-rotations as positive left-rotations.
	if(p < 0)
		return leftDigitalRotate(std::abs(p));

	// Don't do any full rotations.
	p %= static_cast<int>(digitCount());

	// Rotation 0 places has no effect.
	if(p == 0)
		return true;

	// Allocate some buffer memory for our rotation.
	hold = new int[static_cast<std::size_t>(p)];

	try
	{
		// Add the p low digits to our buffer.
		for(std::size_t i = 0; i < static_cast<std::size_t>(p); ++i)
			hold[static_cast<std::size_t>(p) - i - 1] = get(i);

		// Shift right p places.
		rightDigitalShift(p);

		// Place the digits from our buffer back onto the top of our
		// number.
		std::size_t d = digitCount();
		for(std::size_t i = 0; i < static_cast<std::size_t>(p); ++i)
			put(d + (static_cast<std::size_t>(p) - i - 1), hold[i]);
	}
	catch(EValueRangeException &)
	{
		assert(false);
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	// Clean up our buffer.
	delete[] hold;

	r = removeLeadingZeros();

#ifdef EULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(digitCount() >= 1);
#endif

	return r;
}

/*!
 * This function shifts our digits the given number of places to the left,
 * filling in the new empty spaces at the right with 0's. A call of
 * rightDigitalShift(1) is equivalent to MULTIPLYING our number by 10.
 *
 * \param p The number of places to shift our number.
 */
void EDigitInteger::leftDigitalShift(int p)
{
	// A shift of 0 places has no effect.
	if(p == 0)
		return;

	// Treat negative left-shifts as positive right-shifts.
	if(p < 0)
	{
		rightDigitalShift(std::abs(p));
		return;
	}

	try
	{
		std::size_t places = static_cast<std::size_t>(p);
		std::size_t oldDigitCount = digitCount();
		assert(oldDigitCount >= 1);

		// Shift all of the digits.
		for(std::size_t i = oldDigitCount - 1 + places; i >= places;
		    --i)
		{
			put(i, get(i - places));
		}

		// Fill in the new, empty space at the front with 0's.
		for(std::size_t i = 0; i < places; ++i)
			put(i, 0);
	}
	catch(EValueRangeException &)
	{
		assert(false);
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	// Make sure our number still has at least 1 digit.
	assert(digitCount() >= 1);
}

/*!
 * This function performs a left digit-wise rotation of our number by a given
 * number of places. Note that the return value's definition of "losing data"
 * is if our result has leading zeros. These are removed (since they do not
 * change the value of the number) and the appropriate value is returned.
 *
 * \param p The number of places to rotate.
 * \return True if our rotation was done without losing data, or false.
 */
bool EDigitInteger::leftDigitalRotate(int p)
{
	bool r;

	// Treat negative left-rotations as positive right-rotations.
	if(p < 0)
		return rightDigitalRotate(std::abs(p));

	// Don't do any full rotations.
	p %= static_cast<int>(digitCount());
	assert(p < static_cast<int>(digitCount()));

	// Rotation 0 places has no effect.
	if(p == 0)
		return true;

	try
	{
		std::size_t oldDigitCount = digitCount();
		std::size_t places = static_cast<std::size_t>(p);
		std::vector<int> hold(places, 0);

		// Add the 'places' high digits to our buffer.
		for(std::size_t offFromEnd = 0; offFromEnd < places;
		    ++offFromEnd)
		{
			std::size_t idx = digitCount() - 1 - offFromEnd;
			std::size_t holdIdx = places - 1 - offFromEnd;
			hold[holdIdx] = get(idx);
		}

		// Shift left by the specified number of places.
		leftDigitalShift(p);

		// Place the digits in the buffer at the bottom of the number.
		for(std::size_t i = 0; i < places; ++i)
			put(i, hold[i]);

		// Remove any extra high digits from the shift.
		while(digitCount() > oldDigitCount)
			erase(digitCount() - 1);
	}
	catch(EValueRangeException &)
	{
		assert(false);
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	r = removeLeadingZeros();

	// Make sure our number still has at least 1 digit.
	assert(digitCount() >= 1);

	return r;
}

namespace
{
template <typename Comparator>
std::vector<int>
getSortedDigits(std::unordered_map<std::size_t, int> const &digits,
                Comparator comp)
{
	using value_type = std::decay<decltype(digits)>::type::value_type;

	std::vector<int> sortedDigits;
	std::transform(digits.begin(), digits.end(),
	               std::back_inserter(sortedDigits),
	               [](value_type const &v) -> int { return v.second; });
	std::sort(sortedDigits.begin(), sortedDigits.end(), comp);
	return sortedDigits;
}
}

/*!
 * This function sorts the digits of our integer in ascending order. It should
 * be noted that this function will NEVER have to remove leading zeros, since
 * they will be at the low digits of our number.
 */
void EDigitInteger::sortDigitsAscending()
{
	auto sortedDigits = getSortedDigits(digits, std::less<int>());
	for(std::size_t i = 0; i < sortedDigits.size(); ++i)
		put(i, sortedDigits[i]);
}

/*!
 * This function sorts the digits of our integer in descending order. This
 * function will also remove any resulting leading zeros.
 *
 * \return True if no leading zeros were removed, or false otherwise.
 */
bool EDigitInteger::sortDigitsDescending()
{
	auto sortedDigits = getSortedDigits(digits, std::greater<int>());
	for(std::size_t i = 0; i < sortedDigits.size(); ++i)
		put(i, sortedDigits[i]);
	return removeLeadingZeros();
}

/*!
 * This function reverses the order of the digits in our number. Note that the
 * return value's definition of "losing data" is if our result has leading
 * zeros. These are removed (since they do not change the value of our number)
 * and the appropriate value is returned.
 *
 * \param l The left-most digit index to include in the reversal.
 * \param r The right-most digit index to include in the reversal.
 * \return True if the reversal lost no data, or false otherwise.
 */
bool EDigitInteger::reverseDigits(std::size_t l, std::size_t r)
{
	bool ret;

	if(digitCount() <= 1)
		return true;

	r = (r <= l) ? (digitCount() - 1) : r;
	r = (r >= digitCount()) ? (digitCount() - 1) : r;

	try
	{
		for(std::size_t a = l, b = r; a < b; ++a, --b)
		{
			int hold = get(a);
			volatileSetDigitAt(a, get(b));
			volatileSetDigitAt(b, hold);
		}
	}
	catch(EValueRangeException &)
	{
		assert(false);
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	ret = removeLeadingZeros();

#ifdef EULER_DEBUG
	// Make sure our number still has at least 1 digit.
	EASSERT(digitCount() >= 1);
#endif

	return ret;
}

/*!
 * This function returns a certain range in our number as a 64-bit unsigned
 * integer. Note that if the range specified contains leading zeros they will
 * simply be discarded.
 *
 * \param l The left-most bound (inclusive).
 * \param r The right-most bound (inclusive).
 * \return The specified range as a 64-bit unsigned integer.
 */
uint64_t EDigitInteger::rangeToInteger(std::size_t l, std::size_t r) const
{
	if(digitCount() < 1)
		return 0;
	if(r < l)
		std::swap(l, r);
	if(r >= digitCount())
		throw EOutOfBoundsException("Range is out-of-bounds.");

	uint64_t ret = 0;
	for(std::size_t offFromEnd = 0; offFromEnd <= (r - l); ++offFromEnd)
	{
		std::size_t idx = r - offFromEnd;
		ret *= 10;
		ret += static_cast<uint64_t>(get(idx));
	}
	return ret;
}

/*!
 * This is a convenience function, which is equivalent to running
 * rangeToInteger() on our entire number.
 *
 * \return Our entire number, represented as a 64-bit unsigned integer.
 */
uint64_t EDigitInteger::toInteger() const
{
	return rangeToInteger(0, digitCount() - 1);
}

/*!
 * This function returns a certain range in our number as a GMP big integer.
 * Note that if the range specified contains leading zeros they will simply be
 * discarded.
 *
 * \param l The left-most bound (inclusive).
 * \param r The right-most bound (inclusive).
 * \return The specified range as a GMP big integer.
 */
mpz_class EDigitInteger::rangeToBigInteger(std::size_t l, std::size_t r) const
{
	mpz_class ret = 0;

	if(r < l)
		std::swap(l, r);
	if(r >= digitCount())
		throw EOutOfBoundsException("Range is out-of-bounds.");

	for(std::size_t offFromEnd = 0; offFromEnd <= (r - l); ++offFromEnd)
	{
		std::size_t idx = r - offFromEnd;
		ret *= 10;
		ret += get(idx);
	}

	return ret;
}

/*!
 * This is a convenience function, which is equivalent to running
 * rangeToBigInteger() on our entire number.
 *
 * \return Our entire number, represented as a GMP big integer object.
 */
mpz_class EDigitInteger::toBigInteger() const
{
	return rangeToBigInteger(0, digitCount() - 1);
}

/*!
 * This function returns a certain range in our number as a string. Note that if
 * the range specified contains leading zeros they will simply be discarded.
 * Note that since this function is returning just a portion of our string, it
 * doesn't bother prepending a sign character. If you want that, you should call
 * toString() which will, or do it yourself.
 *
 * \param l The left-most bound (inclusive).
 * \param r The right-most bound (inclusive).
 * \return The specified range as a std::string.
 */
std::string EDigitInteger::rangeToString(std::size_t l, std::size_t r) const
{
	std::ostringstream oss;

	if(r < l)
		std::swap(l, r);
	if(r >= digitCount())
		throw EOutOfBoundsException("Range is out-of-bounds.");

	for(std::size_t offFromEnd = 0; offFromEnd <= (r - l); ++offFromEnd)
		oss << get(r - offFromEnd);

	return oss.str();
}

/*!
 * This is a convenience function, which is equivalent to running
 * rangeToString() on our entire number. Note that this function DOES take the
 * sign into account - if our number is negative, then a '-' is prepended to
 * the output number.
 *
 * \return Our entire number, represented as a string.
 */
std::string EDigitInteger::toString() const
{
	std::string r = rangeToString(0, digitCount() - 1);

	if(!isPositive())
		r.insert(0, "-");

	return r;
}

/*!
 * This function behaves the same as our public put() function, except it does
 * not do range checking on the value provided, so it can be used to, e.g.,
 * store intermediate values while performing an addition or subtraction
 * operation.
 *
 * \param i The position of the digit to set.
 * \param v The value of the new digit.
 * \return True if a new digit was inserted, or false if a digit was updated.
 */
bool EDigitInteger::volatileSetDigitAt(std::size_t i, int v)
{
	// Fill in digits between the previous end of our number and the
	// specified digit with 0's.
	for(std::size_t idx = digitCount(); idx < i; ++idx)
		digits.insert(std::make_pair(idx, 0));

	// Actually insert the new value.
	auto result = digits.insert(std::make_pair(i, v));
	if(!result.second)
		result.first->second = v;
	assert(get(i) == v);
	return result.second;
}

/*!
 * This is a convenience function that removes the leading zeros from our
 * number. It returns true if leading zeros were removed, or false otherwise.
 *
 * \return True if leading zeros were removed, or false otherwise.
 */
bool EDigitInteger::removeLeadingZeros()
{
	bool zerosRemoved = false;
	while((digitCount() > 1) && (get(digitCount() - 1) == 0))
	{
		zerosRemoved = true;
		erase(digitCount() - 1);
	}
	return zerosRemoved;
}

/*!
 * This utility function carries all of our digits, starting from the low
 * digits, so it will be "normalized" (that is, 0 <= digit <= 9 is always
 * true), i.e. after an addition operation.
 */
void EDigitInteger::carry()
{
	for(std::size_t j = 0; hasNthDigit(j); ++j)
	{
		while(get(j) > 9)
		{
			volatileSetDigitAt(j, get(j) - 10);
			if(hasNthDigit(j + 1))
				volatileSetDigitAt(j + 1, get(j + 1) + 1);
			else
				volatileSetDigitAt(j + 1, 1);
		}
	}

	for(std::size_t j = 0; j < digitCount(); ++j)
		assert((0 <= get(j)) && (get(j) <= 9));
}

/*!
 * This utility function borrows all of our digits, starting from the low
 * digits, so it will be "normalized" (that is, 0 <= digit <= 9 is always
 * true), i.e. after a subtraction operation.
 */
void EDigitInteger::borrow()
{
	for(std::size_t j = 0; (j + 1) < digitCount(); ++j)
	{
		while(get(j) < 0)
		{
			volatileSetDigitAt(j, get(j) + 10);
			volatileSetDigitAt(j + 1, get(j + 1) - 1);
		}
	}

	// We could possibly have reduced the number of digits in our number,
	// leaving leading zeros...
	removeLeadingZeros();

	// If our leading digit is still negative, an error has occurred.
	if(get(digitCount() - 1) < 0)
		throw EUnderflowException("No more digits to borrow from!");

#ifdef EULER_DEBUG
	for(std::size_t j = 0; j < digitCount(); ++j)
		assert((0 <= get(j)) && (get(j) <= 9));
#endif
}

/*!
 * This function sets our object's value to [positive] zero, clearing all of its
 * existing digits
 * and other properties.
 */
void EDigitInteger::setZero()
{
	digits.clear();
	volatileSetDigitAt(0, 0);
	setPositive(true);
}

/*!
 * This function tests if our value is equal to that of the given other object,
 * ignoring the signs on both.
 *
 * \param o The object to compare ourself to.
 * \return True if we are equal ignoring sign, or false otherwise.
 */
bool EDigitInteger::unsignedEqualTo(const EDigitInteger &o) const
{
	// If our numbers contain varying numbers of digits, return immediately.
	if(digitCount() != o.digitCount())
		return false;

	try
	{
		// Test each digit until we find something that doesn't match.
		for(std::size_t i = 0; i < digitCount(); ++i)
			if(get(i) != o.get(i))
				return false;
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	return true;
}

/*!
 * This function tests if our value is not equal to that of the given other
 * object, ignoring the signs on both.
 *
 * \param o The object to compare ourself to.
 * \return True if we are not equal ignoring sign, or false otherwise.
 */
bool EDigitInteger::unsignedNotEqualTo(const EDigitInteger &o) const
{
	return (!unsignedEqualTo(o));
}

/*!
 * This function tests if our value is less than the value of the given other
 * object, ignoring signs.
 *
 * \param o The object to compare ourself to.
 * \return True if we are less than the other object, or false otherwise.
 */
bool EDigitInteger::unsignedLessThan(const EDigitInteger &o) const
{
	// See if we can determine a return value based purely on the number of
	// digits.
	if(digitCount() > o.digitCount())
		return false; // We have more digits, so we are greater.
	else if(digitCount() < o.digitCount())
		return true; // We have fewer digits, so we are less.

	try
	{
		// Test each of our digits to try and find an answer.
		for(std::size_t offFromEnd = 0; offFromEnd < digitCount();
		    ++offFromEnd)
		{
			std::size_t idx = (digitCount() - 1) - offFromEnd;
			if(get(idx) > o.get(idx))
				return false; // Our digit is greater, so our
			                      // number is greater.
			else if(get(idx) < o.get(idx))
				return true; // Our digit is less, so our number
			                     // is less.
		}
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}

	// We must be equal.
	return false;
}

/*!
 * This function tests if our value is greater than the value of the given other
 * object, ignoring signs.
 *
 * \param o The object to compare ourself to.
 * \return True if we are greater than the other object, or false otherwise.
 */
bool EDigitInteger::unsignedGreaterThan(const EDigitInteger &o) const
{
	return (!unsignedLessThan(o) && !unsignedEqualTo(o));
}

/*!
 * This function tests if our value is less than or equal to that of the given
 * other object, ignoring signs.
 *
 * \param o The object to compare ourself to.
 * \return True if we are less than or equal to the other object, or false.
 */
bool EDigitInteger::unsignedLessThanEqualTo(const EDigitInteger &o) const
{
	return (unsignedLessThan(o) || unsignedEqualTo(o));
}

/*!
 * This function tests if our value is greater than or equal to that of the
 * given other object, ignoring signs.
 *
 * \param o The object to compare ourself to.
 * \return True if we are greater than or equal to the other object, or false.
 */
bool EDigitInteger::unsignedGreaterThanEqualTo(const EDigitInteger &o) const
{
	return (!unsignedLessThan(o));
}

/*!
 * This function does an unsigned add of the given other number to our current
 * number. It doesn't factor in which is positive and which is negative; it
 * just adds magnitudes. It is up to the caller to handle signs correctly.
 * This function operates in O(n) time across our digits.
 *
 * \param i The other value to add to our value.
 */
void EDigitInteger::unsignedAdd(const EDigitInteger &i)
{
	try
	{
		// Insert zeros at the front of our number until we are at least
		// as big as the other.
		if(i.digitCount() > digitCount())
			volatileSetDigitAt(i.digitCount(), 0);

		// Do a digit-by-digit add, carrying as we go...
		for(std::size_t j = 0; j < i.digitCount(); ++j)
			volatileSetDigitAt(j, get(j) + i.get(j));

		carry();
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}
}

/*!
 * This function does an unsigned subtract of the given other number from our
 * current number. It doesn't factor in which is positive and which is
 * negative; it just subtracts one magnitude from the other. It is up to the
 * caller to handle signs correctly, and to MAKE SURE WE ARE >= THE OTHER
 * VALUE. This function operates in O(n) time across our digits.
 *
 * \param i The other value to subtract from our value.
 */
void EDigitInteger::unsignedSubtract(const EDigitInteger &i)
{
	assert(unsignedGreaterThanEqualTo(i));

	// If we are equal, just return now.
	if(*this == i)
	{
		setZero();
		return;
	}

	try
	{
		// Subtract per-digit, maybe leaving some digits negative.
		for(std::size_t idx = 0; idx < i.digitCount(); ++idx)
			volatileSetDigitAt(idx, get(idx) - i.get(idx));

		borrow();
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}
	catch(EUnderflowException &)
	{
		assert(false);
	}
}

/*!
 * This function does an unsigned multiply of our value by the given other
 * number. It doesn't factor in which is positive and which is negative; it
 * just multiplies the magnitudes. It is up to the caller to handle/set signs
 * correctly.
 *
 * \param i The other value to multiply our value by.
 */
void EDigitInteger::unsignedMultiply(const EDigitInteger &i)
{
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
		for(std::size_t b = 0; b < i.digitCount(); ++b)
		{ // "b" represents the digit in the number we're multiplying
			// by.
			for(std::size_t a = 0; a < digitCount(); ++a)
			{ // "a" represents the digit in our current number.
				if((b + a) >= result.digitCount())
					result.volatileSetDigitAt(b + a, 0);

				// Multiply our current digits and add the
				// result to our results array.
				result.volatileSetDigitAt(
				        b + a, result.get(b + a) +
				                       (get(a) * i.get(b)));
			}
		}

		// Set our value to the result.
		result.carry();
		(*this) = result;
	}
	catch(EValueRangeException &)
	{
		assert(false);
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}
}

/*!
 * This function performs an unsigned divide of our value by the given other
 * value, optionally returning either the result of the division or the
 * remainder (i.e., modulus division). It doesn't factor in who is positive
 * and who is negative, so it is up to the caller to make sure that signs are
 * set/handled correctly.
 *
 * \param i The other value to divide ourself by.
 * \param m Whether or not to do modulus division.
 */
void EDigitInteger::unsignedDivide(const EDigitInteger &i, bool m)
{
	EDigitInteger a, b, result;
	bool sign = isPositive();

	if(i == EDigitInteger(0))
		throw EDivideByZeroException("Divide by zero!");

	try
	{
		// Try to eliminate some easy possibilities before we attempt an
		// actual divide.

		if(unsignedEqualTo(EDigitInteger(0)))
		{
			setZero();
			return;
		}

		if(unsignedLessThan(i))
		{
			if(!m)
				setZero();
			return;
		}

		if(unsignedEqualTo(i))
		{
			if(m)
				setZero();
			else
				*this = 1;
			return;
		}

		if(i.unsignedEqualTo(EDigitInteger(1)))
		{
			if(m)
				setZero();
			return;
		}

		/*
		 * An easy way to implement division is just to subtract the
		 * divisor from the dividend over and over again until the
		 * dividend is less than the divisor, and return the number
		 * of subtractions performed.
		 *
		 * This is very inefficient, however, for example in the case of
		 * a very large number divided by one - that would require O(n)
		 * subtractions, where n is the dividend, and would go very
		 * slowly.
		 *
		 * Instead, we're going to right-shift (i.e., multiply by 10)
		 * our divisor until it is close to the dividend, and then
		 * multiply the divisor by a number such that the leading
		 * digits will be as close as possible, to eliminate a lot of
		 * the subtraction operations that will be performed.
		 */

		// Initialize a and b.

		a = *this;
		a.setPositive(true);

		b = i;
		b.setPositive(true);

		std::size_t aDigits = a.digitCount();
		std::size_t bDigits = b.digitCount();

		// Initialize this - which will ultimately be our result.
		setZero();

		// This is our main loop for division, that goes a lot faster
		// than just a naieve subtraction.
		result = 1;
		while(bDigits < aDigits)
		{
			// If b has only 1 fewer digits but a larger or equal
			// leading digit, break out of the loop.
			if((bDigits == (aDigits - 1)) &&
			   (b.get(bDigits - 1) >= a.get(aDigits - 1)))
			{
				break;
			}

#ifdef EULER_DEBUG
			assert(aDigits > 0);
			assert(bDigits > 0);

			// Make sure we aren't left-shifting by a negative value
			// (i.e., right shifting).
			assert(aDigits >= bDigits);
#endif

			// Shift our number (multiply by power of 10) so it has
			// a smaller number of digits.
			if(a.get(aDigits - 1) >= b.get(bDigits - 1))
			{
				b.leftDigitalShift(
				        static_cast<int>(aDigits - bDigits));
				result.leftDigitalShift(
				        static_cast<int>(aDigits - bDigits));
			}
			else
			{
				b.leftDigitalShift(
				        static_cast<int>(aDigits - bDigits) -
				        1);
				result.leftDigitalShift(
				        static_cast<int>(aDigits - bDigits) -
				        1);
			}

			// Try multiplying by the largest possible number to
			// optimize even more.
			for(int j = 9; j > 0; --j)
			{
				uint64_t value = static_cast<uint64_t>(j);
				if((b * EDigitInteger(value)) <= a)
				{
					b *= EDigitInteger(value);
					result *= EDigitInteger(value);
					break;
				}
			}

			// Subtract this multiple and add it to our result.
			a -= b;
			(*this) += result;

			// Reset our variables for the next iteration of this
			// loop.
			b = i;
			b.setPositive(true);
			bDigits = b.digitCount();
			aDigits = a.digitCount();
			result = 1;
		}

		// We've optimized just about as much as we can; finish up just
		// doing a naieve subtraction.
		b = i;
		b.setPositive(true);
		while(a >= b)
		{
			a -= b;
			++(*this);
		}

		// If this was supposed to be a modulus operation, set our value
		// to the remainder.
		if(m)
			(*this) = a;

		// Since this is an unsigned divide, set our sign back to its
		// original value.
		setPositive(sign);
	}
	catch(EOutOfBoundsException &)
	{
		assert(false);
	}
}

/*!
 * This is our output stream operator, which allows our objects to be easily
 * printed to a standard C++ ostream object. The value printed is effectively
 * the same as that returned by our class's toString() member function.
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

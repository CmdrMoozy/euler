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

#include "EFraction.h"

#include <iostream>

#include "libeuler/EDefines.h"
#include "libeuler/math/EMath.h"

#ifdef LIBEULER_DEBUG
/*!
 * This function implements our test suite for this class. It uses non-abort()'ing
 * assertions, and merely prints the result to stdout.
 */
void EFraction::doTestSuite()
{
	bool success;

	std::cout << "\tTesting 'EFraction'...\t\t\t";
	try
	{
		success = true;

		// Test reducing on a bunch of generated fractions.
		EFraction f;
		uint64_t n, d, m;
		double v;

		for(m = 3; m <= 5; ++m)
		{
			for(n = 0; n <= 10; ++n)
			{
				for(d = 1; d <= 10; ++d)
				{
					f.setNumerator(n * m);
					f.setDenominator(d * m);

					EASSERT(f.getNumerator() == (n * m))
					EASSERT(f.getDenominator() == (d * m))

					v = f.toDouble();
					f.reduce();
					EASSERT(f.toDouble() == v)
				}
			}
		}
	}
	catch(EAssertionException &e)
	{
		ELUNUSED(e)
		success = false;
	}
	catch(EValueRangeException &e)
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
 * This function tests if the given numerator and denominator are a reduced proper fraction. That is, we
 * test if a fraction n/d could be reduced or not.
 *
 * \param n The numerator.
 * \param d The denominator.
 * \return True if n/d CANNOT be reduced, or false otherwise.
 */
bool EFraction::isReducedProperFraction(uint64_t n, uint64_t d)
{
	return EMath::areCoprime(n, d);
}

/*!
 * This constructor initializes a new fraction with the given numerator and denominator values.
 *
 * \param n The numerator.
 * \param d The denominator.
 * \exception QValueRangeException This exception is thrown if you try to divide by zero.
 */
EFraction::EFraction(uint64_t n, uint64_t d)
	throw(EValueRangeException &)
{
	setNumerator(n);
	setDenominator(d);
}

/*!
 * This is our copy constructor, which sets our value equal to that of the given other object.
 *
 * \param o The object to make ourself equal to.
 */
EFraction::EFraction(const EFraction &o)
{
	(*this) = o;
}

/*!
 * This is our default destructor, which cleans up & destroys our object.
 */
EFraction::~EFraction()
{
}

/*!
 * This is our assignment operator, which sets our value equal to that of the given other object.
 *
 * \param o The object to make ourself equal to.
 * \return A reference to this, so this operator can be chained.
 */
EFraction &EFraction::operator=(const EFraction &o)
{
	try
	{
		setNumerator(o.getNumerator());
		setDenominator(o.getDenominator());
	}
	catch(EValueRangeException &e)
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
 * This operator tests if our value is equal to the value of the given other object.
 * Note that these operators use only double precision; if you need more precision, you should use
 * toBigDouble() to compare instead.
 *
 * \param o The other object to compare ourself to.
 * \return True if we are equal to the other object, or false otherwise.
 */
bool EFraction::operator==(const EFraction &o) const
{
	return (toDouble() == o.toDouble());
}

/*!
 * This operator tests if our value is greater than the value of the given other object.
 * Note that these operators use only double precision; if you need more precision, you should use
 * toBigDouble() to compare instead.
 *
 * \param o The other object to compare ourself to.
 * \return True if we are greater than the other object, or false otherwise.
 */
bool EFraction::operator>(const EFraction &o) const
{
	return (toDouble() > o.toDouble());
}

/*!
 * This operator tests if our value is less than the value of the given other object.
 * Note that these operators use only double precision; if you need more precision, you should use
 * toBigDouble() to compare instead.
 *
 * \param o The other object to compare ourself to.
 * \return True if we are less than the other object, or false otherwise.
 */
bool EFraction::operator<(const EFraction &o) const
{
	return (toDouble() < o.toDouble());
}

/*!
 * This operator tests if our value is greater than or equal to the value of the given other object.
 * Note that these operators use only double precision; if you need more precision, you should use
 * toBigDouble() to compare instead.
 *
 * \param o The other object to compare ourself to.
 * \return True if we are greater than or equal to the other object, or false otherwise.
 */
bool EFraction::operator>=(const EFraction &o) const
{
	return (toDouble() >= o.toDouble());
}

/*!
 * This operator tests if our value is less than or equal to the value of the given other object.
 * Note that these operators use only double precision; if you need more precision, you should use
 * toBigDouble() to compare instead.
 *
 * \param o The other object to compare ourself to.
 * \return True if we are less than or equal to the other object, or false otherwise.
 */
bool EFraction::operator<=(const EFraction &o) const
{
	return (toDouble() <= o.toDouble());
}

/*!
 * This function adds the given other value to our value, getting a common multiple for both denominators.
 * Note that reduction of the resulting fraction is not done automatically; it is up to the user to perform
 * that action if they want to.
 *
 * \param o The value to add to our value.
 * \return A reference to this, so this operator can be chained.
 */
EFraction &EFraction::operator+=(const EFraction &o)
{
	try
	{
		uint64_t nA = getNumerator(), dA = getDenominator();
		uint64_t nB = o.getNumerator(), dB = o.getDenominator();

		setDenominator(dA * dB);
		setNumerator( (nA * dB) + (nB * dA) );
	}
	catch(EValueRangeException &e)
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
 * This function subtracts the given other value from our value, getting a common multiple for both
 * denominators. Note that reduction of the resulting fraction is not done automatically; it is up to
 * the user to perform that action if they want to. Also note that if the result of this operation would
 * be negative, our value is simply set to zero (since our types are unsigned).
 *
 * \param o The value to subtract from our value.
 * \return A reference to this, so this operator can be chained.
 */
EFraction &EFraction::operator-=(const EFraction &o)
{
	try
	{
		// If our result would be negative, just set our value to zero.
		if( o > (*this) )
		{
			setNumerator(0);
			setDenominator(1);

			return (*this);
		}

		uint64_t nA = getNumerator(), dA = getDenominator();
		uint64_t nB = o.getNumerator(), dB = o.getDenominator();

		setDenominator(dA * dB);
		setNumerator( (nA * dB) - (nB * dA) );
	}
	catch(EValueRangeException &e)
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
 * This function returns our fraction's numerator value.
 *
 * \return Our numerator.
 */
uint64_t EFraction::getNumerator() const
{
	return numerator;
}

/*!
 * This function sets a new numerator for our fraction.
 *
 * \param n The new numerator value.
 */
void EFraction::setNumerator(uint64_t n)
{
	numerator = n;
}

/*!
 * This function returns our fraction's denominator value.
 *
 * \return Our denominator.
 */
uint64_t EFraction::getDenominator() const
{
	return denominator;
}

/*!
 * This function sets a new denominator for our fraction.
 *
 * \param d The new denominator value.
 * \exception EValueRangeException This exception is thrown if you try to divide by zero.
 */
void EFraction::setDenominator(uint64_t d)
	throw(EValueRangeException &)
{
	if(d == 0) throw EValueRangeException("Denominator value of 0 is not allowed!");
	denominator = d;
}

/*!
 * This function will set our value to the mediant of our current value and the given other value.
 * More information: http://en.wikipedia.org/wiki/Mediant_(mathematics)
 *
 * Note that the result may not be reduced; it is up to the caller to reduce the resulting fraction
 * if that is indeed what is desired.
 *
 * \param o The other value used in the computation.
 */
void EFraction::mediant(const EFraction &o)
{
	uint64_t a, b, c, d;

	if( (*this) == o ) return;

	if( (*this) < o )
	{
		a = getNumerator();
		c = getDenominator();
		b = o.getNumerator();
		d = o.getDenominator();
	}
	else
	{
		a = o.getNumerator();
		c = o.getDenominator();
		b = getNumerator();
		d = o.getDenominator();
	}

	setNumerator(a+b);
	setDenominator(c+d);
}

/*!
 * This function tests whether or not our fraction could be reduced or not. Note that this is
 * computationally almost equivalent to reduce(), so you might consider just using that function
 * instead.
 *
 * \return True if our fraction could be reduced, or false otherwise.
 */
bool EFraction::canReduce() const
{
	return !EFraction::isReducedProperFraction(getNumerator(), getDenominator());
}

/*!
 * This function completely reduces our numerator and denominator.
 *
 * \return True if the fraction was reduced, or false if it was already in lowest terms.
 */
bool EFraction::reduce()
{
	uint64_t gcd = EMath::greatestCommonDivisor(getNumerator(), getDenominator());

	switch(gcd)
	{
		case 0:
		case 1:
			return false;
			break;

		default:
			setNumerator(getNumerator() / gcd);
			setDenominator(getDenominator() / gcd);
			return true;
			break;
	}
}

/*!
 * This function returns the decimal value of our fraction as a primitive double.
 *
 * \return Our numerator divided by our denominator.
 */
double EFraction::getDecimalValue() const
{
	return toDouble();
}

/*!
 * This function returns the decimal value of our fraction as a primitive double.
 *
 * \return Our numerator divided by our denominator.
 */
double EFraction::toDouble() const
{
	return ( static_cast<double>(getNumerator()) / static_cast<double>(getDenominator()) );
}

/*!
 * This function is similar to toDouble(), but it returns our value as a high-precision GMP floating
 * point value.
 *
 * \return Our numerator divided by our denominator.
 */
mpf_class EFraction::toBigDouble(uint32_t p) const
{
#if (defined _WIN32 || defined __APPLE__)
	mpf_class r = EMath::int64ToBigFloat(getNumerator(), p);
	r /= EMath::int64ToBigFloat(getDenominator(), p);
#else
	mpf_class r(getNumerator(), p);
	r /= getDenominator();

	return r;
#endif
}

/*!
 * This is our output stream operator, which allows our objects to be easily printed to
 * a standard C++ ostream object. The value printed will be in the format "n/d."
 *
 * \param out The output stream to which we will write.
 * \param i The QFraction object we will be writing.
 * \return A reference to the output stream, so the operator can be chained.
 */
std::ostream &operator<<(std::ostream &out, const EFraction &f)
{
	out << f.getNumerator() << "/" << f.getDenominator();
	return out;
}

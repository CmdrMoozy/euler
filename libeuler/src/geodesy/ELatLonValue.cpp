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

#include "ELatLonValue.h"

#include <iomanip>
#include <iostream>

/*!
 * This constructor creates a new, zero latitude/longitude value.
 */
ELatLonValue::ELatLonValue()
	: precision(ELatLonValue::DEFAULT_PRECISION), direction(ELatLonValue::None)
{
	mpfr_init2(degrees, getPrecision());
	mpfr_init2(minutes, getPrecision());
	mpfr_init2(seconds, getPrecision());
	
	mpfr_set_ui(degrees, 0, MPFR_RNDZ);
	mpfr_set_ui(minutes, 0, MPFR_RNDZ);
	mpfr_set_ui(minutes, 0, MPFR_RNDZ);
}

/*!
 * This is our copy constructor, which creates a new latitude/longitude value equal to
 * that of the given other one.
 *
 * \param o The value to make ourself equal to.
 */
ELatLonValue::ELatLonValue(const ELatLonValue &o)
	: precision(ELatLonValue::DEFAULT_PRECISION)
{
	mpfr_init2(degrees, getPrecision());
	mpfr_init2(minutes, getPrecision());
	mpfr_init2(seconds, getPrecision());
	
	(*this) = o;
}

/*!
 * This is one of our single-value constructors. It takes a single angle measurement, in either degrees
 * or radians, as well as a direction, to set our value.
 *
 * \param v The single-value angle measurement.
 * \param t Whether the given measurement is degrees or radians.
 * \param d The direction of the angle - NSEW or "None".
 */
ELatLonValue::ELatLonValue(mpfr_t v, ELatLonValue::ValueType t, ELatLonValue::ValueDirection d)
	: precision(ELatLonValue::DEFAULT_PRECISION), direction(d)
{
	mpfr_init2(degrees, getPrecision());
	mpfr_init2(minutes, getPrecision());
	mpfr_init2(seconds, getPrecision());
	
	fromValue(v, t);
}

/*!
 * This is one of our single-value constructors. It takes a single angle measurement, in either degrees
 * or radians, as well as a direction, to set our value.
 *
 * \param v The single-value angle measurement.
 * \param t Whether the given measurement is degrees or radians.
 * \param d The direction of the angle - NSEW or "None".
 */
ELatLonValue::ELatLonValue(long double v, ELatLonValue::ValueType t, ELatLonValue::ValueDirection d)
	: precision(ELatLonValue::DEFAULT_PRECISION), direction(d)
{
	mpfr_init2(degrees, getPrecision());
	mpfr_init2(minutes, getPrecision());
	mpfr_init2(seconds, getPrecision());
	
	mpfr_t value;
	mpfr_init2(value, getPrecision());
	mpfr_set_ld(value, v, MPFR_RNDN);
	
	fromValue(value, t);
	
	mpfr_clear(value);
	
	normalize();
}

/*!
 * This constructor creates a new latitude/longitude value form the given value in
 * degrees/minutes/seconds, and the given direction.
 *
 * \param d The degrees portion of the measurement.
 * \param m The minutes portion of the measurement.
 * \param s The seconds portion of the measurement.
 * \param di The direction of the angle - NSEW or "None".
 */
ELatLonValue::ELatLonValue(double d, double m, double s, ELatLonValue::ValueDirection di)
	: precision(ELatLonValue::DEFAULT_PRECISION), direction(di)
{
	mpfr_init2(degrees, getPrecision());
	mpfr_init2(minutes, getPrecision());
	mpfr_init2(seconds, getPrecision());
	
	mpfr_set_d(degrees, d, MPFR_RNDN);
	mpfr_set_d(minutes, m, MPFR_RNDN);
	mpfr_set_d(seconds, s, MPFR_RNDN);
	
	normalize();
}

/*!
 * This constructor creates a new latitude/longitude value form the given value in
 * degrees/minutes/seconds, and the given direction.
 *
 * \param d The degrees portion of the measurement.
 * \param m The minutes portion of the measurement.
 * \param s The seconds portion of the measurement.
 * \param di The direction of the angle - NSEW or "None".
 */
ELatLonValue::ELatLonValue(mpfr_t d, mpfr_t m, mpfr_t s, ELatLonValue::ValueDirection di)
	: precision(ELatLonValue::DEFAULT_PRECISION), direction(di)
{
	mpfr_init2(degrees, getPrecision());
	mpfr_init2(minutes, getPrecision());
	mpfr_init2(seconds, getPrecision());
	
	mpfr_set(degrees, d, MPFR_RNDN);
	mpfr_set(minutes, m, MPFR_RNDN);
	mpfr_set(seconds, s, MPFR_RNDN);
	
	normalize();
}

/*!
 * This is our default destructor, which cleans up & destroys our object.
 */
ELatLonValue::~ELatLonValue()
{
	mpfr_clear(degrees);
	mpfr_clear(minutes);
	mpfr_clear(seconds);
	
	mpfr_free_cache();
}

/*!
 * This is our assignment operator, which makes our value equal to that of the given other value.
 *
 * \param o The value to make ourself equal to.
 * \return A reference to this, so this operator can be chained.
 */
ELatLonValue &ELatLonValue::operator=(const ELatLonValue &o)
{
	setPrecision(o.precision);
	
	direction = o.direction;
	mpfr_set(degrees, o.degrees, MPFR_RNDN);
	mpfr_set(minutes, o.minutes, MPFR_RNDN);
	mpfr_set(seconds, o.seconds, MPFR_RNDN);
	
	return (*this);
}

/*!
 * This is our equivalence operator. It tests if our value is equal to that of the given other
 * value. Note that this is comparing floating point numbers; this can return false in unexpected
 * situations due to rounding. If you want to account for some rounding error, compare the return
 * value of toValue() manually.
 *
 * \param o The value to compare ourself to.
 * \param True if our values are exactly equal, or false otherwise.
 */
bool ELatLonValue::operator==(const ELatLonValue &o) const
{
	if(direction != o.direction) return false;
	if(!mpfr_equal_p(seconds, o.seconds)) return false;
	if(!mpfr_equal_p(minutes, o.minutes)) return false;
	if(!mpfr_equal_p(degrees, o.degrees)) return false;
	
	return true;
}

/*!
 * This function simply returns the precision our object is currently using internally.
 *
 * \return The number of bits of precision being used.
 */
mpfr_prec_t ELatLonValue::getPrecision() const
{
	return precision;
}

/*!
 * This function sets the number of bits of precision this class uses internally. Note that calling this function
 * will update it immediately, invalidating any value this object is storing. If you need to call this, call it
 * first.
 *
 * \param p The new number of bits of precision to use.
 */
void ELatLonValue::setPrecision(mpfr_prec_t p)
{
	precision = p;
	
	mpfr_set_prec(degrees, precision);
	mpfr_set_prec(minutes, precision);
	mpfr_set_prec(seconds, precision);
}

/*!
 * This function returns our value's direction.
 *
 * \return Our value's direction.
 */
ELatLonValue::ValueDirection ELatLonValue::getDirection() const
{
	return direction;
}

/*!
 * This function returns whether or not our value is a latitude measurement.
 *
 * \return True if this is a latitude value, or false otherwise.
 */
bool ELatLonValue::isLatitude() const
{
	return ((direction == ELatLonValue::North) || (direction == ELatLonValue::South) ||
		(direction == ELatLonValue::None));
}

/*!
 * This function returns whether or not our value is a longitude measurement.
 *
 * \return True if this is a longitude value, or false otherwise.
 */
bool ELatLonValue::isLongitude() const
{
	return ((direction == ELatLonValue::East) || (direction == ELatLonValue::West) ||
		(direction == ELatLonValue::None));
}

/*!
 * This function returns the degrees component of our value in degrees/minutes/seconds format. Note
 * that, when normalized, this value is always integral - no precision is lost.
 *
 * \return The degrees portion of our angle.
 */
unsigned long ELatLonValue::getDegrees() const
{
	return mpfr_get_ui(degrees, MPFR_RNDZ);
}

/*!
 * This function returns the minutes component of our value in degrees/minutes/seconds format. Note
 * that, when normalized, this value is always integral - no precision is lost.
 *
 * \return The minutes portion of our angle.
 */
unsigned long ELatLonValue::getMinutes() const
{
	return mpfr_get_ui(minutes, MPFR_RNDZ);
}

/*!
 * This function returns the seconds component of our value in degrees/minutes/seconds format. Note
 * that, when normalized, this is the only value that is not integral. If we overflow the precision
 * on a long double, we just round to the nearest number (MPFR_RNDN).
 *
 * \return The seconds portion of our angle.
 */
long double ELatLonValue::getSeconds() const
{
	return mpfr_get_ld(seconds, MPFR_RNDN);
}

/*!
 * This function returns our LatLonValue's value as a single angle measurement, in either degrees or radians
 * based on the given type.
 *
 * \param d The destination variable we will store the resulting value in.
 * \param t Whether you want degrees or radians.
 */
void ELatLonValue::toValue(mpfr_t d, ELatLonValue::ValueType t) const
{
	mpfr_set_prec(d, getPrecision());
	mpfr_set(d, seconds, MPFR_RNDN);
	mpfr_div_ui(d, d, 60, MPFR_RNDN);
	
	mpfr_add(d, d, minutes, MPFR_RNDN);
	mpfr_div_ui(d, d, 60, MPFR_RNDN);
	
	mpfr_add(d, d, degrees, MPFR_RNDN);
	
	if(t == ELatLonValue::Radians)
	{
		mpfr_t conv;
		mpfr_init2(conv, getPrecision());
		
		mpfr_const_pi(conv, MPFR_RNDN);
		mpfr_div_ui(conv, conv, 180, MPFR_RNDN);
		mpfr_mul(d, d, conv, MPFR_RNDN);
		
		mpfr_clear(conv);
	}
}

/*!
 * This function normalizes our measurement. We make sure our internal values are all positive (sign/direction is
 * denoted by "direction"), and we make sure that our value is < 180deg (if it is not, it can be represented equivalently
 * with a smaller value but different direction).
 */
void ELatLonValue::normalize()
{
	if(direction == ELatLonValue::None)
	{
		mpfr_set_ui(degrees, 0, MPFR_RNDZ);
		mpfr_set_ui(minutes, 0, MPFR_RNDZ);
		mpfr_set_ui(seconds, 0, MPFR_RNDZ);
		return;
	}
	
	mpfr_abs(degrees, degrees, MPFR_RNDN);
	mpfr_abs(minutes, minutes, MPFR_RNDN);
	mpfr_abs(seconds, seconds, MPFR_RNDN);
	
	mpfr_t deg;
	mpfr_init(deg);
	
	toValue(deg, ELatLonValue::Degrees);
	
	if(mpfr_zero_p(deg))
	{
		direction = ELatLonValue::None;
		
		mpfr_clear(deg);
		return;
	}
	
	while(mpfr_cmp_ui(deg, 360) >= 0)
		mpfr_sub_ui(deg, deg, 360, MPFR_RNDN);
		
	if(mpfr_cmp_ui(deg, 180) > 0)
	{
		switch(direction)
		{
			case ELatLonValue::North:
				direction = ELatLonValue::South;
				break;
			
			case ELatLonValue::South:
				direction = ELatLonValue::North;
				break;
			
			case ELatLonValue::East:
				direction = ELatLonValue::West;
				break;
			
			case ELatLonValue::West:
				direction = ELatLonValue::East;
				break;
			
			default:
				direction = ELatLonValue::None;
				break;
		};
		
		mpfr_sub_ui(deg, deg, 180, MPFR_RNDN);
	}
	
	fromValue(deg, ELatLonValue::Degrees);
	mpfr_clear(deg);
}

/*!
 * This function sets our LatLonValue's value based on the single value given in either degrees or
 * radians.
 *
 * \param v Our new value.
 * \param t Whether the given value is degrees or radians.
 */
void ELatLonValue::fromValue(mpfr_t v, ELatLonValue::ValueType t)
{
	mpfr_abs(v, v, MPFR_RNDN);
	
	if(t == ELatLonValue::Radians)
	{
		mpfr_t conv;
		mpfr_init2(conv, getPrecision());
		
		mpfr_mul_ui(v, v, 180, MPFR_RNDN);
		mpfr_const_pi(conv, MPFR_RNDN);
		mpfr_div(v, v, conv, MPFR_RNDN);
		
		mpfr_clear(conv);
	}
	
	unsigned long d, m;
	
	d = mpfr_get_ui(v, MPFR_RNDZ);
	mpfr_sub_ui(v, v, d, MPFR_RNDN);
	
	mpfr_mul_ui(v, v, 60, MPFR_RNDN);
	m = mpfr_get_ui(v, MPFR_RNDZ);
	mpfr_sub_ui(v, v, m, MPFR_RNDN);
	
	mpfr_mul_ui(v, v, 60, MPFR_RNDN);
	
	mpfr_set_ui(degrees, d, MPFR_RNDN);
	mpfr_set_ui(minutes, m, MPFR_RNDN);
	mpfr_set(seconds, v, MPFR_RNDN);
}

/*!
 * This lets you print a LatLonValue to a standard ostream in a convenient way.
 *
 * \param out The output stream to write to.
 * \param v The value to write.
 * \return A reference to the output stream, to this operator can be chained.
 */
std::ostream &operator<<(std::ostream &out, const ELatLonValue &v)
{
	switch(v.getDirection())
	{
		case ELatLonValue::North:
			out << "N ";
			break;
		
		case ELatLonValue::South:
			out << "S ";
			break;
		
		case ELatLonValue::East:
			out << "E ";
			break;
		
		case ELatLonValue::West:
			out << "W ";
			break;
		
		default:
			break;
	};
	
	out << v.getDegrees() << "° " << v.getMinutes() << "' ";
	out << std::fixed << std::setprecision(2) << v.getSeconds() << "\"";
	
	return out;
}

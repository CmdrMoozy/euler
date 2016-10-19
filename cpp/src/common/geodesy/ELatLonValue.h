/*
 * euler - A collection of ProjectEuler solutions, and supporting libraries and
 *tools.
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

#ifndef INCLUDE_LIBEULER_GEODESY_LAT_LON_VALUE_H
#define INCLUDE_LIBEULER_GEODESY_LAT_LON_VALUE_H

#include <cstddef>

#include <mpfr.h>

/*!
 * \brief This class denotes a single latitude or longitude measurement.
 *
 * In general, we store an angle measurement in degrees, and the "direction" it
 *goes in is stored
 * (this is more or less the same as storing whether we are a positive/negative
 *latitude/longitude
 * value). We provide some conversion functions, but serious math should
 *probably be done via
 * QGeoCoord.
 *
 * Note that these values are created, by default, with
 *QLatLonValue::DEFAULT_PRECISION bits of
 * precision. If you need to change this, you should do so with setPrecision()
 *before using the
 * object for anything else.
 *
 * The default, 128 bits, should be sufficient for most applications, however.
 *
 * It is also worth noting that, instead of having a test suite function
 *ourselves, we depend on
 * EGeoCoord to test our objects. Since it does math with us, all of our
 *functions are utilized
 * there anyway, so there is no reason to test them again.
 */
class ELatLonValue
{
public:
	/*!
	 * \brief This constant denotes the default number of bits of precision
	 * our class uses.
	 */
	static const mpfr_prec_t DEFAULT_PRECISION = 128;

	/*!
	 * \brief This enumeration indicates a type of angle measurement -
	 * either degrees or radians.
	 */
	enum ValueType
	{
		Degrees,
		Radians
	};

	/*!
	 * \brief This enumeration denotes an angle direction - NSEW, or "None"
	 * for zero longitude/latitude.
	 */
	enum ValueDirection
	{
		North,
		South,
		East,
		West,
		None
	};

	ELatLonValue();
	ELatLonValue(const ELatLonValue &o);

	ELatLonValue(mpfr_t v, ValueType t, ValueDirection d);
	ELatLonValue(long double v, ValueType t, ValueDirection d);

	ELatLonValue(double d, double m, double s, ValueDirection di);
	ELatLonValue(mpfr_t d, mpfr_t m, mpfr_t s, ValueDirection di);

	virtual ~ELatLonValue();

	ELatLonValue &operator=(const ELatLonValue &o);
	bool operator==(const ELatLonValue &o) const;

	mpfr_prec_t getPrecision() const;
	void setPrecision(mpfr_prec_t p);

	ValueDirection getDirection() const;
	bool isLatitude() const;
	bool isLongitude() const;

	unsigned long getDegrees() const;
	unsigned long getMinutes() const;
	long double getSeconds() const;

	void toValue(mpfr_t d, ValueType t) const;

private:
	mpfr_prec_t precision;
	ValueDirection direction;
	mpfr_t degrees, minutes, seconds;

	void normalize();

	void fromValue(mpfr_t v, ValueType t);
};

std::ostream &operator<<(std::ostream &out, const ELatLonValue &v);

#endif

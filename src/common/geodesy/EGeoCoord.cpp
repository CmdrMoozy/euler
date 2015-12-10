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

#include "EGeoCoord.h"

#include <iostream>
#include <cmath>

#include "common/EDefines.h"

/*!
 * This is our default constructor, which creates a new object with
 * default-initialized latitude and longitude
 * values.
 */
EGeoCoord::EGeoCoord()
{
	latitude = new ELatLonValue();
	longitude = new ELatLonValue();

	normalize();
}

/*!
 * This is our copy constructor, which creates a new coordinate equal to the
 *given other one.
 *
 * \param o The coordinate to make ourself equal to.
 */
EGeoCoord::EGeoCoord(const EGeoCoord &o) : latitude(NULL), longitude(NULL)
{
	(*this) = o;
}

/*!
 * This is our main constructor, which creates a new coordinate based upon the
 *given longitude and latitude
 * values. Note that if the "latitude" parameter is, in fact, longitude, then it
 *is discarded for a default-constructed
 * value (same for the other parameter).
 *
 * \param lat The latitude portion of our coordinate.
 * \param lon The longitude portion of our coordinate.
 */
EGeoCoord::EGeoCoord(const ELatLonValue &lat, const ELatLonValue &lon)
{
	latitude = new ELatLonValue(lat);
	longitude = new ELatLonValue(lon);

	normalize();
}

/*!
 * This is our default destructor, which cleans up & destroys our object.
 */
EGeoCoord::~EGeoCoord()
{
	delete latitude;
	delete longitude;

	mpfr_free_cache();
}

/*!
 * This is our assignment operator, which sets our value equal to that of the
 *given other coordinate.
 *
 * \param o The coordinate to make ourself equal to.
 * \return A reference to this, so this operator can be chained.
 */
EGeoCoord &EGeoCoord::operator=(const EGeoCoord &o)
{
	if(latitude == NULL)
		latitude = new ELatLonValue();
	if(longitude == NULL)
		longitude = new ELatLonValue();

	(*latitude) = (*o.latitude);
	(*longitude) = (*o.longitude);

	return (*this);
}

/*!
 * This is our equivalence operator. It tests if this coordinate is equivalent
 *to the given other coordinate.
 * Note that this is comparing floating point numbers; this can return false in
 *unexpected
 * situations due to rounding. If you want to account for some rounding error,
 *compare the return
 * value of toValue() (on our latitude and longitude values, respectively)
 *manually.
 *
 * \param o The value to compare ourself to.
 * \return True if we are equal, or false otherwise.
 */
bool EGeoCoord::operator==(const EGeoCoord &o) const
{
	return ((getLatitude() == o.getLatitude()) &&
	        (getLongitude() == o.getLongitude()));
}

/*!
 * This function returns the latitude portion of our coordinate.
 *
 * \return Our latitude value.
 */
const ELatLonValue &EGeoCoord::getLatitude() const
{
	return (*latitude);
}

/*!
 * This function returns the longitude portion of our coordinate.
 *
 * \return Our longitude value.
 */
const ELatLonValue &EGeoCoord::getLongitude() const
{
	return (*longitude);
}

/*!
 * This function returns the hemisphere our coordinate is in. This is two of our
 *HemisphereFlags values
 * OR'ed together - North/South | East/West.
 *
 * \return A flag specifying what hemisphere this coordinate is in.
 */
int EGeoCoord::getHemisphere() const
{
	int f = 0;

	if(latitude->getDirection() == ELatLonValue::North)
		f |= EGeoCoord::Northern;
	else if(latitude->getDirection() == ELatLonValue::South)
		f |= EGeoCoord::Southern;

	if(longitude->getDirection() == ELatLonValue::East)
		f |= EGeoCoord::Eastern;
	else if(longitude->getDirection() == ELatLonValue::West)
		f |= EGeoCoord::Western;

	return f;
}

/*!
 * This function tests if this coordinate and the given other coordinate are in
 *the same hemisphere.
 *
 * \param o The other coordinate to test.
 * \return True if we are in the same hemisphere, or false otherwise.
 */
bool EGeoCoord::inSameHemisphere(const EGeoCoord &o) const
{
	return (getHemisphere() == o.getHemisphere());
}

/*!
 * This function tests if this coordinate and the given other coordinate are
 *approximately antipodal.
 * We allow for an accuracy parameter, with is 5.0 (degrees) by default, which
 *means we return true
 * if the other point is within 5.0 degrees of being antipodal.
 *
 * \param o The other coordinate to test.
 * \param a The "accuracy" - 5.0deg by default.
 * \return True if our coordinates are (approximately) antipodal, or false
 *otherwise.
 */
bool EGeoCoord::isAntipodal(const EGeoCoord &o, double a) const
{
	// If we're in the same hemisphere, just return false.
	if(inSameHemisphere(o))
		return false;

	// Initialize variables.

	mpfr_t latA, lonA, latB, lonB;

	mpfr_init(latA);
	mpfr_init(lonA);
	mpfr_init(latB);
	mpfr_init(lonB);

	// Get existing latitude/longitude.

	getLatitude().toValue(latA, ELatLonValue::Degrees);
	getLongitude().toValue(lonA, ELatLonValue::Degrees);

	o.getLatitude().toValue(latB, ELatLonValue::Degrees);
	o.getLongitude().toValue(lonB, ELatLonValue::Degrees);

	// Flip the second point to its antipode.

	mpfr_ui_sub(lonB, 180, lonB, MPFR_RNDN);

	// Get the difference.

	mpfr_sub(latA, latB, latA, MPFR_RNDN);
	mpfr_abs(latA, latA, MPFR_RNDN);
	mpfr_sub(lonA, lonB, lonA, MPFR_RNDN);
	mpfr_abs(lonA, lonA, MPFR_RNDN);

	// Test if it is within our tolerance.

	bool ret = ((mpfr_get_d(latA, MPFR_RNDN) <= a) &&
	            (mpfr_get_d(lonA, MPFR_RNDN) <= a));

	// Clear memory.

	mpfr_clear(latA);
	mpfr_clear(lonA);
	mpfr_clear(latB);
	mpfr_clear(lonB);

	// Return! :)

	return ret;
}

/*!
 * This function gives a fairly approximate midpoint between our point and the
 *given other point. This
 * is done, generally speaking, using the great circle arc between our two
 *points.
 *
 * \param o The "end" coordinate.
 * \param p The number of bits of precision to use.
 * \return A new coordinate that is approximately the midpoint.
 */
EGeoCoord EGeoCoord::getMidpointTo(const EGeoCoord &o, mpfr_prec_t p) const
{
	// Initalize variables.

	mpfr_t latA, lonA, latB, lonB;
	mpfr_t Bx, By;
	mpfr_t newLat, newLon;
	mpfr_t tmpA, tmpB;

	mpfr_init(latA);
	mpfr_init(lonA);
	mpfr_init(latB);
	mpfr_init(lonB);
	mpfr_init2(Bx, p);
	mpfr_init2(By, p);
	mpfr_init2(newLat, p);
	mpfr_init2(newLon, p);
	mpfr_init2(tmpA, p);
	mpfr_init2(tmpB, p);

	// Get existing latitude/longitude.

	getLatitude().toValue(latA, ELatLonValue::Radians);
	getLongitude().toValue(lonA, ELatLonValue::Radians);

	if(getHemisphere() & EGeoCoord::Southern)
		mpfr_neg(latA, latA, MPFR_RNDN);
	if(getHemisphere() & EGeoCoord::Western)
		mpfr_neg(lonA, lonA, MPFR_RNDN);

	o.getLatitude().toValue(latB, ELatLonValue::Radians);
	o.getLongitude().toValue(lonB, ELatLonValue::Radians);

	if(o.getHemisphere() & EGeoCoord::Southern)
		mpfr_neg(latB, latB, MPFR_RNDN);
	if(o.getHemisphere() & EGeoCoord::Western)
		mpfr_neg(lonB, lonB, MPFR_RNDN);

	/*
	 * Compute Bx - given by:
	 *     Bx = cos(latB) * cos(delta lon)
	 */

	mpfr_cos(tmpA, latB, MPFR_RNDN);
	mpfr_sub(Bx, lonB, lonA, MPFR_RNDN);
	mpfr_cos(Bx, Bx, MPFR_RNDN);
	mpfr_mul(Bx, tmpA, Bx, MPFR_RNDN); // Bx contains our result.

	/*
	 * Compute By - given by:
	 *     By = cos(latB) * sin(delta lon)
	 */

	mpfr_cos(tmpA, latB, MPFR_RNDN);
	mpfr_sub(By, lonB, lonA, MPFR_RNDN);
	mpfr_sin(By, By, MPFR_RNDN);
	mpfr_mul(By, tmpA, By, MPFR_RNDN); // By contains our result.

	/*
	 * Compute newLat - given by:
	 *     newLat = atan2( sin(latA) + sin(latB), sqrt( ( cos(latA)+Bx )^2 +
	 * By^2 )
	 */

	mpfr_cos(newLat, latA, MPFR_RNDN);
	mpfr_add(newLat, newLat, Bx, MPFR_RNDN);
	mpfr_pow_ui(newLat, newLat, 2, MPFR_RNDN);

	mpfr_pow_ui(tmpA, By, 2, MPFR_RNDN);

	mpfr_add(newLat, newLat, tmpA, MPFR_RNDN);
	mpfr_sqrt(newLat, newLat, MPFR_RNDN);

	mpfr_sin(tmpA, latA, MPFR_RNDN);
	mpfr_sin(tmpB, latB, MPFR_RNDN);
	mpfr_add(tmpA, tmpA, tmpB, MPFR_RNDN);

	mpfr_atan2(newLat, tmpA, newLat,
	           MPFR_RNDN); // newLat contains our result.

	/*
	 * Compute newLon - given by:
	 *     newLon = lonA + atan2(By, cos(latA)+Bx)
	 */

	mpfr_cos(newLon, latA, MPFR_RNDN);
	mpfr_add(newLon, newLon, Bx, MPFR_RNDN);
	mpfr_atan2(newLon, By, newLon, MPFR_RNDN);
	mpfr_add(newLon, lonA, newLon,
	         MPFR_RNDN); // newLon contains our result.

	// Create our new coordinate.

	ELatLonValue::ValueDirection latDir =
	        (mpfr_sgn(newLat) < 0 ? ELatLonValue::South
	                              : ELatLonValue::North);
	ELatLonValue::ValueDirection lonDir =
	        (mpfr_sgn(newLon) < 0 ? ELatLonValue::West
	                              : ELatLonValue::East);

	EGeoCoord ret(ELatLonValue(newLat, ELatLonValue::Radians, latDir),
	              ELatLonValue(newLon, ELatLonValue::Radians, lonDir));

	// Clean up memory.

	mpfr_clear(latA);
	mpfr_clear(lonA);
	mpfr_clear(latB);
	mpfr_clear(lonB);
	mpfr_clear(Bx);
	mpfr_clear(By);
	mpfr_clear(newLat);
	mpfr_clear(newLon);
	mpfr_clear(tmpA);
	mpfr_clear(tmpB);

	// Return the new point! :)

	return ret;
}

/*!
 * This function gets the distance between this point and the given other point.
 *For more information:
 *     http://en.wikipedia.org/wiki/Vincenty%27s_formulae
 *
 * \param d The destination variable to store our result in.
 * \param b The second point to get the distance to.
 * \param p The number of bits of precision to use.
 */
void EGeoCoord::getDistanceTo(mpfr_t d, const EGeoCoord &b, mpfr_prec_t p) const
{
	if(isAntipodal(b))
	{
		// Our formula fails to converge for nearly-antipodal points.
		// Calculate the distance using a midpoint intstead.

		EGeoCoord mid = getMidpointTo(b);

		mpfr_t tmp;
		mpfr_init(tmp);

		distanceCalculation(d, (*this), mid, p);
		distanceCalculation(tmp, mid, b, p);

		mpfr_add(d, d, tmp, MPFR_RNDN);

		mpfr_clear(tmp);
	}
	else
	{
		distanceCalculation(d, (*this), b, p);
	}
}

/*!
 * This function normalizes our coordinate - this means we ensure that our
 * lat/lon values really ARE latitude/longitude,
 * and if not, sets them to default-constructed values.
 */
void EGeoCoord::normalize()
{
	if(!latitude->isLatitude())
		(*latitude) = ELatLonValue();

	if(!longitude->isLongitude())
		(*longitude) = ELatLonValue();
}

/*!
 * This is our behind-the-scenes function that actually does distance
 *calculations for us. The result will be stored in d, and will
 * use an accuracy of p bits (a value around 80 is more than enough to be
 *accurate to a fraction of a millimeter).
 *
 * \param d The destination variable to store our result in.
 * \param cA Coordinate "A".
 * \param cB Coordinate "B".
 * \param p The number of bits of precision to use.
 */
void EGeoCoord::distanceCalculation(mpfr_t d, const EGeoCoord &cA,
                                    const EGeoCoord &cB, mpfr_prec_t p) const
{
	// Variables.

	mpfr_t convergence, cDelta, a, f, b;
	mpfr_t tmpA, tmpB, tmpC, tmpD;
	mpfr_t latA, lonA, latB, lonB;
	mpfr_t U1, U2, L;
	mpfr_t sinU1, cosU1, sinU2, cosU2;
	mpfr_t lambda, sinSigma, cosSigma, sigma, sinAzimuth, cos2Azimuth,
	        cos2SigmaM, C;
	mpfr_t u2, A, B, deltaSigma;

	// Initialize variables.

	mpfr_init2(convergence, p);
	mpfr_set_ui(convergence, 10, MPFR_RNDN);
	mpfr_pow_si(convergence, convergence, -digitsFromPrecision(EABS(p)),
	            MPFR_RNDN);

	mpfr_init2(cDelta, p);

	mpfr_init_set_d(a, EGeoCoord::ELLIPSOID_MAJOR_AXIS, MPFR_RNDN);

	mpfr_init2(f, p);
	mpfr_set_ui(f, 1, MPFR_RNDN);
	mpfr_div_d(f, f, EGeoCoord::ELLIPSOID_FLATTENING_REC, MPFR_RNDN);

	mpfr_init2(b, p);
	mpfr_ui_sub(b, 1, f, MPFR_RNDN);
	mpfr_mul(b, b, a, MPFR_RNDN);

	mpfr_init2(tmpA, p);
	mpfr_init2(tmpB, p);
	mpfr_init2(tmpC, p);
	mpfr_init2(tmpD, p);

	mpfr_init2(latA, p);
	mpfr_init2(lonA, p);
	mpfr_init2(latB, p);
	mpfr_init2(lonB, p);

	mpfr_init2(U1, p);
	mpfr_init2(U2, p);
	mpfr_init2(L, p);

	mpfr_init2(sinU1, p);
	mpfr_init2(cosU1, p);
	mpfr_init2(sinU2, p);
	mpfr_init2(cosU2, p);

	mpfr_init2(lambda, p);
	mpfr_init2(sinSigma, p);
	mpfr_init2(cosSigma, p);
	mpfr_init2(sigma, p);
	mpfr_init2(sinAzimuth, p);
	mpfr_init2(cos2Azimuth, p);
	mpfr_init2(cos2SigmaM, p);
	mpfr_init2(C, p);

	mpfr_init2(u2, p);
	mpfr_init2(A, p);
	mpfr_init2(B, p);
	mpfr_init2(deltaSigma, p);

	// Get point coordinates in radians.

	cA.getLatitude().toValue(latA, ELatLonValue::Radians);
	cA.getLongitude().toValue(lonA, ELatLonValue::Radians);

	if(cA.getHemisphere() & EGeoCoord::Southern)
		mpfr_neg(latA, latA, MPFR_RNDN);
	if(cA.getHemisphere() & EGeoCoord::Western)
		mpfr_neg(lonA, lonA, MPFR_RNDN);

	cB.getLatitude().toValue(latB, ELatLonValue::Radians);
	cB.getLongitude().toValue(lonB, ELatLonValue::Radians);

	if(cB.getHemisphere() & EGeoCoord::Southern)
		mpfr_neg(latB, latB, MPFR_RNDN);
	if(cB.getHemisphere() & EGeoCoord::Western)
		mpfr_neg(lonB, lonB, MPFR_RNDN);

	// Calculate U1 - reduced latitude of point A. Given by: atan( (1-f) *
	// tan(latA) )

	mpfr_set_ui(tmpA, 1, MPFR_RNDN);
	mpfr_sub(tmpA, tmpA, f, MPFR_RNDN);

	mpfr_set(tmpB, latA, MPFR_RNDN);
	mpfr_tan(tmpB, tmpB, MPFR_RNDN);

	mpfr_mul(tmpA, tmpA, tmpB, MPFR_RNDN);

	mpfr_atan(U1, tmpA, MPFR_RNDN);

	mpfr_sin(sinU1, U1, MPFR_RNDN);
	mpfr_cos(cosU1, U1, MPFR_RNDN);

	// Calculate U2 - reduced latitude of point B. Given by: atan( (1-f) *
	// tan(latB) )

	mpfr_set_ui(tmpA, 1, MPFR_RNDN);
	mpfr_sub(tmpA, tmpA, f, MPFR_RNDN);

	mpfr_set(tmpB, latB, MPFR_RNDN);
	mpfr_tan(tmpB, tmpB, MPFR_RNDN);

	mpfr_mul(tmpA, tmpA, tmpB, MPFR_RNDN);

	mpfr_atan(U2, tmpA, MPFR_RNDN);

	mpfr_sin(sinU2, U2, MPFR_RNDN);
	mpfr_cos(cosU2, U2, MPFR_RNDN);

	// Calculate L - Difference in longitude. Given by: lonB - lonA

	mpfr_sub(L, lonB, lonA, MPFR_RNDN);

	// Set our initial value of lambda.

	mpfr_set(lambda, L, MPFR_RNDN);

	// Compute the solution iteratively until lambda converges.

	do
	{
		/*
		 * Compute sin(sigma) - given by:
		 *     sin(sigma) = sqrt( ( cos(U2) * sin(lambda) )^2 + ( (
		 * cos(U1) * sin(U2) ) - ( sin(U1) * cos(U2) * cos(lambda) ) )^2
		 * )
		 */

		mpfr_sin(tmpA, lambda, MPFR_RNDN);
		mpfr_mul(tmpA, tmpA, cosU2, MPFR_RNDN);
		mpfr_pow_ui(tmpA, tmpA, 2, MPFR_RNDN);

		mpfr_mul(tmpB, cosU1, sinU2, MPFR_RNDN);

		mpfr_mul(tmpC, sinU1, cosU2, MPFR_RNDN);
		mpfr_cos(tmpD, lambda, MPFR_RNDN);
		mpfr_mul(tmpC, tmpC, tmpD, MPFR_RNDN);

		mpfr_sub(tmpB, tmpB, tmpC, MPFR_RNDN);
		mpfr_pow_ui(tmpB, tmpB, 2, MPFR_RNDN);

		mpfr_add(tmpA, tmpA, tmpB, MPFR_RNDN);
		mpfr_sqrt(sinSigma, tmpA,
		          MPFR_RNDN); // sinSigma contains our result.

		/*
		 * Compute cos(sigma) - given by:
		 *     cos(sigma) = ( sin(U1) * sin(U2) ) + ( cos(U1) * cos(U2)
		 * * cos(lambda) )
		 */

		mpfr_mul(tmpA, sinU1, sinU2, MPFR_RNDN);

		mpfr_mul(tmpB, cosU1, cosU2, MPFR_RNDN);
		mpfr_cos(tmpC, lambda, MPFR_RNDN);
		mpfr_mul(tmpB, tmpB, tmpC, MPFR_RNDN);

		mpfr_add(cosSigma, tmpA, tmpB,
		         MPFR_RNDN); // cosSigma contains our result.

		/*
		 * Compute sigma - given by:
		 *     sigma = atan2( sin(sigma), cos(sigma) )
		 */

		mpfr_atan2(sigma, sinSigma, cosSigma,
		           MPFR_RNDN); // sigma contains our result.

		/*
		 * Compute sin(azimuth) - given by:
		 *     sin(azimuth) = ( cos(U1) * cos(U2) * sin(lambda) ) /
		 * sin(sigma)
		 */

		mpfr_mul(sinAzimuth, cosU1, cosU2, MPFR_RNDN);
		mpfr_sin(tmpA, lambda, MPFR_RNDN);
		mpfr_mul(sinAzimuth, sinAzimuth, tmpA, MPFR_RNDN);
		mpfr_div(sinAzimuth, sinAzimuth, sinSigma,
		         MPFR_RNDN); // sinAzimuth contains our result.

		/*
		 * Compute cos2(azimuth) - given by:
		 *     cos2(azimuth) = 1 - sin2(azimuth)
		 */

		mpfr_pow_ui(cos2Azimuth, sinAzimuth, 2, MPFR_RNDN);
		mpfr_set_ui(tmpA, 1, MPFR_RNDN);
		mpfr_sub(cos2Azimuth, tmpA, cos2Azimuth,
		         MPFR_RNDN); // cos2Azimuth contains our result.

		/*
		 * Compute cos(2sigmam) - given by:
		 *     cos(2sigmam) = cos(sigma) - ( ( 2 * sin(U1) * sin(U2) ) /
		 * cos2(azimuth) )
		 */

		mpfr_mul(tmpA, sinU1, sinU2, MPFR_RNDN);
		mpfr_mul_ui(tmpA, tmpA, 2, MPFR_RNDN);
		mpfr_div(tmpA, tmpA, cos2Azimuth, MPFR_RNDN);
		mpfr_sub(cos2SigmaM, cosSigma, tmpA,
		         MPFR_RNDN); // cos2SigmaM contains our result.

		/*
		 * Compute C - given by:
		 *     C = (f / 16) * cos2Azimuth * (4 + f(4 - 3 * cos2Azimuth))
		 */

		mpfr_div_ui(tmpA, f, 16, MPFR_RNDN);

		mpfr_mul_ui(tmpB, cos2Azimuth, 3, MPFR_RNDN);
		mpfr_ui_sub(tmpB, 4, tmpB, MPFR_RNDN);
		mpfr_mul(tmpB, tmpB, f, MPFR_RNDN);
		mpfr_add_ui(tmpB, tmpB, 4, MPFR_RNDN);

		mpfr_mul(C, tmpA, cos2Azimuth, MPFR_RNDN);
		mpfr_mul(C, C, tmpB, MPFR_RNDN); // C contains our result.

		/*
		 * Compute new theta - given by:
		 *     theta = L + (1-C)*f*sin(azimuth)*( sigma + C*sin(sigma)*(
		 * cos2SigmaM +
		 *       C*cos(sigma)*(-1 + 2 * cos2SigmaM^2))))
		 */

		mpfr_pow_ui(tmpA, cos2SigmaM, 2, MPFR_RNDN);
		mpfr_mul_ui(tmpA, tmpA, 2, MPFR_RNDN);
		mpfr_si_sub(tmpA, -1, tmpA, MPFR_RNDN);

		mpfr_mul(tmpA, cosSigma, tmpA, MPFR_RNDN);
		mpfr_mul(tmpA, C, tmpA, MPFR_RNDN);
		mpfr_add(tmpA, cos2SigmaM, tmpA, MPFR_RNDN);

		mpfr_mul(tmpA, sinSigma, tmpA, MPFR_RNDN);
		mpfr_mul(tmpA, C, tmpA, MPFR_RNDN);
		mpfr_add(tmpA, sigma, tmpA, MPFR_RNDN);

		mpfr_mul(tmpA, sinAzimuth, tmpA, MPFR_RNDN);
		mpfr_mul(tmpA, f, tmpA, MPFR_RNDN);
		mpfr_ui_sub(tmpB, 1, C, MPFR_RNDN);
		mpfr_mul(tmpA, tmpB, tmpA, MPFR_RNDN);
		mpfr_add(tmpA, L, tmpA, MPFR_RNDN);

		/*
		 * Compute cDelta and then set lambda to its new value.
		 */

		mpfr_sub(cDelta, tmpA, lambda, MPFR_RNDN);
		mpfr_abs(cDelta, cDelta, MPFR_RNDN);
		mpfr_set(lambda, tmpA, MPFR_RNDN);

	} while(mpfr_greater_p(cDelta, convergence));

	/*
	 * Compute u^2 - given by:
	 *     u^2 = cos2Azimuth * ((a^2 - b^2) / b^2)
	 */

	mpfr_pow_ui(u2, a, 2, MPFR_RNDN);
	mpfr_pow_ui(tmpA, b, 2, MPFR_RNDN);
	mpfr_sub(u2, u2, tmpA, MPFR_RNDN);
	mpfr_div(u2, u2, tmpA, MPFR_RNDN);
	mpfr_mul(u2, cos2Azimuth, u2, MPFR_RNDN); // u2 contains our result.

	/*
	 * Compute A - given by:
	 *     A = 1 + (u2 / 16384)(4096 + u2( -768 + u2(320 - 174u2)))
	 */

	mpfr_mul_ui(A, u2, 174, MPFR_RNDN);
	mpfr_ui_sub(A, 320, A, MPFR_RNDN);

	mpfr_mul(A, u2, A, MPFR_RNDN);
	mpfr_sub_ui(A, A, 768, MPFR_RNDN);

	mpfr_mul(A, u2, A, MPFR_RNDN);
	mpfr_add_ui(A, A, 4096, MPFR_RNDN);

	mpfr_div_ui(tmpA, u2, 16384, MPFR_RNDN);

	mpfr_mul(A, tmpA, A, MPFR_RNDN);
	mpfr_add_ui(A, A, 1, MPFR_RNDN); // A contains our result.

	/*
	 * Compute B - given by:
	 *     B = (u2 / 1024)(256 + u2(-128 + u2(74 - 47u2)))
	 */

	mpfr_mul_ui(B, u2, 47, MPFR_RNDN);
	mpfr_ui_sub(B, 74, B, MPFR_RNDN);

	mpfr_mul(B, u2, B, MPFR_RNDN);
	mpfr_add_si(B, B, -128, MPFR_RNDN);

	mpfr_mul(B, u2, B, MPFR_RNDN);
	mpfr_add_ui(B, B, 256, MPFR_RNDN);

	mpfr_div_ui(tmpA, u2, 1024, MPFR_RNDN);

	mpfr_mul(B, tmpA, B, MPFR_RNDN); // B contains our result.

	/*
	 * Compute delta sigma - given by:
	 *     delta sigma = B sinSigma ( cos2SigmaM + (1/4)B( cosSigma( -1 +
	 * 2cos2SigmaM^2)
	 */

	mpfr_pow_ui(deltaSigma, cos2SigmaM, 2, MPFR_RNDN);
	mpfr_mul_ui(deltaSigma, deltaSigma, 4, MPFR_RNDN);
	mpfr_sub_ui(deltaSigma, deltaSigma, 3, MPFR_RNDN);

	mpfr_pow_ui(tmpA, sinSigma, 2, MPFR_RNDN);
	mpfr_mul_ui(tmpA, tmpA, 4, MPFR_RNDN);
	mpfr_sub_ui(tmpA, tmpA, 3, MPFR_RNDN);

	mpfr_set_ui(tmpB, 1, MPFR_RNDN);
	mpfr_div_ui(tmpB, tmpB, 6, MPFR_RNDN);
	mpfr_mul(tmpB, tmpB, B, MPFR_RNDN);
	mpfr_mul(tmpB, tmpB, cos2SigmaM, MPFR_RNDN);

	mpfr_mul(deltaSigma, deltaSigma, tmpA, MPFR_RNDN);
	mpfr_mul(deltaSigma, deltaSigma, tmpB, MPFR_RNDN);

	mpfr_pow_ui(tmpA, cos2SigmaM, 2, MPFR_RNDN);
	mpfr_mul_ui(tmpA, tmpA, 2, MPFR_RNDN);
	mpfr_sub_ui(tmpA, tmpA, 1, MPFR_RNDN);
	mpfr_mul(tmpA, cosSigma, tmpA, MPFR_RNDN);

	mpfr_sub(deltaSigma, tmpA, deltaSigma, MPFR_RNDN);
	mpfr_mul(deltaSigma, B, deltaSigma, MPFR_RNDN);
	mpfr_mul_d(deltaSigma, deltaSigma, 0.25, MPFR_RNDN);
	mpfr_add(deltaSigma, cos2SigmaM, deltaSigma, MPFR_RNDN);

	mpfr_mul(deltaSigma, sinSigma, deltaSigma, MPFR_RNDN);
	mpfr_mul(deltaSigma, B, deltaSigma,
	         MPFR_RNDN); // deltaSigma contains our result.

	/*
	 * FINALLY - Compute s - given by:
	 *     s = bA(sigma - deltaSigma)
	 */

	mpfr_set_prec(d, p);
	mpfr_sub(d, sigma, deltaSigma, MPFR_RNDN);
	mpfr_mul(d, A, d, MPFR_RNDN);
	mpfr_mul(d, b, d, MPFR_RNDN);

	// Clear up memory.

	mpfr_clear(convergence);
	mpfr_clear(cDelta);
	mpfr_clear(a);
	mpfr_clear(f);
	mpfr_clear(b);
	mpfr_clear(tmpA);
	mpfr_clear(tmpB);
	mpfr_clear(tmpC);
	mpfr_clear(tmpD);
	mpfr_clear(latA);
	mpfr_clear(lonA);
	mpfr_clear(latB);
	mpfr_clear(lonB);
	mpfr_clear(U1);
	mpfr_clear(U2);
	mpfr_clear(L);
	mpfr_clear(sinU1);
	mpfr_clear(cosU1);
	mpfr_clear(sinU2);
	mpfr_clear(cosU2);
	mpfr_clear(lambda);
	mpfr_clear(sinSigma);
	mpfr_clear(cosSigma);
	mpfr_clear(sigma);
	mpfr_clear(sinAzimuth);
	mpfr_clear(cos2Azimuth);
	mpfr_clear(cos2SigmaM);
	mpfr_clear(C);
	mpfr_clear(u2);
	mpfr_clear(A);
	mpfr_clear(B);
	mpfr_clear(deltaSigma);
}

/*!
 * This is a convenience function that will approximate the number of digits of
 * accuracy a given number of bits of accuracy will provide.
 *
 * \param p The number of bits of accuracy.
 * \return The number of digits of accuracy.
 */
int EGeoCoord::digitsFromPrecision(mpfr_prec_t p) const
{
	long double prec = (log10l(2.0) * p) - 1;
	return static_cast<int>(floorl(prec));
}

/*!
 * This lets you print a GeoCoord to a standard ostream in a convenient way.
 *
 * \param out The output stream to write to.
 * \param c The coordinate to print.
 * \return A reference to the output stream, so this operator can be chained.
 */
std::ostream &operator<<(std::ostream &out, const EGeoCoord &c)
{
	out << c.getLatitude() << ", " << c.getLongitude();
	return out;
}

#ifndef INCLUDE_LIBEULER_GEODESY_GEO_COORD_H
#define INCLUDE_LIBEULER_GEODESY_GEO_COORD_H

#include <mpfr.h>

#include "../geodesy/ELatLonValue.h"

/*!
 * \brief This class represents a geographic coordinate.
 *
 * It denotes a coordinate on the surface of the earth, in latitude/longitude format. It also
 * provides the ability to do some math with these coordiantes, such as finding distance (using
 * the WGS-84 ellipsoid model), and finding midpoints.
 */
class EGeoCoord
{
	public:
		/*!
		 * \brief This constant provides the major axis length of our reference ellipsoid (WGS-84).
		 */
		static constexpr double ELLIPSOID_MAJOR_AXIS = 6378137.0;
	
		/*!
		 * \brief This constant provides the reciprocal of the "flattening" value of our reference ellipsoid (WGS-84).
		 */
		static constexpr double ELLIPSOID_FLATTENING_REC = 298.257223563;
		
		/*!
		 * \brief This is a flags enumerator, which denotes a hemisphere of the earth.
		 */
		enum HemisphereFlags
		{
			Eastern  = 0x01,
			Western  = 0x02,
			Northern = 0x04,
			Southern = 0x08
		};
		
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
		
		EGeoCoord();
		EGeoCoord(const EGeoCoord &o);
		EGeoCoord(const ELatLonValue &lat, const ELatLonValue &lon);
		virtual ~EGeoCoord();
	
		EGeoCoord &operator=(const EGeoCoord &o);
		bool operator==(const EGeoCoord &o) const;
		
		const ELatLonValue &getLatitude() const;
		const ELatLonValue &getLongitude() const;
		int getHemisphere() const;
		bool inSameHemisphere(const EGeoCoord &o) const;
		bool isAntipodal(const EGeoCoord &o, double a = 5.0) const;
		
		EGeoCoord getMidpointTo(const EGeoCoord &o, mpfr_prec_t p = ELatLonValue::DEFAULT_PRECISION) const;
		
		void getDistanceTo(mpfr_t d, const EGeoCoord &b, mpfr_prec_t p = ELatLonValue::DEFAULT_PRECISION) const;
	
	private:
		ELatLonValue *latitude, *longitude;
		
		void normalize();
		
		void distanceCalculation(mpfr_t d, const EGeoCoord &cA, const EGeoCoord &cB, mpfr_prec_t p) const;
		int digitsFromPrecision(mpfr_prec_t p) const;
};

std::ostream &operator<<(std::ostream &out, const EGeoCoord &c);

#endif

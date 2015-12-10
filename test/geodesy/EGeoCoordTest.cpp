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

#include <catch/catch.hpp>

#include "common/geodesy/EGeoCoord.h"
#include "common/geodesy/ELatLonValue.h"
#include "common/types/BigDecimal.hpp"

TEST_CASE("Test EGeoCoord", "[EGeoCoord]")
{
	// Construct a bunch of geo coordinates.

	EGeoCoord aA(ELatLonValue(48.8583, ELatLonValue::Degrees,
	                          ELatLonValue::North),
	             ELatLonValue(2.2945, ELatLonValue::Degrees,
	                          ELatLonValue::East));
	EGeoCoord aB(ELatLonValue(43.0, 43.0, 24.0, ELatLonValue::North),
	             ELatLonValue(10.0, 23.0, 39.0, ELatLonValue::East));

	EGeoCoord bA(ELatLonValue(25.0, 11.0, 49.7, ELatLonValue::North),
	             ELatLonValue(55.0, 16.0, 26.8, ELatLonValue::East));
	EGeoCoord bB(ELatLonValue(25.0, 2.0, 1.0, ELatLonValue::North),
	             ELatLonValue(121.0, 33.0, 54.0, ELatLonValue::East));

	EGeoCoord cA(ELatLonValue(51.0, 50.0, 0.0, ELatLonValue::North),
	             ELatLonValue(107.0, 35.0, 60.0, ELatLonValue::East));
	EGeoCoord cB(ELatLonValue(51.0, 44.0, 0.0, ELatLonValue::South),
	             ELatLonValue(72.0, 30.0, 60.0, ELatLonValue::West));

	EGeoCoord dA(ELatLonValue(39.0, 54.0, 50.0, ELatLonValue::North),
	             ELatLonValue(116.0, 23.0, 30.0, ELatLonValue::East));
	EGeoCoord dB(ELatLonValue(34.0, 36.0, 12.0, ELatLonValue::South),
	             ELatLonValue(58.0, 22.0, 54.0, ELatLonValue::West));

	EGeoCoord eA(
	        ELatLonValue(0.0, ELatLonValue::Radians, ELatLonValue::North),
	        ELatLonValue(0.0, ELatLonValue::Radians, ELatLonValue::East));
	EGeoCoord eB(
	        ELatLonValue(0.5, ELatLonValue::Degrees, ELatLonValue::South),
	        ELatLonValue(179.5, ELatLonValue::Degrees, ELatLonValue::West));

	// Test getHemisphere and inSameHemisphere.

	CHECK(aA.getHemisphere() == (EGeoCoord::Northern | EGeoCoord::Eastern));
	CHECK(aB.getHemisphere() == (EGeoCoord::Northern | EGeoCoord::Eastern));
	CHECK(bA.getHemisphere() == (EGeoCoord::Northern | EGeoCoord::Eastern));
	CHECK(bB.getHemisphere() == (EGeoCoord::Northern | EGeoCoord::Eastern));
	CHECK(cA.getHemisphere() == (EGeoCoord::Northern | EGeoCoord::Eastern));
	CHECK(cB.getHemisphere() == (EGeoCoord::Southern | EGeoCoord::Western));
	CHECK(dA.getHemisphere() == (EGeoCoord::Northern | EGeoCoord::Eastern));
	CHECK(dB.getHemisphere() == (EGeoCoord::Southern | EGeoCoord::Western));

	CHECK(aA.inSameHemisphere(cA));
	CHECK(!aA.inSameHemisphere(cB));
	CHECK(cB.inSameHemisphere(dB));
	CHECK(!dB.inSameHemisphere(bA));

	// Test getDistanceTo

	euler::BigDecimal distance;
	long double distanceDouble;

	aA.getDistanceTo(distance.get(), aB);
	distanceDouble = mpfr_get_ld(distance.get(), MPFR_RNDN);
	CHECK((distanceDouble / 1000.0 - 844.0) < 1.0);

	bA.getDistanceTo(distance.get(), bB);
	distanceDouble = mpfr_get_ld(distance.get(), MPFR_RNDN);
	CHECK((distanceDouble / 1000.0 - 6610.0) < 1.0);

	cA.getDistanceTo(distance.get(), cB);
	distanceDouble = mpfr_get_ld(distance.get(), MPFR_RNDN);
	CHECK((distanceDouble / 1000.0 - 19994.0) < 1.0);

	dA.getDistanceTo(distance.get(), dB);
	distanceDouble = mpfr_get_ld(distance.get(), MPFR_RNDN);
	CHECK((distanceDouble / 1000.0 - 19262.0) < 1.0);

	eA.getDistanceTo(distance.get(), eB);
	distanceDouble = mpfr_get_ld(distance.get(), MPFR_RNDN);
	CHECK((distanceDouble / 1000.0 - 19942.0) < 1.0);

	// Test assignment and equivalence operators.

	CHECK(!(bA == aA));
	bA = aA;
	CHECK(bA == aA);

	CHECK(!(cA == cB));
	CHECK(!(dA == dB));
	dA = cA = cB;
	CHECK(dA == cA);
	CHECK(cA == cB);
}

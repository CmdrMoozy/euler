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

#ifndef INCLUDE_LIBEULER_TYPES_FRACTION_H
#define INCLUDE_LIBEULER_TYPES_FRACTION_H

#include <cstddef>
#include <cstdint>

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

#include "libeuler/EExceptions.h"

// Forward declarations.
class EFraction;
std::ostream &operator<<(std::ostream &out, const EFraction &f);

/*!
 * \brief This class represents a numerator/denominator fraction.
 *
 * It is more accurate than doing everything with floating-point numbers, and provides
 * extra functionality like reducing and whatnot.
 */
class EFraction
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif

		static bool isReducedProperFraction(uint64_t n, uint64_t d);

		EFraction(uint64_t n = 0, uint64_t d = 1) throw(EValueRangeException &);
		EFraction(const EFraction &o);
		virtual ~EFraction();

		EFraction &operator=(const EFraction &o);

		bool operator==(const EFraction &o) const;
		bool operator>(const EFraction &o) const;
		bool operator<(const EFraction &o) const;
		bool operator>=(const EFraction &o) const;
		bool operator<=(const EFraction &o) const;

		EFraction &operator+=(const EFraction &o);
		EFraction &operator-=(const EFraction &o);

		uint64_t getNumerator() const;
		void setNumerator(uint64_t n);
		uint64_t getDenominator() const;
		void setDenominator(uint64_t d) throw(EValueRangeException &);

		void mediant(const EFraction &o);

		bool canReduce() const;
		bool reduce();

		double getDecimalValue() const;
		double toDouble() const;
		mpf_class toBigDouble(uint32_t p = 100) const;

	private:
		uint64_t numerator;
		uint64_t denominator;
};

#endif

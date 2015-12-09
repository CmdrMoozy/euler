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

#ifndef INCLUDE_LIBEULER_MATH_FACTORIZATION_H
#define INCLUDE_LIBEULER_MATH_FACTORIZATION_H

#include <map>
#include <set>
#include <cstdint>

// Forward Declarations
class EPrimeSieve;

/*!
 * \brief This class facilitates the factoring or numbers.
 *
 * It provides a way to get the prime factorization, or the TOTAL factorization,
 * along with some other utility functions.
 */
class EFactorization
{
public:
	EFactorization(uint32_t n = 0);
	virtual ~EFactorization();

	uint32_t getNumber();
	void setNumber(uint32_t n);

	std::size_t getPrimeFactorsCount();
	std::size_t getAllFactorsCount();
	const std::map<uint32_t, uint32_t> &getPrimeFactors();

	const std::set<uint32_t> &getAllFactors();

private:
	EPrimeSieve *sieve;
	uint32_t number;
	bool primesGenerated, allGenerated;
	std::map<uint32_t, uint32_t> primeFactors;
	std::set<uint32_t> allFactors;

	void generatePrimeFactors();
	void generateAllFactors();
};

#endif

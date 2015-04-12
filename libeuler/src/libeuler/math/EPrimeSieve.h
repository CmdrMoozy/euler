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

#ifndef INCLUDE_LIBEULER_MATH_PRIME_SIEVE_H
#define INCLUDE_LIBEULER_MATH_PRIME_SIEVE_H

#include <set>
#include <cstdint>

/*!
 * \brief This class is a sieve that generates prime numbers.
 *
 * It is a very simple, and not very optimized implementation of the Sieve of Atkin.
 */
class EPrimeSieve
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
	
		EPrimeSieve(uint32_t l = 0);
		virtual ~EPrimeSieve();
	
		uint32_t getLimit() const;
		void setLimit(uint32_t nL);
	
		uint32_t getSize() const;
	
		bool contains(uint32_t i) const;
		bool erase(uint32_t i);
	
		std::set<uint32_t>::iterator find(uint32_t n);
	
		std::set<uint32_t>::iterator begin();
		std::set<uint32_t>::const_iterator begin() const;
		std::set<uint32_t>::iterator end();
		std::set<uint32_t>::const_iterator end() const;
		std::set<uint32_t>::reverse_iterator rbegin();
		std::set<uint32_t>::const_reverse_iterator rbegin() const;
		std::set<uint32_t>::reverse_iterator rend();
		std::set<uint32_t>::const_reverse_iterator rend() const;
		
		std::set<uint32_t>::iterator lowerBound(const uint32_t &n) const;
		std::set<uint32_t>::iterator upperBound(const uint32_t &n) const;
	
	protected:
		virtual void generatePrimes();
	
	private:
		uint32_t limit;
		std::set<uint32_t> primes;
};


#endif

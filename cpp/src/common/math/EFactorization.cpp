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

#include "EFactorization.h"

#include "common/math/EPrimeSieve.h"
#include "common/util/EArrayUtilities.h"

/*!
 * This is our default constructor, which initializes a new EFactorization
 * object to factor the given number.
 *
 * \param n The number this object will be factoring.
 */
EFactorization::EFactorization(uint32_t n)
{
	sieve = new EPrimeSieve(1000000);
	setNumber(n);
}

/*!
 * This is our default destructor, which cleans up & destroys our object.
 */
EFactorization::~EFactorization()
{
	delete sieve;
}

/*!
 * This function returns the number our object is operating on.
 *
 * \return The number we are factoring.
 */
uint32_t EFactorization::getNumber()
{
	return number;
}

/*!
 * This function sets the number our object will be operating on, possibly
 * resizing our object's prime number sieve if need be.
 *
 * \param n The new number to be factored.
 */
void EFactorization::setNumber(uint32_t n)
{
	number = n;

	if(n >= sieve->getLimit())
		sieve->setLimit(sieve->getLimit() * 2);

	primesGenerated = allGenerated = false;
	primeFactors.clear();
	allFactors.clear();
}

/*!
 * This function returns the number of prime factors our number has.
 *
 * \return The number of prime factors of our number.
 */
std::size_t EFactorization::getPrimeFactorsCount()
{
	if(!primesGenerated)
		generatePrimeFactors();

	return primeFactors.size();
}

/*!
 * This function returns the NUMBER of factors our number has (in total),
 * without actually generating the list of them. This function will, however,
 * generate only the PRIME factors if they have not been generated already.
 *
 * \return The number of ALL factors our number has.
 */
std::size_t EFactorization::getAllFactorsCount()
{
	std::map<uint32_t, uint32_t>::iterator it;
	std::size_t result = 1;

	if(!primesGenerated)
		generatePrimeFactors();

	if(number == 1)
		return 1; // 1 is a factor of itself, but not a PRIME factor.
	else if(getPrimeFactorsCount() == 0)
		return 0; // Otherwise, no prime factors means no factors.

	/*
	 * If you factor a number into its prime power factors, then the total
	 * number of factors is found by adding one to all the exponents and
	 * multiplying those results together.
	 */

	for(it = primeFactors.begin(); it != primeFactors.end(); ++it)
		result *= (it->second + 1);

	return result;
}

/*!
 * This function generates our list of primes factors if it hasn't already been
 * generated, and then returns a const reference to the list. Note that the map
 * returns maps prime to its exponent.
 *
 * \return A list of all of our number's prime factors.
 */
const std::map<uint32_t, uint32_t> &EFactorization::getPrimeFactors()
{
	if(!primesGenerated)
		generatePrimeFactors();

	return primeFactors;
}

/*!
 * This function generates our list of all factors if it hasn't already been
 * generated, and then returns a const reference to the list.
 *
 * \return A list of all of our number's factors.
 */
const std::set<uint32_t> &EFactorization::getAllFactors()
{
	if(!allGenerated)
		generateAllFactors();

	return allFactors;
}

/*!
 * This is our behind-the-scenes function that generates our number's prime
 * factors.
 */
void EFactorization::generatePrimeFactors()
{
	uint32_t n = number, c;
	std::set<uint32_t>::iterator sieveIt;
	std::map<uint32_t, uint32_t>::iterator resultIt;

	primeFactors.clear();

	// 1 or 0 can't be prime-factored.
	if(number < 2)
	{
		primesGenerated = true;
		primeFactors.clear();
		return;
	}

	// If this number is prime, then it is its own prime factor.
	if(sieve->contains(number))
	{
		primeFactors.insert(std::pair<uint32_t, uint32_t>(number, 1));
		primesGenerated = true;
		return;
	}

	// Factor our number.
	resultIt = primeFactors.end();
	for(sieveIt = sieve->begin(); n > 1; sieveIt++)
	{
		c = 0;
		while((n % (*sieveIt)) == 0)
		{
			n /= (*sieveIt);
			c++;
		}

		if(c > 0)
			primeFactors.insert(
			        std::pair<uint32_t, uint32_t>((*sieveIt), c));
	}

	primesGenerated = true;
}

/*!
 * This is our behind-the-scenes function that generates all of our factors. If
 * the prime factors have not been generated yet, then they will be generated
 * first, and then expanded into all of the factors.
 */
void EFactorization::generateAllFactors()
{
	std::multiset<uint32_t> primesList;
	uint32_t i;
	std::multiset<std::multiset<uint32_t>> primesPS;

	// 0 can't be factored.
	if(number == 0)
	{
		allGenerated = true;
		allFactors.clear();
		return;
	}

	// If our primes haven't been generated yet, generate them.
	if(!primesGenerated)
		generatePrimeFactors();

	// Generate a list of all factors, including "duplicates" for powers.
	for(std::map<uint32_t, uint32_t>::iterator it = primeFactors.begin();
	    it != primeFactors.end(); ++it)
		for(i = 0; i < it->second; ++i)
			primesList.insert(it->first);

	// Multiply out all the different combinations to get our list of all
	// factors.
	primesPS = EArrayUtilities::getPowerSet<uint32_t>(primesList);
	for(std::multiset<std::multiset<uint32_t>>::iterator it =
	            primesPS.begin();
	    it != primesPS.end(); ++it)
	{
		i = 1;
		for(std::multiset<uint32_t>::iterator sit = it->begin();
		    sit != it->end(); ++sit)
			i *= (*sit);

		allFactors.insert(i);
	}

	allGenerated = true;
}

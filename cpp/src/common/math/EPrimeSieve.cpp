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

#include "EPrimeSieve.h"

#include "common/EDefines.h"
#include "common/math/Math.hpp"
#include "common/structs/BitArray.hpp"

/*!
 * This is our default constructor, which initializes a new EPrimeSieve object
 * with
 * a limit of 0.
 */
EPrimeSieve::EPrimeSieve(uint32_t l)
{
	setLimit(l);
}

/*!
 * This is our default destructor, which cleans up & destroys our object.
 */
EPrimeSieve::~EPrimeSieve()
{
}

/*!
 * This returns our sieve's current upper limit for prime generation.
 *
 * \return Our number limit.
 */
uint32_t EPrimeSieve::getLimit() const
{
	return limit;
}

/*!
 * This function sets the limit up to which primes will be generated, discarding
 *previous
 * data and re-generating all of the appropriate primes.
 *
 * \param nL The new number limit.
 */
void EPrimeSieve::setLimit(uint32_t nL)
{
	limit = nL;
	generatePrimes();
}

/*!
 * This function returns the size of our sieve, or in other words, the number of
 *prime numbers
 * it currently contains.
 *
 * \return The number of primes in our sieve.
 */
uint32_t EPrimeSieve::getSize() const
{
	return static_cast<uint32_t>(primes.size());
}

/*!
 * This function tests whether our prime number sieve contains the given number
 *(i.e., whether
 * or not it is prime, assuming it is <= our number limit).
 *
 * \param i The number to search for.
 * \return True if our sieve contains the number, or false otherwise.
 */
bool EPrimeSieve::contains(uint32_t i) const
{
	return (primes.find(i) != primes.end());
}

/*!
 * This function erases the given value from our prime sieve, if it is present.
 *
 * \param i The value to erase.
 * \return True if the value was erased, or false if it was not found.
 */
bool EPrimeSieve::erase(uint32_t i)
{
	return (primes.erase(i) > 0);
}

/*!
 * This function returns an iterator to the given number in our prime sieve, or
 * set::end if the item is not in our sieve.
 *
 * \param n The value to search for.
 * \return An iterator to the number in the sieve, of set::end if it is not
 *found.
 */
std::set<uint32_t>::const_iterator EPrimeSieve::find(uint32_t n) const
{
	return primes.find(n);
}

/*!
 * Returns an iterator to the beginning of our list of primes.
 *
 * \return An iterator to the beginning of our list.
 */
std::set<uint32_t>::iterator EPrimeSieve::begin()
{
	return primes.begin();
}

/*!
 * Returns a const iterator to the beginning of our list of primes.
 *
 * \return An iterator to the beginning of our list.
 */
std::set<uint32_t>::const_iterator EPrimeSieve::begin() const
{
	return primes.begin();
}

/*!
 * Returns an iterator to the "past-the-end" element in our list of primes.
 *
 * \return An iterator to the element past the end of our list.
 */
std::set<uint32_t>::iterator EPrimeSieve::end()
{
	return primes.end();
}

/*!
 * Returns a const iterator to the "past-the-end" element in our list of primes.
 *
 * \return An iterator to the element past the end of our list.
 */
std::set<uint32_t>::const_iterator EPrimeSieve::end() const
{
	return primes.end();
}

/*!
 * Returns an iterator to the beginning of our list in reverse order.
 *
 * \return An iterator the reverse beginning of our list.
 */
std::set<uint32_t>::reverse_iterator EPrimeSieve::rbegin()
{
	return primes.rbegin();
}

/*!
 * Returns a const iterator to the beginning of our list in reverse order.
 *
 * \return An iterator the reverse beginning of our list.
 */
std::set<uint32_t>::const_reverse_iterator EPrimeSieve::rbegin() const
{
	return primes.rbegin();
}

/*!
 * Returns an iterator to the "before-the-first" element in our list of primes,
 *which is
 * the "end" of our list in reverse order.
 *
 * \return An iterator to the element before the beginning of our list.
 */
std::set<uint32_t>::reverse_iterator EPrimeSieve::rend()
{
	return primes.rend();
}

/*!
 * Returns a const iterator to the "before-the-first" element in our list of
 *primes, which is
 * the "end" of our list in reverse order.
 *
 * \return An iterator to the element before the beginning of our list.
 */
std::set<uint32_t>::const_reverse_iterator EPrimeSieve::rend() const
{
	return primes.rend();
}

/*!
 * Returns an iterator to the first prime number that is greater than or equal
 *to n.
 *
 * \param n The target number.
 * \return An iterator to the first prime >= n.
 */
std::set<uint32_t>::iterator EPrimeSieve::lowerBound(const uint32_t &n) const
{
	return primes.lower_bound(n);
}

/*!
 * This is our behind-the-scenes worker function, which generates all of the
 * prime numbers >= limit,
 * and then inserts them into our binary search tree for the user to access.
 */
void EPrimeSieve::generatePrimes()
{
	euler::structs::BitArray isPrime(limit + 1);
	uint64_t root = euler::math::isqrt(limit);
	uint32_t x, y, n, s, k;
	uint32_t a, b, c;

	try
	{
		for(x = 1; x <= root; ++x)
		{
			a = (x * x);
			b = 3 * a;
			a *= 4;

			for(y = 1; y <= root; ++y)
			{
				c = (y * y);

				n = a + c;
				if((n <= limit) &&
				   (((n % 12) == 1) || ((n % 12) == 5)))
					isPrime.flip(n);

				n = b + c;
				if((n <= limit) && ((n % 12) == 7))
					isPrime.flip(n);

				n = b - c;
				if((x > y) && (n <= limit) && ((n % 12) == 11))
					isPrime.flip(n);
			}
		}

		for(n = 5; n <= root; n += 2)
		{
			if(isPrime.test(n))
			{
				s = n * n;
				for(k = s; k <= limit; k += s)
					isPrime.set(k, false);
			}
		}

		primes.insert(2);
		primes.insert(3);
		for(n = 5; n <= limit; n += 2)
		{
			if(isPrime.at(n))
				primes.insert(n);
		}
	}
	catch(EOutOfBoundsException &)
	{
#ifdef EULER_DEBUG
		EDIE_LOGIC(std::runtime_error("Got EOutOfBoundsException."))
#endif
	}
}
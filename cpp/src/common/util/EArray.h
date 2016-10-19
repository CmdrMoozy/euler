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

#ifndef INCLUDE_LIBEULER_UTIL_ARRAY_H
#define INCLUDE_LIBEULER_UTIL_ARRAY_H

#include <cstdlib>

#include "common/EDefines.h"
#include "common/util/EArrayUtilities.h"

/*!
 * \brief This class implements the functions in EArrayUtilities.
 *
 * It allows the functions in that class to be used as an object, rather than
 *just
 * as standalone function calls.
 */
template <typename T> class EArray
{
public:
	/*!
	 * This is our default constructor, which creates a new EArray of the
	 *given size, and optionally
	 * using the given array of existing data.
	 *
	 * \param s The initial size of our array.
	 * \param a The initial data of our array.
	 */
	EArray(std::size_t s = 0, const T *a = NULL) : array(NULL), size(0)
	{
		if(a != NULL)
		{
			array = EArrayUtilities::copy<T>(a, s);
			size = s;
		}
		else
		{
			setSize(s, false);
		}
	}

	/*!
	 * This is our copy constructor, which initializes a new EArray given an
	 *existing other EArray.
	 *
	 * \param o The other object to make ourself equal to.
	 */
	EArray(const EArray<T> &o) : array(NULL), size(0)
	{
		(*this) = o;
	}

	/*!
	 * This is our default destructor, which just frees up the memory used
	 * by our internal
	 * array.
	 */
	virtual ~EArray()
	{
		if(array != NULL)
			delete[] array;
	}

	/*!
	 * This is our assignment operator, which changes our value to be equal
	 *to that of the given other
	 * array object.
	 *
	 * \param o The other array to make ourself equal to.
	 * \return A reference to this, so the operator can be chained.
	 */
	EArray &operator=(const EArray<T> &o)
	{
		if(array != NULL)
			delete[] array;

		array = EArrayUtilities::copy<T>(o.array, o.getSize());
		size = o.getSize();

		return (*this);
	}

	/*!
	 * This is our equivalence operator, which tests if our value is equal
	 *to that of the given other
	 * object. Note that this operator is equivalent to calling isEqualTo().
	 *
	 * \param o The other object to compare ourself to.
	 * \return True if our objects are equal, or false otherwise.
	 */
	bool operator==(const EArray<T> &o) const
	{
		return isEqualTo(o);
	}

	bool operator!=(const EArray<T> &o) const
	{
		return !(*this == o);
	}

	/*!
	 * This returns the current size (i.e., capacity) of our array object.
	 *
	 * \return The current size of our object.
	 */
	std::size_t getSize() const
	{
		return size;
	}

	/*!
	 * This function resizes our array object, optionally preserving
	 *existing data.
	 *
	 * \param s The new size of our object.
	 * \param p True if you want data preserved, or false otherwise.
	 */
	void setSize(std::size_t s, bool p = true)
	{
		EArrayUtilities::resize<T>(array, getSize(), s, p);
		size = s;
	}

	T const *get() const
	{
		return array;
	}

	/*!
	 * This function just returns a non-const reference to the element at
	 *the given index in our
	 * array.
	 *
	 * \param i The index of the desired element.
	 * \return A reference to the element at the given index.
	 */
	T &at(std::size_t i) const
	{
		if(i >= getSize())
		{
			throw EOutOfBoundsException(
			        "Array index is out-of-bounds.");
		}

		return array[i];
	}

	/*!
	 * This function sets the value of the element at the given index in our
	 *array. Note that the same
	 * thing can be achieved with at(), since it returns a reference.
	 *
	 * \param i The index of the desired element.
	 * \param v The new value for the given element.
	 */
	void set(std::size_t i, const T &v)
	{
		at(i) = v;
	}

	/*!
	 * This function does a linear search for the given value. Note that
	 *binarySearch() is MUCH faster,
	 * but requires that our array is already sorted in ascending order.
	 *
	 * \param n The value we are searching for.
	 * \return The first index of the given value, or -1 if it isn't found.
	 */
	int search(const T &n) const
	{
		return EArrayUtilities::search<T>(array, getSize(), n);
	}

	/*!
	 * This function does a binary search for the given value. This function
	 *is much faster than search(),
	 * but requires that our array is sorted in ascending order. If the
	 *array isn't sorted, then the
	 * behavior of this function is undefined.
	 *
	 * \param n The value we are searching for.
	 * \param l The left-most index to include in the search (inclusive).
	 * \param r The right-most index to include in the search (inclusive).
	 * \return The index of the given value, or -1 if it isn't found.
	 */
	int binarySearch(const T &n, int l = 0, int r = -1) const
	{
		if(getSize() == 0)
			return -1;

		l = (l < 0) ? 0 : l;
		r = (r == -1) ? static_cast<int>(getSize() - 1) : r;
		r = (r >= static_cast<int>(getSize()))
		            ? static_cast<int>(getSize() - 1)
		            : r;

		if(r < l)
		{
			int hold = l;
			l = r;
			r = hold;
		}

		return EArrayUtilities::binarySearch<T>(array, l, r, n);
	}

	/*!
	 * This function sorts our array in ascending order.
	 */
	void sortAscending()
	{
		EArrayUtilities::sortAscending<T>(array, getSize());
	}

	/*!
	 * This function sorts our array in descending order.
	 */
	void sortDescending()
	{
		EArrayUtilities::sortDescending<T>(array, getSize());
	}

	/*!
	 * This function just tests if our array is equal to the given other
	 *array. Note that this
	 * does the same thing as our "==" operator.
	 *
	 * \param o The other array to compare ourself to.
	 * \return True if our arrays are equal, or false otherwise.
	 */
	bool isEqualTo(const EArray<T> &o) const
	{
		if(getSize() == o.getSize())
			return EArrayUtilities::equal<T>(array, o.array,
			                                 getSize());
		else
			return false;
	}

	/*!
	 * This function tests if our array is equal to the given other array,
	 *ignoring all sorting
	 * of the elements.
	 *
	 * \param o The other array to compare ourself to.
	 * \return True if our arrays are equal (ignoring sorting), or false
	 *otherwise.
	 */
	bool isEqualToUnsorted(const EArray<T> &o) const
	{
		if(getSize() == o.getSize())
			return EArrayUtilities::equalUnsorted<T>(array, o.array,
			                                         getSize());
		else
			return false;
	}

	/*!
	 * This function tests whether or not our array contains duplicate
	 *elements.
	 *
	 * \return True if our array contains duplicates, or false otherwise.
	 */
	bool isUnique() const
	{
		return EArrayUtilities::isUnique<T>(array, getSize());
	}

	/*!
	 * This function removes all of the duplicate elements in our array.
	 */
	void makeUnique()
	{
		size = EArrayUtilities::makeUnique<T>(array, getSize());
	}

	/*!
	 * This function reverses a section of our array between the two given
	 *indices (inclusive),
	 * or the entire array if no indices are given.
	 *
	 * \param l The left-most index in our reversal (inclusive).
	 * \param r The right-most index in our reversal (inclusive).
	 */
	void reverse(int l = 0, int r = -1)
	{
		if(getSize() == 0)
			return;
		if((l < 0) || (l >= static_cast<int>(getSize())))
			l = 0;
		if(r == -1)
			r = static_cast<int>(getSize() - 1);
		if(r >= static_cast<int>(getSize()))
			r = static_cast<int>(getSize() - 1);

		if(r < l)
		{
			int hold = l;
			l = r;
			r = hold;
		}

		EArrayUtilities::reverse<T>(array, static_cast<std::size_t>(l),
		                            static_cast<std::size_t>(r));
	}

	/*!
	 * This is an implementation of Knuth's "Algorithm L," which permutates
	 *a given array of elements
	 * in lexicographic order. Note that because they are in lexicographic
	 *order, an array sorted in
	 * ascending order is the "first" permutation.
	 *
	 * More information:
	 *     http://en.wikipedia.org/wiki/Permutation#Systematic_generation_of_all_permutations
	 *     http://blog.bjrn.se/2008/04/lexicographic-permutations-using.html
	 *
	 * \return True if there are more permutations, or false if this is the
	 *last one.
	 */
	bool permutate()
	{
		return EArrayUtilities::permutate<T>(array, getSize());
	}

	/*!
	 * This function is equivalent to permutate(), except it generates
	 *permutations in REVERSE lexicographic
	 * order, instead of forwards. Accordingly, our "first" permutation is
	 *when our list is sorted in
	 * descending order.
	 *
	 * \return True if there are more permutations, or false if this is the
	 *last one.
	 */
	bool reversePermutate()
	{
		return EArrayUtilities::reversePermutate<T>(array, getSize());
	}

private:
	T *array;
	std::size_t size;
};

#endif

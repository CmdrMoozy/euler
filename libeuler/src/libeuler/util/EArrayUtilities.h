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

#ifndef INCLUDE_LIBEULER_UTIL_ARRAY_UTILITIES_H
#define INCLUDE_LIBEULER_UTIL_ARRAY_UTILITIES_H

#include <set>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <iterator>

#ifdef LIBEULER_DEBUG
#include <iostream>
#include <cmath>

#include "libeuler/EDefines.h"
#endif

/*!
 * \brief This class provides utility functions for arrays.
 */
class EArrayUtilities
{
public:
#ifdef LIBEULER_DEBUG
	/*!
	 * This function implements our test suite for this class. It uses
	 * non-abort()'ing
	 * assertions, and merely prints the result to stdout.
	 */
	static void doTestSuite()
	{
		int *a, *b;
		a = b = NULL;
		bool success;

		std::cout << "\tTesting 'EArrayUtilities'...\t\t";
		try
		{
			success = true;

			bool rVal;
			int i;

			// getPowerSet

			std::set<int> os;
			os.insert(0);
			os.insert(1);
			os.insert(2);
			os.insert(3);
			os.insert(4);
			os.insert(5);
			os.insert(6);
			os.insert(7);
			os.insert(8);
			os.insert(9);

			int psc = static_cast<int>(
			        pow(2.0, static_cast<double>(os.size())));
			std::set<std::set<int>> ps =
			        EArrayUtilities::getPowerSet<int>(os);

			EASSERT(static_cast<int>(ps.size()) == psc)

			// copy + equal + equalUnsorted

			a = new int[10];

			a[0] = 34;
			a[1] = 2345;
			a[2] = 112;
			a[3] = 123;
			a[4] = 8539;
			a[5] = 90123;
			a[6] = 234;
			a[7] = 467;
			a[8] = 168;
			a[9] = 19233;

			b = EArrayUtilities::copy<int>(a, 10);

			for(i = 0; i < 10; ++i)
				EASSERT(a[i] == b[i])

			rVal = EArrayUtilities::equal<int>(a, b, 10);
			EASSERT(rVal)

			std::random_shuffle(&a[0], &a[10]);
			std::random_shuffle(&b[0], &b[10]);

			rVal = EArrayUtilities::equalUnsorted<int>(a, b, 10);
			EASSERT(rVal)

			delete[] a;
			delete[] b;
			a = b = NULL;

			// resize

			a = new int[5];
			a[0] = 34;
			a[1] = 2345;
			a[2] = 112;
			a[3] = 123;
			a[4] = 8539;

			EArrayUtilities::resize<int>(a, 5, 10, true);
			EASSERT(a[0] == 34)
			EASSERT(a[1] == 2345)
			EASSERT(a[2] == 112)
			EASSERT(a[3] == 123)
			EASSERT(a[4] == 8539)

			EArrayUtilities::resize<int>(a, 10, 5, false);
			for(i = 0; i < 5; ++i)
				EASSERT(a[i] == 0)

			delete[] a;
			a = NULL;

			// sortAscending + sortDescending + reverse

			a = new int[10];
			a[0] = 34;
			a[1] = 2345;
			a[2] = 112;
			a[3] = 123;
			a[4] = 8539;
			a[5] = 90123;
			a[6] = 234;
			a[7] = 467;
			a[8] = 168;
			a[9] = 19233;

			EArrayUtilities::sortAscending<int>(a, 10);
			for(i = 0; i < (10 - 1); ++i)
				EASSERT(a[i] <= a[i + 1])

			b = EArrayUtilities::copy<int>(a, 10);
			EArrayUtilities::sortDescending<int>(b, 10);

			for(i = 0; i < (10 - 1); ++i)
				EASSERT(b[i] >= b[i + 1])

			EArrayUtilities::reverse<int>(b, 0, 9);
			for(i = 0; i < 10; ++i)
				EASSERT(a[i] == b[i])

			delete[] a;
			delete[] b;
			a = b = NULL;

			// search + binarySearch

			a = new int[10];
			a[0] = 34;
			a[1] = 2345;
			a[2] = 112;
			a[3] = 123;
			a[4] = 8539;
			a[5] = 90123;
			a[6] = 234;
			a[7] = 467;
			a[8] = 168;
			a[9] = 19233;

			b = EArrayUtilities::copy<int>(a, 10);
			EArrayUtilities::sortAscending<int>(b, 10);

			for(i = 0; i < 9; ++i)
			{
				int aI, bI;

				aI = EArrayUtilities::search<int>(a, 10, a[i]);
				bI = EArrayUtilities::binarySearch<int>(b, 0, 9,
				                                        b[i]);

				EASSERT(aI == i)
				EASSERT(bI == i)

				aI = EArrayUtilities::search<int>(a, 10, i);
				bI = EArrayUtilities::binarySearch<int>(b, 0, 9,
				                                        i);

				EASSERT(aI == -1)
				EASSERT(bI == -1)
			}

			delete[] a;
			delete[] b;
			a = b = NULL;

			// isUnique + makeUnique

			a = new int[10];

			a[0] = -168;
			a[1] = 2345;
			a[2] = 112;
			a[3] = 234;
			a[4] = 8539;
			a[5] = 90123;
			a[6] = 234;
			a[7] = 467;
			a[8] = 168;
			a[9] = 19233;

			rVal = EArrayUtilities::isUnique<int>(a, 10);
			EASSERT(!rVal)

			i = EArrayUtilities::makeUnique<int>(a, 10);
			rVal = EArrayUtilities::isUnique<int>(a, i);
			EASSERT(rVal)
			EASSERT(i == 9)

			delete[] a;
			a = NULL;

			// permutate + reversePermutate

			a = new int[3];
			a[0] = 3;
			a[1] = 1;
			a[2] = 2;

			EArrayUtilities::sortAscending<int>(a, 3);
			b = EArrayUtilities::copy<int>(a, 3);

			EArrayUtilities::permutate<int>(b, 3);
			EArrayUtilities::reversePermutate<int>(b, 3);

			rVal = EArrayUtilities::equal<int>(a, b, 3);
			EASSERT(rVal)

			EArrayUtilities::permutate<int>(a, 3);
			EASSERT(a[0] == 1)
			EASSERT(a[1] == 3)
			EASSERT(a[2] == 2)

			delete[] a;
			delete[] b;
			a = b = NULL;
		}
		catch(EAssertionException &e)
		{
			ELUNUSED(e)

			if(a != NULL)
				delete[] a;
			if(b != NULL)
				delete[] b;
			a = b = NULL;

			success = false;
		}

		// Print out our results.
		if(success)
			std::cout << "[ OK ]\n";
		else
			std::cout << "[FAIL]\n";

		if(a != NULL)
			delete[] a;
		if(b != NULL)
			delete[] b;
		a = b = NULL;
	}
#endif

	template <typename T>
	static std::multiset<std::multiset<T>>
	getPowerSet(const std::multiset<T> &s)
	{
		std::multiset<std::multiset<T>> result;
		std::vector<typename std::multiset<T>::const_iterator> elements;
		std::multiset<T> tmp;
		typename std::multiset<T>::iterator sit;

		struct operators
		{
			static T dereference(
			        typename std::multiset<T>::const_iterator it)
			{
				return (*it);
			}
		};

		do
		{
			tmp.clear();
			std::transform(elements.begin(), elements.end(),
			               std::inserter(tmp, tmp.end()),
			               operators::dereference);

			result.insert(tmp);

			if(!elements.empty() && (++elements.back() == s.end()))
			{
				elements.pop_back();
			}
			else
			{
				if(elements.empty())
				{
					sit = s.begin();
				}
				else
				{
					sit = elements.back();
					sit++;
				}

				for(; sit != s.end(); sit++)
					elements.push_back(sit);
			}
		} while(!elements.empty());

		return result;
	}

	/*!
	 * This function calculates and returns the power set of the given set
	 *s. That is, the set of all
	 * subsets of s -- which will be 2^|s| in size.
	 *
	 * This implementation is courtesy of a pretty straight-forward
	 *implementation provided on RosettaCode:
	 *     http://rosettacode.org/wiki/Power_Set#Non-recursive_version
	 *
	 * \param s The set whose power set we will calculate.
	 * \return P(s) -- the power set of s.
	 */
	template <typename T>
	static std::set<std::set<T>> getPowerSet(const std::set<T> &s)
	{
		std::set<std::set<T>> result;
		std::vector<typename std::set<T>::const_iterator> elements;
		std::set<T> tmp;
		typename std::set<T>::iterator sit;

		struct operators
		{
			static T
			dereference(typename std::set<T>::const_iterator it)
			{
				return (*it);
			}
		};

		do
		{
			tmp.clear();
			std::transform(elements.begin(), elements.end(),
			               std::inserter(tmp, tmp.end()),
			               operators::dereference);

			result.insert(tmp);

			if(!elements.empty() && (++elements.back() == s.end()))
			{
				elements.pop_back();
			}
			else
			{
				if(elements.empty())
				{
					sit = s.begin();
				}
				else
				{
					sit = elements.back();
					sit++;
				}

				for(; sit != s.end(); sit++)
					elements.push_back(sit);
			}
		} while(!elements.empty());

		return result;
	}

	/*!
	 * This function just copies the given array, returning a pointer to a
	 *brand-new identical array.
	 *
	 * \param a The original array.
	 * \param l The length of the original array.
	 * \return Your new, duplicated array.
	 */
	template <typename T> static T *copy(const T *a, int l)
	{
		int i;

		T *n = new T[l];

		for(i = 0; i < l; ++i)
			n[i] = a[i];

		return n;
	}

	/*!
	 * This function tests whether or not the two arrays given are exactly
	 *equal, including ordering.
	 * Note that the length of both arrays is assumed to be the same, since
	 *arrays of different sizes
	 * are obviously not equal.
	 *
	 * \param a The first array.
	 * \param b The second array.
	 * \param l The length of both arrays.
	 * \return True if the arrays are equal, or false otherwise.
	 */
	template <typename T> static bool equal(const T *a, const T *b, int l)
	{
		int i;

		// Handle NULL arrays.
		if((a == NULL) && (b == NULL))
			return true;
		else if((a == NULL) || (b == NULL))
			return false;

		// Just check each element in order until we find one that isn't
		// equal.
		for(i = 0; i < l; ++i)
			if(a[i] != b[i])
				return false;

		return true;
	}

	/*!
	 * This function tests whether or not the two arrays are equal, ignoring
	 *sorting. Note that this function
	 * is somewhat slow, since it achieves this by simply sorting the arrays
	 *and then namking the comparison.
	 * Note that the length of both arrays is assumed to be the same, since
	 *arrays of different sizes
	 * are obviously not equal.
	 *
	 * \param a The first array.
	 * \param b The second array.
	 * \param l The length of both arrays.
	 */
	template <typename T>
	static bool equalUnsorted(const T *a, const T *b, int l)
	{
		bool r;
		T *aC, *bC;

		// Handle NULL arrays.
		if((a == NULL) && (b == NULL))
			return true;
		else if((a == NULL) || (b == NULL))
			return false;

		aC = copy<T>(a, l);
		bC = copy<T>(b, l);

		sortAscending<T>(aC, l);
		sortAscending<T>(bC, l);

		r = equal<T>(aC, bC, l);

		delete[] aC;
		delete[] bC;

		return r;
	}

	/*!
	 * This function resizes the given array to a given new size, optionally
	 *preserving existing data.
	 *
	 * \param a The array to resize.
	 * \param l The original length of the array.
	 * \param nL The new length of the array.
	 * \param p Whether or not to preserve existing data.
	 */
	template <typename T>
	static void resize(T *&a, int l, int nL, bool p = true)
	{
		int i;

		nL = (nL < 0) ? 0 : nL;
		if(l == nL)
			return;

		T *n = new T[nL];

		for(i = 0; i < nL; ++i)
		{
			if(p && (a != NULL) && (i < l) && (i < nL))
				n[i] = a[i];
			else
				n[i] = T();
		}

		if(a != NULL)
			delete[] a;
		a = n;
	}

	/*!
	 * This function sorts the given array of given length in ascending
	 *order.
	 *
	 * \param a The array to sort.
	 * \param l The length of the array to sort.
	 */
	template <typename T> static void sortAscending(T *a, int l)
	{
		quicksortAsc<T>(a, 0, l - 1);
	}

	/*!
	 * This function sorts the given array of given length in descending
	 *order.
	 *
	 * \param a The array to sort.
	 * \param l The length of the array to sort.
	 */
	template <typename T> static void sortDescending(T *a, int l)
	{
		quicksortDesc<T>(a, 0, l - 1);
	}

	/*!
	 * This function reverses the given array from the index l to the index
	 *r (inclusive).
	 *
	 * \param a The array to reverse.
	 * \param l The left index.
	 * \param r The right index.
	 */
	template <typename T> static void reverse(T *a, int l, int r)
	{
		T hold;
		while(l < r)
		{
			hold = a[l];
			a[l++] = a[r];
			a[r--] = hold;
		}
	}

	/*!
	 * This function just does a linear search for the given needle,
	 *returning the first
	 * occurrence of it.
	 *
	 * \param a The array to search.
	 * \param l The length of the array.
	 * \param n The needle we are searching for.
	 * \return The index of the first instance of the needle, or -1 if it
	 *wasn't found.
	 */
	template <typename T> static int search(const T *a, int l, const T &n)
	{
		int i;

		if(a == NULL)
			return -1;

		for(i = 0; i < l; ++i)
			if(a[i] == n)
				return i;

		return -1;
	}

	/*!
	 * This function does a binary search for a given needle in the given
	 *array. It operates
	 * much faster than search(), but it requires that the array is sorted
	 *in ascending order
	 * first. If the array is not sorted, then the behavior of this function
	 *is undefined.
	 *
	 * \param a The array to search.
	 * \param l The left index.
	 * \param r The right index.
	 * \param n The needle we are searching for.
	 * \return The index of n, or -1 if it isn't found.
	 */
	template <typename T>
	static int binarySearch(const T *a, int l, int r, const T &n)
	{
		int m;

		if(a == NULL)
			return -1;

		while(l <= r)
		{
			m = static_cast<int>((l + r) / 2);

			if(n > a[m])
				l = m + 1;
			else if(n < a[m])
				r = m - 1;
			else
				return m;
		}

		return -1;
	}

	/*!
	 * This function tests whether or not the given array contains duplicate
	 *elements or not.
	 *
	 * \param a The array to test.
	 * \param l The length of the array.
	 * \return True if the array is totally unique, or false otherwise.
	 */
	template <typename T> static bool isUnique(const T *a, int l)
	{
		int i;
		T *s;

		if(a == NULL)
			return true;

		// Arrays of length 1 are always unique.
		if(l <= 1)
			return true;

		s = copy<T>(a, l);
		sortAscending<T>(s, l);

		for(i = 0; i < (l - 1); ++i)
		{
			if(s[i] == s[i + 1])
			{
				delete[] s;
				return false;
			}
		}

		delete[] s;
		return true;
	}

	/*!
	 * This function removes all duplicate elements of the array.
	 *
	 * \param a The array to process.
	 * \param l The length of the array.
	 * \return The resulting size of our array.
	 */
	template <typename T> static int makeUnique(T *&a, int l)
	{
		int i, j, n;
		T *tmp;

		if(a == NULL)
			return 0;

		// Make a temporary array to process.
		tmp = copy<T>(a, l);
		sortAscending<T>(tmp, l);

		// Remove duplicates.
		i = 0;
		j = 1;
		while(j < l)
		{
			if(tmp[i] != tmp[j])
				tmp[++i] = tmp[j];

			++j;
		}

		// Pack the array to not waste space.
		n = i + 1;
		if(n != l)
			resize<T>(tmp, l, n, true);

		// Clean up the old array and change the pointer we were given.
		if(a != NULL)
			delete[] a;
		a = tmp;

		// Return our resulting size.
		return n;
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
	template <typename T> static bool permutate(T *a, int s)
	{
		T hold;
		int k, l, i;

		if(a == NULL)
			return false;

		/*
		 * Step 1: Find the largest index k such that a[k] < a[k + 1].
		 * If no such index
		 *         exists, the permutation is the last permutation.
		 */

		k = -1;
		for(i = (s - 2); i >= 0; --i)
		{
			if(a[i] < a[i + 1])
			{
				k = i;
				break;
			}
		}

		if(k == -1)
			return false;

		/*
		 * Step 2: Find the largest index l such that a[k] < a[l]. Since
		 * k + 1 is such
		 *         an index, l is well defined and satisfies k < l.
		 */

		l = -1;
		for(i = (s - 1); k < i; --i)
		{
			if(a[k] < a[i])
			{
				l = i;
				break;
			}
		}

		if(l == -1)
			return false;

		/*
		 * Step 3: Swap a[k] and a[l].
		 */

		hold = a[k];
		a[k] = a[l];
		a[l] = hold;

		/*
		 * Step 4: Reverse the sequence from a[k + 1] up to and
		 * including the final element a[n].
		 */

		reverse<T>(a, k + 1, s - 1);

		return true;
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
	template <typename T> static bool reversePermutate(T *a, int s)
	{
		T hold;
		int k, l, i;

		if(a == NULL)
			return false;

		/*
		 * Step 1: Find the largest index k such that a[k] > a[k + 1].
		 * If no such index
		 *         exists, the permutation is the last permutation.
		 */

		k = -1;
		for(i = (s - 2); i >= 0; --i)
		{
			if(a[i] > a[i + 1])
			{
				k = i;
				break;
			}
		}

		if(k == -1)
			return false;

		/*
		 * Step 2: Find the largest index l such that a[k] > a[l]. Since
		 * k + 1 is such
		 *         an index, l is well defined and satisfies k < l.
		 */

		l = -1;
		for(i = (s - 1); k < i; --i)
		{
			if(a[k] > a[i])
			{
				l = i;
				break;
			}
		}

		if(l == -1)
			return false;

		/*
		 * Step 3: Swap a[k] and a[l].
		 */

		hold = a[k];
		a[k] = a[l];
		a[l] = hold;

		/*
		 * Step 4: Reverse the sequence from a[k + 1] up to and
		 * including the final element a[n].
		 */

		reverse<T>(a, k + 1, s - 1);

		return true;
	}

private:
	/*!
	 * This is our behind-the-scenes ascending quicksort function.
	 *
	 * \param a The array to sort.
	 * \param l The left index.
	 * \param r The right index.
	 */
	template <typename T> static void quicksortAsc(T *a, int l, int r)
	{
		T pivot, hold;
		int i, j;

		/*
		 * Choose a pivot value. In this case, we just select the value
		 * in the center-ish of our
		 * array, but this could in theory be chosen a bit more
		 * intelligently.
		 */
		pivot = a[(l + r) / 2];

		// Initialize our loop indices...
		i = l;
		j = r;

		// Keep looping until we have swapped all of the values to the
		// correct side of the pivot.
		while(i <= j)
		{
			// Move right until we find a value that is >= our
			// pivot.
			while(a[i] < pivot)
				++i;

			// Move left until we find a value that is <= our pivot.
			while(a[j] > pivot)
				--j;

			// If our left index is still left of our right index,
			// then swap the two nodes.
			if(i < j)
			{
				hold = a[i];
				a[i] = a[j];
				a[j] = hold;
			}

			// Move our indices one more place for the next
			// iteration of the loop.
			if(i <= j)
			{
				++i;
				--j;
			}
		}

		// If our left-most chunk is of size >= 1, then recurse on it.
		if(l < j)
			quicksortAsc<T>(a, l, j);

		// If our right-most chunk is of size <= 1, then recurse on it.
		if(i < r)
			quicksortAsc<T>(a, i, r);
	}

	/*!
	 * This is our behind-the-scenes descending quicksort function.
	 *
	 * \param a The array to sort.
	 * \param l The left index.
	 * \param r The right index.
	 */
	template <typename T> static void quicksortDesc(T *a, int l, int r)
	{
		T pivot, hold;
		int i, j;

		/*
		 * Choose a pivot value. In this case, we just select the value
		 * in the center-ish of our
		 * array, but this could in theory be chosen a bit more
		 * intelligently.
		 */
		pivot = a[(l + r) / 2];

		// Initialize our loop indices...
		i = l;
		j = r;

		// Keep looping until we have swapped all of the values to the
		// correct side of the pivot.
		while(i <= j)
		{
			// Move right until we find a value that is <= our
			// pivot.
			while(a[i] > pivot)
				++i;

			// Move left until we find a value that is >= our pivot.
			while(a[j] < pivot)
				--j;

			// If our left index is still left of our right index,
			// then swap the two nodes.
			if(i < j)
			{
				hold = a[i];
				a[i] = a[j];
				a[j] = hold;
			}

			// Move our indices one more place for the next
			// iteration of the loop.
			if(i <= j)
			{
				++i;
				--j;
			}
		}

		// If our left-most chunk is of size >= 1, then recurse on it.
		if(l < j)
			quicksortDesc<T>(a, l, j);

		// If our right-most chunk is of size >= 1, then recurse on it.
		if(i < r)
			quicksortDesc<T>(a, i, r);
	}
};

#endif

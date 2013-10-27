#ifndef INCLUDE_LIBEULER_UTIL_ARRAY_H
#define INCLUDE_LIBEULER_UTIL_ARRAY_H

#include <cstdlib>

#include "../EDefines.h"
#include "../util/EArrayUtilities.h"

#ifdef LIBEULER_DEBUG
	#include <iostream>
#endif

/*!
 * \brief This class implements the functions in EArrayUtilities.
 *
 * It allows the functions in that class to be used as an object, rather than just
 * as standalone function calls.
 */
template<typename T>
class EArray
{
	public:
#ifdef LIBEULER_DEBUG
		/*!
		 * This function implements our test suite for this class. It uses non-abort()'ing
		 * assertions, and merely prints the result to stdout.
		 */
		static void doTestSuite()
		{
			bool success;
			int i;
			
			std::cout << "\tTesting 'EArray'...\t\t\t";
			try
			{
				success = true;
				
				int *array = new int[5];
				array[0] = 32;
				array[1] = 12;
				array[2] = 237;
				array[3] = 98;
				array[4] = 10;
				
				/*
				 * Constructor + Copy Constructor + Equivalence Operator + Assignment Operator +
				 *     isEqualTo + isEqualToUnsorted + sortAscending
				 */
				
				EArray<int> a(5, array);
				EArray<int> b(a);
				
				delete[] array;
				array = NULL;
				
				EASSERT(a.at(0) == 32)
				EASSERT(a.at(1) == 12)
				EASSERT(a.at(2) == 237)
				EASSERT(a.at(3) == 98)
				EASSERT(a.at(4) == 10)
				EASSERT(b.at(0) == 32)
				EASSERT(b.at(1) == 12)
				EASSERT(b.at(2) == 237)
				EASSERT(b.at(3) == 98)
				EASSERT(b.at(4) == 10)
				
				EASSERT(a == b)
				EASSERT(a.isEqualTo(b))
				
				b.sortAscending();
				
				EASSERT(!a.isEqualTo(b))
				EASSERT(a.isEqualToUnsorted(b))
				
				b = a;
				
				EASSERT(a.isEqualTo(b))
				
				// getSize + setSize
				
				a.setSize(10, true);
				b.setSize(0);
				
				EASSERT(a.at(0) == 32)
				EASSERT(a.at(1) == 12)
				EASSERT(a.at(2) == 237)
				EASSERT(a.at(3) == 98)
				EASSERT(a.at(4) == 10)
				for(i = 5; i < 10; ++i)
					EASSERT(a.at(i) == 0)
					
				EASSERT(a.getSize() == 10)
				EASSERT(b.getSize() == 0)
				
				// at + set
				
				a.set(9, 100);
				EASSERT(a.at(9) == 100)
				
				a.at(8) = 72;
				EASSERT(a.at(8) == 72)
				
				// search + binarySearch
				
				a.at(5) = 278327;
				a.at(6) = 293;
				a.at(7) = 18;
				
				a.sortAscending();
				
				for(i = 0; i < a.getSize(); ++i)
					EASSERT(a.search(a.at(i)) == a.binarySearch(a.at(i)))
					
				EASSERT(a.search(-10) == -1)
				EASSERT(a.binarySearch(-10) == -1)
				
				// sortAscending + sortDescending + reverse
				
				a.sortAscending();
				b = a;
				b.sortDescending();
				b.reverse();
				
				EASSERT(a == b)
				
				// isUnique + makeUnique
				
				a.at(0) = -168;
				a.at(1) = 2345;
				a.at(2) = 112;
				a.at(3) = 234;
				a.at(4) = 8539;
				a.at(5) = 90123;
				a.at(6) = 234;
				a.at(7) = 467;
				a.at(8) = 168;
				a.at(9) = 19233;
				
				EASSERT(!a.isUnique())
				a.makeUnique();
				EASSERT(a.isUnique())
				
				EASSERT(a.getSize() == 9)
				
				// permutate + reversePermutate
				
				a.setSize(3, false);
				a.at(0) = 3;
				a.at(1) = 1;
				a.at(2) = 2;
				
				a.sortAscending();
				b = a;
				
				b.permutate();
				b.reversePermutate();
				
				EASSERT(b == a)
				
				a.permutate();
				EASSERT(a.at(0) == 1)
				EASSERT(a.at(1) == 3)
				EASSERT(a.at(2) == 2)
			}
			catch(EAssertionException &e)
			{
				ELUNUSED(e)
				success = false;
			}
			catch(EOutOfBoundsException &e)
			{
				EDIE_LOGIC(e)
			}
			
			// Print out our results.
			if(success)
				std::cout << "[ OK ]\n";
			else
				std::cout << "[FAIL]\n";
		}
#endif
	
		/*!
		 * This is our default constructor, which creates a new EArray of the given size, and optionally
		 * using the given array of existing data.
		 *
		 * \param s The initial size of our array.
		 * \param a The initial data of our array.
		 */
		EArray(int s = 0, const T *a = NULL)
			: array(NULL), size(0)
		{
			if(a != NULL)
			{
				array = EArrayUtilities::copy<T>(a, s);
				size = s;
			}
			else
			{
				setSize( s, false );
			}
		}
		
		/*!
		 * This is our copy constructor, which initializes a new EArray given an existing other EArray.
		 *
		 * \param o The other object to make ourself equal to.
		 */
		EArray(const EArray<T> &o)
			: array(NULL), size(0)
		{
			(*this) = o;
		}
		
		/*!
		 * This is our default destructor, which just frees up the memory used by our internal
		 * array.
		 */
		virtual ~EArray()
		{
			if(array != NULL)
				delete[] array;
		}
		
		/*!
		 * This is our assignment operator, which changes our value to be equal to that of the given other
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
		 * This is our equivalence operator, which tests if our value is equal to that of the given other
		 * object. Note that this operator is equivalent to calling isEqualTo().
		 *
		 * \param o The other object to compare ourself to.
		 * \return True if our objects are equal, or false otherwise.
		 */
		bool operator==(const EArray<T> &o) const
		{
			return isEqualTo(o);
		}
		
		/*!
		 * This returns the current size (i.e., capacity) of our array object.
		 *
		 * \return The current size of our object.
		 */
		int getSize() const
		{
			return size;
		}
		
		/*!
		 * This function resizes our array object, optionally preserving existing data.
		 *
		 * \param s The new size of our object.
		 * \param p True if you want data preserved, or false otherwise.
		 */
		void setSize(int s, bool p = true)
		{
			s = (s < 0) ? 0 : s;
			
			EArrayUtilities::resize<T>(array, getSize(), s, p);
			size = s;
		}
		
		/*!
		 * This function just returns a non-const reference to the element at the given index in our
		 * array.
		 *
		 * \param i The index of the desired element.
		 * \exception EOutOfBoundsException This exception is thrown if the given index is out-of-bounds.
		 * \return A reference to the element at the given index.
		 */
		T &at(int i) const
			throw(EOutOfBoundsException &)
		{
			if( (i < 0) || (i >= getSize()) )
				throw EOutOfBoundsException("Array index is out-of-bounds.");
			
			return array[i];
		}
		
		/*!
		 * This function sets the value of the element at the given index in our array. Note that the same
		 * thing can be achieved with at(), since it returns a reference.
		 *
		 * \param i The index of the desired element.
		 * \param v The new value for the given element.
		 * \exception EOutOfBoundsException This exception is thrown if the given index is out-of-bounds.
		 */
		void set(int i, const T &v)
			throw(EOutOfBoundsException &)
		{
			at(i) = v;
		}
		
		/*!
		 * This function does a linear search for the given value. Note that binarySearch() is MUCH faster,
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
		 * This function does a binary search for the given value. This function is much faster than search(),
		 * but requires that our array is sorted in ascending order. If the array isn't sorted, then the
		 * behavior of this function is undefined.
		 *
		 * \param n The value we are searching for.
		 * \param l The left-most index to include in the search (inclusive).
		 * \param r The right-most index to include in the search (inclusive).
		 * \return The index of the given value, or -1 if it isn't found.
		 */
		int binarySearch(const T &n, int l = 0, int r = -1) const
		{
			l = (l < 0) ? 0 : l;
			r = (r == -1) ? (getSize() - 1) : r;
			r = (r >= getSize()) ? (getSize() - 1) : r;
			
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
		 * This function just tests if our array is equal to the given other array. Note that this
		 * does the same thing as our "==" operator.
		 *
		 * \param o The other array to compare ourself to.
		 * \return True if our arrays are equal, or false otherwise.
		 */
		bool isEqualTo(const EArray<T> &o) const
		{
			if(getSize() == o.getSize())
				return EArrayUtilities::equal<T>(array, o.array, getSize());
			else
				return false;
		}
		
		/*!
		 * This function tests if our array is equal to the given other array, ignoring all sorting
		 * of the elements.
		 *
		 * \param o The other array to compare ourself to.
		 * \return True if our arrays are equal (ignoring sorting), or false otherwise.
		 */
		bool isEqualToUnsorted(const EArray<T> &o) const
		{
			if(getSize() == o.getSize())
				return EArrayUtilities::equalUnsorted<T>(array, o.array, getSize());
			else
				return false;
		}
		
		/*!
		 * This function tests whether or not our array contains duplicate elements.
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
		 * This function reverses a section of our array between the two given indices (inclusive),
		 * or the entire array if no indices are given.
		 *
		 * \param l The left-most index in our reversal (inclusive).
		 * \param r The right-most index in our reversal (inclusive).
		 */
		void reverse(int l = 0, int r = -1)
		{
			if( (l < 0) || (l >= getSize()) ) l = 0;
			if(r == -1) r = (getSize() - 1);
			if(r >= getSize()) r = (getSize() - 1);
			
			if(r < l)
			{
				int hold = l;
				l = r;
				r = hold;
			}
			
			EArrayUtilities::reverse<T>(array, l, r);
		}
		
		/*!
		 * This is an implementation of Knuth's "Algorithm L," which permutates a given array of elements
		 * in lexicographic order. Note that because they are in lexicographic order, an array sorted in
		 * ascending order is the "first" permutation.
		 *
		 * More information:
		 *     http://en.wikipedia.org/wiki/Permutation#Systematic_generation_of_all_permutations
		 *     http://blog.bjrn.se/2008/04/lexicographic-permutations-using.html
		 *
		 * \return True if there are more permutations, or false if this is the last one.
		 */
		bool permutate()
		{
			return EArrayUtilities::permutate<T>(array, getSize());
		}
		
		/*!
		 * This function is equivalent to permutate(), except it generates permutations in REVERSE lexicographic
		 * order, instead of forwards. Accordingly, our "first" permutation is when our list is sorted in
		 * descending order.
		 *
		 * \return True if there are more permutations, or false if this is the last one.
		 */
		bool reversePermutate()
		{
			return EArrayUtilities::reversePermutate<T>(array, getSize());
		}
		
	private:
		T *array;
		int size;
};

#endif

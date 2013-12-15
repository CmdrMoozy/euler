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

#ifndef INCLUDE_LIBEULER_STRUCTS_HASH_MAP_H
#define INCLUDE_LIBEULER_STRUCTS_HASH_MAP_H

#include <cstdint>
#include <cstdlib>
#include <string>
#include <cmath>

#include "../EDefines.h"
#include "../math/EMath.h"

#ifdef LIBEULER_DEBUG
	#include <iostream>
#endif

/*!
 * \brief This class implements the hash function our HashTable will use.
 *
 * It must implement an () operator which returns the resulting hash as a uint32_t, and accepts a
 * key value, and a uint32_t value r representing the number of bits desired in the resulting hash.
 */
struct Hash
{
	/*!
	 * This function hashes a string-based key for us. It just adds up the values in the string and then calls
	 * operator() (uint32_t, uint32_t) on the result.
	 *
	 * \param k The key we are about to hash.
	 * \param r The capacity of the hash table is assumed to be 2^r.
	 * \return The resulting hash.
	 */
	uint32_t operator() (const std::string &k, uint32_t r)
	{
		size_t i;
		uint32_t v = 0xb11924e1; // Start with some large, random prime number.
		
		/*
		 * We expand each individual character, so even a very short (e.g, 1-character-long) string will
		 * affect ALL the bits in our starting prime.
		 */
		for(i = 0; i < k.size(); ++i)
		{
			if(k[i]&1)
			{
				v += static_cast<uint32_t>(k[i]);
				v += (~static_cast<uint32_t>(k[i])) << 8;
				v += static_cast<uint32_t>(Hash::rotateLeft(k[i], 3)) << 16;
				v += static_cast<uint32_t>(Hash::rotateRight(k[i], 5)) << 24;
			}
			else
			{
				v += (~static_cast<uint32_t>(k[i]));
				v += static_cast<uint32_t>(k[i]) << 8;
				v += static_cast<uint32_t>(Hash::rotateLeft(k[i], 4)) << 16;
				v += static_cast<uint32_t>(Hash::rotateRight(k[i], 6)) << 24;
			}
		}
		
		return operator()(v, r);
	}
	
	/*!
	 * This function uses a multiplicative method of hashing (see "Introduction to Algorithms," pp. 231),
	 * returning (A*k % 2^w) >> (w-r), where A is a constant, k is the key value we are trying to hash,
	 * w is the word size of our hardware (this code enforces a word-size of 32-bits), and our table contains
	 * 2^r slots.
	 *
	 * Assuming our table does indeed contain 2^r slots, and r is passed correctly, this function will never
	 * return an out-of-bounds hash.
	 *
	 * \param k The key we are about to hash.
	 * \param r The capacity of the hash table is assumed to be 2^r.
	 * \return The resulting hash.
	 */
	uint32_t operator() (uint32_t k, uint32_t r)
	{
		// r Must be <= 32-bits, as that's the maximum word size for us.
		r = (r > 32) ? 32 : r;
		
		return (( (Hash::A * k) % ( ~static_cast<uint32_t>(0) ) ) >> (32 - r));
	}
	
	private:
		/*
		 * For this hashing method, A should be an ODD constant that is reasonably far away from
		 * both 2^31 and 2^32.
		 */
		static const uint32_t A = 0xbf8d031b;
	
		/*!
		 * This function performs a circular left shift of the given char value by n places.
		 *
		 * \param c The char value we will be modifying.
		 * \param n The number of places to shift the value.
		 * \return The resulting value.
		 */
		static inline char rotateLeft(char c, int n)
		{
			return ((c << (n%8)) | (c >> (8 - (n%8))));
		}
		
		/*!
		 * This function performs a circular right shift of the given char value by n places.
		 *
		 * \param c The char value we will be modifying.
		 * \param n The number of places to shift the value.
		 * \return The resulting value.
		 */
		static inline char rotateRight(char c, int n)
		{
			return ((c >> (n%8)) | (c << (8 - (n%8))));
		}
};

/*!
 * \brief This class implements a templated, fixed-size hash map.
 *
 * All operations should, on average, operate in constant (i.e., O(1)) time, assuming the load factor
 * of the hash table (that is, the ratio of keys being stored to the size of the table) is < 1.0, assuming
 * that our hash function distributes everything evenly (this should be relatively true in most common-use
 * cases).
 */
template< typename Key, typename Value, class Hasher = Hash >
class EHashMap
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
			
			std::cout << "\tTesting 'EHashMap'...\t\t\t";
			try
			{
				success = true;
				
				uint32_t i;
				EHashMap<uint32_t, uint32_t> n;
				EHashMap<uint32_t, uint32_t> m(4, 0.75);
				
				// Initialize our hash map.

				m.put(0, 6602);
				m.put(1, 4649);
				m.put(2, 6197);
				m.put(3, 4316);
				m.put(4, 5501);
				m.put(5, 5757);
				m.put(6, 8864);
				m.put(7, 6258);
				m.put(8, 4442);
				m.put(9, 5959);
				m.put(10, 6939);
				m.put(11, 2707);
				m.put(12, 5551);
				m.put(13, 8735);
				m.put(14, 4447);
				m.put(15, 8898);

				// Test put, isEmpty, getKeys, containsKey and get
				
				EASSERT(!m.isEmpty())

				m.clear();
				EASSERT(m.isEmpty())
				EASSERT(m.getKeys() == 0)

				m.put(0, 6602);
				m.put(1, 4649);
				m.put(2, 6197);
				m.put(3, 4316);
				m.put(4, 5501);
				m.put(5, 5757);
				m.put(6, 8864);
				m.put(7, 6258);
				m.put(8, 4442);
				m.put(9, 5959);
				m.put(10, 6939);
				m.put(11, 2707);
				m.put(12, 5551);
				m.put(13, 8735);
				m.put(14, 4447);
				m.put(15, 8898);

				EASSERT(m.getKeys() == 16)

				EASSERT(m.containsKey(0)  && (m.get(0)  == 6602))
				EASSERT(m.containsKey(1)  && (m.get(1)  == 4649))
				EASSERT(m.containsKey(2)  && (m.get(2)  == 6197))
				EASSERT(m.containsKey(3)  && (m.get(3)  == 4316))
				EASSERT(m.containsKey(4)  && (m.get(4)  == 5501))
				EASSERT(m.containsKey(5)  && (m.get(5)  == 5757))
				EASSERT(m.containsKey(6)  && (m.get(6)  == 8864))
				EASSERT(m.containsKey(7)  && (m.get(7)  == 6258))
				EASSERT(m.containsKey(8)  && (m.get(8)  == 4442))
				EASSERT(m.containsKey(9)  && (m.get(9)  == 5959))
				EASSERT(m.containsKey(10) && (m.get(10) == 6939))
				EASSERT(m.containsKey(11) && (m.get(11) == 2707))
				EASSERT(m.containsKey(12) && (m.get(12) == 5551))
				EASSERT(m.containsKey(13) && (m.get(13) == 8735))
				EASSERT(m.containsKey(14) && (m.get(14) == 4447))
				EASSERT(m.containsKey(15) && (m.get(15) == 8898))
				
				// Test our assignment operator / copy constructor.
				n = m;
				EASSERT(n.containsKey(0)  && (n.get(0)  == 6602))
				EASSERT(n.containsKey(1)  && (n.get(1)  == 4649))
				EASSERT(n.containsKey(2)  && (n.get(2)  == 6197))
				EASSERT(n.containsKey(3)  && (n.get(3)  == 4316))
				EASSERT(n.containsKey(4)  && (n.get(4)  == 5501))
				EASSERT(n.containsKey(5)  && (n.get(5)  == 5757))
				EASSERT(n.containsKey(6)  && (n.get(6)  == 8864))
				EASSERT(n.containsKey(7)  && (n.get(7)  == 6258))
				EASSERT(n.containsKey(8)  && (n.get(8)  == 4442))
				EASSERT(n.containsKey(9)  && (n.get(9)  == 5959))
				EASSERT(n.containsKey(10) && (n.get(10) == 6939))
				EASSERT(n.containsKey(11) && (n.get(11) == 2707))
				EASSERT(n.containsKey(12) && (n.get(12) == 5551))
				EASSERT(n.containsKey(13) && (n.get(13) == 8735))
				EASSERT(n.containsKey(14) && (n.get(14) == 4447))
				EASSERT(n.containsKey(15) && (n.get(15) == 8898))

				// Test erase
				
				EASSERT(m.erase(1))
				EASSERT(m.erase(3))
				EASSERT(m.erase(5))
				EASSERT(m.erase(7))
				EASSERT(m.erase(9))
				EASSERT(m.erase(11))
				EASSERT(m.erase(13))
				EASSERT(m.erase(15))

				EASSERT(!m.erase(1))
				EASSERT(!m.erase(3))
				EASSERT(!m.erase(5))
				EASSERT(!m.erase(7))
				EASSERT(!m.erase(9))
				EASSERT(!m.erase(11))
				EASSERT(!m.erase(13))
				EASSERT(!m.erase(15))

				EASSERT(m.getKeys() == 8)
				
				// Clear our map and add a whole bunch of items to it, to test our rehash() function.
				
				for(i = 0; i < 50000; ++i)
					m.put(i, i);
				
				EASSERT(m.getKeys() == 50000)
				EASSERT(m.getDesiredLoadFactor() > m.getCurrentLoadFactor())
				
				for(i = 0; i < 50000; ++i)
					EASSERT(m.containsKey(i) && (m.get(i) == i))
				
				// Test our copy constructor and copy assignment operator.
				
				m.clear();
				for(i = 0; i < 100; ++i)
					m.put(i, i);
				
				n = m;
				EHashMap<uint32_t, uint32_t> o(m);
				
				for(i = 0; i < 100; ++i)
				{
					EASSERT(m.containsKey(i) && (m.get(i) == i));
					EASSERT(n.containsKey(i) && (n.get(i) == i));
					EASSERT(o.containsKey(i) && (o.get(i) == i));
				}
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
			
			// Test our subclasses.
			Node::doTestSuite();
			BucketList::doTestSuite();
		}
#endif
	
		/*!
		 * This is our default constructor, which initializes a new SHashMap object with the given
		 * initial bit-length (the initial capacity will be 2^r) and the given desired load factor.
		 * Our hash map resizes itself automatically in order to maintain the given desired load factor,
		 * but this operation is quite expensive, so you should try to choose a reasonable initial
		 * capacity and/or load factor for the specific case.
		 *
		 * The load factor is defined as the ratio of stored keys to the total capacity.
		 *
		 * \param r The bit-length of our hash (our capacity will be 2^r).
		 * \param l The desired load factor for this hash map.
		 */
		EHashMap(int r = 10, float l = 0.75)
			: bits(r), load(l), keys(0)
		{
			int i;
			capacity = static_cast<int>(EMath::integerPow(2, getHashBits()));
			
			array = new BucketList *[getCapacity()];
			for(i = 0; i < getCapacity(); i++)
				array[i] = NULL;
		}
		
		/*!
		 * This is our copy constructor, which will initialize our object to be equal in every way to
		 * the given other object.
		 *
		 * \param o The other hash map to make ourself equal to.
		 */
		EHashMap(const EHashMap<Key, Value, Hash> &o)
			: array(NULL), bits(0), capacity(0), load(0.75), keys(0)
		{
			(*this) = o;
		}
		
		/*!
		 * This is our default destructor, which frees all of our contents so our object can be cleaned
		 * up and destroyed.
		 */
		virtual ~EHashMap()
		{
			int i;
			for(i = 0; i < getCapacity(); i++)
				if(array[i] != NULL)
					delete array[i];
			
			delete[] array;
		}
		
		/*!
		 * This is our assignment operator, which sets our hash map's value equal to that of the given
		 * other hash map.
		 *
		 * \param o The other hash map to make ourself equal to.
		 * \return A reference to this, so the operator can be chained.
		 */
		EHashMap &operator=(const EHashMap<Key, Value, Hash> &o)
		{
			int i;
			
			// Delete our existing data.
			clear();
			if(array != NULL)
				delete[] array;
			
			// Set our properties.
			bits = o.getHashBits();
			capacity = o.getCapacity();
			load = o.getDesiredLoadFactor();
			keys = o.getKeys();
			
			// Populate our new list.
			array = new BucketList *[getCapacity()];
			for(i = 0; i < o.getCapacity(); ++i)
			{
				if(o.array[i] != NULL)
					array[i] = new BucketList( (*o.array[i]) );
				else
					array[i] = NULL;
			}
			
			return (*this);
		}
		
		/*!
		 * This function returns our current desired load factor. The load factor is defined
		 * as a ratio of the number of keys stored to the total capacity of the hash map.
		 *
		 * \return Our desired load factor.
		 */
		float getDesiredLoadFactor() const
		{
			return load;
		}
		
		/*!
		 * This function sets our desired load factor. The load factor is defined as a ratio
		 * of the number of keys stored to the total capacity of the hash map. This function
		 * can result in a rehash operation (which is quite expensive), if the given load factor
		 * is less than our current load factor.
		 *
		 * \param l The new desired load factor.
		 */
		void setDesiredLoadFactor(float l)
		{
			load = l;
			rehash();
		}
		
		/*!
		 * This function returns our calculated current load factor. The load factor is defined
		 * as a ratio of the number of keys stored to the total current capacity of our hash map.
		 *
		 * \return Our hash map's current load factor.
		 */
		float getCurrentLoadFactor() const
		{
			return (static_cast<float>(keys) / static_cast<float>(getCapacity()));
		}
		
		/*!
		 * This function returns the number of bits in our hash and (via calculation) the total
		 * capacity of our hash map (2^r).
		 *
		 * \return The number of bits in our hash.
		 */
		int getHashBits() const
		{
			return bits;
		}
		
		/*!
		 * This function returns the capacity of our hash map (i.e., the number of distinct keys
		 * that could be stored without creating lists). The square root of this value is the bit
		 * length of our hash.
		 *
		 * \return Our hash map's current capacity.
		 */
		int getCapacity() const
		{
			return capacity;
		}
		
		/*!
		 * This function returns the number of distinct keys our hash map is currently storing.
		 *
		 * \return The number of distinct keys being stored.
		 */
		int getKeys() const
		{
			return keys;
		}
		
		/*!
		 * This function clears our list of all keys (but doesn't modify our hash bit length, our
		 * capacity, or our desired load factor).
		 */
		void clear()
		{
			int i;
			for(i = 0; i < getCapacity(); i++)
			{
				if(array[i] != NULL)
				{
					delete array[i];
					array[i] = NULL;
				}
			}
			
			keys = 0;
		}
		
		/*!
		 * This is a convenience function, which tests whether or not our map is empty.
		 *
		 * \return True if our map is empty, or false otherwise.
		 */
		bool isEmpty() const
		{
			return (getKeys() == 0);
		}
		
		/*!
		 * This function returns the value that is mapped to by the given key. This function should operate
		 * in constant (O(1)) time, assuming a good hash distribution is achieved.
		 *
		 * \param k The key to search for.
		 * \exception EOutOfBoundsException This exception is thrown if our map doesn't contain the given key.
		 * \return The value that corresponds to the given key.
		 */
		virtual Value &get(const Key &k) const
			throw(EOutOfBoundsException &)
		{
			uint32_t hash = h(k, getHashBits());
			Node *n = NULL;
			
			if(array[hash] != NULL)
				n = array[hash]->search(k);
			
			if(n != NULL)
				return n->getValue();
			else
				throw EOutOfBoundsException("The QHashMap doesn't contain the given key.");
		}
		
		/*!
		 * This function inserts the given value for the given key. If a value for that key is already present,
		 * then we just replace it with the given new value.
		 *
		 * \param k The key for which to insert our value.
		 * \param v The value to insert.
		 * \return True if a new key was inserted, or false if the value was merely updated.
		 */
		virtual bool put(const Key &k, const Value &v)
		{
			bool r;
			uint32_t hash = h(k, getHashBits());
			
			if(array[hash] == NULL)
				array[hash] = new BucketList();
			
			r = array[hash]->insert(k, v);
			if(r)
				keys++;
			
			rehash();
			return r;
		}
		
		/*!
		 * This function erases the given key from our hash map, if it is present.
		 *
		 * \param k The key to search for.
		 * \return True if the key was removed, or false if it was never present to begin with.
		 */
		virtual bool erase(const Key &k)
		{
			bool r = false;
			uint32_t hash = h(k, getHashBits());
			
			if(array[hash] != NULL)
				r = array[hash]->erase(k);
			
			if(r)
				keys--;
			
			return r;
		}
		
		/*!
		 * This function tests whether our map contains the given key or not.
		 *
		 * \param k The key to search for.
		 * \return True if the key was found, or false otherwise.
		 */
		bool containsKey(const Key &k) const
		{
			uint32_t hash = h(k, getHashBits());
			
			if(array[hash] != NULL)
				return (array[hash]->search(k) != NULL);
			else
				return false;
		}
		
		/*!
		 * This is a convenience function which trades our values with that of the given
		 * other object. Since this function just trades pointers, it operates in O(1) time.
		 *
		 * \param o The other SHashMap to swap our values with.
		 */
		void swapValues(EHashMap<Key, Value, Hasher> &o)
		{
			float holdf;
			BucketList **hold = o.array;
			o.array = array;
			array = hold;
			
			{
				int holdi = bits;
				bits = o.bits;
				o.bits = holdi;
			}
			
			{
				int holdi = capacity;
				capacity = o.capacity;
				o.capacity = holdi;
			}
			
			{
				int holdi = keys;
				keys = o.keys;
				o.keys = holdi;
			}
			
			holdf = load;
			load = o.load;
			o.load = holdf;
		}
	
	private:
		/*!
		 * \brief This class represents a single node in our hash table.
		 *
		 * Pointers to this class are what our BucketList class stores. This class contains the key and value
		 * pair that was inserted into our hash table, and also a pointer to the next Node in the BucketList.
		 */
		class Node
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
					
					// Initialize a blank node.
					Node n, c, next;
					
					std::cout << "\t\tTesting 'Node'...\t\t";
					try
					{
						success = true;
						
						// Test default constructor + getters.
						EASSERT(n.getKey() == 0)
						EASSERT(n.getValue() == 0)
						
						// Test setters.
						
						n.setKey(100);
						n.setValue(1000);
						
						EASSERT(n.getKey() == 100)
						EASSERT(n.getValue() == 1000)
						
						// Test copy constructor.
						Node copy(n);
						
						EASSERT(n.getKey() == copy.getKey())
						EASSERT(n.getValue() == copy.getValue())
					}
					catch(EAssertionException &e)
					{
						ELUNUSED(e)
						success = false;
					}
					
					// Print out our results.
					if(success)
						std::cout << "[ OK ]\n";
					else
						std::cout << "[FAIL]\n";
				}
#endif
			
				/*!
				 * This is our default constructor, which initializes a new Node object with (optionally) the
				 * given key, value and next-node values.
				 *
				 * \param k The key value for this node.
				 * \param v The value this node will store.
				 * \param n A pointer to our next node in a BucketList.
				 */
				Node(const Key &k = Key(), const Value &v = Value(), Node *n = NULL)
				{
					setKey(k);
					setValue(v);
					setNext(n);
				}
				
				/*!
				 * This is our copy constructor, which initializes our object to be equal
				 * to the given other object.
				 *
				 * \param o The other object to make ourself equal to.
				 */
				Node(const Node &o)
				{
					(*this) = o;
				}
				
				/*!
				 * This is our default destructor. To make it easier to free up our hash table, this destructor
				 * will delete our next node as well if it is non-NULL, which will in turn delete its next node,
				 * and so on. What this means is, if you do not want any other nodes to be deleted, you need to
				 * make sure to call setNext(NULL) first.
				 */
				virtual ~Node()
				{
					if(next != NULL)
						delete next;
				}
				
				/*!
				 * This function returns a pointer to the node after this one in a BucketList, or NULL if no such
				 * node exists.
				 *
				 * \return Our next node.
				 */
				Node *getNext() const
				{
					return next;
				}
				
				/*!
				 * This function sets our next node to the given value.
				 *
				 * \param n The new next node.
				 */
				void setNext(Node *n)
				{
					next = n;
				}
				
				/*!
				 * This function returns our node's key value.
				 *
				 * \return Our key value.
				 */
				Key &getKey()
				{
					return key;
				}
				
				/*!
				 * This function sets our node's key value.
				 *
				 * \param k Our new key value.
				 */
				void setKey(const Key &k)
				{
					key = k;
				}
				
				/*!
				 * This function returns the value our node is storing.
				 *
				 * \return The value our node is storing.
				 */
				Value &getValue()
				{
					return value;
				}
				
				/*!
				 * This function sets the value our node is storing.
				 *
				 * \param v The value our node will store.
				 */
				void setValue(const Value &v)
				{
					value = v;
				}
			
			private:
				Node *next;
				Key key;
				Value value;
		};
		
		/*!
		 * \brief This class represents a single bucket in our hash table.
		 *
		 * In order to handle hash collisions, our hash table utilizes a scheme called "separate chaining"
		 * (http://en.wikipedia.org/wiki/Hash_table#Separate_chaining), where each slot in our table is a
		 * singly-linked list, and any collisions are simply appended to that list.
		 */
		class BucketList
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
					
					// Initialize a blank node.
					Node n, c, next;
					
					std::cout << "\t\tTesting 'BucketList'...\t\t";
					try
					{
						success = true;
						
						// Test default constructor.
						
						BucketList b;
						
						EASSERT(b.getHead() == NULL)
						EASSERT(b.getLength() == 0)
						
						// Insert some stuff.
						b.insert(100, 100);
						b.insert(200, 200);
						b.insert(300, 300);
						b.insert(400, 400);
						b.insert(500, 500);
						b.insert(600, 600);
						b.insert(700, 700);
						b.insert(800, 800);
						b.insert(900, 900);
						
						// Test getHead and getLength.
						EASSERT(b.getHead() != NULL)
						EASSERT(b.getLength() == 9)
						
						// Make sure insert overrides existing keys correctly.
						EASSERT(!b.insert(100, 900))
						EASSERT(b.insert(1000, 1000))
						
						// Try erasing some things.
						EASSERT(b.erase(1000))
						EASSERT(!b.erase(2000))
						
						// Try finding some things.
						EASSERT(b.search(100) != NULL)
						EASSERT(b.search(800) != NULL)
						EASSERT(b.search(1000) == NULL)
						EASSERT(b.search(2000) == NULL)
						
						// Test our copy constructor.
						BucketList copy(b);
						EASSERT(copy.getLength() == b.getLength())
						
						// Test our assignment operator.
						BucketList d;
						d = b;
						EASSERT(d.getLength() == b.getLength())
					}
					catch(EAssertionException &e)
					{
						ELUNUSED(e)
						success = false;
					}
					
					// Print out our results.
					if(success)
						std::cout << "[ OK ]\n";
					else
						std::cout << "[FAIL]\n";
				}
#endif
			
				/*!
				 * This is our default constructor, which initializes a new, empty BucketList object.
				 */
				BucketList()
					: head(NULL)
				{
				}
				
				/*!
				 * This is our copy constructor, which initializes our object to be equal
				 * to the given other object.
				 *
				 * \param o The other object to make ourself equal to.
				 */
				BucketList(const BucketList &o)
					: head(NULL)
				{
					(*this) = o;
				}
				
				/*!
				 * This is our default destructor, which deletes every element of our list recursively,
				 * so out object can be cleaned up & destroyed.
				 */
				virtual ~BucketList()
				{
					// We delete our head node, which should in turn recursively delete the entire list.
					if(head != NULL)
						delete head;
				}
				
				/*!
				 * This is our assignment operator, which will set our value equal to that
				 * of the given other object, deleting any existing data we are storing in
				 * the process.
				 *
				 * \param o The other object to make ourself equal to.
				 * \return A reference to this, so the operator can be chained.
				 */
				BucketList &operator=(const BucketList &o)
				{
					// We delete our head node, emptying our entire list.
					if(head != NULL)
						delete head;
					
					// Copy our data.
					Node *c = o.getHead();
					while(c != NULL)
					{
						insert(c->getKey(), c->getValue());
						c = c->getNext();
					}
					
					return (*this);
				}
				
				/*!
				 * This function inserts the given key/value pair into our list. If the list already contains
				 * the given key, then its corresponding value is simply updated, or otherwise, we add a brand
				 * new node.
				 *
				 * \param k The key for this node.
				 * \param v The value for this node.
				 * \return True if a new node was created, or false if a value was simply updated.
				 */
				bool insert(const Key &k, const Value &v)
				{
					Node *c = head;
					
					while(c != NULL)
					{
						if(c->getKey() == k)
						{
							c->setValue(v);
							return false;
						}
						
						c = c->getNext();
					}
					
					Node *n = new Node(k, v, head);
					head = n;
					return true;
				}
				
				/*!
				 * This function erases the node with the given key value from our list, and returns whether
				 * or not a node with that key value was found.
				 *
				 * \param k The key value we are searching for.
				 * \return True if a node was removed, or false otherwise.
				 */
				bool erase(const Key &k)
				{
					Node *p, *c;
					
					p = NULL;
					c = head;
					while(c != NULL)
					{
						if(c->getKey() == k)
						{
							if(p != NULL)
								p->setNext(c->getNext());
							else
								head = c->getNext();
							
							c->setNext(NULL);
							delete c;
							return true;
						}
						
						p = c;
						c = p->getNext();
					}
					
					return false;
				}
				
				/*!
				 * This function does a linear search through our list, and returns a pointer to the node with the
				 * given key value, or NULL if one could not be found.
				 *
				 * \param k The key value we are searching for.
				 * \return A pointer to the node with the given key, or NULL if no such node exists.
				 */
				Node *search(const Key &k) const
				{
					Node *c = head;
					while(c != NULL)
					{
						if(c->getKey() == k)
							return c;
						
						c = c->getNext();
					}
					
					return NULL;
				}
				
				/*!
				 * This function returns a pointer to our head element (for instance, so the
				 * caller can manually iterate through our list).
				 *
				 * \return A pointer to our head element.
				 */
				Node *getHead() const
				{
					return head;
				}
				
				/*!
				 * This function returns the number of nodes this BucketList contains.
				 *
				 * \return This list's length.
				 */
				int getLength() const
				{
					uint32_t r = 0;
					Node *c = head;
					
					while(c != NULL)
					{
						r++;
						c = c->getNext();
					}
					
					return r;
				}
			
			private:
				Node *head;
		};
		
		/*!
		 * This is a convenience function, which calculates the minimum number of hash-bits required
		 * to store the given number of keys while maintaining the given desired load factor.
		 *
		 * \param r The starting minimum for our hash bit length.
		 * \param k The number of keys we need to store.
		 * \param l The desired load factor of our map.
		 * \return The minimum hash bit length needed to store the given amount of keys.
		 */
		int getMinimumBits(int r, int k, float l)
		{
			uint32_t c;
			
			do
			{
				c = static_cast<uint32_t>(pow(2.0, static_cast<double>(r++)));
			} while( (static_cast<float>(k)/static_cast<float>(c)) <= l);
			
			return r;
		}
		
		/*!
		 * This internal function rehashes all of our keys, generally to maintain our desired
		 * load factor. If we are already within that number, then no action is taken.
		 */
		void rehash()
		{
			int i;
			Node *node;
			
			// Do nothing if we are within our desired load factor.
			if(getCurrentLoadFactor() <= getDesiredLoadFactor())
				return;
			
			// Initialize a new hash table to rehash our contents into.
			EHashMap<Key, Value, Hasher> newTable(getMinimumBits(getHashBits(), getKeys(), getDesiredLoadFactor()),
				getDesiredLoadFactor());
			
			// Insert all of our existing key/value pairs into the new table.
			for(i = 0; i < getCapacity(); ++i)
			{
				if(array[i] == NULL)
					continue;
				
				node = array[i]->getHead();
				while(node != NULL)
				{
					newTable.put(node->getKey(), node->getValue());
					node = node->getNext();
				}
			}
			
			(*this) = newTable;
		}
		
		mutable Hasher h;
		BucketList **array;
		int bits;
		int capacity;
		float load;
		int keys;
};

#endif

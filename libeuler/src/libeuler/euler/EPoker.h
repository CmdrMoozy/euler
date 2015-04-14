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

#ifndef INCLUDE_LIBEULER_EULER_POKER_H
#define INCLUDE_LIBEULER_EULER_POKER_H

#include <cstdint>
#include <string>
#include <iosfwd>

// Forward declarations.
class EPoker;
std::ostream &operator<<(std::ostream &out, const EPoker &i);

/*!
 * \brief This class represents a series of poker cards.
 *
 * It can be used, for instance, to represent a single poker hand, and can rank itself against
 * other hands.
 */
class EPoker
{
	public:
		/*!
		 * \brief This enumeration lists the standard playing card values.
		 */
		enum CardValue
		{
			Two   = 0,
			Three = 1,
			Four  = 2,
			Five  = 3,
			Six   = 4,
			Seven = 5,
			Eight = 6,
			Nine  = 7,
			Ten   = 8,
			Jack  = 9,
			Queen = 10,
			King  = 11,
			Ace   = 12
		};

		/*!
		 * \brief This enumeration lists the four standard playing card suits.
		 */
		enum CardSuit
		{
			Clubs    = 0,
			Diamonds = 1,
			Hearts   = 2,
			Spades   = 3
		};

		/*!
		 * \brief This enumeration lists the different hand ranks available.
		 */
		enum HandRank
		{
			HighCard      = 0,
			OnePair       = 1,
			TwoPair       = 2,
			ThreeOfAKind  = 3,
			Straight      = 4,
			Flush         = 5,
			FullHouse     = 6,
			FourOfAKind   = 7,
			StraightFlush = 8
		};

#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif

		EPoker();
		EPoker(const EPoker &o);
		virtual ~EPoker();

		EPoker &operator=(const EPoker &o);

		bool operator==(const EPoker &o) const;
		bool operator<(const EPoker &o) const;
		bool operator<=(const EPoker &o) const;
		bool operator>(const EPoker &o) const;
		bool operator>=(const EPoker &o) const;

		bool parse(const std::string &s);

		bool isValid() const;
		void addCard(EPoker::CardValue v, EPoker::CardSuit s);
		void removeCard(EPoker::CardValue v, EPoker::CardSuit s);
		void clear();
		bool containsValue(EPoker::CardValue v) const;
		bool containsCard(EPoker::CardValue v, EPoker::CardSuit s) const;

		std::string toString() const;

	private:
		uint64_t cards;
		uint64_t values;

		mutable bool rankValid;
		mutable EPoker::HandRank rank;
		mutable uint64_t rankCards;

		uint64_t getValueIsolator(EPoker::CardValue v) const;

		int cardsIndexOf(EPoker::CardValue v, EPoker::CardSuit s) const;
		EPoker::CardValue valueOfIndex(uint32_t i) const;
		EPoker::CardSuit suitOfIndex(uint32_t i) const;
		uint64_t getComparableValuesList(uint64_t c) const;

		void buildRank() const;

		int compare(const EPoker &o) const;
};

#endif

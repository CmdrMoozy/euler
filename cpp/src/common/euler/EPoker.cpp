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

#include "EPoker.h"

#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>

#include "common/EDefines.h"
#include "common/util/Bitwise.hpp"
#include "common/util/EBitwise.h"

/*!
 * This is our default constructor, which creates a new empty object.
 */
EPoker::EPoker()
        : cards(0), values(0), rankValid(false), rank(HighCard), rankCards(0)
{
}

/*!
 * This is our copy constructor, which creates a new object equal to the given
 * other object.
 *
 * \param o The object to use for an initial value
 */
EPoker::EPoker(const EPoker &o)
        : cards(0), values(0), rankValid(false), rank(HighCard), rankCards(0)
{
	(*this) = o;
}

/*!
 * This is our default destructor, which cleans up & destroys our object.
 */
EPoker::~EPoker()
{
}

/*!
 * This is our assignment operator, which makes our value equal to that of the
 * given other object.
 *
 * \param o The object to make ourself equal to.
 * \return A reference to this, so this operator can be chained.
 */
EPoker &EPoker::operator=(const EPoker &o)
{
	cards = o.cards;

	if(o.rankValid)
	{
		rankCards = o.rankCards;
		rank = o.rank;
		rankValid = true;
	}
	else
	{
		rankValid = false;
	}

	return (*this);
}

/*!
 * This comparison operator tests whether this hand's rank is equal to that of
 * the given other hand.
 *
 * Note that, if either hand is invalid, then our return value is undefined. It
 * is up to the caller to verify this, if necessary, before comparing two hands.
 *
 * \param o The hand to compare ourself to.
 * \return True if our rank is equal to o's, or false otherwise.
 */
bool EPoker::operator==(const EPoker &o) const
{
	return (compare(o) == 0);
}

/*!
 * This comparison operator tests whether this hand's rank is less than that of
 * the given other hand.
 *
 * Note that, if either hand is invalid, then our return value is undefined. It
 * is up to the caller to verify this, if necessary, before comparing two hands.
 *
 * \param o The hand to compare ourself to.
 * \return True if our rank is less than o's, or false otherwise.
 */
bool EPoker::operator<(const EPoker &o) const
{
	return (compare(o) < 0);
}

/*!
 * This comparison operator tests whether this hand's rank is less than or equal
 * to that of the given other hand.
 *
 * Note that, if either hand is invalid, then our return value is undefined. It
 * is up to the caller to verify this, if necessary, before comparing two hands.
 *
 * \param o The hand to compare ourself to.
 * \return True if our rank is less than or equal to o's, or false otherwise.
 */
bool EPoker::operator<=(const EPoker &o) const
{
	return (compare(o) <= 0);
}

/*!
 * This comparison operator tests whether this hand's rank is greater than that
 * of the given other hand.
 *
 * Note that, if either hand is invalid, then our return value is undefined. It
 * is up to the caller to verify this, if necessary, before comparing two hands.
 *
 * \param o The hand to compare ourself to.
 * \return True if our rank is greater than o's, or false otherwise.
 */
bool EPoker::operator>(const EPoker &o) const
{
	return (compare(o) > 0);
}

/*!
 * This comparison operator tests whether this hand's rank is greater than or
 * equal to that of the given other hand.
 *
 * Note that, if either hand is invalid, then our return value is undefined. It
 * is up to the caller to verify this, if necessary, before comparing two hands.
 *
 * \param o The hand to compare ourself to.
 * \return True if our rank is greater than or equal to o's, or false otherwise.
 */
bool EPoker::operator>=(const EPoker &o) const
{
	return (compare(o) >= 0);
}

/*!
 * This function sets the cards present in our deck using a string. This string
 * should be formatted as follows:
 *
 *     "VS VS VS VS VS"
 *
 * Where 'V' represents the card value, and 'S' represents the card suit. 'V'
 * should be one of 2, 3, 4, 5, 6, 7, 8, 9, T(en), J(ack), Q(ueen), K(ing),
 * A(ce) and 'S' should be one of C(lubs), D(iamonds), H,(earts) S(pades).
 *
 * If for some reason the string given cannot be parsed successfully, this
 * function will return false to indicate this, and the hand will be emptied.
 * If this function returns true, it is also the case that isValid() should
 * return true (at least until you modify the hand).
 *
 * \param s The string to parse.
 * \return True on success, or false on failure.
 */
bool EPoker::parse(const std::string &s)
{
	bool r;
	EPoker::CardValue v = EPoker::Two;
	EPoker::CardSuit u = EPoker::Clubs;

	clear();
	if(s.length() != 14)
		return false;

	r = true;

	// Loop through the string.

	for(std::string::size_type i = 0; i < 14; i += 3)
	{
		// Determine the value.

		switch(s[i])
		{
		case '2':
			v = EPoker::Two;
			break;
		case '3':
			v = EPoker::Three;
			break;
		case '4':
			v = EPoker::Four;
			break;
		case '5':
			v = EPoker::Five;
			break;
		case '6':
			v = EPoker::Six;
			break;
		case '7':
			v = EPoker::Seven;
			break;
		case '8':
			v = EPoker::Eight;
			break;
		case '9':
			v = EPoker::Nine;
			break;
		case 'T':
			v = EPoker::Ten;
			break;
		case 'J':
			v = EPoker::Jack;
			break;
		case 'Q':
			v = EPoker::Queen;
			break;
		case 'K':
			v = EPoker::King;
			break;
		case 'A':
			v = EPoker::Ace;
			break;

		default:
			r = false;
			break;
		};

		// Determine the suit.

		switch(s[i + 1])
		{
		case 'C':
			u = EPoker::Clubs;
			break;
		case 'D':
			u = EPoker::Diamonds;
			break;
		case 'H':
			u = EPoker::Hearts;
			break;
		case 'S':
			u = EPoker::Spades;
			break;

		default:
			r = false;
			break;
		};

		// Add the card.

		if(r)
			addCard(v, u);
		else
			break;
	}

	// Make sure our ending state is valid.

	r = isValid();

	// Return our status.

	if(!r)
		clear();
	return r;
}

/*!
 * This function determines if the current hand is a "valid" poker hand. Valid
 * hands are those that contain exactly five unique cards.
 *
 * \return True if the hand is valid, or false otherwise.
 */
bool EPoker::isValid() const
{
	return (euler::util::bitwise::opop(cards) == 5);
}

/*!
 * This function adds the card denoted by the given value and suit from this
 * hand. If the card is already present, then no action is taken.
 *
 * \param v The value of the card.
 * \param s The card's suit.
 */
void EPoker::addCard(EPoker::CardValue v, EPoker::CardSuit s)
{
	cards |= (1ULL << cardsIndexOf(v, s));
	values |= (1ULL << static_cast<int>(v));
	rankValid = false;
}

/*!
 * This function removes the card denoted by the given value and suit from this
 * hand. If the card is not in the hand, then no action is taken.
 *
 * \param v The value of the card.
 * \param s The card's suit.
 */
void EPoker::removeCard(EPoker::CardValue v, EPoker::CardSuit s)
{
	// Remove the card.

	cards &= ~(1ULL << cardsIndexOf(v, s));

	// Update the values list.

	if((cards & getValueIsolator(v)) != 0)
		values &= (1ULL << static_cast<int>(v));

	// Invalidate our existing rank.

	rankValid = false;
}

/*!
 * This function clears our object of all cards.
 */
void EPoker::clear()
{
	cards = 0;
	values = 0;
	rankValid = false;
	rank = HighCard;
	rankCards = 0;
}

/*!
 * This function returns whether or not our object contains at least one card
 * with the given value, in any suit.
 *
 * \param v The value to search for.
 * \return True if our object contains a matching card, or false otherwise.
 */
bool EPoker::containsValue(EPoker::CardValue v) const
{
	return ((values & (1ULL << static_cast<int>(v))) > 0);
}

/*!
 * This function returns whether or not our object contains the given card.
 *
 * \param v The value of the desired card.
 * \param s The suit of the desired card.
 * \return True if our object contains that card, or false otherwise.
 */
bool EPoker::containsCard(EPoker::CardValue v, EPoker::CardSuit s) const
{
	return ((cards & (1ULL << cardsIndexOf(v, s))) > 0);
}

/*!
 * This function returns a string representation of this hand, in the format:
 *
 *     VS VS VS VS VS
 *
 * Where V is one of: 23456789TJQKA and S is one of: C(lubs), D(iamonds),
 * H(earts) or S(pades).
 *
 * Note that, if this hand isn't valid, then we will return an empty string
 * instead.
 *
 * \return A string representation of this hand.
 */
std::string EPoker::toString() const
{
	std::string ret = "";

	if(isValid())
	{
		uint64_t c = cards;

		while(c != 0)
		{
			uint64_t card = EBitwise::rmoIsolate(c);
			c = c & ~card;

			uint32_t idx = EBitwise::lg64(card);

			switch(valueOfIndex(idx))
			{
			case EPoker::Two:
				ret.append("2");
				break;
			case EPoker::Three:
				ret.append("3");
				break;
			case EPoker::Four:
				ret.append("4");
				break;
			case EPoker::Five:
				ret.append("5");
				break;
			case EPoker::Six:
				ret.append("6");
				break;
			case EPoker::Seven:
				ret.append("7");
				break;
			case EPoker::Eight:
				ret.append("8");
				break;
			case EPoker::Nine:
				ret.append("9");
				break;
			case EPoker::Ten:
				ret.append("T");
				break;
			case EPoker::Jack:
				ret.append("J");
				break;
			case EPoker::Queen:
				ret.append("Q");
				break;
			case EPoker::King:
				ret.append("K");
				break;
			case EPoker::Ace:
				ret.append("A");
				break;
			};

			switch(suitOfIndex(idx))
			{
			case EPoker::Clubs:
				ret.append("C");
				break;
			case EPoker::Diamonds:
				ret.append("D");
				break;
			case EPoker::Hearts:
				ret.append("H");
				break;
			case EPoker::Spades:
				ret.append("S");
				break;
			};

			ret.append(" ");
		}

		ret = ret.substr(0, ret.size() - 1);
	}

	return ret;
}

/*!
 * This function returns a bit mask which, when AND'ed with our cards list, will
 * return only the cards whose value is the one specified, regardless of suit.
 */
uint64_t EPoker::getValueIsolator(EPoker::CardValue v) const
{
	uint64_t iso = 0;

	iso |= (1ULL << cardsIndexOf(v, EPoker::Clubs));
	iso |= (1ULL << cardsIndexOf(v, EPoker::Diamonds));
	iso |= (1ULL << cardsIndexOf(v, EPoker::Hearts));
	iso |= (1ULL << cardsIndexOf(v, EPoker::Spades));

	return iso;
}

/*!
 * This function returns the index of the bit in our cards list which represents
 * the card of the given value of the given suit.
 *
 * \param v The value of the card.
 * \param s The card's suit.
 * \return The index representing the card.
 */
int EPoker::cardsIndexOf(EPoker::CardValue v, EPoker::CardSuit s) const
{
	return (static_cast<int>(v) * 4) + static_cast<int>(s);
}

/*!
 * This function returns the card value represented by a bit at the given index
 * in our cards list.
 *
 * \param i The index to interpret.
 * \return The card value the index corresponds to.
 */
EPoker::CardValue EPoker::valueOfIndex(uint32_t i) const
{
	return static_cast<EPoker::CardValue>(i / 4);
}

/*!
 * This function returns the card suit represented by a bit at the given index
 * in our cards list.
 *
 * \param i The index to interpret.
 * \return The card suit the index corresponds to.
 */
EPoker::CardSuit EPoker::suitOfIndex(uint32_t i) const
{
	return static_cast<EPoker::CardSuit>(i % 4);
}

/*!
 * This function accepts a list of cards (this should be in the normal,
 * suit-inclusive format), and returns a list of values, ignoring suits. This
 * means that the highest bit which can be set in our result is 1 << 12.
 *
 * This is useful to compare the "high cards" of a hand, for instance.
 *
 * \param c The list of cards to interpret.
 * \return A list of card VALUES based upon the given card list.
 */
uint64_t EPoker::getComparableValuesList(uint64_t c) const
{
	uint64_t vals = 0, card;
	uint32_t idx;

	while(c != 0)
	{
		card = EBitwise::rmoIsolate(c);
		c &= ~card;
		idx = EBitwise::lg64(card);
		vals |= (1ULL << static_cast<int>(valueOfIndex(idx)));
	}

	return vals;
}

/*!
 * This function takes our hand's cards and builds a numeric rank from them.
 * This allows us to quickly compare two hands to see which "beats" the other.
 *
 * Note that if isValid() returns false, then this function will just clear the
 * rank, because it has no valid hand to build a rank from.
 */
void EPoker::buildRank() const
{
	if(isValid() && (!rankValid))
	{
		// Collect some attributes of this hand so we can analyze it.

		std::map<EPoker::CardValue, int> valueCount;
		std::set<EPoker::CardValue> valuess;
		std::set<EPoker::CardSuit> suits;

		{
			uint64_t c = cards;

			uint64_t card;
			uint32_t idx;
			std::map<EPoker::CardValue, int>::iterator it;
			EPoker::CardValue val;

			while(c != 0)
			{
				// Retrieve the next card.

				card = EBitwise::rmoIsolate(c);
				c &= ~card;

				idx = EBitwise::lg64(card);

				// Update the value count list for this value.

				val = valueOfIndex(idx);

				it = valueCount.find(val);

				if(it != valueCount.end())
					++it->second;
				else
					valueCount.insert(
					        std::pair<EPoker::CardValue,
					                  int>(val, 1));

				// Add its value to the values list.

				valuess.insert(val);

				// Add its suit to the suits list.

				suits.insert(suitOfIndex(idx));
			}
		}

		// Determine if our hand is a straight or a flush.

		bool flush = (suits.size() == 1);

		bool straight = true;

		{
			std::set<EPoker::CardValue>::iterator iti, itj;

			if(valuess.size() != 5)
			{
				straight = false;
			}
			else
			{
				for(iti = valuess.begin(); iti != valuess.end();
				    ++iti)
				{
					itj = iti;
					++itj;

					if(itj == valuess.end())
						break;

					if(((*itj) - (*iti)) > 1)
					{
						straight = false;
						break;
					}
				}
			}

			// Check if this hand is the steel wheel.

			if(values == 0x000000000000100FULL)
				straight = true;
		}

		// If we've already found the highest rank, we're done.

		if(straight && flush)
		{
			rankCards = cards;
			rank = EPoker::StraightFlush;
			rankValid = true;
			return;
		}

		// Next, check for either four of a kind or a full house.

		if(valueCount.size() == 2)
		{
			std::map<EPoker::CardValue, int>::iterator it;
			int a, b, av, bv;

			it = valueCount.begin();
			a = it->second;
			av = static_cast<int>(it->first);
			++it;
			b = it->second;
			bv = static_cast<int>(it->second);

			if(a > b)
			{
				int hold = a;
				a = b;
				b = hold;

				hold = av;
				av = bv;
				bv = hold;
			}

			if((a == 1) && (b == 4))
			{
				rankCards =
				        cards &
				        getValueIsolator(
				                static_cast<EPoker::CardValue>(
				                        bv));
				rank = EPoker::FourOfAKind;
				rankValid = true;
				return;
			}
			else if((a == 2) && (b == 3))
			{
				rankCards = cards;
				rank = EPoker::FullHouse;
				rankValid = true;
				return;
			}
		}

		// Check for just a normal flush or straight.

		if(flush)
		{
			rankCards = cards;
			rank = EPoker::Flush;
			rankValid = true;
			return;
		}

		if(straight)
		{
			rankCards = cards;
			rank = EPoker::Straight;
			rankValid = true;
			return;
		}

		// Check for three of a kind or two pairs.

		if(valueCount.size() == 3)
		{
			std::map<EPoker::CardValue, int>::iterator it;
			int a, b, c, av, bv, cv;

			it = valueCount.begin();
			a = it->second;
			av = static_cast<int>(it->first);
			++it;
			b = it->second;
			bv = static_cast<int>(it->first);
			++it;
			c = it->second;
			cv = static_cast<int>(it->first);

			if(a > b)
			{
				int hold = a;
				a = b;
				b = hold;

				hold = av;
				av = bv;
				bv = hold;
			}

			if(b > c)
			{
				int hold = b;
				b = c;
				c = hold;

				hold = bv;
				bv = cv;
				cv = hold;
			}

			if(a > b)
			{
				int hold = a;
				a = b;
				b = hold;

				hold = av;
				av = bv;
				bv = hold;
			}

			if((a == 1) && (b == 1) && (c == 3))
			{
				rankCards =
				        cards &
				        getValueIsolator(
				                static_cast<EPoker::CardValue>(
				                        cv));
				rank = EPoker::ThreeOfAKind;
				rankValid = true;
				return;
			}
			else if((a == 1) && (b == 2) && (c == 2))
			{
				rankCards =
				        cards &
				        (getValueIsolator(
				                 static_cast<EPoker::CardValue>(
				                         bv)) |
				         getValueIsolator(
				                 static_cast<EPoker::CardValue>(
				                         cv)));
				rank = EPoker::TwoPair;
				rankValid = true;
				return;
			}
		}

		// Finally, check for one pair.

		if(valueCount.size() == 4)
		{
			for(std::map<EPoker::CardValue, int>::iterator it =
			            valueCount.begin();
			    it != valueCount.end(); ++it)
			{
				if(it->second == 2)
				{
					rankCards = cards &
					            getValueIsolator(it->first);
					break;
				}
			}

			rank = EPoker::OnePair;
			rankValid = true;
			return;
		}

		// By default, this hand is just a high card hand.

		rankCards = cards;
		rank = EPoker::HighCard;
		rankValid = true;
	}
}

/*!
 * This function compares our hand's value with another hand's value. We return
 * a value less than, equal to or greater than zero if this hand is less than,
 * equal to or greater than the given other hand, respectively.
 *
 * Note that, if either hand is invalid, then our return value is undefined. It
 * is up to the caller to verify this, if necessary, before comparing two hands.
 *
 * \param o The hand to compare ourself to.
 * \return The comparison result, as described above.
 */
int EPoker::compare(const EPoker &o) const
{
	// Compute the ranks of the hands.

	buildRank();
	o.buildRank();

	// First, see if we can determine the result based only on the rank.

	if(static_cast<int>(rank) < static_cast<int>(o.rank))
	{
		return -1;
	}
	else if(static_cast<int>(rank) > static_cast<int>(o.rank))
	{
		return 1;
	}
	else
	{
		// We need to compare the cards in either hand, since their rank
		// is the same.

		switch(rank)
		{
		case EPoker::HighCard:
		case EPoker::Flush:
		{
			// For these hands, we simply compare the highest values
			// in the hands.

			if(values < o.values)
				return -1;
			else if(values > o.values)
				return 1;
			else
				return 0;
		}

		case EPoker::Straight:
		case EPoker::StraightFlush:
		{
			// For these two hands, compare high cards, taking into
			// account the "steel wheel."

			// Check for either hand (or both) being the "steel
			// wheel."

			bool asw = false, bsw = false;

			if(containsValue(EPoker::Ace) &&
			   containsValue(EPoker::Two))
				asw = true;

			if(o.containsValue(EPoker::Ace) &&
			   o.containsValue(EPoker::Two))
				bsw = true;

			if(asw && bsw)
				return 0;
			else if(asw)
				return -1;
			else if(bsw)
				return 1;

			// Otherwise, just compare the highest card, like
			// normal.

			if(values < o.values)
				return -1;
			else if(values > o.values)
				return 1;
			else
				return 0;
		}

		case EPoker::OnePair:
		case EPoker::TwoPair:
		case EPoker::ThreeOfAKind:
		case EPoker::FourOfAKind:
		{
			// For these hands, we compare the cards in the hand,
			// and then the other cards.

			uint64_t arv = getComparableValuesList(rankCards),
			         brv = getComparableValuesList(o.rankCards),
			         aov, bov;

			if(arv < brv)
			{
				return -1;
			}
			else if(arv > brv)
			{
				return 1;
			}
			else
			{
				aov = getComparableValuesList(cards &
				                              ~rankCards);
				bov = getComparableValuesList(o.cards &
				                              ~o.rankCards);

				if(aov < bov)
					return -1;
				else if(aov > bov)
					return 1;
				else
					return 0;
			}
		}

		case EPoker::FullHouse:
		{
			// For this hand, we compare the three cards, then the
			// two cards.

			uint32_t aa, ab, ba, bb;

			aa = EBitwise::lg64(EBitwise::rmoIsolate(values));
			ab = EBitwise::lg64(values &
			                    ~(1ULL << static_cast<int>(aa)));

			ba = EBitwise::lg64(EBitwise::rmoIsolate(o.values));
			bb = EBitwise::lg64(o.values &
			                    ~(1ULL << static_cast<int>(ba)));

			if(euler::util::bitwise::opop(
			           cards &
			           getValueIsolator(
			                   static_cast<EPoker::CardValue>(
			                           aa))) == 3)
			{
				uint32_t hold = aa;
				aa = ab;
				ab = hold;
			}

			if(euler::util::bitwise::opop(
			           o.cards &
			           getValueIsolator(
			                   static_cast<EPoker::CardValue>(
			                           ba))) == 3)
			{
				uint32_t hold = ba;
				ba = bb;
				bb = hold;
			}

			if(aa < ba)
			{
				return -1;
			}
			else if(aa > ba)
			{
				return 1;
			}
			else
			{
				if(ab < bb)
					return -1;
				else if(ab > bb)
					return 1;
				else
					return 0;
			}
		}
		};

		// If we get to this point, then our rank is invalid. This
		// should never occur.
		assert(false);
		throw std::runtime_error("Invalid rank.");
	}
}

/*!
 * This is our output stream operator, which allows our objects to be easily
 * printed to a standard C++ ostream object. The value printed is effectively
 * the same as that returned by our class's toString() member function.
 *
 * \param out The output stream to which we will write.
 * \param i The QPoker object we will be writing.
 * \return A reference to the output stream, so the operator can be chained.
 */
std::ostream &operator<<(std::ostream &out, const EPoker &i)
{
	out << i.toString();
	return out;
}

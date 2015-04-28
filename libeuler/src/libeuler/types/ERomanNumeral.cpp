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

#include "ERomanNumeral.h"

#include <cstdlib>
#include <sstream>

#include <pcre.h>

#include "libeuler/util/EString.h"

/*!
 * \brief This maps a numeral to its value. These are used for parsing roman numerals.
 */
const std::map<char, uint64_t> ERomanNumeral::VALUES = {
	{ 'I', 1    },
	{ 'V', 5    },
	{ 'X', 10   },
	{ 'L', 50   },
	{ 'C', 100  },
	{ 'D', 500  },
	{ 'M', 1000 }
};

/*!
 * \brief This is a set of strings and their values, for turning values into numerals.
 */
const std::set<OVPair, ERomanNumeral::OVPairComparator> ERomanNumeral::OUT_VALUES = {
	{ "M",  1000 },
	{ "CM", 900  },
	{ "D",  500  },
	{ "CD", 400  },
	{ "C",  100  },
	{ "XC", 90   },
	{ "L",  50   },
	{ "XL", 40   },
	{ "X",  10   },
	{ "IX", 9    },
	{ "V",  5    },
	{ "IV", 4    },
	{ "I",  1    }
};

/*!
 * This is our default constructor, which creates a new roman numeral object with a
 * default value of 0.
 */
ERomanNumeral::ERomanNumeral()
	: value(0)
{
}

/*!
 * This constructor creates a new roman numeral object with the given initial value.
 *
 * \param v The value for this new object.
 */
ERomanNumeral::ERomanNumeral(uint64_t v)
	: value(0)
{
	setValue(v);
}

/*!
 * This constructor creates a new roman numeral object with an initial value equal to the
 * given roman numeral string. If the given string is invalid (i.e., parse() would return
 * false), then our value is set to 0 instead.
 *
 * \param v The value for this new object, as a roman numeral string.
 */
ERomanNumeral::ERomanNumeral(const std::string &v)
	: value(0)
{
	parse(v);
}

/*!
 * This is our copy constructor, which creates a new roman numeral object which is equal
 * to the given other existing object.
 *
 * \param o The object to copy.
 */
ERomanNumeral::ERomanNumeral(const ERomanNumeral &o)
	: value(0)
{
	*this = o;
}

/*!
 * This is our default destructor, which cleans up & destroys our object.
 */
ERomanNumeral::~ERomanNumeral()
{
}

/*!
 * This is our assignment operator, which sets this roman numeral object equal to the
 * given other object.
 *
 * \param o The object to set ourself equal to.
 * \return A reference to this, for operator chaining.
 */
ERomanNumeral &ERomanNumeral::operator=(const ERomanNumeral &o)
{
	value = o.value;

	return *this;
}

/*!
 * This operator tests if the value of this roman numeral object is equal to the value of
 * the given other roman numeral object.
 *
 * \param o The other object to compare ourself to.
 * \return True if this is equal to the given object, or false otherwise.
 */
bool ERomanNumeral::operator==(const ERomanNumeral &o) const
{
	return value == o.value;
}

/*!
 * This operator tests if the value of this roman numeral object is less than the value of
 * the given other roman numeral object.
 *
 * \param o The other object to compare ourself to.
 * \return True if this is less than the given object, or false otherwise.
 */
bool ERomanNumeral::operator<(const ERomanNumeral &o) const
{
	return value < o.value;
}

/*!
 * This operator tests if the value of this roman numeral object is greater than the value
 * of the given other roman numeral object.
 *
 * \param o The other object to compare ourself to.
 * \return True if this is greater than the given object, or false otherwise.
 */
bool ERomanNumeral::operator>(const ERomanNumeral &o) const
{
	return value > o.value;
}

/*!
 * This operator tests if the value of this roman numeral object is less than or equal to
 * the value of the given other roman numeral object.
 *
 * \param o The other object to compare ourself to.
 * \return True if this is less than or equal to the given object, or false otherwise.
 */
bool ERomanNumeral::operator<=(const ERomanNumeral &o) const
{
	return value <= o.value;
}

/*!
 * This operator tests if this value of this roman numeral object is greater than or equal
 * to the value of the given other roman numeral object.
 *
 * \param o The other object to compare ourself to.
 * \return True if this is greater than or equal to the given object, or false otherwise.
 */
bool ERomanNumeral::operator>=(const ERomanNumeral &o) const
{
	return value >= o.value;
}

/*!
 * This function returns the current numeric value of our roman numeral object.
 *
 * \return This roman numeral's value.
 */
uint64_t ERomanNumeral::getValue() const
{
	return value;
}

/*!
 * This function returns the current value of this roman numeral object, as a minimal
 * roman numeral string. That is, the resulting string uses the smallest possible number
 * of numerals to represent the value.
 *
 * \return This roman numeral's value, as a string.
 */
std::string ERomanNumeral::getStringValue() const
{
	std::stringstream ss;

	uint64_t v = getValue();

	for(std::set<OVPair>::const_iterator it = ERomanNumeral::OUT_VALUES.cbegin();
		it != ERomanNumeral::OUT_VALUES.cend(); ++it)
	{
		while(v >= it->second)
		{
			ss << it->first;
			v -= it->second;
		}
	}

	return ss.str();
}

/*!
 * This function sets the value of this roman numeral object to the given integer value.
 *
 * \param v The new value for this object.
 */
void ERomanNumeral::setValue(uint64_t v)
{
	value = v;
}

/*!
 * This function attempts to set our roman numeral object's value from the given roman
 * numeral string literal. Note that this input string is case-insensitive, and doesn't
 * neccessarily need to be minimal (e.g., this function considers "IIIII" a valid way to
 * represent 5). If the given string can't be parsed because it appears to be invalid, our
 * object's value will be set to 0 and this function will return appropriately.
 *
 * \param v The value string to try and parse.
 * \return True if the string was parsed successfully, or false otherwise.
 */
bool ERomanNumeral::parse(const std::string &v)
{
	pcre *regex;
	const char *error;
	int erroroff;
	int ovector[42];
	int rc, i;

	// Reset our object's value.

	setValue(0);

	// Preprocess our input string.

	std::string pv = v;

	EString::trim(pv);
	EString::strtoupper(pv);

	// Prepare the regular expression we'll use to match the input string.

	std::string regexs = "^(M*)([DCLXVI]M)?(D*)([CLXVI]D)?(C*)([LXVI]C)?(L*)"
		"([XVI]L)?(X*)([VI]X)?(V*)(IV)?(I*)$";

	regex = pcre_compile(regexs.c_str(), 0, &error, &erroroff, NULL);

	if(regex == NULL)
	{
		return false;
	}

	// Execute the regular expression on our input string.

	rc = pcre_exec(regex, NULL, pv.c_str(), static_cast<int>(pv.length()),
		0, 0, ovector, 42);

	if(rc <= 0)
	{
		return false;
	}

	// Process each captured group.

	uint64_t total = 0, gv;

	for(i = 1; i < rc; ++i)
	{
		/*
		 * From our regular expression, we have the following capture groups:
		 *
		 *     i = 1, 3, 5, 7, 9, 11, 13 - Additive groups.
		 *
		 *     i = 2, 4, 6, 8, 10, 12 - Subtractive groups.
		 *
		 * Add their values to the running total, checking that they're valid.
		 */

		// Get this group as a std::string.

		int off = ovector[2 * i];
		int len = ovector[2 * i + 1] - ovector[2 * i];

		std::string group = "";

		if(len > 0)
			group = pv.substr(off, len);

		// Get the value for this group.

		switch(i)
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 9:
			case 11:
			case 13:
			{
				if(!ERomanNumeral::getAdditiveStringValue(group, &gv))
					return false;

				total += gv;
			}
			break;

			case 2:
			case 4:
			case 6:
			case 8:
			case 10:
			case 12:
			{
				if(!ERomanNumeral::getSubtractiveStringValue(group, &gv))
					return false;

				total += gv;
			}
			break;

			default:
				return false;
		}
	}

	// Done!

	value = total;

	return true;
}

/*!
 * This is the () operator of our OVPairComparator struct, which is used to sort output
 * value pairs in descending order.
 *
 * \param a The first output value pair to compare.
 * \param b The second output value pair to compare.
 * \return True if a comes before b, or false otherwise.
 */
bool ERomanNumeral::OVPairComparator::operator()(const OVPair &a, const OVPair &b)
{
	return a.second > b.second;
}

/*!
 * This function computes the numeric value of the given additive string. That is, a
 * string of numerals which contains no "subtractive pairs" (e.g., "IV" = 4). Empty srings
 * are considered valid, and are assumed to have a value of 0.
 *
 * \param s The additive string to examine.
 * \param v This will be set to the resulting value of the string, or 0 on error.
 * \return True if the input string was valid, or false otherwise.
 */
bool ERomanNumeral::getAdditiveStringValue(const std::string &s, uint64_t *v)
{
	// Set our total and value initially.

	uint64_t total = 0;

	*v = 0;

	// If we were given an empty string, we're done.

	if(s.length() == 0)
	{
		return true;
	}

	// Add each character's value to the total.

	for(size_t i = 0; i < s.length(); ++i)
	{
		std::map<char, uint64_t>::const_iterator it =
			ERomanNumeral::VALUES.find(s.at(i));

		if(it == ERomanNumeral::VALUES.cend())
			return false;

		total += it->second;
	}

	// Done!

	*v = total;

	return true;
}

/*!
 * This function computes the numeric value of the given subtractive pair string. That is,
 * the given input string should be a two-character subtractive pair (e.g., "IX" = 9), or
 * an empty string (which results in a value of 0).
 *
 * \param s The subtractive string to examine.
 * \param v This will be set to the resulting value of the string, or 0 on error.
 * \return True if the input string was valid, or false otherwise.
 */
bool ERomanNumeral::getSubtractiveStringValue(const std::string &s, uint64_t *v)
{
	// Reset the value initially.

	*v = 0;

	// If we were given an empty string, we're done.

	if(s.length() == 0)
	{
		return true;
	}

	// Get the value and the subtractive value.

	if(s.length() != 2)
		return false;

	std::map<char, uint64_t>::const_iterator subit =
		ERomanNumeral::VALUES.find(s.at(0));

	std::map<char, uint64_t>::const_iterator valit =
		ERomanNumeral::VALUES.find(s.at(1));

	// Make sure both characters were valid.

	std::map<char, uint64_t>::const_iterator end = ERomanNumeral::VALUES.cend();

	if( (subit == end) || (valit == end) )
		return false;

	if(valit->second < subit->second)
		return false;

	// Set the value and we're done!

	*v = (valit->second - subit->second);

	return true;
}

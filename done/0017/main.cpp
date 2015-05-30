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

#include <sstream>
#include <cctype>
#include <iostream>
#include <cassert>
#include <cstdint>

#include "libeuler/types/EDigitInteger.h"

/*
 * If the numbers 1 to 5 are written out in words: one, two, three, four, five,
 * then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
 *
 * If all the numbers from 1 to 1000 (one thousand) inclusive were written out
 * in words, how many letters would be used?
 *
 * NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and
 * forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20
 * letters. The use of "and" when writing out numbers is in compliance with
 * British usage.
 */

namespace
{
const std::string LITERAL_DIGITS[10] = {"Zero",  "One",  "Two", "Three",
                                        "Four",  "Five", "Six", "Seven",
                                        "Eight", "Nine"};

const std::string LITERAL_SPECIAL[10] = {
        "",        "Eleven",  "Twelve",    "Thirteen", "Fourteen",
        "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

const std::string LITERAL_TEN_MULTIPLES[10] = {
        "",      "Ten",   "Twenty",  "Thirty", "Forty",
        "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

const std::string LITERAL_PLACES[10] = {
        "", "", "", "Hundred", "Thousand", "", "Million", "", "", "Billion"};

/*
 * This function will spell-out an input number -- i.e., "123" becomes "one
 *hundred and twenty-three".
 *
 * It is up to the caller to make sure that dest is large enough; although, this
 *function will not write
 * more than destSize bytes (chars) to dest.
 *
 * that this function can only handle numbers up to the billions, so your input
 *number must be
 * >= 9,999,999,999 (e.g., we can handle up to an unsigned 32-bit integer
 *value).
 *
 * This function returns 1 (TRUE) on success or 0 (FALSE) on failure.
 */
std::string numberToLiteral(uint32_t n)
{
	EDigitInteger edi;
	std::ostringstream oss;
	int i, place;

	edi = n;
	for(i = (edi.digitCount() - 1); i >= 0; --i)
	{ // Loop through each digit in our number.
		place = i + 1;

		switch(place)
		{
		case 10:
			oss << LITERAL_DIGITS[edi.get(i)] << " "
			    << LITERAL_PLACES[place - 1] << " ";
			break;

		case 9:
			if(edi.get(i) > 0)
			{
				oss << LITERAL_DIGITS[edi.get(i)] << " "
				    << LITERAL_PLACES[3] << " ";

				if((edi.get(i - 2) > 0) || (edi.get(i - 1) > 0))
					oss << "and ";
			}

			break;

		case 8:
			if(edi.get(i) == 1)
			{
				if(edi.get(i - 1) > 0)
				{
					oss << LITERAL_SPECIAL[edi.get(i - 1)]
					    << " " << LITERAL_PLACES[place - 1]
					    << " ";
					--i;
				}
			}
			else if(edi.get(i) > 1)
			{
				oss << LITERAL_TEN_MULTIPLES[edi.get(i)];

				if(edi.get(i - 1) > 0)
				{
					oss << "-";
				}
				else
				{
					oss << " " << LITERAL_PLACES[place - 1]
					    << " ";
					--i;
				}
			}

			break;

		case 7:
			if(edi.get(i) > 0)
				oss << LITERAL_DIGITS[edi.get(i)] << " ";

			oss << LITERAL_PLACES[place - 1] << " ";

			break;

		case 6:
			if(edi.get(i) > 0)
			{
				oss << LITERAL_DIGITS[edi.get(i)] << " "
				    << LITERAL_PLACES[3] << " ";

				if((edi.get(i - 2) > 0) || (edi.get(i - 1) > 0))
					oss << "and ";
			}

			break;

		case 5:
			if(edi.get(i) == 1)
			{
				if(edi.get(i - 1) > 0)
				{
					oss << LITERAL_SPECIAL[edi.get(i - 1)]
					    << " " << LITERAL_PLACES[place - 1]
					    << " ";
					--i;
				}
			}
			else if(edi.get(i) > 1)
			{
				oss << LITERAL_TEN_MULTIPLES[edi.get(i)];

				if(edi.get(i - 1) > 0)
				{
					oss << "-";
				}
				else
				{
					oss << " " << LITERAL_PLACES[place - 1]
					    << " ";
					--i;
				}
			}

			break;

		case 4:
			if(edi.get(i) > 0)
				oss << LITERAL_DIGITS[edi.get(i)] << " ";

			oss << LITERAL_PLACES[place] << " ";

			break;

		case 3:
			if(edi.get(i) > 0)
			{
				oss << LITERAL_DIGITS[edi.get(i)] << " "
				    << LITERAL_PLACES[3] << " ";

				if((edi.get(i - 2) > 0) || (edi.get(i - 1) > 0))
					oss << "and ";
			}

			break;

		case 2:
			if(edi.get(i) == 1)
			{
				if(edi.get(i - 1) > 0)
					oss << LITERAL_SPECIAL[edi.get(i - 1)]
					    << " ";
				else
					oss << LITERAL_TEN_MULTIPLES[1] << " ";

				--i;
			}
			else if(edi.get(i) > 1)
			{
				oss << LITERAL_TEN_MULTIPLES[edi.get(i)];

				if(edi.get(i - 1) > 0)
				{
					oss << "-";
				}
				else
				{
					oss << " ";
					--i;
				}
			}

			break;

		case 1:
			if(edi.get(i) > 0)
				oss << LITERAL_DIGITS[edi.get(i)] << " ";

			break;

		default:
			return "";
		};
	}

	return oss.str();
}
}

int main(void)
{
	int count;
	unsigned int j;
	std::string s;

	count = 0;
	for(uint32_t i = 1; i <= 1000; i++)
	{
		s = numberToLiteral(i);

		for(j = 0; j < s.length(); j++)
		{
			if(!isspace(s[j]) && (s[j] != '-'))
				count++;
		}
	}

	std::cout << "The total number of characters used if all of the "
	             "numbers from 1 to 1000 "
	          << "(inclusive) are spelled out is: " << count << "\n";

	assert(count == 21124);
	return 0;
}

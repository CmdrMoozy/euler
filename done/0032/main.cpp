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

#include <iostream>
#include <cassert>
#include <cstdint>
#include <set>

#include "libeuler/util/EArrayUtilities.h"

/*
 * We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly
 * once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.
 *
 * The product 7254 is unusual, as the identity, 39 x 186 = 7254, containing multiplicand, multiplier,
 * and product is 1 through 9 pandigital.
 *
 * Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1
 * through 9 pandigital.
 *
 * HINT: Some products can be obtained in more than one way so be sure to include it only once in your
 * sum.
 */

int main(void)
{
	std::set<uint64_t> products; // A std::set eliminates any duplicate products.
	uint8_t digits[9] = {1,2,3,4,5,6,7,8,9};
	uint64_t product, a, b, total;
	int i, j;
	std::set<uint64_t>::iterator it;
	
	do
	{
		
		/*
		 * We know that the product of two numbers which contain m and n digits respectively
		 * is always between (m+n-1) and (m+n) in length.
		 *
		 * Because of this, along with the fact that the multiplicative identity we are checking
		 * MUST contain all 9 numbers from 1-9 (inclusive), we know that the product must be either
		 * 4 or 5 digits in length.
		 *
		 * (If the product were more than 5 digits in length, there aren't enough remaining digits
		 * to produce it. If the product were less than 4 digits, the remaining digits would have
		 * to product a larger product than the one given.)
		 */
		
		// Test the four-digit product.
		
		product = digits[5];
		product = (product * 10) + digits[6];
		product = (product * 10) + digits[7];
		product = (product * 10) + digits[8];
		
		for(i = 1; i <= 4; ++i)
		{ // The number of digits in the first number are between 1 and 4.
			
			a = b = 0;
			
			// Build the first number.
			for(j = 0; j < i; ++j)
				a = (a * 10) + digits[j];
			
			// Build the second number.
			for(j = i; j <= 4; ++j)
				b = (b * 10) + digits[j];
			
			// If we've formed the product successfully, add it to the list.
			if(product == (a*b))
				products.insert(product);
			
		}
		
		// Test the five-digit product.
		
		product += static_cast<uint64_t>(digits[4]) * 10000;
		
		for(i = 1; i <= 3; ++i)
		{ // The number of digits in the first number are between 1 and 3.
			
			a = b = 0;
			
			// Build the first number.
			for(j = 0; j < i; ++j)
				a = (a * 10) + digits[j];
			
			// Build the second number.
			for(j = i; j <= 3; ++j)
				b = (b * 10) + digits[j];
			
			// If we've formed the product successfully, add it to the list.
			if(product == (a*b))
				products.insert(product);
			
		}
		
	} while(EArrayUtilities::permutate<uint8_t>(digits, 9));
	
	// Get the sum of all of the unique products we were able to form.
	total = 0;
	for(it = products.begin(); it != products.end(); it++)
		total += (*it);
	
	// Print the answer!
	std::cout << "The sum of the products whose multiplicative identity is 1-9 pandigital is: " << total << "\n";
	assert(total == 45228);
	
	return 0;
}

#include <iostream>
#include <cassert>

#include "libeuler/util/EDate.h"

/*
 * You are given the following information, but you may prefer to do some reasearch for yourself.
 *
 * - 1 Jan 1900 was a Monday.
 * - Thirty days has September,
 *   April, June and November.
 *   All the rest have thirty-one,
 *   Saving February alone,
 *   Which has twenty-eight, rain or shine
 *   And on leap years, twenty-nine.
 * - A leap year occurs on any year evenly divisible by 4, but not on a century unless it is
 *   divisble by 400.
 *
 * How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to
 * 31 Dec 2000)?
 */

int main(void)
{
	int s;
	EDate d(1900, 1, 1, EDate::Monday);
	EDate e(2000, 12, 31);
	
	// Fast-forward to the start of our interval, 1901/01/01.
	d.addDays(EDate::getDaysInYear(1900));
	
	// Progress to our first Sunday.
	while(d.getDayOfWeek() != EDate::Sunday)
		d.addDays(1);
	
	// Keep looping from here until we have found every Sunday!
	s = 0;
	do
	{
		if(d.getDay() == 1)
			s++;
		
		d.addWeeks(1);
	} while(d < e);
	
	std::cout << "The number of Sundays that fell on the first of the month between 1901/01/01 and " <<
		"2000/12/31 (inclusive) is: " << s << "\n";
	
	assert(s == 171);
	return 0;
}

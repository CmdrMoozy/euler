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

#include "EDate.h"

/*!
 * This function converts our EDate::DayOfWeek value to a literal string, so it
 * can be (for instance) printed out.
 *
 * \param d The numerical day-of-the-week.
 * \return The literal representation of the given value.
 */
std::string EDate::dayOfWeekToString(EDate::DayOfWeek d)
{
	switch(d)
	{
	case EDate::Sunday:
		return "Sunday";
	case EDate::Monday:
		return "Monday";
	case EDate::Tuesday:
		return "Tuesday";
	case EDate::Wednesday:
		return "Wednesday";
	case EDate::Thursday:
		return "Thursday";
	case EDate::Friday:
		return "Friday";
	case EDate::Saturday:
		return "Saturday";
	};

	return "";
}

/*!
 * This function returns the number of days in the given month of the given
 * year, taking into account leap-years and whatnot. Note that the year only
 * matters for February; the rest of the time, one can just use the
 * randomly-selected default year value by not passing their own value.
 *
 * \param m The numeric month.
 * \param y The numeric year.
 * \return The number of days in the given month.
 */
int EDate::getDaysInMonth(int m, int y)
{
	switch(m)
	{
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;

	case 2:
		switch(EDate::getDaysInYear(y))
		{
		case 365:
			return 28;

		case 366:
			return 29;
		};
		break;
	};

	return 31;
}

/*!
 * This function returns the number of days in a given year, including
 * leap-years and leap-centuries and whatnot.
 *
 * \param y The year.
 * \return The number of days in the given year.
 */
int EDate::getDaysInYear(int y)
{
	if((y % 100) != 0)
	{
		if((y % 4) != 0)
			return 365;
		else
			return 366;
	}
	else
	{
		if((y % 400) != 0)
			return 365;
		else
			return 366;
	}
}

/*!
 * This is our default constructor, which initializes our date to the given
 * year, month and day, and (optionally) accounting for the given day of the
 * week.
 *
 * \param y The year.
 * \param m The month.
 * \param d The day.
 * \param dow The day of the week.
 */
EDate::EDate(int y, int m, int d, EDate::DayOfWeek dow)
        : year(y), month(m), day(d), dayOfWeek(dow)
{
}

/*!
 * This is our default constructor, which cleans up & destroys our object.
 */
EDate::~EDate()
{
}

/*!
 * This is one of our comparison operators, which tests whether our object is
 * less than the value of the given other object.
 *
 * \param o The other date to compare ourself to.
 * \return True if our date is less than the other date, or false otherwise.
 */
bool EDate::operator<(const EDate &o) const
{
	if(getYear() > o.getYear())
		return false;
	else if(getYear() < o.getYear())
		return true;
	else
	{
		if(getMonth() > o.getMonth())
			return false;
		else if(getMonth() < o.getMonth())
			return true;
		else
		{
			if(getDay() < o.getDay())
				return true;
			else
				return false;
		}
	}
}

/*!
 * This function returns our current year value.
 *
 * \return The year our object represents.
 */
int EDate::getYear() const
{
	return year;
}

/*!
 * This function returns our current month value.
 *
 * \return The month our object represents.
 */
int EDate::getMonth() const
{
	return month;
}

/*!
 * This function returns our current day value.
 *
 * \return The day our object represents.
 */

int EDate::getDay() const
{
	return day;
}

/*!
 * This function returns our current day-of-the-week.
 *
 * \return The day-of-the-week our object represents.
 */
EDate::DayOfWeek EDate::getDayOfWeek() const
{
	return dayOfWeek;
}

/*!
 * This function adds a given number of days to our object's current date,
 * accounting for rollovers in the month and year, as well as keeping track of
 * the correct day-of-the-week.
 *
 * \param d The number of days to add.
 */
void EDate::addDays(int d)
{
	int i;

	for(i = 0; i < d; i++)
	{
		day++;
		switch(dayOfWeek)
		{
		case EDate::Sunday:
			dayOfWeek = EDate::Monday;
			break;

		case EDate::Monday:
			dayOfWeek = EDate::Tuesday;
			break;

		case EDate::Tuesday:
			dayOfWeek = EDate::Wednesday;
			break;

		case EDate::Wednesday:
			dayOfWeek = EDate::Thursday;
			break;

		case EDate::Thursday:
			dayOfWeek = EDate::Friday;
			break;

		case EDate::Friday:
			dayOfWeek = EDate::Saturday;
			break;

		case EDate::Saturday:
			dayOfWeek = EDate::Sunday;
			break;
		};

		if(day > EDate::getDaysInMonth(month, year))
		{
			day = 1;
			month++;
		}

		if(month > 12)
		{
			month = 1;
			year++;
		}
	}
}

/*!
 * This is a convenience function that adds a given number of weeks to our
 * object's current date. This is equivalent to addDays(w * 7).
 *
 * \param w The number of weeks to add to our date.
 */
void EDate::addWeeks(int w)
{
	addDays(w * 7);
}
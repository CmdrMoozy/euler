#ifndef INCLUDE_LIBEULER_UTIL_DATE_H
#define INCLUDE_LIBEULER_UTIL_DATE_H

#include <string>

/*!
 * \brief This class allows doing math with dates.
 *
 * It implements some basic functionality, most notably the ability to keep track of the
 * day of the week while adding a certain number of days to the current date. Note that since,
 * as of right now, this class is only utilized by a single problem, there is quite a bit
 * of functionality that probably should be but isn't implemented right now. As such, this
 * class is pretty barebones.
 */
class EDate
{
	public:
		enum DayOfWeek
		{
			Sunday,
			Monday,
			Tuesday,
			Wednesday,
			Thursday,
			Friday,
			Saturday
		};
		
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
		
		static std::string dayOfWeekToString(EDate::DayOfWeek d);
		static int getDaysInMonth(int m, int y = 2011);
		static int getDaysInYear(int y);
		
		EDate(int y, int m, int d, EDate::DayOfWeek dow = EDate::Friday);
		virtual ~EDate();
		
		bool operator<(const EDate &o) const;
		
		int getYear() const;
		int getMonth() const;
		int getDay() const;
		EDate::DayOfWeek getDayOfWeek() const;
		
		void addDays(int d);
		void addWeeks(int w);
		
	private:
		int year, month, day;
		EDate::DayOfWeek dayOfWeek;
};

#endif

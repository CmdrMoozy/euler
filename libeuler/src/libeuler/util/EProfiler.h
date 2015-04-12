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

#ifndef INCLUDE_LIBEULER_UTIL_PROFILER
#define INCLUDE_LIBEULER_UTIL_PROFILER

#if (defined _WIN32 || defined __APPLE__)
	#include <cstdint>
#endif

/*!
 * \brief This class provides easy-to-use profiling for applications.
 *
 * It utilizes OS-dependant high precision timers to calculate the amount of time that has
 * passed between the object's instantiation and its destruction. Timer precision varies by
 * operating system, but it is safe to assume the accuracy of this timer approaches the
 * nanosecond level.
 *
 * This class is currently implemented on:
 *     Windows
 *     Linux/UNIX
 *     Mac
 */
class EProfiler
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
		
		EProfiler();
		virtual ~EProfiler();
	
		double done();
		
	private:
		#ifdef _WIN32
			int64_t rate;
			double start;
			double end;
		#elif defined __APPLE__
			uint64_t start;
			uint64_t end;
		#else
			double start;
			double end;
		#endif
};

#endif

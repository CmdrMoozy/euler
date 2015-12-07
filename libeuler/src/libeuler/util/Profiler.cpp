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

#include "Profiler.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#ifdef LIBEULER_DEBUG
#include <cmath>
#include <thread>

#include "libeuler/EDefines.h"
#include "libeuler/EExceptions.h"
#endif

namespace euler
{
#ifdef LIBEULER_DEBUG
/*!
 * This function implements our test suite for this class. It uses
 * non-abort()'ing assertions, and merely prints the result to stdout.
 */
void Profiler::doTestSuite()
{
	bool success = true;

	std::cout << "\tTesting 'Profiler'...\t\t\t";
	try
	{
		// Make sure timing on a one-second sleep is fairly accurate.
		for(int i = 0; i < 10; ++i)
		{
			Profiler p;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			double t = std::abs(1.0 - p.getElapsed());
			EASSERT(t < 0.1);
		}

		// Check a ten-second sleep as well.
		Profiler p;
		std::this_thread::sleep_for(std::chrono::seconds(10));
		double lt = std::abs(10.0 - p.getElapsed());
		EASSERT(lt < 0.1);
	}
	catch(EAssertionException &)
	{
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
 * This is our constructor, which records our "starting" time.
 *
 * \param p Whether or not to print the elasped time on destruction.
 * \param pp The string to prefix when printing profile results.
 */
Profiler::Profiler(bool p, std::string const &pp)
        : print(p),
          printPrefix(pp),
          start(std::chrono::high_resolution_clock::now())
{
}

/*!
 * This is our destructor, which will print the time elapsed since
 * construction to standard output (if enabled).
 */
Profiler::~Profiler()
{
	if(print)
		printElapsed();
}

/*!
 * \return The number of seconds elapsed since this instance was constructed.
 */
double Profiler::getElapsed() const
{
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(
	        end - start);
	return static_cast<double>(elapsed.count()) / 1000000000.0;
}

/*!
 * This function prints the current elapsed time since construction to
 * standard output.
 */
void Profiler::printElapsed() const
{
	double elapsed = getElapsed();
	std::ostringstream oss;
	oss << printPrefix << "Profiler: " << std::fixed << std::setprecision(4)
	    << elapsed << "s\n";
	std::cout << oss.str();
}
}

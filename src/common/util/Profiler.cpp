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

#include <cstdio>

namespace euler
{
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
	std::fprintf(stdout, "%sElapsed time: %0.9fs\n", printPrefix.c_str(),
	             elapsed);
}
}

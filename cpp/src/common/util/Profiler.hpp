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

#ifndef common_util_Profiler_HPP
#define common_util_Profiler_HPP

#include <chrono>
#include <string>

namespace euler
{
namespace util
{
/*!
 * \brief This class provides easy-to-use profiling for applications.
 */
class Profiler
{
public:
	Profiler(bool p = false, std::string const &pp = "");
	~Profiler();

	double getElapsed() const;
	void printElapsed() const;

private:
	bool print;
	std::string printPrefix;
	std::chrono::high_resolution_clock::time_point start;
};
}
}

#endif

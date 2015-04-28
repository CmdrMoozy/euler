/*
 * euler - A collection of ProjectEuler solutions, and supporting libraries and
 *tools.
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

#ifndef INCLUDE_TESTS_MATH_MATH_TEST_H
#define INCLUDE_TESTS_MATH_MATH_TEST_H

#include <Vrfy/Vrfy.h>

namespace euler
{
namespace test
{
/*!
 * \brief This class defines unit test for our various math utilities.
 */
class MathTest : public vrfy::Test
{
public:
	MathTest() = default;
	virtual ~MathTest() = default;

	/*!
	 * This function executes all of the tests this class defines.
	 */
	virtual void test() override;
};
}
}

#endif

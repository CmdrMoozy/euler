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

#include "EExceptions.h"

/*!
 * This is a standard constructor for our class. It simply sets our exception
 *text to the given string.
 *
 * \param wh The exception text to use.
 */
EException::EException(const std::string &wh) : w(wh)
{
}

/*!
 * This is the accessor function that returns our exception string. It returns a
 *cstring, because
 * std::string's copy constructor can throw an exception. This function MUST NOT
 *throw any exceptions.
 *
 * \return A C-string version of our exception text.
 */
const char *EException::what() const noexcept
{
	return w.c_str();
}

EAssertionException::EAssertionException(const std::string &wh) : EException(wh)
{
}

/*!
 * This is a standard constructor for our class. It simply sets our exception
 *text to the given string.
 *
 * \param wh The exception text to use.
 */
EOutOfBoundsException::EOutOfBoundsException(const std::string &wh)
        : EException(wh)
{
}

/*!
 * This is a standard constructor for our class. It simply sets our exception
 *text to the given string.
 *
 * \param wh The exception text to use.
 */
EValueRangeException::EValueRangeException(const std::string &wh)
        : EException(wh)
{
}

/*!
 * This is a standard constructor for our class. It simply sets our exception
 *text to the given string.
 *
 * \param wh The exception text to use.
 */
EOverflowException::EOverflowException(const std::string &wh) : EException(wh)
{
}

/*!
 * This is a standard constructor for our class. It simply sets our exception
 *text to the given string.
 *
 * \param wh The exception text to use.
 */
EUnderflowException::EUnderflowException(const std::string &wh) : EException(wh)
{
}

/*!
 * This is a standard constructor for our class. It simply sets our exception
 *text to the given string.
 *
 * \param wh The exception text to use.
 */
EDivideByZeroException::EDivideByZeroException(const std::string &wh)
        : EException(wh)
{
}

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

#include "BigDecimal.hpp"

namespace euler
{
BigDecimal::BigDecimal()
{
	mpfr_init(value);
}

BigDecimal::~BigDecimal()
{
	mpfr_clear(value);
}

mpfr_t &BigDecimal::get()
{
	return const_cast<mpfr_t &>(
	        static_cast<BigDecimal const *>(this)->get());
}

mpfr_t const &BigDecimal::get() const
{
	return value;
}
}

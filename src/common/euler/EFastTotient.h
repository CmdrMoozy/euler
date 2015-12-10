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

#ifndef INCLUDE_LIBEULER_EULER_FAST_TOTIENT_H
#define INCLUDE_LIBEULER_EULER_FAST_TOTIENT_H

#include <cstdint>

class EPrimeSieve;

class EFastTotient
{
public:
	EFastTotient(EPrimeSieve *s, uint32_t l = 0);
	virtual ~EFastTotient();

	uint32_t getLimit() const;
	void setLimit(uint32_t l);

	uint32_t totient(uint32_t n);

private:
	EPrimeSieve *sieve;
};

#endif

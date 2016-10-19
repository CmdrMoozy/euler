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

#include <cstddef>
#include <cstdint>

#include "common/structs/BitArray.hpp"

namespace euler
{
namespace math
{
class PrimeSieve
{
public:
	PrimeSieve(uint64_t l);

	PrimeSieve(PrimeSieve const &) = delete;
	PrimeSieve(PrimeSieve &&) = default;
	PrimeSieve &operator=(PrimeSieve const &) = delete;
	PrimeSieve &operator=(PrimeSieve &&) = default;

	~PrimeSieve() = default;

	uint64_t getLimit() const;
	void setLimit(uint64_t l);

	std::size_t size() const;

	bool contains(uint64_t n) const;

private:
	uint64_t limit;
	euler::structs::BitArray isPrime;
};
}
}

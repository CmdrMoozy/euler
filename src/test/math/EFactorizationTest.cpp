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

#include <catch/catch.hpp>

#include <cstdint>
#include <map>
#include <set>

#include "common/math/EFactorization.h"

TEST_CASE("Test prime factors and all factors for 56", "[EFactorization]")
{
	EFactorization f(56);
	std::map<uint32_t, uint32_t> primes = f.getPrimeFactors();
	std::set<uint32_t> all = f.getAllFactors();

	CHECK(f.getPrimeFactorsCount() == 2);
	CHECK(primes.size() == 2);
	REQUIRE(primes.find(2) != primes.end());
	CHECK(primes.find(2)->second == 3);
	REQUIRE(primes.find(7) != primes.end());
	CHECK(primes.find(7)->second == 1);

	CHECK(f.getAllFactorsCount() == 8);
	CHECK(all.size() == 8);
	CHECK(all.find(1) != all.end());
	CHECK(all.find(2) != all.end());
	CHECK(all.find(4) != all.end());
	CHECK(all.find(7) != all.end());
	CHECK(all.find(8) != all.end());
	CHECK(all.find(14) != all.end());
	CHECK(all.find(28) != all.end());
	CHECK(all.find(56) != all.end());
}

TEST_CASE("Test prime factors and all factors for 150", "[EFactorization]")
{
	EFactorization f(150);
	std::map<uint32_t, uint32_t> primes = f.getPrimeFactors();
	std::set<uint32_t> all = f.getAllFactors();

	CHECK(f.getPrimeFactorsCount() == 3);
	CHECK(primes.size() == 3);
	REQUIRE(primes.find(2) != primes.end());
	CHECK(primes.find(2)->second == 1);
	REQUIRE(primes.find(3) != primes.end());
	CHECK(primes.find(3)->second == 1);
	REQUIRE(primes.find(5) != primes.end());
	CHECK(primes.find(5)->second == 2);

	CHECK(f.getAllFactorsCount() == 12);
	CHECK(all.size() == 12);
	CHECK(all.find(1) != all.end());
	CHECK(all.find(2) != all.end());
	CHECK(all.find(3) != all.end());
	CHECK(all.find(5) != all.end());
	CHECK(all.find(6) != all.end());
	CHECK(all.find(10) != all.end());
	CHECK(all.find(15) != all.end());
	CHECK(all.find(25) != all.end());
	CHECK(all.find(30) != all.end());
	CHECK(all.find(50) != all.end());
	CHECK(all.find(75) != all.end());
	CHECK(all.find(150) != all.end());
}

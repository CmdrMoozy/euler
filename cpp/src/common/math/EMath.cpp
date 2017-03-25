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

#include "EMath.h"

#include <cmath>
#include <cstdlib>
#include <map>

#include "common/EDefines.h"
#include "common/math/Math.hpp"
#include "common/util/EBitwise.h"

#if(defined _WIN32 || defined __APPLE__)
/*!
 * This is a convenience function, that will return a GMP mpz object whose value
 *is that of
 * the given 64-bit integer.
 *
 * \param n The value we are going to set.
 * \return A GMP object whose value is equal to the one given.
 */
mpz_class EMath::int64ToBigInteger(uint64_t n)
{
	mpz_class r = 0;

	r += static_cast<uint32_t>(n >> 32);
	mpz_mul_2exp(r.get_mpz_t(), r.get_mpz_t(), 32);
	r += static_cast<uint32_t>((n << 32) >> 32);

	return r;
}

/*!
 * This is a convenience function, that will return a GMP mpf object whose value
 *is that of
 * the given 64-bit integer.
 *
 * \param n The value we are going to set.
 * \param p The precision desired for the new object.
 * \return A GMP object whose value is equal to the one given.
 */
mpf_class EMath::int64ToBigFloat(uint64_t n, mp_bitcnt_t p)
{
	mpf_class r(0, p);

	r += static_cast<uint32_t>(n >> 32);
	mpf_mul_2exp(r.get_mpf_t(), r.get_mpf_t(), 32);
	r += static_cast<uint32_t>((n << 32) >> 32);

	return r;
}
#endif

/*!
 * This function returns the nth heptagonal number.
 *
 * \param n The nth heptagonal number will be generated.
 * \return The value of the nth heptagonal number.
 */
uint64_t EMath::getHeptagonalNumberN(uint64_t n)
{
	// The heptagonal number Hn is given by Hn = n(5n-3)/2
	return ((n * (5 * n - 3)) >> 1);
}

/*!
 * This function returns the nth octagonal number.
 *
 * \param n The nth octagonal number will be generated.
 * \return The value of the nth octagonal number.
 */
uint64_t EMath::getOctagonalNumberN(uint64_t n)
{
	// The octagonal number On is given by On = n(3n - 2)
	return (n * (3 * n - 2));
}

/*!
 * This function returns the nth Fibonacci number.
 *
 * The Fibonacci sequence is defined such that F(0) = 0, F(1) = 1, and F(n) =
 *F(n-1) + F(n-2).
 * For this function, however, we use a closed-form solution to the Fibonacci
 *sequence, so we can
 * avoid unnecessary recursion.
 *
 * Note that precision is only guaranteed up to n = 5000.
 *
 * \param n The nth Fibonacci number will be generated.
 * \return The value of the nth Fibonacci number.
 */
mpz_class EMath::getFibonacciNumberN(uint32_t n)
{
	/*
	 * We use the closed-form solution called "Binet's Formula," defined
	 *here:
	 *   http://en.wikipedia.org/wiki/Fibonacci_number#Relation_to_the_golden_ratio
	 *
	 * The formula is:
	 *     F(n) = (p^n - (1 - p)^n) / sqrt(5)
	 *
	 * Where p is phi, the Golden Ratio:
	 *     p = (1 + sqrt(5)) / 2
	 */

	// Since we are dealing with irrational square roots, we want a VERY
	// HIGH level of precision.
	mpf_class sf(5.0, 4000);
	mpf_class p(0.0, 4000);
	mpf_class pn(0.0, 4000), opn(0.0, 4000);
	mpf_class ret(0.0, 4000);

	mpf_sqrt(sf.get_mpf_t(), sf.get_mpf_t());

	p = sf;
	p += 1.0;
	p /= 2.0;

	mpf_pow_ui(pn.get_mpf_t(), p.get_mpf_t(), n);

	opn = 1 - p;
	mpf_pow_ui(opn.get_mpf_t(), opn.get_mpf_t(), n);

	ret = (pn - opn) / sf;
	ret += 0.5;
	mpf_floor(ret.get_mpf_t(), ret.get_mpf_t());

	return mpz_class(ret);
}

/*!
 * This is a convenience function for isPrime(), which just wraps the given
 *primitive value in an mpz_class
 * object.
 *
 * \param n The value to test for primality.
 * \param p The precision with which to perform our test.
 * \return True if the number is probably prime, or false otherwise.
 */
bool EMath::isPrime_UI(uint64_t n, int p)
{
#ifdef _WIN32
	return EMath::isPrime(EMath::int64ToBigInteger(n), p);
#elif defined __APPLE__
	return EMath::isPrime(EMath::int64ToBigInteger(n), p);
#else
	return EMath::isPrime(mpz_class(n), p);
#endif
}

/*!
 * This function tests probabalistically whether or not the given number is
 *probably prime. It
 * takes a precision argument -- a precision of 15 is fairly normal, a precision
 *of 100 is VERY
 * precise.
 *
 * \param n The value to test for primality.
 * \param p The precision with which to perform our test.
 * \return True if the number is probably prime, or false otherwise.
 */
bool EMath::isPrime(const mpz_class &n, int p)
{
	int i;
	mpz_class a, tA;
	gmp_randstate_t randState;

	// If we were given an invalid precision, just use the default of 15.
	p = (p < 1 ? 15 : p);

	// 0 is NOT prime.
	if(n == 0)
		return false;

	// 1 is NOT prime.
	if(n == 1)
		return false;

	// 2 and 3 are prime.
	if((n == 2) || (n == 3))
		return true;

	// Even numbers are NOT prime.
	if((n % 2) == 0)
		return false;

	// Numbers divisible by 3 are NOT prime.
	if((n % 3) == 0)
		return false;

	gmp_randinit_mt(randState);
	for(i = 0; i < p; i++)
	{
		// a = rand [1, value - 1]
		tA = n - 2;
		mpz_urandomm(a.get_mpz_t(), randState, tA.get_mpz_t());
		a += 1;

		// if (a ^ (value - 1) % value) != 1 then our number is not
		// prime.
		tA += 1;
		mpz_powm(tA.get_mpz_t(), a.get_mpz_t(), tA.get_mpz_t(),
		         n.get_mpz_t());
		if(tA != 1)
		{
			gmp_randclear(randState);
			return false;
		}
	}
	gmp_randclear(randState);

	return true;
}

/*!
 * This function tests if the two given integers, a and b, are coprime. Two
 *integers
 * are considered coprime if their greatest common divisor is equal to 1.
 *
 * \param a The first value to check.
 * \param b The second value to check.
 * \return True if a and b are coprime, or false otherwise.
 */
bool EMath::areCoprime(uint32_t a, uint32_t b)
{
	return (euler::math::gcd(a, b) == 1);
}

/*!
 * The totient of a number (also called phi(n)) is defined as the number of
 *positive integers less than
 * or equal to n that are coprime to n.
 *
 * \param n The number to operate on.
 * \return The totient of n.
 */
uint32_t EMath::totient(uint32_t n)
{
	uint32_t i, r;

	for(r = 0, i = 1; i <= n; i++)
		if(EMath::areCoprime(i, n))
			++r;

	return r;
}

/*!
 * This function returns the least common multiple of a and b. To make it easy,
 * we reduce this problem to being able to find the greatest common divisor,
 * which we can already do using the fast Euclidean algorithm.
 *
 * More information:
 *     http://en.wikipedia.org/wiki/Least_common_multiple#Reduction_by_the_greatest_common_divisor
 *
 * Note that this function fails if both a and b are 0.
 *
 * \param a The first integer input.
 * \param b The second integer input.
 * \return The least common multiple of a and b.
 */
uint64_t EMath::leastCommonMultiple(uint64_t a, uint64_t b)
{
	uint64_t gcd = euler::math::gcd(a, b);

	if(gcd == 0)
		return 0;

	return ((a * b) / gcd);
}

/*!
 * This function returns whether or not the given number is a perfect square.
 *
 * \param n The number to test.
 * \return True if n is a square, or false otherwise.
 */
bool EMath::isSquare(uint64_t n)
{
	uint64_t i = euler::math::isqrt(n);

	return ((i * i) == n);

	// TODO - This code fails for n = 206468161
	/*
	// Pre-computed table of values for use in Hensel's lemma lifting.
	static const int start[1024] =
	{
	        1,3,1769,5,1937,1741,7,1451,479,157,9,91,945,659,1817,11,
	        1983,707,1321,1211,1071,13,1479,405,415,1501,1609,741,15,339,1703,203,
	        129,1411,873,1669,17,1715,1145,1835,351,1251,887,1573,975,19,1127,395,
	        1855,1981,425,453,1105,653,327,21,287,93,713,1691,1935,301,551,587,
	        257,1277,23,763,1903,1075,1799,1877,223,1437,1783,859,1201,621,25,779,
	        1727,573,471,1979,815,1293,825,363,159,1315,183,27,241,941,601,971,
	        385,131,919,901,273,435,647,1493,95,29,1417,805,719,1261,1177,1163,
	        1599,835,1367,315,1361,1933,1977,747,31,1373,1079,1637,1679,1581,1753,1355,
	        513,1539,1815,1531,1647,205,505,1109,33,1379,521,1627,1457,1901,1767,1547,
	        1471,1853,1833,1349,559,1523,967,1131,97,35,1975,795,497,1875,1191,1739,
	        641,1149,1385,133,529,845,1657,725,161,1309,375,37,463,1555,615,1931,
	        1343,445,937,1083,1617,883,185,1515,225,1443,1225,869,1423,1235,39,1973,
	        769,259,489,1797,1391,1485,1287,341,289,99,1271,1701,1713,915,537,1781,
	        1215,963,41,581,303,243,1337,1899,353,1245,329,1563,753,595,1113,1589,
	        897,1667,407,635,785,1971,135,43,417,1507,1929,731,207,275,1689,1397,
	        1087,1725,855,1851,1873,397,1607,1813,481,163,567,101,1167,45,1831,1205,
	        1025,1021,1303,1029,1135,1331,1017,427,545,1181,1033,933,1969,365,1255,1013,
	        959,317,1751,187,47,1037,455,1429,609,1571,1463,1765,1009,685,679,821,
	        1153,387,1897,1403,1041,691,1927,811,673,227,137,1499,49,1005,103,629,
	        831,1091,1449,1477,1967,1677,697,1045,737,1117,1737,667,911,1325,473,437,
	        1281,1795,1001,261,879,51,775,1195,801,1635,759,165,1871,1645,1049,245,
	        703,1597,553,955,209,1779,1849,661,865,291,841,997,1265,1965,1625,53,
	        1409,893,105,1925,1297,589,377,1579,929,1053,1655,1829,305,1811,1895,139,
	        575,189,343,709,1711,1139,1095,277,993,1699,55,1435,655,1491,1319,331,
	        1537,515,791,507,623,1229,1529,1963,1057,355,1545,603,1615,1171,743,523,
	        447,1219,1239,1723,465,499,57,107,1121,989,951,229,1521,851,167,715,
	        1665,1923,1687,1157,1553,1869,1415,1749,1185,1763,649,1061,561,531,409,907,
	        319,1469,1961,59,1455,141,1209,491,1249,419,1847,1893,399,211,985,1099,
	        1793,765,1513,1275,367,1587,263,1365,1313,925,247,1371,1359,109,1561,1291,
	        191,61,1065,1605,721,781,1735,875,1377,1827,1353,539,1777,429,1959,1483,
	        1921,643,617,389,1809,947,889,981,1441,483,1143,293,817,749,1383,1675,
	        63,1347,169,827,1199,1421,583,1259,1505,861,457,1125,143,1069,807,1867,
	        2047,2045,279,2043,111,307,2041,597,1569,1891,2039,1957,1103,1389,231,2037,
	        65,1341,727,837,977,2035,569,1643,1633,547,439,1307,2033,1709,345,1845,
	        1919,637,1175,379,2031,333,903,213,1697,797,1161,475,1073,2029,921,1653,
	        193,67,1623,1595,943,1395,1721,2027,1761,1955,1335,357,113,1747,1497,1461,
	        1791,771,2025,1285,145,973,249,171,1825,611,265,1189,847,1427,2023,1269,
	        321,1475,1577,69,1233,755,1223,1685,1889,733,1865,2021,1807,1107,1447,1077,
	        1663,1917,1129,1147,1775,1613,1401,555,1953,2019,631,1243,1329,787,871,885,
	        449,1213,681,1733,687,115,71,1301,2017,675,969,411,369,467,295,693,
	        1535,509,233,517,401,1843,1543,939,2015,669,1527,421,591,147,281,501,
	        577,195,215,699,1489,525,1081,917,1951,2013,73,1253,1551,173,857,309,
	        1407,899,663,1915,1519,1203,391,1323,1887,739,1673,2011,1585,493,1433,117,
	        705,1603,1111,965,431,1165,1863,533,1823,605,823,1179,625,813,2009,75,
	        1279,1789,1559,251,657,563,761,1707,1759,1949,777,347,335,1133,1511,267,
	        833,1085,2007,1467,1745,1805,711,149,1695,803,1719,485,1295,1453,935,459,
	        1151,381,1641,1413,1263,77,1913,2005,1631,541,119,1317,1841,1773,359,651,
	        961,323,1193,197,175,1651,441,235,1567,1885,1481,1947,881,2003,217,843,
	        1023,1027,745,1019,913,717,1031,1621,1503,867,1015,1115,79,1683,793,1035,
	        1089,1731,297,1861,2001,1011,1593,619,1439,477,585,283,1039,1363,1369,1227,
	        895,1661,151,645,1007,1357,121,1237,1375,1821,1911,549,1999,1043,1945,1419,
	        1217,957,599,571,81,371,1351,1003,1311,931,311,1381,1137,723,1575,1611,
	        767,253,1047,1787,1169,1997,1273,853,1247,413,1289,1883,177,403,999,1803,
	        1345,451,1495,1093,1839,269,199,1387,1183,1757,1207,1051,783,83,423,1995,
	        639,1155,1943,123,751,1459,1671,469,1119,995,393,219,1743,237,153,1909,
	        1473,1859,1705,1339,337,909,953,1771,1055,349,1993,613,1393,557,729,1717,
	        511,1533,1257,1541,1425,819,519,85,991,1693,503,1445,433,877,1305,1525,
	        1601,829,809,325,1583,1549,1991,1941,927,1059,1097,1819,527,1197,1881,1333,
	        383,125,361,891,495,179,633,299,863,285,1399,987,1487,1517,1639,1141,
	        1729,579,87,1989,593,1907,839,1557,799,1629,201,155,1649,1837,1063,949,
	        255,1283,535,773,1681,461,1785,683,735,1123,1801,677,689,1939,487,757,
	        1857,1987,983,443,1327,1267,313,1173,671,221,695,1509,271,1619,89,565,
	        127,1405,1431,1659,239,1101,1159,1067,607,1565,905,1755,1231,1299,665,373,
	        1985,701,1879,1221,849,627,1465,789,543,1187,1591,923,1905,979,1241,181
	};

	// This is a pre-computed table of quadratic residues for use in step 2.
	static const bool badResidue[256] = {
	        0,0,1,1,0,1,1,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,
	        1,0,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,
	        0,0,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,
	        1,0,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,
	        1,0,1,1,0,1,1,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,
	        1,0,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,
	        1,0,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,
	        1,0,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1
	};

	/
	 * 1. Filter out obvious answers. We return TRUE for 0, and
	additionally, in base 16, perfect squares
	 * MUST end with 0, 1, 4 or 9, so if our number ends with anything else
	we return FALSE.
	 /

	if( (n & 2) || ((n & 7) == 5) || ((n & 11) == 8) ) return false;
	if(n == 0) return true;

	/
	 * 2. We test if our number is a quadratic residue modulo 256 to try and
	filter out a LOT of the numbers that
	 * are obviously non-prime. More information:
	http://en.wikipedia.org/wiki/Quadratic_residue
	 /

	if(badResidue[ QBitwise::modPowTwo(n, 8) ]) return false;

	/
	 * 3. Divide out all powers of 4 to make our number a bit more
	managable, if possible. Once this is done, it is
	 * guaranteed that our number is ODD based on step 1 and our dividing
	out of all powers of 4, and therefore it
	 * is true that, if our number is a square, then it is congruent to 1
	modulo 8.
	 /

	if( !(n & 4294967295ULL) ) n >>= 32;
	if( !(n & 65535)         ) n >>= 16;
	if( !(n & 255)           ) n >>=  8;
	if( !(n & 15)            ) n >>=  4;
	if( !(n & 3)             ) n >>=  2;

	if(QBitwise::modPowTwo(n, 3) != 1) return false;

	// Lift a solution using Hensel's lemma.

	uint64_t r, t, z;
	r = start[(n >> 3) & 1023];
	do {

	        z = r*r;

	        if(z == n) return true;
	        if(z > n) return false;

	        z = n - z;

	        t = z & (-z);
	        r += (z & t) >> 1;

	        if( r > (t  >> 1) )
	                r = t - r;

	} while( t <= (1ULL >> 33) );

	return false;
	*/
}

/*!
 * This function tests if the given number is a multiple of three. We use a very
 *simple finite
 * state machine and only bitwish shifts and ANDs, so this should in theory be
 *faster than using
 * naive techniques such as the modulus division operator.
 *
 * \param n The number to test.
 * \return True if n is a multiple of three, or false otherwise.
 */
bool EMath::isMultipleThree(uint64_t n)
{
	int r = 0;

	while(n != 0)
	{
		if(n & 1)
		{ // Low-bit is a 1.

			switch(r)
			{
			case 0:
				r = 1;
				break;

			case 1:
				r = 0;
				break;
			};
		}
		else
		{ // Low-bit is a 0.

			switch(r)
			{
			case 1:
				r = 2;
				break;

			case 2:
				r = 1;
				break;
			};
		}

		// Move to the next digit
		n >>= 1;
	}

	// Return result.

	return (r == 0);
}

/*!
 * This function tests if b is a permutation of a (i.e., b contains exactly the
 *same digits as a,
 * ignoring zeros). Zero digits are ignored since they can simply be
 *"permutated" to the front of
 * the number, and leading zeros do not change value.
 *
 * \param a The first number to test.
 * \param b The second number to test.
 * \return True if b is a permutation of a, or false otherwise.
 */
bool EMath::isPermutationOf(uint64_t a, uint64_t b)
{
	int digits[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	while(a > 0)
	{
		++digits[a % 10];
		a /= 10;
	}

	while(b > 0)
	{
		--digits[b % 10];
		b /= 10;
	}

	for(int i = 1; i <= 9; ++i)
		if(digits[i] != 0)
			return false;

	return true;
}

/*!
 * This functions returns the number of ways r objects can be drawn from n
 *objects,
 * assuming that order matters.
 *
 * \param n The number of available choices.
 * \param r The number of selections we will make.
 * \return n permutations of r.
 */
uint64_t EMath::permutations(int n, int r)
{
	uint64_t result;
	uint32_t i;

	/*
	 * We can only do r permutations of n if:
	 *
	 *   - r <= n
	 *   - n >= 0
	 *   - r >= 0
	 */
	if((r > n) || (n < 0) || (r < 0))
		throw EValueRangeException("Undefined permutation.");

	/*
	 * The number of permutations of r objects from n objects is:
	 *     n! / (n-r)!
	 */

	/*
	 * Because factorials get very large very fast, we are going to "cancel"
	 *in order
	 * to get the correct answer. Because factorials necessarily contain the
	 *same numbers
	 * being multipled, we only need to multiply in the range of [n, n-r).
	 *
	 * I.e., for n = 5 and r = 3, we would have:
	 *       5! / (5 - 3)!
	 *     = 5! / 2!
	 *     = (5 * 4 * 3 * 2 * 1) / (2 * 1)
	 *     = 5 * 4 * 3
	 */

	result = 1;
	for(i = static_cast<uint32_t>(n); i > static_cast<uint32_t>(n - r); i--)
		result *= i;

	return result;
}

/*!
 * This function is part of Euclid's formula for generating Pythagorean triples.
 *Given
 * values m, n and k, this will provide the A value of our triple.
 *
 * More infomration about Euclid's formula:
 *     http://en.wikipedia.org/wiki/Pythagorean_triple#Generating_a_triple
 *
 * \param m A positive integer greater than n.
 * \param n A positive integer less than m.
 * \param k The multiple for this triple.
 * \return The A component of our triple.
 */
uint64_t EMath::getPythagoreanTripleA(uint64_t m, uint64_t n, uint64_t k)
{
	return (k * ((m * m) - (n * n)));
}

/*!
 * This function is part of Euclid's formula for generating Pythagorean triples.
 *Given
 * values m, n and k, this will provide the B value of our triple.
 *
 * More infomration about Euclid's formula:
 *     http://en.wikipedia.org/wiki/Pythagorean_triple#Generating_a_triple
 *
 * \param m A positive integer greater than n.
 * \param n A positive integer less than m.
 * \param k The multiple for this triple.
 * \return The B component of our triple.
 */
uint64_t EMath::getPythagoreanTripleB(uint64_t m, uint64_t n, uint64_t k)
{
	return (k * (2 * m * n));
}

/*!
 * This function is part of Euclid's formula for generating Pythagorean triples.
 *Given
 * values m, n and k, this will provide the C value of our triple.
 *
 * More infomration about Euclid's formula:
 *     http://en.wikipedia.org/wiki/Pythagorean_triple#Generating_a_triple
 *
 * \param m A positive integer greater than n.
 * \param n A positive integer less than m.
 * \param k The multiple for this triple.
 * \return The C component of our triple.
 */
uint64_t EMath::getPythagoreanTripleC(uint64_t m, uint64_t n, uint64_t k)
{
	return (k * ((m * m) + (n * n)));
}

/*!
 * This is a utility function for binary searches; it returns the index nearest
 *to the middle of the
 * indices l and r.
 *
 * \param l The left index.
 * \param r The right index.
 * \return The index in the middle of l and r.
 */
uint64_t EMath::mid(uint64_t l, uint64_t r)
{
	return ((l + r) / 2);
}

/*!
 * This function performs a binary search on the Fibonacci sequence. Both the
 *lower and upper indices
 * passed to this functions, along with the value returned by it, are indexes in
 *the Fibonacci sequence.
 * The goal of this function is to find the smallest number in the Fibonacci
 *sequence that exceeds the
 * given target number t.
 *
 * It is assumed that F(l) is <= the target number, and F(u) is >= the target
 *number.
 *
 * \param l The lower-bound index number in the sequence.
 * \param u The upper-bound index number in the sequence.
 * \param t The target number.
 * \return The sequence index of the smallest number that exceeds the given
 *target number.
 */
uint64_t EMath::binaryFibonacciSearch(uint32_t l, uint32_t u,
                                      const mpz_class &t)
{
	uint32_t m = static_cast<uint32_t>(mid(l, u));
	mpz_class v = EMath::getFibonacciNumberN(m);

	if(l == m)
	{
		if(v < t)
		{
			do
			{
				v = EMath::getFibonacciNumberN(++m);
			} while(v < t);

			return m;
		}
		else if(v > t)
		{
			do
			{
				v = EMath::getFibonacciNumberN(--m);
			} while(v >= t);

			return (m + 1);
		}
		else
			return m;
	}

	if(v < t)
		return EMath::binaryFibonacciSearch(m, u, t);
	else if(v > t)
		return EMath::binaryFibonacciSearch(l, m, t);
	else
		return m;
}

#include "EMath.h"

#include <cmath>
#include <cstdlib>
#include <map>

#include "EDefines.h"
#include "math/EFactorization.h"
#include "util/EBitwise.h"

#ifdef LIBEULER_DEBUG
	#include <iostream>
	#include <cmath>
#endif

#ifdef LIBEULER_DEBUG
/*!
 * This function implements our test suite for this class. It uses non-abort()'ing
 * assertions, and merely prints the result to stdout.
 */
void EMath::doTestSuite()
{
	bool success;
	EFactorization fac;
	uint64_t i, j, k, n;
	uint64_t a, b, c;
	bool rVal;
	double d;
	
	std::cout << "\tTesting 'EMath'...\t\t\t";
	try
	{
		success = true;
		
		// getTriangleNumberN
		
		EASSERT(EMath::getTriangleNumberN(0) == 0)
		EASSERT(EMath::getTriangleNumberN(1) == 1)
		EASSERT(EMath::getTriangleNumberN(2) == 3)
		EASSERT(EMath::getTriangleNumberN(3) == 6)
		EASSERT(EMath::getTriangleNumberN(4) == 10)
		EASSERT(EMath::getTriangleNumberN(5) == 15)
		EASSERT(EMath::getTriangleNumberN(6) == 21)
		EASSERT(EMath::getTriangleNumberN(7) == 28)
		EASSERT(EMath::getTriangleNumberN(8) == 36)
		EASSERT(EMath::getTriangleNumberN(9) == 45)
		EASSERT(EMath::getTriangleNumberN(10) == 55)
		EASSERT(EMath::getTriangleNumberN(11) == 66)
		EASSERT(EMath::getTriangleNumberN(12) == 78)
		EASSERT(EMath::getTriangleNumberN(13) == 91)
		EASSERT(EMath::getTriangleNumberN(14) == 105)
		EASSERT(EMath::getTriangleNumberN(15) == 120)
		EASSERT(EMath::getTriangleNumberN(16) == 136)
		EASSERT(EMath::getTriangleNumberN(17) == 153)
		EASSERT(EMath::getTriangleNumberN(18) == 171)
		EASSERT(EMath::getTriangleNumberN(19) == 190)
		EASSERT(EMath::getTriangleNumberN(20) == 210)
		EASSERT(EMath::getTriangleNumberN(21) == 231)
		EASSERT(EMath::getTriangleNumberN(22) == 253)
		EASSERT(EMath::getTriangleNumberN(23) == 276)
		EASSERT(EMath::getTriangleNumberN(24) == 300)
		EASSERT(EMath::getTriangleNumberN(25) == 325)
		EASSERT(EMath::getTriangleNumberN(26) == 351)
		EASSERT(EMath::getTriangleNumberN(27) == 378)
		EASSERT(EMath::getTriangleNumberN(28) == 406)
		EASSERT(EMath::getTriangleNumberN(29) == 435)
		EASSERT(EMath::getTriangleNumberN(30) == 465)
		EASSERT(EMath::getTriangleNumberN(31) == 496)
		EASSERT(EMath::getTriangleNumberN(32) == 528)
		EASSERT(EMath::getTriangleNumberN(33) == 561)
		EASSERT(EMath::getTriangleNumberN(34) == 595)
		EASSERT(EMath::getTriangleNumberN(35) == 630)
		EASSERT(EMath::getTriangleNumberN(36) == 666)
		EASSERT(EMath::getTriangleNumberN(37) == 703)
		EASSERT(EMath::getTriangleNumberN(38) == 741)
		EASSERT(EMath::getTriangleNumberN(39) == 780)
		EASSERT(EMath::getTriangleNumberN(40) == 820)
		EASSERT(EMath::getTriangleNumberN(41) == 861)
		EASSERT(EMath::getTriangleNumberN(42) == 903)
		EASSERT(EMath::getTriangleNumberN(43) == 946)
		EASSERT(EMath::getTriangleNumberN(44) == 990)
		EASSERT(EMath::getTriangleNumberN(45) == 1035)
		EASSERT(EMath::getTriangleNumberN(46) == 1081)
		EASSERT(EMath::getTriangleNumberN(47) == 1128)
		EASSERT(EMath::getTriangleNumberN(48) == 1176)
		EASSERT(EMath::getTriangleNumberN(49) == 1225)
		EASSERT(EMath::getTriangleNumberN(50) == 1275)
		EASSERT(EMath::getTriangleNumberN(51) == 1326)
		EASSERT(EMath::getTriangleNumberN(52) == 1378)
		EASSERT(EMath::getTriangleNumberN(53) == 1431)
		
		// getPentagonalNumberN
		
		EASSERT(EMath::getPentagonalNumberN(0) == 0)
		EASSERT(EMath::getPentagonalNumberN(1) == 1)
		EASSERT(EMath::getPentagonalNumberN(2) == 5)
		EASSERT(EMath::getPentagonalNumberN(3) == 12)
		EASSERT(EMath::getPentagonalNumberN(4) == 22)
		EASSERT(EMath::getPentagonalNumberN(5) == 35)
		EASSERT(EMath::getPentagonalNumberN(6) == 51)
		EASSERT(EMath::getPentagonalNumberN(7) == 70)
		EASSERT(EMath::getPentagonalNumberN(8) == 92)
		EASSERT(EMath::getPentagonalNumberN(9) == 117)
		EASSERT(EMath::getPentagonalNumberN(10) == 145)
		EASSERT(EMath::getPentagonalNumberN(11) == 176)
		EASSERT(EMath::getPentagonalNumberN(12) == 210)
		EASSERT(EMath::getPentagonalNumberN(13) == 247)
		EASSERT(EMath::getPentagonalNumberN(14) == 287)
		EASSERT(EMath::getPentagonalNumberN(15) == 330)
		EASSERT(EMath::getPentagonalNumberN(16) == 376)
		EASSERT(EMath::getPentagonalNumberN(17) == 425)
		EASSERT(EMath::getPentagonalNumberN(18) == 477)
		EASSERT(EMath::getPentagonalNumberN(19) == 532)
		EASSERT(EMath::getPentagonalNumberN(20) == 590)
		EASSERT(EMath::getPentagonalNumberN(21) == 651)
		EASSERT(EMath::getPentagonalNumberN(22) == 715)
		EASSERT(EMath::getPentagonalNumberN(23) == 782)
		EASSERT(EMath::getPentagonalNumberN(24) == 852)
		EASSERT(EMath::getPentagonalNumberN(25) == 925)
		EASSERT(EMath::getPentagonalNumberN(26) == 1001)
		EASSERT(EMath::getPentagonalNumberN(27) == 1080)
		EASSERT(EMath::getPentagonalNumberN(28) == 1162)
		EASSERT(EMath::getPentagonalNumberN(29) == 1247)
		EASSERT(EMath::getPentagonalNumberN(30) == 1335)
		EASSERT(EMath::getPentagonalNumberN(31) == 1426)
		EASSERT(EMath::getPentagonalNumberN(32) == 1520)
		EASSERT(EMath::getPentagonalNumberN(33) == 1617)
		EASSERT(EMath::getPentagonalNumberN(34) == 1717)
		EASSERT(EMath::getPentagonalNumberN(35) == 1820)
		EASSERT(EMath::getPentagonalNumberN(36) == 1926)
		EASSERT(EMath::getPentagonalNumberN(37) == 2035)
		EASSERT(EMath::getPentagonalNumberN(38) == 2147)
		EASSERT(EMath::getPentagonalNumberN(39) == 2262)
		EASSERT(EMath::getPentagonalNumberN(40) == 2380)
		EASSERT(EMath::getPentagonalNumberN(41) == 2501)
		EASSERT(EMath::getPentagonalNumberN(42) == 2625)
		EASSERT(EMath::getPentagonalNumberN(43) == 2752)
		EASSERT(EMath::getPentagonalNumberN(44) == 2882)
		EASSERT(EMath::getPentagonalNumberN(45) == 3015)
		EASSERT(EMath::getPentagonalNumberN(46) == 3151)
		
		// getHexagonalNumberN
		
		EASSERT(EMath::getHexagonalNumberN(0) == 0)
		EASSERT(EMath::getHexagonalNumberN(1) == 1)
		EASSERT(EMath::getHexagonalNumberN(2) == 6)
		EASSERT(EMath::getHexagonalNumberN(3) == 15)
		EASSERT(EMath::getHexagonalNumberN(4) == 28)
		EASSERT(EMath::getHexagonalNumberN(5) == 45)
		EASSERT(EMath::getHexagonalNumberN(6) == 66)
		EASSERT(EMath::getHexagonalNumberN(7) == 91)
		EASSERT(EMath::getHexagonalNumberN(8) == 120)
		EASSERT(EMath::getHexagonalNumberN(9) == 153)
		EASSERT(EMath::getHexagonalNumberN(10) == 190)
		EASSERT(EMath::getHexagonalNumberN(11) == 231)
		EASSERT(EMath::getHexagonalNumberN(12) == 276)
		EASSERT(EMath::getHexagonalNumberN(13) == 325)
		EASSERT(EMath::getHexagonalNumberN(14) == 378)
		EASSERT(EMath::getHexagonalNumberN(15) == 435)
		EASSERT(EMath::getHexagonalNumberN(16) == 496)
		EASSERT(EMath::getHexagonalNumberN(17) == 561)
		EASSERT(EMath::getHexagonalNumberN(18) == 630)
		EASSERT(EMath::getHexagonalNumberN(19) == 703)
		EASSERT(EMath::getHexagonalNumberN(20) == 780)
		EASSERT(EMath::getHexagonalNumberN(21) == 861)
		EASSERT(EMath::getHexagonalNumberN(22) == 946)
		EASSERT(EMath::getHexagonalNumberN(23) == 1035)
		EASSERT(EMath::getHexagonalNumberN(24) == 1128)
		EASSERT(EMath::getHexagonalNumberN(25) == 1225)
		EASSERT(EMath::getHexagonalNumberN(26) == 1326)
		EASSERT(EMath::getHexagonalNumberN(27) == 1431)
		EASSERT(EMath::getHexagonalNumberN(28) == 1540)
		EASSERT(EMath::getHexagonalNumberN(29) == 1653)
		EASSERT(EMath::getHexagonalNumberN(30) == 1770)
		EASSERT(EMath::getHexagonalNumberN(31) == 1891)
		EASSERT(EMath::getHexagonalNumberN(32) == 2016)
		EASSERT(EMath::getHexagonalNumberN(33) == 2145)
		EASSERT(EMath::getHexagonalNumberN(34) == 2278)
		EASSERT(EMath::getHexagonalNumberN(35) == 2415)
		EASSERT(EMath::getHexagonalNumberN(36) == 2556)
		EASSERT(EMath::getHexagonalNumberN(37) == 2701)
		EASSERT(EMath::getHexagonalNumberN(38) == 2850)
		EASSERT(EMath::getHexagonalNumberN(39) == 3003)
		EASSERT(EMath::getHexagonalNumberN(40) == 3160)
		EASSERT(EMath::getHexagonalNumberN(41) == 3321)
		EASSERT(EMath::getHexagonalNumberN(42) == 3486)
		EASSERT(EMath::getHexagonalNumberN(43) == 3655)
		EASSERT(EMath::getHexagonalNumberN(44) == 3828)
		EASSERT(EMath::getHexagonalNumberN(45) == 4005)
		EASSERT(EMath::getHexagonalNumberN(46) == 4186)
		EASSERT(EMath::getHexagonalNumberN(47) == 4371)
		EASSERT(EMath::getHexagonalNumberN(48) == 4560)
		
		// getFibonacciNumberN_UI (+ getFibonacciNumberN)
		
		EASSERT(EMath::getFibonacciNumberN_UI(0) == 0)
		EASSERT(EMath::getFibonacciNumberN_UI(1) == 1)
		EASSERT(EMath::getFibonacciNumberN_UI(2) == 1)
		EASSERT(EMath::getFibonacciNumberN_UI(3) == 2)
		EASSERT(EMath::getFibonacciNumberN_UI(4) == 3)
		EASSERT(EMath::getFibonacciNumberN_UI(5) == 5)
		EASSERT(EMath::getFibonacciNumberN_UI(6) == 8)
		EASSERT(EMath::getFibonacciNumberN_UI(7) == 13)
		EASSERT(EMath::getFibonacciNumberN_UI(8) == 21)
		EASSERT(EMath::getFibonacciNumberN_UI(9) == 34)
		EASSERT(EMath::getFibonacciNumberN_UI(10) == 55)
		EASSERT(EMath::getFibonacciNumberN_UI(11) == 89)
		EASSERT(EMath::getFibonacciNumberN_UI(12) == 144)
		EASSERT(EMath::getFibonacciNumberN_UI(13) == 233)
		EASSERT(EMath::getFibonacciNumberN_UI(14) == 377)
		EASSERT(EMath::getFibonacciNumberN_UI(15) == 610)
		EASSERT(EMath::getFibonacciNumberN_UI(16) == 987)
		EASSERT(EMath::getFibonacciNumberN_UI(17) == 1597)
		EASSERT(EMath::getFibonacciNumberN_UI(18) == 2584)
		EASSERT(EMath::getFibonacciNumberN_UI(19) == 4181)
		EASSERT(EMath::getFibonacciNumberN_UI(20) == 6765)
		EASSERT(EMath::getFibonacciNumberN_UI(21) == 10946)
		EASSERT(EMath::getFibonacciNumberN_UI(22) == 17711)
		EASSERT(EMath::getFibonacciNumberN_UI(23) == 28657)
		EASSERT(EMath::getFibonacciNumberN_UI(24) == 46368)
		EASSERT(EMath::getFibonacciNumberN_UI(25) == 75025)
		EASSERT(EMath::getFibonacciNumberN_UI(26) == 121393)
		EASSERT(EMath::getFibonacciNumberN_UI(27) == 196418)
		EASSERT(EMath::getFibonacciNumberN_UI(28) == 317811)
		EASSERT(EMath::getFibonacciNumberN_UI(29) == 514229)
		EASSERT(EMath::getFibonacciNumberN_UI(30) == 832040)
		EASSERT(EMath::getFibonacciNumberN_UI(31) == 1346269)
		EASSERT(EMath::getFibonacciNumberN_UI(32) == 2178309)
		EASSERT(EMath::getFibonacciNumberN_UI(33) == 3524578)
		EASSERT(EMath::getFibonacciNumberN_UI(34) == 5702887)
		EASSERT(EMath::getFibonacciNumberN_UI(35) == 9227465)
		EASSERT(EMath::getFibonacciNumberN_UI(36) == 14930352)
		EASSERT(EMath::getFibonacciNumberN_UI(37) == 24157817)
		EASSERT(EMath::getFibonacciNumberN_UI(38) == 39088169)
		
		/*
		 * fibonacciSearch
		 *
		 * The first number in the Fibonacci sequence to have over 1,000 digits (10^999) is
		 * number 4782 -- test that we get the correct result.
		 */
		
		mpz_class fibsTarget = 10;
		mpz_pow_ui(fibsTarget.get_mpz_t(), fibsTarget.get_mpz_t(), 999);
		EASSERT(EMath::fibonacciSearch(1000, fibsTarget) == 4782)
		
		/*
		 * isPrime_UI (+ isPrime)
		 *
		 * The sum of the primes under 2,000,000 is 142913828922 - make sure we get the correct
		 * result.
		 */
		
		for(i = 1, n = 0; i < 2000000; ++i)
			if(EMath::isPrime_UI(i, 100))
				n += i;
			
		EASSERT(n == 142913828922)
		
		// areCoprime
		
		for(i = 1; i < 1000; ++i)
		{
			for(j = 1; j < 1000; ++j)
			{
				if(EMath::greatestCommonDivisor(i, j) == 1)
				{
					EASSERT(EMath::areCoprime(static_cast<uint32_t>(i), static_cast<uint32_t>(j)))
				}
			}
		}
		
		// totient
		
		EASSERT(EMath::totient(1) == 1)
		EASSERT(EMath::totient(2) == 1)
		EASSERT(EMath::totient(3) == 2)
		EASSERT(EMath::totient(4) == 2)
		EASSERT(EMath::totient(5) == 4)
		EASSERT(EMath::totient(6) == 2)
		EASSERT(EMath::totient(7) == 6)
		EASSERT(EMath::totient(8) == 4)
		EASSERT(EMath::totient(9) == 6)
		EASSERT(EMath::totient(10) == 4)
		EASSERT(EMath::totient(11) == 10)
		EASSERT(EMath::totient(12) == 4)
		EASSERT(EMath::totient(13) == 12)
		EASSERT(EMath::totient(14) == 6)
		EASSERT(EMath::totient(15) == 8)
		EASSERT(EMath::totient(16) == 8)
		EASSERT(EMath::totient(17) == 16)
		EASSERT(EMath::totient(18) == 6)
		EASSERT(EMath::totient(19) == 18)
		EASSERT(EMath::totient(20) == 8)
		EASSERT(EMath::totient(21) == 12)
		EASSERT(EMath::totient(22) == 10)
		EASSERT(EMath::totient(23) == 22)
		EASSERT(EMath::totient(24) == 8)
		EASSERT(EMath::totient(25) == 20)
		EASSERT(EMath::totient(26) == 12)
		EASSERT(EMath::totient(27) == 18)
		EASSERT(EMath::totient(28) == 12)
		EASSERT(EMath::totient(29) == 28)
		EASSERT(EMath::totient(30) == 8)
		EASSERT(EMath::totient(31) == 30)
		EASSERT(EMath::totient(32) == 16)
		EASSERT(EMath::totient(33) == 20)
		EASSERT(EMath::totient(34) == 16)
		EASSERT(EMath::totient(35) == 24)
		EASSERT(EMath::totient(36) == 12)
		EASSERT(EMath::totient(37) == 36)
		EASSERT(EMath::totient(38) == 18)
		EASSERT(EMath::totient(39) == 24)
		EASSERT(EMath::totient(40) == 16)
		EASSERT(EMath::totient(41) == 40)
		EASSERT(EMath::totient(42) == 12)
		EASSERT(EMath::totient(43) == 42)
		EASSERT(EMath::totient(44) == 20)
		EASSERT(EMath::totient(45) == 24)
		EASSERT(EMath::totient(46) == 22)
		EASSERT(EMath::totient(47) == 46)
		EASSERT(EMath::totient(48) == 16)
		EASSERT(EMath::totient(49) == 42)
		EASSERT(EMath::totient(50) == 20)
		EASSERT(EMath::totient(51) == 32)
		EASSERT(EMath::totient(52) == 24)
		EASSERT(EMath::totient(53) == 52)
		EASSERT(EMath::totient(54) == 18)
		EASSERT(EMath::totient(55) == 40)
		EASSERT(EMath::totient(56) == 24)
		EASSERT(EMath::totient(57) == 36)
		EASSERT(EMath::totient(58) == 28)
		EASSERT(EMath::totient(59) == 58)
		EASSERT(EMath::totient(60) == 16)
		EASSERT(EMath::totient(61) == 60)
		EASSERT(EMath::totient(62) == 30)
		EASSERT(EMath::totient(63) == 36)
		EASSERT(EMath::totient(64) == 32)
		EASSERT(EMath::totient(65) == 48)
		EASSERT(EMath::totient(66) == 20)
		EASSERT(EMath::totient(67) == 66)
		EASSERT(EMath::totient(68) == 32)
		EASSERT(EMath::totient(69) == 44)
		EASSERT(EMath::totient(70) == 24)
		EASSERT(EMath::totient(71) == 70)
		EASSERT(EMath::totient(72) == 24)
		EASSERT(EMath::totient(73) == 72)
		EASSERT(EMath::totient(74) == 36)
		EASSERT(EMath::totient(75) == 40)
		EASSERT(EMath::totient(76) == 36)
		EASSERT(EMath::totient(77) == 60)
		EASSERT(EMath::totient(78) == 24)
		EASSERT(EMath::totient(79) == 78)
		EASSERT(EMath::totient(80) == 32)
		EASSERT(EMath::totient(81) == 54)
		EASSERT(EMath::totient(82) == 40)
		EASSERT(EMath::totient(83) == 82)
		EASSERT(EMath::totient(84) == 24)
		EASSERT(EMath::totient(85) == 64)
		EASSERT(EMath::totient(86) == 42)
		EASSERT(EMath::totient(87) == 56)
		EASSERT(EMath::totient(88) == 40)
		EASSERT(EMath::totient(89) == 88)
		EASSERT(EMath::totient(90) == 24)
		EASSERT(EMath::totient(91) == 72)
		EASSERT(EMath::totient(92) == 44)
		EASSERT(EMath::totient(93) == 60)
		EASSERT(EMath::totient(94) == 46)
		EASSERT(EMath::totient(95) == 72)
		EASSERT(EMath::totient(96) == 32)
		EASSERT(EMath::totient(97) == 96)
		EASSERT(EMath::totient(98) == 42)
		EASSERT(EMath::totient(99) == 60)
		
		// repetendLength
		
		n = EMath::repetendLength(2, fac);
		EASSERT(n == 0)
		n = EMath::repetendLength(3, fac);
		EASSERT(n == 1)
		n = EMath::repetendLength(4, fac);
		EASSERT(n == 0)
		n = EMath::repetendLength(5, fac);
		EASSERT(n == 0)
		n = EMath::repetendLength(6, fac);
		EASSERT(n == 1)
		n = EMath::repetendLength(7, fac);
		EASSERT(n == 6)
		n = EMath::repetendLength(8, fac);
		EASSERT(n == 0)
		n = EMath::repetendLength(9, fac);
		EASSERT(n == 1)
		n = EMath::repetendLength(10, fac);
		EASSERT(n == 0)
		
		/*
		 * It is known that the number, 1/d, for d < 1000 that has the longest repetend
		 * length is d = 983 -- test that we get the correct answer.
		 */
		
		for(i = 2, j = 2; i < 1000; ++i)
		{
			if(EMath::repetendLength(static_cast<uint32_t>(i), fac) >
				EMath::repetendLength(static_cast<uint32_t>(j), fac))
			{
				j = i;
			}
		}
			
		EASSERT(j == 983)
		
		// greatestCommonDivisor
		
		n = EMath::greatestCommonDivisor(900, 736);
		EASSERT(n == 4)
		n = EMath::greatestCommonDivisor(951, 474);
		EASSERT(n == 3)
		n = EMath::greatestCommonDivisor(377, 540);
		EASSERT(n == 1)
		n = EMath::greatestCommonDivisor(210, 818);
		EASSERT(n == 2)
		n = EMath::greatestCommonDivisor(832, 17);
		EASSERT(n == 1)
		n = EMath::greatestCommonDivisor(986, 799);
		EASSERT(n == 17)
		n = EMath::greatestCommonDivisor(855, 469);
		EASSERT(n == 1)
		n = EMath::greatestCommonDivisor(990, 604);
		EASSERT(n == 2)
		n = EMath::greatestCommonDivisor(138, 827);
		EASSERT(n == 1)
		n = EMath::greatestCommonDivisor(424, 203);
		EASSERT(n == 1)
		n = EMath::greatestCommonDivisor(522, 813);
		EASSERT(n == 3)
		n = EMath::greatestCommonDivisor(251, 26);
		EASSERT(n == 1)
		n = EMath::greatestCommonDivisor(329, 191);
		EASSERT(n == 1)
		n = EMath::greatestCommonDivisor(965, 435);
		EASSERT(n == 5)
		n = EMath::greatestCommonDivisor(759, 400);
		EASSERT(n == 1)
		n = EMath::greatestCommonDivisor(53, 549);
		EASSERT(n == 1)
		n = EMath::greatestCommonDivisor(218, 678);
		EASSERT(n == 2)
		n = EMath::greatestCommonDivisor(453, 767);
		EASSERT(n == 1)
		n = EMath::greatestCommonDivisor(396, 594);
		EASSERT(n == 198)
		n = EMath::greatestCommonDivisor(821, 615);
		EASSERT(n == 1)
		n = EMath::greatestCommonDivisor(104, 410);
		EASSERT(n == 2)
		n = EMath::greatestCommonDivisor(725, 153);
		EASSERT(n == 1)
		n = EMath::greatestCommonDivisor(744, 764);
		EASSERT(n == 4)
		n = EMath::greatestCommonDivisor(765, 436);
		EASSERT(n == 1)
		n = EMath::greatestCommonDivisor(666, 86);
		EASSERT(n == 2)
		
		// leastCommonMultiple
		
		n = EMath::leastCommonMultiple(900, 736);
		EASSERT(n == 165600)
		n = EMath::leastCommonMultiple(951, 474);
		EASSERT(n == 150258)
		n = EMath::leastCommonMultiple(377, 540);
		EASSERT(n == 203580)
		n = EMath::leastCommonMultiple(210, 818);
		EASSERT(n == 85890)
		n = EMath::leastCommonMultiple(832, 17);
		EASSERT(n == 14144)
		n = EMath::leastCommonMultiple(986, 799);
		EASSERT(n == 46342)
		n = EMath::leastCommonMultiple(855, 469);
		EASSERT(n == 400995)
		n = EMath::leastCommonMultiple(990, 604);
		EASSERT(n == 298980)
		n = EMath::leastCommonMultiple(138, 827);
		EASSERT(n == 114126)
		n = EMath::leastCommonMultiple(424, 203);
		EASSERT(n == 86072)
		n = EMath::leastCommonMultiple(522, 813);
		EASSERT(n == 141462)
		n = EMath::leastCommonMultiple(251, 26);
		EASSERT(n == 6526)
		n = EMath::leastCommonMultiple(329, 191);
		EASSERT(n == 62839)
		n = EMath::leastCommonMultiple(965, 435);
		EASSERT(n == 83955)
		n = EMath::leastCommonMultiple(759, 400);
		EASSERT(n == 303600)
		n = EMath::leastCommonMultiple(53, 549);
		EASSERT(n == 29097)
		n = EMath::leastCommonMultiple(218, 678);
		EASSERT(n == 73902)
		n = EMath::leastCommonMultiple(453, 767);
		EASSERT(n == 347451)
		n = EMath::leastCommonMultiple(396, 594);
		EASSERT(n == 1188)
		n = EMath::leastCommonMultiple(821, 615);
		EASSERT(n == 504915)
		n = EMath::leastCommonMultiple(104, 410);
		EASSERT(n == 21320)
		n = EMath::leastCommonMultiple(725, 153);
		EASSERT(n == 110925)
		n = EMath::leastCommonMultiple(744, 764);
		EASSERT(n == 142104)
		n = EMath::leastCommonMultiple(765, 436);
		EASSERT(n == 333540)
		n = EMath::leastCommonMultiple(666, 86);
		EASSERT(n == 28638)
		
		// aliquotNumberDivisors
		
		for(i = 0; i < 1000; ++i)
		{
			fac.setNumber( static_cast<uint32_t>(i) );
			EASSERT(fac.getAllFactorsCount() == static_cast<int>(EMath::aliquotNumberDivisors(static_cast<uint32_t>(i))))
		}
		
		// aliquotSumDivisors + aliquotSumProperDivisors
		
		EASSERT(EMath::aliquotSumProperDivisors(1) == 0)
		EASSERT(EMath::aliquotSumProperDivisors(2) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(3) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(4) == 3)
		EASSERT(EMath::aliquotSumProperDivisors(5) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(6) == 6)
		EASSERT(EMath::aliquotSumProperDivisors(7) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(8) == 7)
		EASSERT(EMath::aliquotSumProperDivisors(9) == 4)
		EASSERT(EMath::aliquotSumProperDivisors(10) == 8)
		EASSERT(EMath::aliquotSumProperDivisors(11) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(12) == 16)
		EASSERT(EMath::aliquotSumProperDivisors(13) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(14) == 10)
		EASSERT(EMath::aliquotSumProperDivisors(15) == 9)
		EASSERT(EMath::aliquotSumProperDivisors(16) == 15)
		EASSERT(EMath::aliquotSumProperDivisors(17) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(18) == 21)
		EASSERT(EMath::aliquotSumProperDivisors(19) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(20) == 22)
		EASSERT(EMath::aliquotSumProperDivisors(21) == 11)
		EASSERT(EMath::aliquotSumProperDivisors(22) == 14)
		EASSERT(EMath::aliquotSumProperDivisors(23) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(24) == 36)
		EASSERT(EMath::aliquotSumProperDivisors(25) == 6)
		EASSERT(EMath::aliquotSumProperDivisors(26) == 16)
		EASSERT(EMath::aliquotSumProperDivisors(27) == 13)
		EASSERT(EMath::aliquotSumProperDivisors(28) == 28)
		EASSERT(EMath::aliquotSumProperDivisors(29) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(30) == 42)
		EASSERT(EMath::aliquotSumProperDivisors(31) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(32) == 31)
		EASSERT(EMath::aliquotSumProperDivisors(33) == 15)
		EASSERT(EMath::aliquotSumProperDivisors(34) == 20)
		EASSERT(EMath::aliquotSumProperDivisors(35) == 13)
		EASSERT(EMath::aliquotSumProperDivisors(36) == 55)
		EASSERT(EMath::aliquotSumProperDivisors(37) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(38) == 22)
		EASSERT(EMath::aliquotSumProperDivisors(39) == 17)
		EASSERT(EMath::aliquotSumProperDivisors(40) == 50)
		EASSERT(EMath::aliquotSumProperDivisors(41) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(42) == 54)
		EASSERT(EMath::aliquotSumProperDivisors(43) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(44) == 40)
		EASSERT(EMath::aliquotSumProperDivisors(45) == 33)
		EASSERT(EMath::aliquotSumProperDivisors(46) == 26)
		EASSERT(EMath::aliquotSumProperDivisors(47) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(48) == 76)
		EASSERT(EMath::aliquotSumProperDivisors(49) == 8)
		EASSERT(EMath::aliquotSumProperDivisors(50) == 43)
		EASSERT(EMath::aliquotSumProperDivisors(51) == 21)
		EASSERT(EMath::aliquotSumProperDivisors(52) == 46)
		EASSERT(EMath::aliquotSumProperDivisors(53) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(54) == 66)
		EASSERT(EMath::aliquotSumProperDivisors(55) == 17)
		EASSERT(EMath::aliquotSumProperDivisors(56) == 64)
		EASSERT(EMath::aliquotSumProperDivisors(57) == 23)
		EASSERT(EMath::aliquotSumProperDivisors(58) == 32)
		EASSERT(EMath::aliquotSumProperDivisors(59) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(60) == 108)
		EASSERT(EMath::aliquotSumProperDivisors(61) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(62) == 34)
		EASSERT(EMath::aliquotSumProperDivisors(63) == 41)
		EASSERT(EMath::aliquotSumProperDivisors(64) == 63)
		EASSERT(EMath::aliquotSumProperDivisors(65) == 19)
		EASSERT(EMath::aliquotSumProperDivisors(66) == 78)
		EASSERT(EMath::aliquotSumProperDivisors(67) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(68) == 58)
		EASSERT(EMath::aliquotSumProperDivisors(69) == 27)
		EASSERT(EMath::aliquotSumProperDivisors(70) == 74)
		EASSERT(EMath::aliquotSumProperDivisors(71) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(72) == 123)
		EASSERT(EMath::aliquotSumProperDivisors(73) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(74) == 40)
		EASSERT(EMath::aliquotSumProperDivisors(75) == 49)
		EASSERT(EMath::aliquotSumProperDivisors(76) == 64)
		EASSERT(EMath::aliquotSumProperDivisors(77) == 19)
		EASSERT(EMath::aliquotSumProperDivisors(78) == 90)
		EASSERT(EMath::aliquotSumProperDivisors(79) == 1)
		EASSERT(EMath::aliquotSumProperDivisors(80) == 106)
		
		for(i = 0; i < 1000; ++i)
		{
			EASSERT( EMath::aliquotSumProperDivisors(i) == (EMath::aliquotSumDivisors(i) - i) )
		}
		
		// integerPow
		for(i = 0; i <= 10; ++i)
		{
			for(j = 0; j <= 10; ++j)
			{
				rVal = (EMath::integerPow(i, j) ==
					static_cast<uint64_t>(pow(static_cast<double>(i),
						static_cast<double>(j))));
				
				EASSERT(rVal)
			}
		}
		
		// modularIntegerPow
		for(i = 1; i <= 5; ++i)
		{
			for(j = 1; j <= 5; ++j)
			{
				rVal = ( EMath::modularIntegerPow( i, j, 5 ) ==
					(static_cast<uint32_t>(pow(static_cast<double>(i),
						static_cast<double>(j))) % 5) );
					
				EASSERT(rVal);
			}
		}
		
		// logBaseTen
		for(i = 0; i <= 1000000; ++i)
		{
			rVal = ( EMath::logBaseTen( static_cast<uint32_t>(i) ) ==
				static_cast<uint32_t>(floor(log10(static_cast<double>(i)))) );
			
			EASSERT(rVal);
		}
		
		// isSquare
		for(i = 1; i <= 1000000; ++i)
		{
			d = sqrt(static_cast<double>(i));
			
			if(EMath::isSquare( static_cast<uint32_t>(i) ))
			{
				EASSERT(floor(d) == d)
			}
			else
			{
				EASSERT(floor(d) != d)
			}
		}
		
		// permutations
		
		rVal = EMath::permutations(5, 4) == 120;
		EASSERT(rVal)
		rVal = EMath::permutations(4, 1) == 4;
		EASSERT(rVal)
		rVal = EMath::permutations(5, 2) == 20;
		EASSERT(rVal)
		rVal = EMath::permutations(4, 2) == 12;
		EASSERT(rVal)
		rVal = EMath::permutations(5, 3) == 60;
		EASSERT(rVal)
		rVal = EMath::permutations(3, 2) == 6;
		EASSERT(rVal)
		rVal = EMath::permutations(5, 1) == 5;
		EASSERT(rVal)
		rVal = EMath::permutations(4, 4) == 24;
		EASSERT(rVal)
		rVal = EMath::permutations(1, 1) == 1;
		EASSERT(rVal)
		rVal = EMath::permutations(5, 5) == 120;
		EASSERT(rVal)
		
		// combinations
		
		rVal = EMath::combinations(10, 8) == 45;
		EASSERT(rVal)
		rVal = EMath::combinations(9, 3) == 84;
		EASSERT(rVal)
		rVal = EMath::combinations(4, 1) == 4;
		EASSERT(rVal)
		rVal = EMath::combinations(1, 1) == 1;
		EASSERT(rVal)
		rVal = EMath::combinations(6, 1) == 6;
		EASSERT(rVal)
		rVal = EMath::combinations(10, 6) == 210;
		EASSERT(rVal)
		rVal = EMath::combinations(9, 5) == 126;
		EASSERT(rVal)
		rVal = EMath::combinations(7, 2) == 21;
		EASSERT(rVal)
		rVal = EMath::combinations(9, 7) == 36;
		EASSERT(rVal)
		rVal = EMath::combinations(4, 3) == 4;
		EASSERT(rVal)
		
		// getPythagoreanTriple(A+B+C)
		
		for(i = 1; i <= 5; ++i)
		{
			for(j = 1; j <= 5; ++j)
			{
				for(k = 1; k <= 5; ++k)
				{
					a = EMath::getPythagoreanTripleA(i, j, k);
					b = EMath::getPythagoreanTripleB(i, j, k);
					c = EMath::getPythagoreanTripleC(i, j, k);
					
					rVal = (EMath::integerPow(a, 2) + EMath::integerPow(b, 2)) == EMath::integerPow(c, 2);
					EASSERT(rVal)
				}
			}
		}
	}
	catch(EAssertionException &e)
	{
		ELUNUSED(e)
		success = false;
	}
	catch(EValueRangeException &e)
	{
		EDIE_LOGIC(e)
	}
	
	// Print out our results.
	if(success)
		std::cout << "[ OK ]\n";
	else
		std::cout << "[FAIL]\n";
}
#endif

#if (defined _WIN32 || defined __APPLE__)
/*!
 * This is a convenience function, that will return a GMP mpz object whose value is that of
 * the given 64-bit integer.
 *
 * \param n The value we are going to set.
 * \return A GMP object whose value is equal to the one given.
 */
mpz_class EMath::int64ToBigInteger(uint64_t n)
{
	mpz_class r = 0;
	
	r += static_cast<uint32_t>( n >> 32 );
	mpz_mul_2exp(r.get_mpz_t(), r.get_mpz_t(), 32);
	r += static_cast<uint32_t>( (n << 32) >> 32 );
	
	return r;
}

/*!
 * This is a convenience function, that will return a GMP mpf object whose value is that of
 * the given 64-bit integer.
 *
 * \param n The value we are going to set.
 * \param p The precision desired for the new object.
 * \return A GMP object whose value is equal to the one given.
 */
mpf_class EMath::int64ToBigFloat(uint64_t n, mp_bitcnt_t p)
{
	mpf_class r(0, p);
	
	r += static_cast<uint32_t>( n >> 32 );
	mpf_mul_2exp(r.get_mpf_t(), r.get_mpf_t(), 32);
	r += static_cast<uint32_t>( (n << 32) >> 32 );
	
	return r;
}
#endif

/*!
 * This function returns the nth triangle number.
 *
 * A triangle number is equal to the sum of the positive integers less than or equal to
 * its place, i.e., the 7th triangle number = 7 + 6 + 5 + 4 + 3 + 2 + 1.
 *
 * \param n The nth triangle number will be generated.
 * \return The value of the nth triangle number.
 */
uint64_t EMath::getTriangleNumberN(uint64_t n)
{
	// Using Faulhaber's Formula we can express triangle numbers as the statement below:
	return ( (n * (n + 1)) /2);
}

/*!
 * This function returns the nth pentagonal number.
 *
 * Pentagonal numbers extend the idea of triangle numbers; more information can be found here:
 *     http://en.wikipedia.org/wiki/Pentagonal_number
 *
 * \param n The nth pentagonal number will be generated.
 * \return The value of the nth pentagonal number.
 */
uint64_t EMath::getPentagonalNumberN(uint64_t n)
{
	// The pentagonal number Pn is given by Pn = n(3n-1)/2
	return (n * ((3 * n) - 1)) >> 1;
}

/*!
 * A given number, x, can be shown to be pentagonal iff (sqrt(24*x + 1) + 1) / 6 is a natural
 * number. Thus, we test if (24*x + 1) is a perfect square, and if so then we test if sqrt(24*x + 1) + 1
 * is evenly divisible by 6.
 *
 * \param x The number to test.
 * \return True if x is pentagonal, or false otherwise.
 */
bool EMath::isPentagonal(uint64_t x)
{
	if(!EMath::isSquare((x * 24) + 1))
		return false;
	
	x = EMath::isqrt((x * 24) + 1) + 1;
	
	if(x & 1)
		return false;
	
	x >>= 1;
	
	return EMath::isMultipleThree(x);
}

/*!
 * This function returns the nth hexagonal number.
 *
 * Hexagonal numbers extend the idea of triangle numbers; more information can be found here:
 *     http://en.wikipedia.org/wiki/Hexagonal_number
 *
 * \param n The nth hexagonal number will be generated.
 * \return The value of the nth hexagonal number.
 */
uint64_t EMath::getHexagonalNumberN(uint64_t n)
{
	// The hexagonal number Hn is given by Hn = n(2n - 1)
	return (n * ( (n << 1) - 1) );
}

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
 * The Fibonacci sequence is defined such that F(0) = 0, F(1) = 1, and F(n) = F(n-1) + F(n-2).
 * For this function, however, we use a closed-form solution to the Fibonacci sequence, so we can
 * avoid unnecessary recursion.
 *
 * Note that precision is only guaranteed up to n = 5000.
 *
 * \param n The nth Fibonacci number will be generated.
 * \return The value of the nth Fibonacci number.
 */
uint64_t EMath::getFibonacciNumberN_UI(uint32_t n)
{
	return EMath::getFibonacciNumberN(n).get_ui();
}

/*!
 * This function returns the nth Fibonacci number.
 *
 * The Fibonacci sequence is defined such that F(0) = 0, F(1) = 1, and F(n) = F(n-1) + F(n-2).
 * For this function, however, we use a closed-form solution to the Fibonacci sequence, so we can
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
	 * We use the closed-form solution called "Binet's Formula," defined here:
	 *   http://en.wikipedia.org/wiki/Fibonacci_number#Relation_to_the_golden_ratio
	 *
	 * The formula is:
	 *     F(n) = (p^n - (1 - p)^n) / sqrt(5)
	 *
	 * Where p is phi, the Golden Ratio:
	 *     p = (1 + sqrt(5)) / 2
	 */
	
	// Since we are dealing with irrational square roots, we want a VERY HIGH level of precision.
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
 * This function finds the smallest Fibonacci number that is greater than the given target number 
 * t. This function does a binary search, using the given start index s, which should (ideally) be
 * the index of a number less than the target, but reasonably close to it. 
 *
 * \param s The starting index with which to begin our binary search.
 * \param t The target number we are searching for.
 * \return The index of the smallest number greater than the target number.
 */
uint64_t EMath::fibonacciSearch(uint32_t s, const mpz_class &t)
{
	mpz_class ln, un;
	uint32_t li, ui;
	
	ln = EMath::getFibonacciNumberN( (li = s) );
	
	while(ln > t)
		ln = EMath::getFibonacciNumberN( (li /= 2) );
	
	ui = li;
	do
	{
		un = EMath::getFibonacciNumberN( (ui *= 2) );
	} while(un <= t);
	
	return EMath::binaryFibonacciSearch(li, ui, t);
}

/*!
 * This is a convenience function for isPrime(), which just wraps the given primitive value in an mpz_class
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
 * This function tests probabalistically whether or not the given number is probably prime. It
 * takes a precision argument -- a precision of 15 is fairly normal, a precision of 100 is VERY
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
	if( (n == 2) || (n == 3) )
		return true;
	
	// Even numbers are NOT prime.
	if( (n % 2) == 0)
		return false;
	
	// Numbers divisible by 3 are NOT prime.
	if( (n % 3) == 0)
		return false;
	
	gmp_randinit_mt(randState);
	for(i = 0; i < p; i++)
	{
		// a = rand [1, value - 1]
		tA = n-2;
		mpz_urandomm(a.get_mpz_t(), randState, tA.get_mpz_t());
		a += 1;
		
		// if (a ^ (value - 1) % value) != 1 then our number is not prime.
		tA += 1;
		mpz_powm(tA.get_mpz_t(), a.get_mpz_t(), tA.get_mpz_t(), n.get_mpz_t());
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
 * This function tests if the two given integers, a and b, are coprime. Two integers
 * are considered coprime if their greatest common divisor is equal to 1.
 *
 * \param a The first value to check.
 * \param b The second value to check.
 * \return True if a and b are coprime, or false otherwise.
 */
bool EMath::areCoprime(uint32_t a, uint32_t b)
{
	return (EMath::greatestCommonDivisor(a, b) == 1);
}

/*!
 * The totient of a number (also called phi(n)) is defined as the number of positive integers less than
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
 * This function returns the length of the repeating portion of the decimal part of the reciprocal
 * of n.
 *
 * This function's behavior is explained in-depth here:
 *     http://mathforum.org/library/drmath/view/67018.html
 *
 * \param n The number to calculate (i.e., 1/n).
 * \param f The factorization object to use to perform our prime factorizations.
 * \return The length of the repetend of the reciprocal of n.
 */
uint32_t EMath::repetendLength(uint32_t n, EFactorization &f)
{
	std::map<uint32_t, uint32_t> factors;
	std::map<uint32_t, uint32_t>::const_iterator it;
	uint32_t d;
	
	// Remove all factors of 10 from our number.
	while((n % 2) == 0) n /= 2;
	while((n % 5) == 0) n /= 5;
	
	// Make it so numbers that do not repeat return 0.
	if(n == 1)
		return 0;
	
	d = EMath::totient(n);
	f.setNumber(d);
	factors = f.getPrimeFactors();
	
	for(it = factors.begin(); it != factors.end(); ++it)
		if(EMath::modularIntegerPow(10, (d / it->first), n) == 1)
			d /= it->first;
	
	return d;
}

/*!
 * This function implements Algorithm B from "The Art of Computer Programming - Volume 2" pp. 338
 * to calculate the greatest common divisor of the two integers provided, u and v.
 *
 * Note that this function returns x for gcd(0,x) and 0 for gcd(0,0).
 *
 * \param u The first integer.
 * \param v The second integer.
 * \return The greatest common divisor of u and v.
 */
#ifdef __GNUC__
	#warning TODO - Grok and comment.
#endif
uint64_t EMath::greatestCommonDivisor(uint64_t u, uint64_t v)
{
	int k;
	
	// gcd(0,x) = x and gcd(0,0) = 0
	if( (u == 0) || (v == 0) )
		return (u | v);
	
	/*
	 * Find the largest power of 2 that divides both u and v. That is, divide u and v by
	 * the smallest 2^k value such that u and v are not both even.
	 */
	
	for(k = 0; ((u | v) & 1) == 0; ++k)
	{
		u >>= 1;
		v >>= 1;
	}
	
	// Keep halving u until it is odd.
	while((u & 1) == 0)
		u >>= 1;
	
	do
	{
		while((v & 1) == 0)
			v >>= 1;
		
		if(u < v)
		{
			v -= u;
		}
		else
		{
			uint64_t d = u - v;
			u = v;
			v = d;
		}
		
		v >>= 1;
	} while(v != 0);
	
	// Return u * 2^k.
	return (u << k);
}

/*!
 * This function returns the least common multiple of a and b. To make it easy, we reduce this
 * problem to being able to find the greatest common divisor, which we can already do using the
 * fast Euclidean algorithm.
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
	uint64_t gcd = EMath::greatestCommonDivisor(a, b);
	
	if(gcd == 0)
		return 0;
	
	return ((a*b) / gcd);
}

/*!
 * This function returns the number of divisors of the given number. The definition for this
 * function is provided by: http://en.wikipedia.org/wiki/Aliquot_sum#Definition.
 *
 * \param n The number to process.
 * \return The number of divisors of n.
 */
uint64_t EMath::aliquotNumberDivisors(uint32_t n)
{
	uint32_t i, limit, r;
	
	if(n == 0) return 0;
	if(n == 1) return 1;
	
	for(i = 1, limit = n, r = 0; i < limit; ++i)
	{
		if( (n%i) == 0 )
		{
			limit = n/i;
			++r;
		}
	}
	
	r *= 2;
	if(EMath::isSquare(n)) r -= 1;
	
	return r;
}

/*!
 * This function returns the sum of the divisors of the given number. The definition for this
 * function is provided by: http://en.wikipedia.org/wiki/Aliquot_sum#Definition.
 *
 * \param n The number to process.
 * \return The sum of the divisors of n.
 */
uint64_t EMath::aliquotSumDivisors(uint64_t n)
{
	return EMath::aliquotSumProperDivisors(n) + n;
}

/*!
 * This function returns the sum of the proper divisors of the given number. The definition
 * for this function is provided by: http://en.wikipedia.org/wiki/Aliquot_sum#Definition.
 *
 * \param n The number to process.
 * \return The sum of the proper divisors of n.
 */
uint64_t EMath::aliquotSumProperDivisors(uint64_t n)
{
	uint64_t i, j;
	uint64_t limit = static_cast<uint64_t>(floor(sqrt(static_cast<double>(n))));
	uint64_t sum = 1;

	if(n == 0) return 0;
	if(n == 1) return 0;
	
	for(i = 2; i <= limit; ++i)
	{
		if((n % i) == 0)
		{
			sum += i;
			
			j = n/i;
			j = (j == i ? 0 : j);
			
			sum += j;
		}
	}
	
	return sum;
}

/*!
 * This function uses integer math to calculate the base b raised to the eth power. Note
 * that this function does not handle any overflow.
 *
 * \param b The base.
 * \param e The exponent.
 * \return b^e
 */
uint64_t EMath::integerPow(uint64_t b, uint64_t e)
{
	uint64_t i, r;
	if(e == 0) return 1;
	for(i = 1, r = b; i < e; ++i) r *= b;
	return r;
}

/*!
 * This algorithm calculates b^e (mod m). This method is known as the "right-to-left binary method," which
 * is explained in more detail here:
 *     http://en.wikipedia.org/wiki/Modular_exponentiation#Right-to-left_binary_method
 *
 * \param b The base.
 * \param e The exponent to raise the base to.
 * \param m The modulus.
 * \return b^e (mod m).
 */
uint64_t EMath::modularIntegerPow(uint64_t b, uint64_t e, uint64_t m)
{
	uint64_t r = 1;
	
	while(e > 0)
	{
		if(e&1)
			r = (r*b) % m;
		
		e >>= 1;
		b = (b*b) % m;
	}
	
	return r;
}

/*!
 * This function returns the floor of the base-10 logarithm of the given number. It should be
 * extremely fast, depending on how quickly the processor branches.
 *
 * \param n The number to process.
 * \return log10(n)
 */
uint32_t EMath::logBaseTen(uint64_t n)
{
	return (
		( n >= 10000000000000000000ULL ) ? 19 :
		( n >= 1000000000000000000ULL  ) ? 18 :
		( n >= 100000000000000000ULL   ) ? 17 :
		( n >= 10000000000000000ULL    ) ? 16 :
		( n >= 1000000000000000ULL     ) ? 15 :
		( n >= 100000000000000ULL      ) ? 14 :
		( n >= 10000000000000ULL       ) ? 13 :
		( n >= 1000000000000ULL        ) ? 12 :
		( n >= 100000000000ULL         ) ? 11 :
		( n >= 10000000000ULL          ) ? 10 :
		( n >= 1000000000              ) ? 9  :
		( n >= 100000000               ) ? 8  :
		( n >= 10000000                ) ? 7  : 
		( n >= 1000000                 ) ? 6  :
		( n >= 100000                  ) ? 5  :
		( n >= 10000                   ) ? 4  : 
		( n >= 1000                    ) ? 3  :
		( n >= 100                     ) ? 2  :
		( n >= 10                      ) ? 1  : 0
	);
}

/*!
 * This function computes the integer square root of the given number. That is, isqrt(x)
 * is equivalent to floor(sqrt(x)). Note that, because we do not use any floating-point
 * arithmetic for this result, it is faster than the built-in sqrt() function.
 *
 * We implement the algorithm using a simple binary search. Note, though, that the initial
 * midpoint chosen works better for large n than small n.
 *
 * \param n The number to take the square root of.
 * \return The integer square root of the given number.
 */
uint64_t EMath::isqrt(uint64_t n)
{
	uint64_t a, b, m;
	
	if(n <= 1) return n;
	
	a = 1;
	b = (n >> 6) + 16;
	do
	{
		
		m = (a + b) >> 1;
		if( (m*m) > n)
			b = m - 1;
		else
			a = m + 1;
		
	} while(b >= a);
	
	return (a - 1);
}

/*!
 * This function returns whether or not the given number is a perfect square.
 *
 * \param n The number to test.
 * \return True if n is a square, or false otherwise.
 */
bool EMath::isSquare(uint64_t n)
{
	#ifdef __GNUC__
		#warning TODO - This function fails for n = 206468161
	#endif
	
	uint64_t i = EMath::isqrt(n);
	
	return( (i*i) == n );
	
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
	 * 1. Filter out obvious answers. We return TRUE for 0, and additionally, in base 16, perfect squares
	 * MUST end with 0, 1, 4 or 9, so if our number ends with anything else we return FALSE.
	 /
	
	if( (n & 2) || ((n & 7) == 5) || ((n & 11) == 8) ) return false;
	if(n == 0) return true;
	
	/
	 * 2. We test if our number is a quadratic residue modulo 256 to try and filter out a LOT of the numbers that
	 * are obviously non-prime. More information: http://en.wikipedia.org/wiki/Quadratic_residue
	 /
	
	if(badResidue[ QBitwise::modPowTwo(n, 8) ]) return false;
	
	/
	 * 3. Divide out all powers of 4 to make our number a bit more managable, if possible. Once this is done, it is
	 * guaranteed that our number is ODD based on step 1 and our dividing out of all powers of 4, and therefore it
	 * is true that, if our number is a square, then it is congruent to 1 modulo 8.
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
 * This function returns the integer cube root of the given number. In general, this
 * is equivalent to floor(cbrt(n)), but is in theory much faster because it uses no
 * floating point arithmetic.
 *
 * \param n The number to compute the integer cube root of.
 * \return The integer cube root of n.
 */
uint64_t EMath::icbrt(uint64_t n)
{
	int s;
	uint64_t y = 0, b;
	
	for(s = 63; s >= 0; s -= 3)
	{
		y += y;
		b = 3 * y * (y + 1) + 1;
		
		if( (n >> s) >= b )
		{
			n -= b << s;
			++y;
		}
	}
	
	return y;
}

/*!
 * This function tests whether or not the given number is a perfect cube.
 *
 * \param n The number to test.
 * \return True if n is a perfect cube, or false otherwise.
 */
bool EMath::isCube(uint64_t n)
{
	uint64_t r = EMath::icbrt(n);
	return ( (r*r*r) == n );
}

/*!
 * This function tests if the given number is a multiple of three. We use a very simple finite
 * state machine and only bitwish shifts and ANDs, so this should in theory be faster than using
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
		if(n&1)
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
 * This function tests if b is a permutation of a (i.e., b contains exactly the same digits as a,
 * ignoring zeros). Zero digits are ignored since they can simply be "permutated" to the front of
 * the number, and leading zeros do not change value.
 *
 * \param a The first number to test.
 * \param b The second number to test.
 * \return True if b is a permutation of a, or false otherwise.
 */
bool EMath::isPermutationOf(uint64_t a, uint64_t b)
{
	int digits[10] = {0,0,0,0,0,0,0,0,0,0};
	
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
		if(digits[i] != 0) return false;
	
	return true;
}

/*!
 * This functions returns the number of ways r objects can be drawn from n objects,
 * assuming that order matters.
 *
 * \param n The number of available choices. 
 * \param r The number of selections we will make.
 * \exception EValueRangeException This exception is thrown if nPr cannot be evaluated.
 * \return n permutations of r.
 */
uint64_t EMath::permutations(int n, int r)
	throw(EValueRangeException &)
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
	if( (r > n) || (n < 0) || (r < 0) )
		throw EValueRangeException("Undefined permutation.");
	
	/*
	 * The number of permutations of r objects from n objects is:
	 *     n! / (n-r)!
	 */
	
	/*
	 * Because factorials get very large very fast, we are going to "cancel" in order
	 * to get the correct answer. Because factorials necessarily contain the same numbers
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
 * This function returns the number of ways r objects can be drawn from n objects,
 * assuming that order doesn't make any difference.
 *
 * \param n The number of available choices.
 * \param r The number of selections we will make.
 * \exception EValueRangeException This exception is thrown if nCr cannot be evaluated.
 * \return n combinations of r.
 */
uint64_t EMath::combinations(int n, int r)
	throw(EValueRangeException &)
{
	int *num, *den;
	int i, j, k;
	int denLength, numLength;
	uint64_t p, q;
	bool reduce;
	
	/*
	 * We can only choose r objects from n objects if:
	 *
	 *   - r <= n
	 *   - n >= 0
	 8   - r >= 0
	 */
	if( (r > n) || (n < 0) || (r < 0) )
		throw EValueRangeException("Undefined combination.");
	
	/*
	 * The combinations of x objects from n objects ix:
	 *
	 * n! / ( (n-r)! * r! )
	 */
	
	/*
	 * Because factorials get very large very fast, we are going to "cancel" just like
	 * in permutations() in order to calculate the answer more easily.
	 *
	 * Because there are two factorials in the denominator, we are going to choose the
	 * larger of the two and cancel that first. After that step, we are left with only
	 * part of the original factorial on top, and either (n-r)! or r! on bottom.
	 *
	 * From that point, we are going to make two lists of products for the numerator and
	 * the denominator, and cancel what we can.
	 *
	 * Then we simply evaluate the two products and divide them to get our result.
	 */
	
	// Figure out which one of these is the biggest so we can cancel effectively.
	j = (n - r) > r ? (n - r) : r;
	
	// Get the products that make up n! over a range of [n, j).
	
	numLength = n - j;
	num = new int[numLength];
	
	k = 0;
	for(i = n; i > j; i--)
		num[k++] = i;
		
	// Now figure out the one we didn't already cancel so we can list its products.
	j = (n - r) < r ? (n - r) : r;
	
	// Get the products that make up the remaining factorial in the denominator.
	
	j = (j > 1) ? j : 1;
	denLength = j - 1;
	
	den = new int[denLength];
	
	for(i = 0; (j - i) > 1; i++)
		den[i] = j - i;
	
	// Cancel everything.
	do
	{
		reduce = false;
		
		for(i = 0; i < denLength; i++)
		{ // For each element in our denominator...
			for(j = 0; j < numLength; j++)
			{ // For each element in our numerator...
				// Cancel out this number if we find something it divides.
				if( ((num[j] % den[i]) == 0) && (den[i] != 1) )
				{
					num[j] /= den[i];
					den[i] = 1;
					reduce = true;
				}
			}
		}
	} while(reduce);
	
	// Multiply out our numerator and denominator.
	
	p = q = 1;
	
	for(i = 0; i < numLength; i++)
		p *= num[i];

	for(i = 0; i < denLength; i++)
		q *= den[i];
	
	// Clean up our temporary arrays.
	delete[] num;
	delete[] den;
	
	return (p / q);
}

/*!
 * This function is part of Euclid's formula for generating Pythagorean triples. Given
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
 * This function is part of Euclid's formula for generating Pythagorean triples. Given
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
 * This function is part of Euclid's formula for generating Pythagorean triples. Given
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
 * This is a utility function for binary searches; it returns the index nearest to the middle of the
 * indices l and r.
 *
 * \param l The left index.
 * \param r The right index.
 * \return The index in the middle of l and r.
 */
uint64_t EMath::mid(uint64_t l, uint64_t r)
{
	return ((l+r)/2);
}

/*!
 * This function performs a binary search on the Fibonacci sequence. Both the lower and upper indices
 * passed to this functions, along with the value returned by it, are indexes in the Fibonacci sequence.
 * The goal of this function is to find the smallest number in the Fibonacci sequence that exceeds the
 * given target number t.
 *
 * It is assumed that F(l) is <= the target number, and F(u) is >= the target number.
 *
 * \param l The lower-bound index number in the sequence.
 * \param u The upper-bound index number in the sequence.
 * \param t The target number.
 * \return The sequence index of the smallest number that exceeds the given target number.
 */
uint64_t EMath::binaryFibonacciSearch(uint32_t l, uint32_t u, const mpz_class &t)
{
	uint32_t m = static_cast<uint32_t>(mid(l,u));
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

			return (m+1);
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

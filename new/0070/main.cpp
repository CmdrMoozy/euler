#include <iostream>
#include <cassert>
#include <cstdint>
#include <set>

#include "libquadra/math/QMath.h"
#include "libquadra/math/QPrimeSieve.h"

int main(void)
{
	// Range is 1 < n < 10^7 as given in the problem description.
	QPrimeSieve sieve(10000000);
	
	uint32_t t, result;
	
	for(std::set<uint32_t>::reverse_iterator it = sieve.rbegin(); it != sieve.rend(); ++it)
	{
std::cout << (*it) << "\n";
		t = QMath::totient((*it));
		
		if(QMath::isPermutationOf((*it), t))
		{
			result = (*it);
			break;
		}
	}
	
	std::cout << "Number with smallest ratio is: " << result << "\n";
	
	return 0;
}

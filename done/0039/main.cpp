#include <iostream>
#include <cassert>
#include <cmath>
#include <set>

#include "libeuler/types/ERightTriangle.h"

/*
 * If p is the perimeter of a right angle triangle with integral length sides, {a,b,c},
 * there are exactly three solutions for p = 120.
 *
 * {20,48,52}, {24,45,51}, {30,40,50}
 *
 * For which value of p <= 1000, is the number of solutions maximised?
 */

#define PERIMETER_MIN 3
#define PERIMETER_MAX 1000

int main(void)
{
	std::set<ERightTriangle> *count;
	uint32_t a, b, ic, mp, mv;
	double c;
	
	count = new std::set<ERightTriangle>[PERIMETER_MAX + 1];
	
	for(a = 1; a <= 998; a++)
	{
		for(b = 1; b <= 998; b++)
		{
			c = sqrt( static_cast<double>(a*a) + static_cast<double>(b*b) );
			ic = static_cast<uint32_t>(floor(c));
			
			if(static_cast<double>(ic) != c)
				continue;
			
			if( (a+b+ic) > PERIMETER_MAX )
				continue;
			
			count[a+b+ic].insert(ERightTriangle( a,b,ic ));
		}
	}

	mv = mp = 0;
	for(a = 0; a < (PERIMETER_MAX + 1); a++)
	{
		if(count[a].size() > mv)
		{
			mp = a;
			mv = count[a].size();
		}
	}
	
	std::cout << "The perimeter with the most solutions is " << mp << " (" << mv << " solutions).\n";
	
	delete[] count;
	assert(mp == 840);
	return 0;
}

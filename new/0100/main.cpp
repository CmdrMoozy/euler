#include <iostream>
#include <cassert>
#include <cstdint>

#include <gmp.h>

int main(void)
{
	mpz_t N, b;
	
	mpz_t tmpA, tmpB, tmpC;
	
	// Start with the first integer over 10^12.
	
	mpz_init(b);
	
	mpz_init(N);
	mpz_set_ui(N, 10);
	mpz_pow_ui(N, N, 12);
	mpz_add_ui(N, N, 1);
	
	mpz_init(tmpA);
	mpz_init(tmpB);
	mpz_init(tmpC);
	
	// Until we find a match...
	
	while(true)
	{
printf("FOO");
//DEBUG
mpz_out_str(stdout, 10, N);
		
		mpz_set_ui(b, 1);
		
		while(mpz_cmp(b, N) < 0)
		{
			// Compute the left-hand side of the equation.
			
			mpz_set(tmpA, b);
			mpz_sub_ui(tmpA, tmpA, 1);
			mpz_mul(tmpA, tmpA, b);
			mpz_mul_ui(tmpA, tmpA, 3);
			
			// Compute the first component of the right-hand side of the equation.
			
			mpz_sub(tmpB, N, b);
			
			// Compute the second component of the right-hand side of the equation.
			
			mpz_mul_ui(tmpC, b, 3);
			mpz_neg(tmpC, tmpC);
			
			mpz_add_ui(tmpC, tmpC, 1);
			mpz_add(tmpC, tmpC, N);
			
			// Add them, to get the full right-hand side of the equation.
			
			mpz_mul(tmpC, tmpB, tmpC);
			
			// Test if this is a solution.
			
			if(mpz_cmp(tmpA, tmpC) == 0)
			{
				printf("Found solution!");
				return 0;
			}
		}
		
		// Increment our total.
		
		mpz_add_ui(N, N, 1);
	}
	
	return 0;
}

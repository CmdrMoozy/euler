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

#include <iostream>
#include <cassert>
#include <vector>
#include <cstdint>

#include "libeuler/types/EDigitInteger.h"
#include "libeuler/types/EFraction.h"

/*
 * The fraction 49/98 is a curious fraction, as an inexperienced mathematician
 *in attempting to
 * simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is
 *obtained by cancelling
 * the 9s.
 *
 * We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
 *
 * There are exactly four non-trivial examples of this type of fraction, less
 *than one in value, and
 * containing two digits in the numerator and denominator.
 *
 * If the product of these four fractions is given in its lowest common terms,
 *find the value of the
 * denominator.
 */

/*
 * This class represents our fraction that does digit-wise cancelling for this
 * particular problem.
 */
class DigitalFraction
{
public:
	/*
	 * This is our default constructor, which initializes a new, clear()'ed
	 * DigitalFraction.
	 */
	DigitalFraction()
	{
		clear();
	}

	/*
	 * This constructor initializes a new DigitalFraction with the given
	 * numerator/denominator.
	 */
	DigitalFraction(uint32_t n, uint32_t d) : numerator(n), denominator(d)
	{
	}

	/*
	 * This is our copy constructor, which initializes our object to be
	 * equal to the given other
	 * object.
	 */
	DigitalFraction(const DigitalFraction &o)
	{
		(*this) = o;
	}

	/*
	 * This is our default destructor.
	 */
	virtual ~DigitalFraction()
	{
	}

	/*
	 * This is our copy assignment operator; it makes our object equal to
	 * the given other object,
	 * and then returns a reference to this so the operator can be chained.
	 */
	DigitalFraction &operator=(const DigitalFraction &o)
	{
		setNumerator(o.getNumerator());
		setDenominator(o.getDenominator());

		return (*this);
	}

	/*
	 * This function tests direct equivalence between us and the given other
	 * DigitalFraction. This
	 * means that we directly compare numerator and denominator; cancelling
	 * / reducing is not taken
	 * into account.
	 */
	bool operator==(const DigitalFraction &o)
	{
		return ((getNumerator() == o.getNumerator()) &&
		        (getDenominator() == o.getDenominator()));
	}

	/*
	 * This function clears our fraction, setting it to 0/0.
	 */
	void clear()
	{
		numerator = 0;
		denominator = 0;
	}

	/*
	 * This function returns our numerator.
	 */
	uint32_t getNumerator() const
	{
		return numerator.toInteger();
	}

	/*
	 * This function sets our numerator.
	 */
	void setNumerator(uint32_t n)
	{
		numerator = n;
	}

	/*
	 * This function returns our denominator.
	 */
	uint32_t getDenominator() const
	{
		return denominator.toInteger();
	}

	/*
	 * This function sets our denominator.
	 */
	void setDenominator(uint32_t d)
	{
		denominator = d;
	}

	/*
	 * A digital fraction is considered "trivial" if both the numerator and
	 * denominator are multiples
	 * of 10.
	 */
	bool isTrivial() const
	{
		return (((numerator.toInteger() % 10) == 0) &&
		        ((denominator.toInteger() % 10) == 0));
	}

	/*
	 * This function does a digit-wise cancel of our fraction. For instance:
	 * 49/98 will become
	 * 4/8. Note that this is, by design, incorrect math, which is what this
	 * problem requires to
	 * solve.
	 */
	void cancelAll()
	{
		std::string n = numerator.toString(),
		            d = denominator.toString();
		int i, j;
		bool reduced;

		do
		{
			reduced = false;

			for(i = 0; i < static_cast<int>(n.size()); i++)
			{
				for(j = 0; j < static_cast<int>(d.size()); j++)
				{
					if(n[i] == d[j])
					{
						n.erase(i, 1);
						d.erase(j, 1);
						reduced = true;
						break;
					}
				}

				if(reduced)
					break;
			}
		} while(reduced);

		numerator = n;
		denominator = d;
	}

	/*
	 * This function returns the decimal value of our fraction -- the
	 * numerator divided by the denominator.
	 */
	double toDecimal() const
	{
		return (static_cast<double>(numerator.toInteger()) /
		        static_cast<double>(denominator.toInteger()));
	}

private:
	EDigitInteger numerator;
	EDigitInteger denominator;
};

int main(void)
{
	std::vector<DigitalFraction> fractions;
	uint32_t n, d;
	DigitalFraction a, b;
	EFraction f(1, 1);
	uint32_t result;

	for(d = 10; d <= 99; d++)
	{
		for(n = 10; n < d; n++)
		{
			a.setNumerator(n);
			a.setDenominator(d);

			if(a.isTrivial())
				continue;

			b = a;
			b.cancelAll();

			if((a.toDecimal() == b.toDecimal()) && !(a == b))
				fractions.push_back(a);
		}
	}

	for(n = 0; n < fractions.size(); n++)
	{
		f.setNumerator(f.getNumerator() * fractions[n].getNumerator());
		f.setDenominator(f.getDenominator() *
		                 fractions[n].getDenominator());
	}

	f.reduce();

	result = f.getDenominator();
	std::cout << "The denominator of the resulting fraction product is: "
	          << result << "\n";

	assert(result == 100);
	return 0;
}

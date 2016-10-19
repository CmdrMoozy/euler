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

#include "ENumberGrid.h"

#include "common/EDefines.h"

ENumberGrid::ENumberGrid(int s) : EGrid<int>(s)
{
}

ENumberGrid::~ENumberGrid()
{
}

int ENumberGrid::greatestConsecutiveProduct(int n) const
{
	int i, j, k, greatest, c;

	if(n > getSize())
		throw EOutOfBoundsException(
		        "The consecutive length provided is out-of-range.");

	try
	{
		greatest = -1;

		// Test all of the normal paths.
		for(i = 0; i <= (getSize() - n); i++)
		{
			for(j = 0; j <= (getSize() - n); j++)
			{
				// Top-left diagonal.
				k = 1;
				c = at(i, j);
				do
				{
					c *= at(i + k, j + k);
					k++;
				} while(k < n);

				if(c > greatest)
					greatest = c;

				// Top-right diagonal.
				k = 1;
				c = at(i + (n - 1), j);
				do
				{
					c *= at(i + ((n - 1) - k), j + k);
					k++;
				} while(k < n);

				if(c > greatest)
					greatest = c;

				// Top horizontal.
				k = 1;
				c = at(i, j);
				do
				{
					c *= at(i, j + k);
					k++;
				} while(k < n);

				if(c > greatest)
					greatest = c;

				// Left vertical.
				k = 1;
				c = at(i, j);
				do
				{
					c *= at(i + k, j);
					k++;
				} while(k < n);

				if(c > greatest)
					greatest = c;
			}
		}

		// Our loop skips the final (n-1) horizontal and vertical rows.
		// Test them.

		// Horizontals.
		for(i = (getSize() - (n - 1)); i < getSize(); i++)
		{
			c = at(i, getSize() - n);
			k = 1;
			for(j = ((getSize() - n) + k); (j + k) < getSize(); j++)
				c *= at(i, j + (k++));

			if(c > greatest)
				greatest = c;
		}

		// Verticals.
		for(j = (getSize() - (n - 1)); j < getSize(); j++)
		{
			k = 1;
			c = at(getSize() - n, j);
			for(i = ((getSize() - n) + k); (i + k) < getSize(); i++)
				c *= at(i + (k++), j);

			if(c > greatest)
				greatest = c;
		}

		return greatest;
	}
	catch(EOutOfBoundsException &)
	{
#ifdef EULER_DEBUG
		EDIE_LOGIC(std::runtime_error("Got EOutOfBoundsException."))
#else
		return -1;
#endif
	}
}

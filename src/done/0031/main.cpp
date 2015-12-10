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
#include <cstdint>

/*
 * In England the currency is made up of pound and pence, and there are eight
 *coins in general
 * circulation:
 *
 *     1p, 2p, 5p, 10p, 20p, 50p, 1pound and 2pound.
 *
 * It is possible to make 2 pounds in the following way:
 *
 *     1x1pound + 1x50p + 2x20p + 1x5p + 1x2p + 3x1p
 *
 * How many different ways can 2 pound be made using any number of coins?
 */

int main(void)
{
	uint64_t total = 0;

	/*
	 * Just calculate the answer using brute force, skipping the interior
	 * loops if the total produced by
	 * the outer loops is already too great. A stupid solution, but
	 * acceptably fast.
	 */

	for(int one = 200; one >= 0; --one)
	{
		for(int two = 200; two >= 0; two -= 2)
		{
			if((one + two) > 200)
				continue;

			for(int five = 200; five >= 0; five -= 5)
			{
				if((one + two + five) > 200)
					continue;

				for(int ten = 200; ten >= 0; ten -= 10)
				{
					if((one + two + five + ten) > 200)
						continue;

					for(int twenty = 200; twenty >= 0;
					    twenty -= 20)
					{
						if((one + two + five + ten +
						    twenty) > 200)
							continue;

						for(int fifty = 200; fifty >= 0;
						    fifty -= 50)
						{
							if((one + two + five +
							    ten + twenty +
							    fifty) > 200)
								continue;

							for(int onequid = 200;
							    onequid >= 0;
							    onequid -= 100)
							{
								if((one + two +
								    five + ten +
								    twenty +
								    fifty +
								    onequid) >
								   200)
									continue;

								for(int twoquid =
								            200;
								    twoquid >=
								    0;
								    twoquid -=
								    200)
								{
									if((one +
									    two +
									    five +
									    ten +
									    twenty +
									    fifty +
									    onequid +
									    twoquid) ==
									   200)
										++total;
								}
							}
						}
					}
				}
			}
		}
	}

	std::cout << "Two pounds can be made " << total << " different ways.\n";
	assert(total == 73682);

	return 0;
}

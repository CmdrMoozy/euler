#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cassert>

/*
 * Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
 * 
 *     [...]
 */

int main(void)
{
	int testResult[10] = {5,5,3,7,3,7,6,2,3,0};
	unsigned int i;
	int addBuf[50];
	std::queue<char> qBuf;
	std::vector< std::queue<char> > numbers;
	std::string buf;
	std::vector< std::queue<char> >::iterator it;
	
	std::ifstream in("numbers.txt");
	if(!in.is_open())
	{
		std::cout << "Unable to open input file 'numbers.txt'!\n";
		return 1;
	}
	
	// Read in our input file.
	while(in.good())
	{
		while(!qBuf.empty())
			qBuf.pop();
		
		getline(in, buf);
		
		// Make sure the input numbers we are reading are 50-digits long.
		if(buf.length() != 50)
		{
			std::cout << "Corrupt/invalid 'numbers.txt'.\n";
			return 1;
		}
		
		// Place all of our digits into the current queue.
		for(i = 0; i < buf.length(); i++)
			if(isdigit(buf[i]))
				qBuf.push(buf[i]);
		
		// Add our digit queue to the back of our numbers list.
		numbers.push_back(qBuf);
	}
	in.close();
	
	// Our input file should contain 100 numbers for this problem.
	if(numbers.size() != 100)
	{
		std::cout << "Corrupt/invalid 'numbers.txt'.\n";
		return 1;
	}
	
	// Clear our add buffer.
	for(i = 0; i < 50; i++)
		addBuf[i] = 0;
	
	// Loop through all of the digits we read in, adding them in our add buffer.
	for(it = numbers.begin(); it < numbers.end(); it++)
	{
		i = 0;
		while(!it->empty())
		{
			addBuf[i++] += static_cast<int>( it->front() - '0' );
			it->pop();
		}
	}

	// addBuf contains the correct numbers!
	
	// Carry!
	for(i = 49; i >= 1; i--)
	{
		while(addBuf[i] >= 10)
		{
			addBuf[i - 1]++;
			addBuf[i] -= 10;
		}
	}
	
	// Continue carrying, but this time we drop off the right-most place as needed to keep our buffer the right size.
	while(addBuf[0] >= 10)
	{
		// Shift our buffer right 1 place, discarding the right-most digit.
		for(i = 49; i > 0; i--)
			addBuf[i] = addBuf[i - 1];
		
		addBuf[0] = 0;
		
		// Carry from buf[1] into buf[0].
		while(addBuf[1] >= 10)
		{
			addBuf[0] += 1;
			addBuf[1] -= 10;
		}
	}
	
	// Print our our result!
	
	std::cout << "The first ten digits of our resulting number after adding one hundred 50-digit numbers are: ";
	
	for(i = 0; i < 10; i++)
		std::cout << addBuf[i];
	
	std::cout << "\n";
	
	for(i = 0; i < 10; i++)
		assert(addBuf[i] == testResult[i]);
	
	return 0;
}

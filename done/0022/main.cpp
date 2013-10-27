#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cassert>

/*
 * Using names.txt, a 46K text file containing over five-thousand first names,
 * begin by sorting it into alphabetical order. Then working out the alphabetical
 * value for each name, multiply this value by its alphabetical position in the list to
 * obtain a name score.
 *
 * For example, when the list is sorted into alphabetical order, COLIN, which is worth
 * 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain
 * a score of 938 x 53 + 49714.
 *
 * What is the total of all the name scores in the file?
 */

int main(void)
{
	/*
	 * This is a bit of a naieve solution... Basically we use a shell script to process the names list
	 * a bit, then we read all of them into a vector, which we then sort, and we add all the scores up.
	 * Despite this, this solution still executes quite rapidly.
	 */
	
	unsigned long int total, name;
	int i;
	std::string buf;
	std::vector<std::string> names;
	std::vector<std::string>::iterator it;
	std::ifstream in("names_processed.txt");
	
	if(!in.is_open())
	{
		std::cerr << "Unable to open 'names_processed.txt'!\n";
		return 1;
	}
	
	while(in.good())
	{
		getline(in, buf);
		names.push_back(buf);
	}
	
	in.close();
	
	std::sort(names.begin(), names.end());
	
	total = 0;
	for(it = names.begin(); it < names.end(); it++)
	{
		name = 0;
		
		for(i = 0; i < static_cast<int>((*it).length()); i++)
			name += static_cast<unsigned long int>((*it).at(i) - 'A' + static_cast<char>(1));
		
		name *= static_cast<unsigned long int>(it - names.begin() + 1);
		total += name;
	}
	
	std::cout << "The total of the name scores is: " << total << "\n";
	
	assert(total == 871198282);
	return 0;
}

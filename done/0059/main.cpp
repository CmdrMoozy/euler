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
#include <cstring>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>

/*
 * Each character on a computer is assigned a unique code and the preferred standard is ASCII
 * (American Standard Code for Information Exchange). For example, uppercase A = 65, asterisk
 * (*) = 42, and lowercase k = 107.
 *
 * A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR each
 * byte with a given value, taken from a secret key. The advantage with the XOR function is that
 * using the same encryption key on the cipher text, restores the plain text; for example, 65
 * XOR 42 = 107, then 107 XOR 42 = 65.
 *
 * For unbreakable encryption, the key is the same length as the plain text message, and the key
 * is made up of random bytes. The user would keep the encrypted message and the encryption key
 * in different locations, and without both "halves", it is impossible to decrypt the message.
 *
 * Unfortunately, this method is impractical for most users, so the modified method is to use a
 * password as a key. If the password is shorter than the message, which is likely, the key is
 * repeated cyclically throughout the message. The balance for this method is using a sufficiently
 * long password key for security, but short enough to be memorable.
 *
 * Your task has been made easy, as the encryption key consists of three lower case characters.
 * Using cipher.txt (right click and 'Save Link/Target As...'), a file containing the encrypted
 * ASCII codes, and the knowledge that the plain text must contain common English words, decrypt
 * the message and find the sum of the ASCII values in the original text.
 */

/*
 * This function tests if the given character is punctuation. This function, as opposed to
 * ispunct() in the standard library, only accepts really common punctuation:
 *
 *     '".,:;()!?
 */
static char punctuation[] = {'\'', '"', '.', ',', ':', ';', '(', ')', '!', '?'};
bool isPunctuation(char c)
{
	int i;
	for(i = 0; i < 10; i++)
		if(c == punctuation[i])
			return true;
		
	return false;
}

int main(void)
{
	std::vector<char> ovalues, tmp;
	std::ifstream fin;
	std::string line;
	char *cline = NULL;
	char *tok;
	uint32_t i, result;
	char key[3] = {'a', 'a', 'a'};
	char c;
	bool fail;
	
	// Read in our input file.
	
	fin.open("cipher1.txt");
	if(!fin.is_open())
	{
		std::cout << "Unable to open 'cipher1.txt'.\n";
		return 1;
	}
	
	while(fin.good())
	{
		getline(fin, line);
		
		if(cline != NULL)
			delete[] cline;
		
		cline = new char[line.length() + 1];
		strcpy(cline, line.c_str());
		
		tok = strtok(cline, ",");
		while(tok != NULL)
		{
			ovalues.push_back( static_cast<char>(atoi(tok)) );
			tok = strtok(NULL, ",");
		}
	}
	
	fin.close();
	
	// Loop through every possible key and try decrypting with it.
	
	result = 0;
	for(key[0] = 'a'; key[0] <= 'z'; key[0]++)
	{
		for(key[1] = 'a'; key[1] <= 'z'; key[1]++)
		{
			for(key[2] = 'a'; key[2] <= 'z'; key[2]++)
			{
				tmp.clear();
				fail = false;
				
				for(i = 0; i < ovalues.size(); i++)
				{
					c = ovalues.at(i) ^ key[ (i % 3) ];
					
					/*
					 * We are given that the resulting message contains only ASCII-characters, so for each
					 * character we make sure it is in range [32], [65, 90], [97, 122]. If we get a resultant
					 * value that is not, then we just continue to the next key.
					 */
					
					if( !isalnum(c) && !isPunctuation(c) && !isspace(c) )
					{
						fail = true;
						break;
					}
					
					tmp.push_back(c);
				}
				
				// If we decrypted the whole message successfully, we need to add up the values of the resulting characters.
				if(!fail)
				{
					for(i = 0; i < tmp.size(); i++)
						result += static_cast<uint32_t>(tmp.at(i));
					
					break;
				}
			}
			
			if(result > 0)
				break;
		}
		
		if(result > 0)
			break;
	}
	
	// Print out our result.
	std::cout << "The sum of the resulting characters is: " << result << "\n";
	
	assert(result == 107359);
	return 0;
}

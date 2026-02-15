#include <string>
#include <vector>
#include <iostream>
#include <cstdint>
#include "FindPalindrome.hpp"

//------------------- HELPER FUNCTIONS -----------------------------------------
// non-class helper functions go here, should be declared as "static"

// helper non-member function to convert string to lower case
static void convertToLowerCase(std::string &value)
{
	for (int i = 0; i < value.size(); i++)
	{
		value[i] = std::tolower(value[i]);
	}
} // finished

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private function to determine if a string is a palindrome
bool FindPalindrome::isPalindrome(std::string currentString) const
{
	// make sure that the string is lower case
	convertToLowerCase(currentString);
	// see if the characters are symmetric
	int stringLength = currentString.size();
	for (int i = 0; i < stringLength / 2; i++)
	{
		if (currentString[i] != currentString[stringLength - i - 1])
		{
			return false;
		}
	}
	return true;
} // finished

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(std::vector<std::string> candidateStringVector,
																							std::vector<std::string> currentStringVector)
{
	// TODO
	return;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	// TODO
}

FindPalindrome::~FindPalindrome()
{
	// TODO
}

int FindPalindrome::number() const
{
	// TODO
	return -1;
}

void FindPalindrome::clear()
{
	// TODO
}

bool FindPalindrome::cutTest1(const std::vector<std::string> &stringVector)
{
	uint8_t numOdd = 0; //the number of characters with odd counts
	uint32_t charIndex = 0; //the index of the character in stringVector being analyzed
	std::vector<int> charCounts(26, 0); //26 letters of the alphabet, initial count 0
	for(int i = stringVector.size() - 1; i >= 0; i--)
	{
		for(int j = stringVector[i].size() - 1; j >= 0; j--)
		{
			charIndex = std::tolower(stringVector[i][j]) - 'a'; //extracts character and converts to index of that character in the alphabet (e.x. 0 for 'a')
			charCounts[charIndex]++; //increments the count for that character
		}
	}
	for(int i = 0; i < 26; i++)
	{
		if(charCounts[i] % 2 != 0) //if the count of a character is odd, then it cannot be in a palindrome sentence (since the characters must be symmetric)
		{
			numOdd++; //increment the count of characters with odd counts
		}
	}
	if(numOdd > 1) //if there are more than one characters with odd counts, then a palindrome sentence cannot be formed
	{
		return false;
	}
	return true;
}

bool FindPalindrome::cutTest2(const std::vector<std::string> &stringVector1,
															const std::vector<std::string> &stringVector2)
{
	uint32_t charIndex = 0; //the index of the character in stringVector being analyzed
	std::vector<int> charCounts1(26, 0); //26 letters of the alphabet, initial count 0
	std::vector<int> charCounts2(26, 0); //26 letters of the alphabet, initial count 0
	for(int i = stringVector1.size() - 1; i >= 0; i--)
	{
		for(int j = stringVector1[i].size() - 1; j >= 0; j--)
		{
			charIndex = std::tolower(stringVector1[i][j]) - 'a'; //extracts character and converts to index of that character in the alphabet (e.x. 0 for 'a')
			charCounts1[charIndex]++; //increments the count for that character
		}
	}
	for(int i = stringVector2.size() - 1; i >= 0; i--)
	{
		for(int j = stringVector2[i].size() - 1; j >= 0; j--)
		{
			charIndex = std::tolower(stringVector2[i][j]) - 'a'; //extracts character and converts to index of that character in the alphabet (e.x. 0 for 'a')
			charCounts2[charIndex]++; //increments the count for that character
		}
	}
	bool comp = (stringVector1.size() < stringVector2.size()); //boolean to determine which vector has fewer characters
	if(comp){
		for(int i = 0; i < 26; i++)
		{
			if(charCounts1[i] > charCounts2[i]) //if the vector of strings with fewer characters has more of a character than the other vector, invalid
			{
				return false;
			}
		}
	}
	else{
		for(int i = 0; i < 26; i++)
		{
			if(charCounts2[i] > charCounts1[i]) //if the vector of strings with fewer characters has more of a character than the other vector, invalid
			{
				return false;
			}
		}
	}
	return true;
}

bool FindPalindrome::add(const std::string &value)
{
	// TODO
	return false;
}

bool FindPalindrome::add(const std::vector<std::string> &stringVector)
{
	// TODO
	return false;
}

std::vector<std::vector<std::string>> FindPalindrome::toVector() const
{
	// TODO
	return std::vector<std::vector<std::string>>();
}
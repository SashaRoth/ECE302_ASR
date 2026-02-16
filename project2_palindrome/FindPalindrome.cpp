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
	// currentStringVector  A vector of strings that are currently in the palindrome sentence being built.
	// candidateStringVector  A vector of strings that are candidates for being in a palindrome sentence.
	for(int i = candidateStringVector.size() - 1; i >= 0; i--) //for each candidate word, add it to the current palindrome sentence and recurse with the remaining candidate words
	{
		std::string thisword = candidateStringVector[i]; //the word being added to the current palindrome sentence
		candidateStringVector.erase(candidateStringVector.begin() + i); //remove the word from the candidate vector
		currentStringVector.push_back(thisword); //add the word to the current palindrome sentence vector

		//cut test 1: if current vector has more than one character with an odd count, then it cannot be a palindrome sentence, so skip the rest of the function and continue with the next candidate word
		if(!cutTest1(currentStringVector)) //if the current palindrome sentence cannot be a palindrome sentence, then skip the rest of the function and continue with the next candidate word
		{
			currentStringVector.pop_back(); //remove the word from the current palindrome sentence vector
			candidateStringVector.insert(candidateStringVector.begin() + i, thisword); //add the word back to the candidate vector
			continue;
		}

		//convert the current palindrome sentence into a string by concatenating the words in currentStringVector
		std::string tostring = ""; //the current palindrome sentence as a string
		for(int j = currentStringVector.size() - 1; j >= 0; j--) 
		{
			tostring += currentStringVector[j];
		}

		//if the current vector is a palindrome, add it to the list of palindromes
		if(isPalindrome(tostring)) 
		{ 
			palindromes.push_back(currentStringVector);
			numPalindromes++; //update the number of palindromes in the class
		}

		//cut test 2: if the bigger vector (current vs candidate) does not have an equal number or more of each character in the smaller vector, no more palindromes can be made, so skip the rest of the function and continue with the next candidate word
		if(!cutTest2(currentStringVector, candidateStringVector))
		{
			currentStringVector.pop_back(); //remove the word from the current palindrome sentence vector
			candidateStringVector.insert(candidateStringVector.begin() + i, thisword); //add the word back to the candidate vector
			continue;
		}
		
		//if there are still candidate words, then continue building the palindrome sentences
		if(candidateStringVector.size() > 0) 
		{
			recursiveFindPalindromes(candidateStringVector, currentStringVector); //recurse with the current palindrome sentence and the remaining candidate words
		}
	}
	return; //if there are no more candidate words, then the current palindrome sentence is complete, so backtrack a level of recursion
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	words = std::vector<std::string>();
	palindromes = std::vector<std::vector<std::string>>();
	numWords = 0;
	numPalindromes = 0;
}

FindPalindrome::~FindPalindrome()
{
	words.clear();
	palindromes.clear();
}

int FindPalindrome::number() const
{
	return numPalindromes;
}

void FindPalindrome::clear()
{
	words.clear();
	palindromes.clear();
	numWords = 0;
	numPalindromes = 0;
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
	int length = value.size();
	if(length < 1) //if the string is empty, invalid
	{
		return false;
	}
	for(int i = 0; i < length; i++)
	{
		if(!std::isalpha(value[i])) //if the string contains a non-letter character, invalid
		{
			return false;
		}
	}
	std::string lowerValue = value; //create lowercase version to check for uniqueness
	convertToLowerCase(lowerValue);

	for(int i = 0; i < words.size(); i++){
		std::string lowerWord = words[i];
		convertToLowerCase(lowerWord);
		if(lowerWord == lowerValue) //if the string is not unique, invalid
		{
			return false;
		}
	}
	words.push_back(value); //add the string to the vector of words
	numWords++; //update the number of words in the class

	//recompute the number of sentence palindromes with the new vector of words
	recursiveFindPalindromes(words, std::vector<std::string>());

	return true;
}

bool FindPalindrome::add(const std::vector<std::string> &stringVector)
{
	//check for duplicate words in the input vector
	for(int i = 0; i < stringVector.size(); i++){
		for(int j = i + 1; j < stringVector.size(); j++){
			std::string lowerValue1 = stringVector[i]; //create lowercase version to check for uniqueness
			std::string lowerValue2 = stringVector[j];
			convertToLowerCase(lowerValue1);
			convertToLowerCase(lowerValue2);
			if(lowerValue1 == lowerValue2) //if there are duplicate strings in the input vector, invalid
			{
				return false;
			}
		}
	}

	//check each individual string in the input vector for validity
	for(int i = 0; i < stringVector.size(); i++){
		int length = stringVector[i].size();
		if(length < 1) //if the string is empty, invalid
		{
			return false;
		}
		for(int j = 0; j < length; j++)
		{
			if(!std::isalpha(stringVector[i][j])) //if the string contains a non-letter character, invalid
			{
				return false;
			}
		}
		std::string lowerValue = stringVector[i]; //create lowercase version to check for uniqueness
		convertToLowerCase(lowerValue);

		for(int i = 0; i < words.size(); i++){
			std::string lowerWord = words[i];
			convertToLowerCase(lowerWord);
			if(lowerWord == lowerValue) //if the string is not unique compared to the existing words in the class, invalid
			{
				return false;
			}
		}
	}

	//if all strings are valid, add them to the vector of words and update the number of words in the class
	for(int i = 0; i < stringVector.size(); i++){
		words.push_back(stringVector[i]); //add the string to the vector of words
		numWords++; //update the number of words in the class
	}

	//recompute the number of sentence palindromes with the new vector of words
	recursiveFindPalindromes(words, std::vector<std::string>()); 

	return true;
}

std::vector<std::vector<std::string>> FindPalindrome::toVector() const
{
	return palindromes;
}
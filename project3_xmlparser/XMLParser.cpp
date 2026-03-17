/** @file XMLParser.cpp */

#include <string>
#include <cctype>
#include <stdexcept>
#include <vector>
#include "XMLParser.hpp"

XMLParser::XMLParser()
{
	// TODO
}

// Then finish this function to pass unit tests 4-6
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	// TODO
	// Use '<' and '>' as anchors to scan the string. Remember to clear each time before
	// tokenizing a new string, and refer to the following code structure:
	
	//initial error checking
	int size = inputString.size();

	if(size <= 1){
		return false;
	}
	if(inputString[0] != '<' || inputString[size-1] != '>'){
		return false;
	}

	//iterate through string
	for(int i = 0; i < size; i++){
		char c = inputString[i];
		
		if(c == '<'){ //tokenize tag
			std::string candidate;
			StringTokenType candidate_type;
			while(c != '>'){
				int term = inputString.find(62, i);
				candidate = inputString.substr(i, term - i);
				//check for valid tag name syntax
			}
		}

		//tokenize content
	}

	// for (char c : inputString)
	// {
	// 	if (c == '<') {?? continue;}
	// 	else if (c == '>') {?? continue;}
	// 	else {?? continue;}
	// }

	return false;
}

// Then finish this function to pass unit tests 7-9
bool XMLParser::parseTokenizedInput()
{
	// TODO
	// Iterate through tokenizedInputVector to check its validity
	// and update the stack and bag accordingly, and refer to the following code structure:

	// for (int i = 0; i < tokenizedInputVector.size(); i++)
	// {
	//   if (?? == START_TAG) {?? continue;}
	//   else if (?? == END_TAG) {?? continue;}
	//   else if (?? == EMPTY_TAG) {?? continue;}
	//   ...
	// }

	return false;
}

void XMLParser::clear()
{
	// TODO
}

std::vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

bool XMLParser::containsElementName(const std::string &element) const
{
	// TODO
	return false;
}

int XMLParser::frequencyElementName(const std::string &element) const
{
	// TODO
	// Throw std::logic_error if either tokenizeInputString()
	// or parseTokenizedInput() returns false
	// If Bag is updated correctly, this should be as simple as one line.

	return -1;
}

// Helper functions

bool XMLParser::isValidSym(char c) const {
	if( c == '_' || c == '-' || c == '.' || (c >= 48 && c <= 57)){
		return true;
	}
	return false;
}

bool XMLParser::isAlpha(char c) const {
	if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)){
		return true;
	}
	return false;
}
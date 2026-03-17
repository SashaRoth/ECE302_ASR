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

	int size = inputString.size();
	char c;
	bool openbracket = false;

	if(size == 0){
		return false;
	}
	
	for(int i = 0; i < size; i++){
		c = inputString[i];
		if(c == '<'){
			if(openbracket) return false;
			openbracket = true;
			continue;
		}
		else if(c == '>'){
			if(!openbracket) return false;
			openbracket = false;

			while(!parseStack.isEmpty()){

			}

			continue;
		}
		//else if(c = ) if c = invalid char

		parseStack.push(std::string(1, c));
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
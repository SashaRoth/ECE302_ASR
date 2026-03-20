/** @file XMLParser.cpp */

#include <string>
#include <cctype>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "XMLParser.hpp"

XMLParser::XMLParser()
{
	tokenized = 0;
	parsed = 0;
}

// Then finish this function to pass unit tests 4-6
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	// TODO
	// Use '<' and '>' as anchors to scan the string. Remember to clear each time before
	// tokenizing a new string, and refer to the following code structure:
	
	//initial error checking
	int size = inputString.size();

	//check for valid size
	if(size <= 1){
		////std::cout << "String is too short to be valid" << std::endl;
		return false;
	}
	int opening = 0, closing = 0;
	for (char c : inputString){
		if(c == '<') opening++;
		else if(c == '>') closing++;
	}
	if(opening != closing){
		std::cout << "Every opening bracket must have a closing bracket";
		return false;
	}

	//remove beginning and end whitespace
	std::string inputCopy = inputString;
	while(std::isspace(inputCopy[0])){ //trim beginning whitespace
		inputCopy.erase(0, 1);
	}
	while(std::isspace(inputCopy[inputCopy.length() - 1])){
		inputCopy.pop_back(); //trim end whitespace
	}
	size = inputCopy.size(); //update size

	//check if string is enclosed by brackets
	//if(inputCopy[0] != '<' || inputCopy[size-1] != '>'){
		//std::cout << "String is not enclosed by brackets" << std::endl;
		//return false;
	//}

	// clear tokens from previous parse
	clear();

	//iterate through string
	for(int i = 0; i < size; i++){
		char c = inputCopy[i];
		bool notbeginning = 0;
		
		if(c == '<'){ //branch if tag is found
			std::string candidate;
			StringTokenType candidate_type;
			bool hasattribute = 0;
		
			//extract substring inside brackets
			//bounds checking in case '<' is not found and returns npos
			size_t name_end = inputCopy.find('>', i);
			if(name_end == std::string::npos){
				//std::cout << "Missing closing '>' for tag" << std::endl;
				return false;
			}
			if(name_end <= static_cast<size_t>(i + 1)){
				//std::cout << "Empty tag content" << std::endl;
				return false;
			}
			candidate = inputCopy.substr(i + 1, name_end - i - 1);

			//identify declarations
			if(candidate.find('?') == -1){ //if no '?', not a declaration
				candidate_type = START_TAG;
			}
			else if(candidate.find('?') == candidate.rfind('?')){ //only one '?', not a valid declaration
				//std::cout << "Invalid use of '?'" << std::endl;
				return false;
			}
			else if((candidate.find('?') != 0) || (candidate.rfind('?') != (candidate.length() - 1))){ // contains multiple '?', but not at the ends
				//std::cout << "Invalid use of multiple '?'" << std::endl;
				return false;
			}
			else{
				if(notbeginning){
					//std::cout << "Declarations not valid if not at the beginning of file" << std::endl;
					return false;
				}
				candidate_type = DECLARATION; //tag is valid declaration, assign type and remove '?'
				candidate.erase(0, 1);
				candidate.pop_back();

				TokenStruct toadd; //add token to tokenized vector
				toadd.tokenString = candidate;
				toadd.tokenType = candidate_type;
				tokenizedInputVector.push_back(toadd);
				i = name_end; //increment i to go to next token
			}

			if(candidate_type != DECLARATION){
				notbeginning = 1;

				//check for nested brackets
				if(candidate.find('<') != -1){ //tag contains nested '<' bracket
					//std::cout << "Tag contains nested bracket" << std::endl;
					return false;
				}

				if(candidate.length() == 0){
					//std::cout << "Tag contains no name" << std::endl;
					return false;
				}

				//old location of whitespace check

				//check for end tag indicators '/' and their validity
				int index = candidate.find('/');
				int revindex = candidate.rfind('/');
				if((index == -1)){ //if no '/' found, this is a start tag
						candidate_type = START_TAG;
				}
				else if(index == revindex){ //if both indicies are equal, only one '/' is present
					if(index == 0){ //if '/' is at the beginning, this is an end tag
						if(hasattribute){
							//std::cout << "End tag cannot contain attributes" << std::endl;
							return false;
						}
						candidate_type = END_TAG;
					}
					else if(index == (candidate.length() - 1)){ //if '/' is at the end, this is an empty tag
						//std::cout << "Empty tag containing attribute detected" << std::endl;
						candidate_type = EMPTY_TAG;
					}
					candidate.erase(index, 1);
				}
				else{ //if indicies are not equal, tag name contains multiple '/' --> invalid
					//std::cout << "Multiple instances of '/' in tag name" << std::endl;
					return false;
				}

				for(char m : candidate){ //if whitespace is found, check validity
					if(std::isspace(m)){
						if(candidate.find(m) == 0){
							//std::cout << "Tag name starts with white space" << std::endl;
							return false;
						}
						//if there are attributes after the tag name, just extract the tag name
						candidate = candidate.substr(0, candidate.find(m)); 
						hasattribute = 1;
						continue;
					}
				}

				//check for valid tag name syntax
				if(isValidSym(candidate[0])){ //check if tag name starts with invalid character
					//std::cout << "Tag name starts with invalid character" << std::endl;
					return false;
				}

				for(char m : candidate){ //check if characters in isolated name (after attribute and '/' removal) are valid
					if(isInvalidSym(m)){
						//std::cout << "Tag name contains invalid symbol" << std::endl;
						return false;
					}
				}

				//this point is only reached if tag name is valid -- push candidate into tokenized input vector
				TokenStruct toadd;
				toadd.tokenString = candidate;
				toadd.tokenType = candidate_type;
				if(candidate_type != DECLARATION){
					notbeginning = 1;
				}
				tokenizedInputVector.push_back(toadd);
				i = name_end; //increment i to go to next token
			}
		}

		else if(isAlpha(c) || isValidSym(c) || isInvalidSym(c)){ //branch if content
			std::string candidate;
			StringTokenType candidate_type = CONTENT;
			
			//error-checking if index of '<' exceeds string bounds
			size_t content_end = inputCopy.find('<', i);
			if(content_end == std::string::npos){
				content_end = inputCopy.size();
			}
			if(content_end <= static_cast<size_t>(i)){
				continue;
			}
			candidate = inputCopy.substr(i, content_end - i);

			//this point is only reached if content  is valid -- push candidate into tokenized input vector
			TokenStruct toadd;
			toadd.tokenString = candidate;
			toadd.tokenType = candidate_type;
			tokenizedInputVector.push_back(toadd);
			i = content_end - 1; //increment i to go to next token
			
		}
	}

	tokenized = 1;
	parsed = 0;
	return true;
}

// Then finish this function to pass unit tests 7-9
bool XMLParser::parseTokenizedInput()
{
	// TODO: check whether there is one root element
	// Iterate through tokenizedInputVector to check its validity
	// and update the stack and bag accordingly, and refer to the following code structure:

	int token_amt = tokenizedInputVector.size();
	std::string root = "";

	if(token_amt == 0){
		//std::cout << "Cannot parse empty input" << std::endl;
		return false;
	}

	for (int i = 0; i < tokenizedInputVector.size(); i++){
		if (tokenizedInputVector[i].tokenType == START_TAG) {
			if(root == ""){
				root = tokenizedInputVector[i].tokenString;
			}
			parseStack.push(tokenizedInputVector[i].tokenString);
		}
		else if (tokenizedInputVector[i].tokenType == END_TAG) { 
			try{
				parseStack.peek();
			}catch(std::logic_error){
				//std::cout << "End tag cannot come before start tag";
				return false;
			}
			if(parseStack.peek() != tokenizedInputVector[i].tokenString){ //if there is a start/end tag mismatch, invalid
				std::string end = tokenizedInputVector[i].tokenString;
				std::string start = parseStack.peek();
				//std::cout << "End tag does not match preceding start tag" << std::endl;
				return false;
			}
			elementNameBag.add(tokenizedInputVector[i].tokenString); //add valid tag name to bag
			parseStack.pop(); //pop last start tag off of stack
		}
		else if (tokenizedInputVector[i].tokenType == EMPTY_TAG) { 
			elementNameBag.add(tokenizedInputVector[i].tokenString); //add valid empty tag name to bag
		}
		else if (tokenizedInputVector[i].tokenType == CONTENT){
			if(parseStack.isEmpty()){
				//std::cout << "Content must be nested between tags";
				return false;
			}
		}
		if(i == tokenizedInputVector.size() - 1){
			if(tokenizedInputVector[i].tokenString != root){
				//std::cout << "String must be enclosed by one root" << std::endl;
				return false;
			}
		}
	}

	parsed = 1;
	return true;
}

void XMLParser::clear()
{
	tokenizedInputVector.clear();
	parseStack.clear();
	elementNameBag.clear();
	tokenized = 0;
	parsed = 0;
}

std::vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

bool XMLParser::containsElementName(const std::string &element) const
{
	if(elementNameBag.contains(element)){
		return true;
	}
	return false;
}

int XMLParser::frequencyElementName(const std::string &element) const
{
	// TODO
	// Throw std::logic_error if either tokenizeInputString()
	// or parseTokenizedInput() returns false
	// If Bag is updated correctly, this should be as simple as one line.
	if(!tokenized){
		throw std::logic_error("Cannot call freuqncyElementName on untokenized XMLParser");
	}
	if(!parsed){
		throw std::logic_error("Cannot call freuqncyElementName on unparsed XMLParser");
	}

	return elementNameBag.getFrequencyOf(element);
}

// Helper functions

bool XMLParser::isValidSym(char c) const {
	if( c == '_' || c == '-' || c == '.' || (c >= 48 && c <= 57)){
		return true;
	}
	return false;
}

bool XMLParser::isInvalidSym(char c) const {
	if((c >= 33 && c <= 44) || c == 47 || (c >= 58 && c <= 64) || (c >= 92 && c <= 94) || c == 96 || (c >= 123 && c <= 126)){
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
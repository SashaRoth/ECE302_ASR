#include <string>
#include <iostream>
#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch)
{
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(std::string s, int last)
{
  char ch = s[last];
  if (isalpha(ch))
  {
    return last; // if char at "last" is an operand, then itself is a valid postfix expression,
                 // so the end ("start" idx from left to right) of the postfix expression is just "last"
  }
  else if (isoperator(ch)) // make sure that ch is an operator, otherwise it is an invalid character and should return -1
  {
    int lastEnd = endPost(s, last - 1); // search for the end ("start" idx from left to right)
                                        // of the first <postfix> before ch in the syntax <postfix> <postfix> ch
    if (lastEnd > -1)
    {
      return endPost(s, lastEnd - 1); // search for the end ("start" idx from left to right)
                                      // of the second <postfix> before ch in the syntax <postfix> <postfix> ch
    }
    return -1;
  }
  return -1;
}

bool isPost(std::string s)
{
  int firstChar = endPost(s, s.size() - 1);
  return (firstChar == 0);
  // A postfix expression is valid if and only if the entire string
  // forms a single valid postfix expression (i.e., starts at index 0)
}

void convert(const std::string &postfix, std::string &prefix)
{
  if(!isPost(postfix)){
    throw std::invalid_argument("Not a valid postfix expression");
  }
  int postLength = postfix.size(); //get postfix expression length

  if(postLength == 0){
    //empty string is a valid postfix expression, so do nothing
  }
  else{
    char last = postfix[postLength - 1]; //get last character of postfix expression

    if(postLength == 1 && isalpha(last)){
      //string is a single letter; base case
      prefix = last + prefix; //concatenate letter to prefix expression
    }
    else if(isoperator(last)){ 
      //last character is an operator
      //postfix has form <post1><post2><operator>
      //example: "ab+cd-/"
      int endPost2 = endPost(postfix, postLength-2); //find end index of post2
      std::string post1 = postfix.substr(0, endPost2); //get post1
      std::string post2 = postfix.substr(endPost2, postLength - 1 - endPost2); //get post2
      //convert post1 into prefix
      convert(post2, prefix);
      //convert post2 into prefix
      convert(post1, prefix);
      prefix = last + prefix; //append operator to beginning of new prefix expression
    }
    else{
      throw std::invalid_argument("Expression contains invalid character");
    }
  }
}
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

TEST_CASE("Test adding words", "[FindPalindrome]")
{
	FindPalindrome b;
	REQUIRE(b.add("kayak"));
	REQUIRE(!b.add("kayak1"));
	REQUIRE(!b.add("kayak"));
	REQUIRE(b.number() == 1);
}

TEST_CASE("test recursion", "[FindPalindrome]")
{
	FindPalindrome b;

	REQUIRE(b.add("a"));
	std::cout << "After adding 'a': " << b.number() << " palindromes" << std::endl;
	
	REQUIRE(b.add("AA"));
	std::cout << "After adding 'AA': " << b.number() << " palindromes" << std::endl;
	
	REQUIRE(b.add("AaA"));
	std::cout << "After adding 'AaA': " << b.number() << " palindromes" << std::endl;
	
	std::vector<std::vector<std::string>> list = b.toVector();
	std::cout << "Final palindromes found: " << std::endl;
	for(int i = 0; i < list.size(); i++){
		for(int j = 0; j < list[i].size(); j++){
			std::cout << list[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	REQUIRE(b.number() == 6);
}

/** Your Test Cases Go Here */

//Test: constructor
TEST_CASE("Test constructor", "[FindPalindrome]")
{
	FindPalindrome b;
	REQUIRE(b.number() == 0); //require no palindromes
	REQUIRE(b.toVector().size() == 0);
}

//Test: add(string) with valid and invalid strings
TEST_CASE("Test add(string)", "[FindPalindrome]")
{
	FindPalindrome b;
	
	REQUIRE(b.add("kayak")); //valid addition
	
	std::cout << "After adding 'kayak': " << b.number() << " palindromes" << std::endl;
	auto list = b.toVector();
	for(int i = 0; i < list.size(); i++){
		for(int j = 0; j < list[i].size(); j++){
			std::cout << list[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	REQUIRE(b.number() == 1); //test that the number of palindromes is correct after adding "kayak"
	
	REQUIRE(b.add("civic")); //valid addition
	
	std::cout << "After adding 'civic': " << b.number() << " palindromes" << std::endl;
	
	list = b.toVector();
	for(int i = 0; i < list.size(); i++){
		for(int j = 0; j < list[i].size(); j++){
			std::cout << list[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	REQUIRE(b.number() == 0); //test that the number of palindromes is correct after adding "civic"
	REQUIRE(!b.add("kayak1")); //test adding a string with a non-letter character (invalid)
	REQUIRE(!b.add("kayak")); //test adding a duplicate string (invalid)
}

//Test: add(vector<string>) with valid and invalid vectors of strings
TEST_CASE("Test add(vector<string>)", "[FindPalindrome]")
{
	FindPalindrome b;
	std::vector<std::string> validVector = {"never", "or", "even", "odd"}; //valid vector of strings
	std::vector<std::string> invalidVector1 = {"kayak1", "civic"}; //invalid because of non-letter character
	std::vector<std::string> invalidVector2 = {"kayak", "civic", "kayak"}; //invalid because of duplicate string

	REQUIRE(b.add(validVector)); //valid addition
	
	std::vector<std::vector<std::string>> list = b.toVector();
	std::cout << "List of palindromes found: " << b.number() << std::endl;
	for(int i = 0; i < list.size(); i++){
		for(int j = 0; j < list[i].size(); j++){
			std::cout << list[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	REQUIRE(b.number() == 1); //test that the number of palindromes is correct after adding the valid vector
	REQUIRE(!b.add(invalidVector1)); //test adding an invalid vector with a non-letter character
	REQUIRE(!b.add(invalidVector2)); //test adding an invalid vector with a duplicate string
}

//Test: cutTest1 with vectors of strings that should pass and fail
TEST_CASE("Test cutTest1", "[FindPalindrome]")
{
	FindPalindrome b;
	std::vector<std::string> validVector = {"never", "or", "even", "odd"}; //valid vector of strings that should pass cutTest1 (all chars have even count)
	std::vector<std::string> invalidVector = {"a", "bb", "ccc"}; //invalid vector of strings that should fail cutTest1 (a:1, b:2, c:3 = 2 odd counts)

	REQUIRE(b.cutTest1(validVector)); //test that the valid vector passes cutTest1
	REQUIRE(!b.cutTest1(invalidVector)); //test that the invalid vector fails cutTest1
}

//Test: cutTest2 with vectors of strings that should pass and fail
TEST_CASE("Test cutTest2", "[FindPalindrome]")
{
	FindPalindrome b;
	std::vector<std::string> vector1 = {"never", "or", "even"}; //vector of strings for cutTest2
	std::vector<std::string> vector2 = {"nor"}; //vector of strings for cutTest2 that should pass cutTest2 with vector1 (all chars of "nor" are in vector1)
	std::vector<std::string> vector3 = {"kayak"}; //vector of strings for cutTest2 that should fail cutTest2 with vector1 (has 'k' and 'y' which vector1 doesn't have)

	REQUIRE(b.cutTest2(vector1, vector2)); //test that vector1 and vector2 pass cutTest2
	REQUIRE(!b.cutTest2(vector1, vector3)); //test that vector1 and vector3 fail cutTest2
}

//Test: clear method
TEST_CASE("Test clear method", "[FindPalindrome]")
{
	FindPalindrome b;
	std::vector<std::string> validVector = {"never", "or", "even", "odd"}; //valid vector of strings
	REQUIRE(b.add(validVector)); //add a valid vector of strings to the class
	REQUIRE(b.number() == 1); //test that the number of palindromes is correct after adding the valid vector
	
	b.clear(); //clear the class

	REQUIRE(b.toVector().size() == 0); //test that the vector of palindromes is empty after clearing
	REQUIRE(b.number() == 0); //test that the number of palindromes is 0 after clearing
}

//Test: toVector method with various vectors of strings
TEST_CASE("Test toVector method", "[FindPalindrome]")
{
	FindPalindrome b;
	std::vector<std::string> validVector1 = {"never", "or", "even", "odd"}; //valid vector of strings
	std::vector<std::vector<std::string>> validVector1Palindromes = {{"never", "odd", "or", "even"}}; //the palindrome that should be found after adding validVector1

	REQUIRE(b.add(validVector1)); //add the first valid vector of strings
	std::vector<std::vector<std::string>> list = b.toVector();
	std::cout << "List of palindromes found after adding validVector1: " << b.number() << std::endl;
	for(int i = 0; i < list.size(); i++){
		for(int j = 0; j < list[i].size(); j++){
			std::cout << list[i][j] << " ";
		}
		std::cout << std::endl;
	}

	REQUIRE(list == validVector1Palindromes); //test that the list of palindromes is correct after adding validVector1
	
}

//checkoff test case: will fail if even string has one odd character

TEST_CASE("Test invlaid even string with cuttest1","[FindPalindrome]"){
	FindPalindrome b;
	std::vector<std::string> invalid_even = {"abcd", "m", "bcd"};
	b.add(invalid_even);
	REQUIRE(b.cutTest1(invalid_even) == FALSE);
}

//checkoff test case: test equivalence operator

TEST_CASE("Test equivalence operator", "[FindPalindrome]"){
	FindPalindrome a;
	FindPalindrome b;
	FindPalindrome c;
	FindPalindrome d;
	std::vector<std::string> valid1 = {"never", "or", "odd", "even"};
	std::vector<std::string> valid2 = {"kayak"};
	std::vector<std::string> invalid = {"word"};

	a.add(valid1);
	b.add(valid1);
	c.add(valid2);
	d.add(invalid);

	REQUIRE(a.number() == 1);
	REQUIRE(b.number() == 1);
	REQUIRE(c.number() == 1);
	REQUIRE(d.number() == 0);

	REQUIRE(a == b); //same number, same palindromes
	REQUIRE_FALSE(a == c); //same number, different palindromes
	REQUIRE_FALSE(a == d); //different number
}
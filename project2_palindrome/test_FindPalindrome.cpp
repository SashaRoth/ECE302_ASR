#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

TEST_CASE("Test adding words", "[FindPalindrome]")
{
	FindPalindrome b;
	REQUIRE(b.add("kayak"));
	REQUIRE(!b.add("kayak1"));
}

TEST_CASE("test recursion", "[FindPalindrome]")
{
	FindPalindrome b;

	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA"));
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
	REQUIRE(b.number() == 1); //test that the number of palindromes is correct after adding "kayak"
	REQUIRE(b.add("civic")); //valid addition
	REQUIRE(b.number() == 3); //test that the number of palindromes is correct after adding "civic"
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
	REQUIRE(b.number() == 1); //test that the number of palindromes is correct after adding the valid vector
	REQUIRE(!b.add(invalidVector1)); //test adding an invalid vector with a non-letter character
	REQUIRE(!b.add(invalidVector2)); //test adding an invalid vector with a duplicate string

	std::vector<std::vector<std::string>> list = b.toVector();
	std::cout << "List of palindromes: " << std::endl;
	for(int i = 0; i < list.size(); i++){
		for(int j = 0; j < list[i].size(); j++){
			std::cout << list[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

//Test: cutTest1 with vectors of strings that should pass and fail

//Test: cutTest2 with vectors of strings that should pass and fail

//Test: clear method

//Test: recursiveFindPalindromes with various vectors of strings

//Test: toVector method with various vectors of strings
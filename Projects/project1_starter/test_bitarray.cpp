#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <iostream>
#include "bitarray.hpp"

// Given test cases for BitArray class
TEST_CASE("Bitarray: Test default construction and asString", "[bitarray]")
{
    BitArray b;
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    // std::string class has compare() member function that returns 0 if the strings are equal
    // research online for more details
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE("Bitarray: Test construction with asString", "[bitarray]")
{
    BitArray b;
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE("Bitarray: Test construction size and asString", "[bitarray]")
{
    // You can construct a string s of as s(n, c)
    // where n is the number of characters and c is the character
    std::string s(64, '0');
    BitArray b(64);
    REQUIRE(b.size() == 64);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE("Bitarray: Test many given methods combined", "[bitarray]")
{
    // << is the left shift operator for integers
    // e.g., 1 << 8 is 2^8=256, 1<<15 is 2^15=32768
    std::string s((1 << 15), '0'); // string of many-many zeros
    BitArray b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);

    // Test a very long BitArray by setting, resetting, toggling, and testing bits
    for (int i = 1; i < (1 << 10); i++)
    {
        REQUIRE(b.good());

        b.set(i);                // set first 1..1023 bits to 1
        b.reset(i + (1 << 10));  // reset bits 1025..2047 to 0
        b.toggle(i + (1 << 11)); // toggle bits 2049..3071

        REQUIRE(b.test(i));
        REQUIRE_FALSE(b.test(i + (1 << 10)));
        REQUIRE((
            (b.test(i + (1 << 11)) == true && s.at(i + (1 << 11)) == '0') || // either this is true
            (b.test(i + (1 << 11)) == false && s.at(i + (1 << 11)) == '1')   // or this is true
            ));
    }
}

// Write your own test cases below

TEST_CASE("Bitarray: Test construction(size) valid and invalid", "[bitarray]")
{
    BitArray b1(10);
    REQUIRE(b1.good() == true);

    BitArray b(-5);
    REQUIRE(b.good() == false);
}

TEST_CASE("Bitarray: Test construction(string) valid and invalid", "[bitarray]")
{
    BitArray b1("101010");
    REQUIRE(b1.good() == true);

    BitArray b("102010"); // invalid string
    REQUIRE(b.good() == false);
}

TEST_CASE("Bitarray: Test size()", "[bitarray]")
{
    BitArray b1;
    REQUIRE(b1.size() == 8);

    BitArray b2(32);
    REQUIRE(b2.size() == 32);

    BitArray b3("1010101010");
    REQUIRE(b3.size() == 10);

    BitArray b4(-2);
    REQUIRE(b4.size() == -2); // size() should return the initialized size even if invalid
}

TEST_CASE("Bitarray: Test set() valid and invalid", "[bitarray]")
{
    BitArray b1(10);
    b1.set(5);
    REQUIRE(b1.test(5) == true);
    REQUIRE(b1.good() == true);

    BitArray b2(10);
    b2.set(10); // invalid index
    REQUIRE(b2.good() == false);
}

TEST_CASE("Bitarray: Test reset() valid and invalid", "[bitarray]")
{
    BitArray b1(10);
    b1.set(5);
    b1.reset(5);
    REQUIRE(b1.test(5) == false);
    REQUIRE(b1.good() == true);

    BitArray b2(10);
    b2.reset(-1); // invalid index
    REQUIRE(b2.good() == false);
}

TEST_CASE("Bitarray: Test toggle() valid and invalid", "[bitarray]")
{
    BitArray b1(10);
    b1.toggle(2);
    REQUIRE(b1.test(2) == true);
    b1.toggle(2);
    REQUIRE(b1.test(2) == false);
    REQUIRE(b1.good() == true);

    BitArray b2(10);
    b2.toggle(10); // invalid index
    REQUIRE(b2.good() == false);
}

TEST_CASE("Bitarray: Test test() true, false, and invalid", "[bitarray]")
{
    BitArray b1(10);
    b1.set(3);
    REQUIRE(b1.test(3) == true);
    REQUIRE(b1.test(4) == false);
    REQUIRE(b1.good() == true);

    BitArray b2(10);
    b2.test(15); // invalid index
    REQUIRE(b2.good() == false);
}

TEST_CASE("Bitarray: Test asString() after various operations", "[bitarray]")
{
    BitArray b1(5);
    REQUIRE(b1.asString().compare("00000") == 0);

    b1.set(0);
    b1.set(2);
    REQUIRE(b1.asString().compare("10100") == 0);

    b1.reset(2);
    REQUIRE(b1.asString().compare("10000") == 0);

    b1.toggle(1);
    REQUIRE(b1.asString().compare("11000") == 0);

    b1.toggle(0);
    REQUIRE(b1.asString().compare("01000") == 0);
}

// Project 1 Checkoff Tests

TEST_CASE("Bitarray: Test reset() and toggle() methods to perform the same function as set()", "[bitarray]")
{
    std::string ex_string = "101010101010100010";

    BitArray b_to_set(ex_string); // create array to be set
    REQUIRE(b_to_set.good() == true);

    b_to_set.set(0);                   // set first bit
    b_to_set.set(b_to_set.size() - 1); // set last bit

    BitArray b_to_toggle(ex_string); // create array to be reset/toggled
    REQUIRE(b_to_toggle.good() == true);

    b_to_toggle.reset(0);                      // reset first bit
    b_to_toggle.reset(b_to_toggle.size() - 1); // reset last bit

    b_to_toggle.toggle(0);                      // toggle first bit
    b_to_toggle.toggle(b_to_toggle.size() - 1); // toggle last bit

    REQUIRE(b_to_toggle.asString() == b_to_set.asString()); // compare
}

TEST_CASE("Bitarry: Test additional complement() method", "[bitarray]")
{
    BitArray unsign("010101");
    std::string comp1 = complement(unsign);
    REQUIRE(comp1 == "010101");

    BitArray ones("111111");
    std::string comp2 = complement(ones);
    REQUIRE(comp2 == "000001");

    BitArray zeros("100000");
    std::string comp3 = complement(zeros);
    REQUIRE(comp3 == "100000");

    BitArray half("111000");
    std::string comp4 = complement(half);
    REQUIRE(comp4 == "00100");
}
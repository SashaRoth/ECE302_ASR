#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"
#include "dynamic_bag.hpp"

// Test cases for LimitedSizeBag
/*
TEST_CASE("Calling all public methods of LimitedSizeBag", "[LimitedSizeBag]")
{
  LimitedSizeBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}

*/

// Test cases for DynamicBag

TEST_CASE("Calling all public methods of DynamicBag", "[DynamicBag]")
{
  DynamicBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}

TEST_CASE("Testing default constructor of DynamicBag", "[DynamicBag]")
{
  DynamicBag<int> b;
  REQUIRE(b.isEmpty() == true);
  REQUIRE(b.getCurrentSize() == 0);
}

TEST_CASE("Testing add and getCurrentSize of DynamicBag", "[DynamicBag]")
{
  DynamicBag<int> b;
  b.add(5);
  b.add(10);
  REQUIRE(b.getCurrentSize() == 2);
}

TEST_CASE("Testing copy contructor and equivalence operator of DynamicBag", "[DynamicBag]")
{
  DynamicBag<int> b1;
  b1.add(5);
  b1.add(10);
  DynamicBag<int> b2(b1);
  REQUIRE(b2.getCurrentSize() == 2);
  REQUIRE(b2.contains(5) == true);
  REQUIRE(b2.contains(10) == true);
  REQUIRE(b1 == b2);
}

TEST_CASE("Testing assignment and equivalence operators of DynamicBag", "[DynamicBag]")
{
  DynamicBag<int> b1;
  b1.add(5);
  b1.add(10);
  DynamicBag<int> b2;
  b2 = b1;
  REQUIRE(b2 == b1); // They should be equal
  b2.add(15);        // Modify b2 after assignment (to ensure deep copy)
  REQUIRE(b1.getCurrentSize() == 2);
  REQUIRE(b2.getCurrentSize() == 3);
  REQUIRE(b2.contains(5) == true);
  REQUIRE(b2.contains(10) == true);
  REQUIRE(b2.contains(15) == true);
  REQUIRE(b1.contains(15) == false);
  REQUIRE((b1 == b2) == false); // They should not be equal now
  REQUIRE(b1 == b2);
}

TEST_CASE("Testing remove, clear, and isEmpty of DynamicBag", "[DynamicBag]")
{
  DynamicBag<int> b;
  b.add(5);
  b.remove(5);
  REQUIRE(b.isEmpty() == true);
  b.add(10);
  b.add(15);
  b.clear();
  REQUIRE(b.isEmpty() == true);
}

TEST_CASE("Testing getFrequencyOf of DynamicBag", "[DynamicBag]")
{
  DynamicBag<int> b;
  b.add(5);
  b.add(5);
  b.add(10);
  REQUIRE(b.getFrequencyOf(5) == 2);
  REQUIRE(b.getFrequencyOf(10) == 1);
  REQUIRE(b.getFrequencyOf(15) == 0);
}

TEST_CASE("Testing contains of DynamicBag", "[DynamicBag]")
{
  DynamicBag<int> b;
  b.add(5);
  REQUIRE(b.contains(5) == true);
  REQUIRE(b.contains(10) == false);
}
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"
#include "dynamic_bag.hpp"

// Test cases for LimitedSizeBag

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
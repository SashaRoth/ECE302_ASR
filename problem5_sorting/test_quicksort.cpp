#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

#include "list.hpp"
#include "quicksort.hpp"

/* Provided test cases */
TEST_CASE("Sort: Test move entry", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  // move forward
  lst.moveEntry(1, 3);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 100);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 11);

  // move backward
  lst.moveEntry(5, 1);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(1) == 11);
  REQUIRE(lst.getEntry(2) == 4);
  REQUIRE(lst.getEntry(3) == 10);
  REQUIRE(lst.getEntry(4) == 100);
  REQUIRE(lst.getEntry(5) == 25);
}

TEST_CASE("Sort: Integer sorting", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  quick_sort(lst, 1, lst.getLength()); // note the change here!

  // check sorted list
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 11);
  REQUIRE(lst.getEntry(4) == 25);
  REQUIRE(lst.getEntry(5) == 100);
}


TEST_CASE("Sort: Test move entry throw", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);
  lst.insert(4, 25);
  lst.insert(5, 11);

  // try to move forward
  REQUIRE_THROWS(lst.moveEntry(1, 6));
  REQUIRE_THROWS(lst.moveEntry(0, 5));

  lst.insert(5, 11);
  REQUIRE_NOTHROW(lst.moveEntry(1, 6));

  // try to move backward
  REQUIRE_THROWS(lst.moveEntry(7, 1));
  REQUIRE_THROWS(lst.moveEntry(6, -1));
}

/* Your test cases */

//test move entry

TEST_CASE("Test move entry valid and invalid", "[sorting]")
{
  List<int> lst;

  lst.insert(1, 100);
  lst.insert(2, 4);
  lst.insert(3, 10);

  //valid move
  lst.moveEntry(1, 3); //move first entry to middle of list
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 100);

  //invalid moves
  REQUIRE_THROWS(lst.moveEntry(0, 2)); //from index is out of bounds
  REQUIRE_THROWS(lst.moveEntry(4, 1)); //from index is out of bounds
  REQUIRE_THROWS(lst.moveEntry(2, 0)); //to index is out of bounds
  REQUIRE_THROWS(lst.moveEntry(1, 4)); //to index is out of bounds
}

//test partition helper method

TEST_CASE("Test partition helper method", "[sorting]"){
  List<int> lst;
  lst.insert(1, 8);
  lst.insert(1, -2);
  lst.insert(1, 7);
  lst.insert(1, 3);
  lst.insert(1, 5); //contents of list: 5, 3, 7, 2, 8

  int result = partition(lst, 1, 5); //partition the list
  
  std::cout << "Sorted partition: ";
  for(int i = 1; i <= 5; i++){
    std::cout << lst.getEntry(i) << " ";
  }
  std::cout << std::endl;

  REQUIRE(result == 3); //new pivot should be at index 3
  REQUIRE(lst.getEntry(1) == 3);
  REQUIRE(lst.getEntry(2) == -2);
  REQUIRE(lst.getEntry(3) == 5);
  REQUIRE(lst.getEntry(4) == 8);
  REQUIRE(lst.getEntry(5) == 7);
}

//test quick sort

TEST_CASE("Test quick sort: integer values", "[sorting]"){
  List<int> lst;
  lst.insert(1, 50);
  lst.insert(1, 90);
  lst.insert(1, 12);
  lst.insert(1, 42);
  lst.insert(1, 66);
  lst.insert(1, 100);
  lst.insert(1, 3);
  lst.insert(1, 14);
  lst.insert(1, 32);
  lst.insert(1, 87);

  quick_sort(lst, 1, lst.getLength());

  for(int i = 1; i < lst.getLength(); i++){
    REQUIRE(lst.getEntry(i) <= lst.getEntry(i + 1)); //check that list is sorted
  }
}

TEST_CASE("Test quick sort: boolean values", "[sorting]"){
  List<bool> lst;
  lst.insert(1, true);
  lst.insert(1, false);
  lst.insert(1, true);
  lst.insert(1, false);
  lst.insert(1, true);

  quick_sort(lst, 1, lst.getLength());

  for(int i = 1; i < lst.getLength(); i++){
    REQUIRE(lst.getEntry(i) <= lst.getEntry(i + 1)); //check that list is sorted
  }
}

TEST_CASE("Test quick sort: float values", "[sorting]"){
  List<float> lst;
  lst.insert(1, 3.14);
  lst.insert(1, 2.71);
  lst.insert(1, 1.41);
  lst.insert(1, 0.577);
  lst.insert(1, 1.618);

  quick_sort(lst, 1, lst.getLength());

  for(int i = 1; i < lst.getLength(); i++){
    std::cout << lst.getEntry(i) << " ";
    REQUIRE(lst.getEntry(i) <= lst.getEntry(i + 1)); //check that list is sorted
  }
}

TEST_CASE("Test quick sort: char values", "[sorting]"){
  List<char> lst;
  lst.insert(1, 'z');
  lst.insert(1, 'a');
  lst.insert(1, 'm');
  lst.insert(1, 'e');
  lst.insert(1, 'b');

  quick_sort(lst, 1, lst.getLength());

  for(int i = 1; i < lst.getLength(); i++){
    REQUIRE(lst.getEntry(i) <= lst.getEntry(i + 1)); //check that list is sorted
  }
}
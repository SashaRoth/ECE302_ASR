#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "sorted_list.hpp"
#include "list.hpp"

/* Provided tests */
TEST_CASE("SortedList: Testing size", "[sorted list]")
{
  SortedList<char> lst;

  REQUIRE(lst.isEmpty());
  REQUIRE(lst.getLength() == 0);

  lst.insert('b');
  REQUIRE(!lst.isEmpty());
  REQUIRE(lst.getLength() == 1);

  lst.insert('a');
  REQUIRE(lst.getLength() == 2);

  lst.removeAt(1);
  REQUIRE(lst.getLength() == 1);

  lst.removeAt(1);
  REQUIRE(lst.getLength() == 0);
  REQUIRE(lst.isEmpty());
}

TEST_CASE("SortedList: Testing insert", "[sorted list]")
{
  SortedList<char> lst;

  char c = 'a';
  while (c <= 'z')
  {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == 26);

  bool getEntryCheck;
  for (int i = 1; i <= 26; ++i)
  {
    getEntryCheck = (lst.getEntry(i) == 'a' + i - 1);
    std::cout << "getEntry(" << i << "): " << lst.getEntry(i) << std::endl; // debug statement to check getEntry
    if (!getEntryCheck)
    {
      break;
    }
  }
  REQUIRE(getEntryCheck);
}

TEST_CASE("SortedList: Testing remove", "[sorted list]")
{
  SortedList<char> lst;

  char c = 'a';
  int size = 10;
  while (c < 'a' + size)
  {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == size);

  lst.remove('c');
  REQUIRE(lst.getLength() == size - 1);
  REQUIRE(lst.getEntry(3) == 'd');

  lst.remove('e');
  REQUIRE(lst.getLength() == size - 2);
  REQUIRE(lst.getEntry(6) == 'h');

  lst.remove('a');
  REQUIRE(lst.getLength() == size - 3);
  REQUIRE(lst.getEntry(1) == 'b');
}

TEST_CASE("SortedList: Testing getPosition and repeated items", "[sorted list]")
{
  SortedList<char> lst;

  lst.insert('a');
  lst.insert('d');
  lst.insert('e');
  lst.insert('c');
  lst.insert('b');
  lst.insert('e');
  lst.insert('f');
  lst.insert('e');

  REQUIRE(lst.getLength() == 8);
  REQUIRE(lst.getPosition('a') == 1);
  REQUIRE(lst.getPosition('b') == 2);
  REQUIRE(lst.getPosition('c') == 3);
  REQUIRE(lst.getPosition('d') == 4);
  REQUIRE(lst.getPosition('e') == 5);
  REQUIRE(lst.getPosition('f') == 8);

  lst.clear();
  REQUIRE_THROWS(lst.getPosition('a'));
}

TEST_CASE("SortedList: Testing constructor from unsorted list", "[sorted list]")
{
  List<char> unsorted;

  unsorted.insert(1, 'a');
  unsorted.insert(2, 'd');
  unsorted.insert(3, 'e');
  unsorted.insert(4, 'c');
  unsorted.insert(5, 'b');

  SortedList<char> sorted(unsorted);

  REQUIRE(sorted.getPosition('a') == 1);
  REQUIRE(sorted.getPosition('b') == 2);
  REQUIRE(sorted.getPosition('c') == 3);
  REQUIRE(sorted.getPosition('d') == 4);
  REQUIRE(sorted.getPosition('e') == 5);
}

TEST_CASE("SortedList: Testing list and sorted list std::out_of_range exceptions", "[sorted list]")
{
  List<char> lst;

  REQUIRE_THROWS_AS(lst.remove(1), std::out_of_range);
  REQUIRE_THROWS_AS(lst.insert(2, 'a'), std::out_of_range);
  REQUIRE_THROWS_AS(lst.getEntry(1), std::out_of_range);
  REQUIRE_THROWS_AS(lst.setEntry(1, 'a'), std::out_of_range);

  lst.insert(1, 'a');
  lst.insert(2, 'b');

  REQUIRE_THROWS_AS(lst.remove(3), std::out_of_range);
  REQUIRE_THROWS_AS(lst.insert(4, 'c'), std::out_of_range);
  REQUIRE_THROWS_AS(lst.getEntry(3), std::out_of_range);
  REQUIRE_THROWS_AS(lst.setEntry(3, 'c'), std::out_of_range);

  SortedList<char> sorted;
  sorted.insert('a');
  sorted.insert('b');
  sorted.insert('c');
  sorted.insert('d');
  sorted.insert('e');

  REQUIRE_THROWS_AS(sorted.removeAt(6), std::out_of_range);
  REQUIRE_THROWS_AS(sorted.getEntry(6), std::out_of_range);
  REQUIRE_THROWS_AS(sorted.getEntry(0), std::out_of_range);
  REQUIRE_THROWS_AS(sorted.removeAt(-1), std::out_of_range);
}

/* Your tests here */

//only tests for methods that are modified in sorted_list; other methods that are inherited from List<T> have already been tested in previous assignments

//test constructor from unsorted list
TEST_CASE("SortedList: Testing constructor taking unsorted list as argument", "[sorted list]")
{
  List<float> unsorted;

  unsorted.insert(1, 2.35);
  unsorted.insert(2, 4.58);
  unsorted.insert(3, 1.05);
  unsorted.insert(4, 1.04);
  unsorted.insert(5, 3.14);

  SortedList<float> sorted(unsorted);

  REQUIRE(sorted.getPosition(1.04) == 1);
  REQUIRE(sorted.getPosition(1.05) == 2);
  REQUIRE(sorted.getPosition(2.35) == 3);
  REQUIRE(sorted.getPosition(3.14) == 4);
  REQUIRE(sorted.getPosition(4.58) == 5);

  //test exceptions and false returns

  REQUIRE_THROWS_AS(sorted.getPosition(5.0), std::invalid_argument);
  REQUIRE_FALSE(sorted.getPosition(1.04) == 2);
}

//test insert
TEST_CASE("SortedList: Testing insert with various cases", "[sorted list]")
{
  SortedList<int> lst;

  //test on empty list
  lst.insert(5);
  REQUIRE(lst.getEntry(1) == 5);

  lst.insert(3);
  REQUIRE(lst.getEntry(1) == 3);
  REQUIRE(lst.getEntry(2) == 5);

  //test adding very big value
  lst.insert(100);
  REQUIRE(lst.getEntry(3) == 100);

  //test adding very small value
  lst.insert(-10);
  REQUIRE(lst.getEntry(1) == -10);

  //test adding value in the middle
  lst.insert(4);
  REQUIRE(lst.getEntry(3) == 4);

  //make sure array is sorted after multiple insertions
  REQUIRE(lst.getEntry(1) == -10);
  REQUIRE(lst.getEntry(2) == 3);
  REQUIRE(lst.getEntry(3) == 4);
  REQUIRE(lst.getEntry(4) == 5);
  REQUIRE(lst.getEntry(5) == 100);
}

//test remove
TEST_CASE("SortedList: Testing remove with various cases", "[sorted list]")
{
  SortedList<int> lst;

  lst.insert(5);
  lst.insert(13);
  lst.insert(2);
  lst.insert(9);
  lst.insert(10);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(1) == 2);
  REQUIRE(lst.getEntry(2) == 5);
  REQUIRE(lst.getEntry(3) == 9);
  REQUIRE(lst.getEntry(4) == 10);
  REQUIRE(lst.getEntry(5) == 13);

  //test removing first element
  lst.remove(2);
  REQUIRE(lst.getEntry(1) == 5);
  REQUIRE(lst.getEntry(2) == 9);
  REQUIRE(lst.getEntry(3) == 10);
  REQUIRE(lst.getEntry(4) == 13);
  lst.insert(2); // add it back for further testing
  

  //test removing last element
  lst.remove(13);
  REQUIRE(lst.getEntry(1) == 2);
  REQUIRE(lst.getEntry(2) == 5);
  REQUIRE(lst.getEntry(3) == 9);
  REQUIRE(lst.getEntry(4) == 10);
  REQUIRE_THROWS_AS(lst.getEntry(5), std::out_of_range); // make sure 5th element is removed
  lst.insert(13); // add it back for further testing

  //test removing middle element
  lst.remove(9);
  REQUIRE(lst.getEntry(1) == 2);
  REQUIRE(lst.getEntry(2) == 5);
  REQUIRE(lst.getEntry(3) == 10);
  REQUIRE(lst.getEntry(4) == 13);

  //test removing element twice
  REQUIRE_THROWS_AS(lst.remove(9), std::invalid_argument);

  //test removing non-existent element
  REQUIRE_THROWS_AS(lst.remove(100), std::invalid_argument);
}

//test removeAt (essially the same as List<T>::remove, but we can still test it to make sure it works for SortedList)
TEST_CASE("SortedList: Testing removeAt with various cases", "[sorted list]")
{
  SortedList<int> lst;

  lst.insert(5);
  lst.insert(13);
  lst.insert(2);
  lst.insert(9);
  lst.insert(10);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(1) == 2);
  REQUIRE(lst.getEntry(2) == 5);
  REQUIRE(lst.getEntry(3) == 9);
  REQUIRE(lst.getEntry(4) == 10);
  REQUIRE(lst.getEntry(5) == 13);

  //test removing first element
  lst.removeAt(1);
  REQUIRE(lst.getEntry(1) == 5);
  REQUIRE(lst.getEntry(2) == 9);
  REQUIRE(lst.getEntry(3) == 10);
  REQUIRE(lst.getEntry(4) == 13);
  
  //test removing last element
  lst.removeAt(4);
  REQUIRE(lst.getEntry(1) == 5);
  REQUIRE(lst.getEntry(2) == 9);
  REQUIRE(lst.getEntry(3) == 10);
  
  //test removing middle element
  lst.removeAt(2);
  REQUIRE(lst.getEntry(1) == 5);
  REQUIRE(lst.getEntry(2) == 10);

   //test removing element at invalid position
   REQUIRE_THROWS_AS(lst.removeAt(3), std::out_of_range); // only two elements left, so position 3 is invalid
   REQUIRE_THROWS_AS(lst.removeAt(-1), std::out_of_range); // negative position is invalid
}

//test getEntry
TEST_CASE("SortedList: Testing getEntry with various cases", "[sorted list]")
{
  SortedList<std::string> lst;

  lst.insert("robot");
  lst.insert("smoothie");
  lst.insert("spring break");

  REQUIRE(lst.getEntry(1) == "robot");
  REQUIRE(lst.getEntry(2) == "smoothie");
  REQUIRE(lst.getEntry(3) == "spring break");

  //test getEntry with invalid position
  REQUIRE_THROWS_AS(lst.getEntry(0), std::out_of_range); // 1-indexed, 0 is invalid
  REQUIRE_THROWS_AS(lst.getEntry(4), std::out_of_range); // out of range
}

//test getPosition
TEST_CASE("SortedList: Testing getPosition with various cases", "[sorted list]")
{
  SortedList<std::string> lst;

  lst.insert("celsius energy drink");
  lst.insert("hi Gavin if you're reading this");
  lst.insert("I am going to sleep so much next week");

  REQUIRE(lst.getPosition("I am going to sleep so much next week") == 1); //sorts uppercase first according to ascii code, even though "i" is last alphabetically
  REQUIRE(lst.getPosition("celsius energy drink") == 2);
  REQUIRE(lst.getPosition("hi Gavin if you're reading this") == 3);

  //test getPosition with non-existent item: "my sleep schedule" is nonexistent
  REQUIRE_THROWS_AS(lst.getPosition("my sleep schedule"), std::invalid_argument);
}
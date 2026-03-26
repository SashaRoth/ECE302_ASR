#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "list.hpp"
#include "sorted_list.hpp"
#include "priority_queue.hpp"

#include <iostream>

/* Provided test cases */
TEST_CASE("Priority: Testing Sorted List", "[sorted list]")
{
  SortedList<int> sort;

  REQUIRE(sort.isEmpty());
  REQUIRE(sort.getLength() == 0);

  sort.insert(1);
  REQUIRE_FALSE(sort.isEmpty());
  REQUIRE(sort.getLength() == 1);
  sort.insert(2);
  REQUIRE(sort.getLength() == 2);
  sort.insert(8);
  REQUIRE(sort.getLength() == 3);
  sort.insert(6);
  REQUIRE(sort.getLength() == 4);
  sort.insert(9);
  REQUIRE(sort.getLength() == 5);
  sort.insert(0);
  REQUIRE(sort.getLength() == 6);

  REQUIRE(sort.getEntry(1) == 0);
  REQUIRE(sort.getPosition(0) == 1);
  REQUIRE(sort.getEntry(2) == 1);
  REQUIRE(sort.getPosition(1) == 2);
  REQUIRE(sort.getEntry(3) == 2);
  REQUIRE(sort.getPosition(2) == 3);
  REQUIRE(sort.getEntry(4) == 6);
  REQUIRE(sort.getPosition(6) == 4);
  REQUIRE(sort.getEntry(5) == 8);
  REQUIRE(sort.getPosition(8) == 5);
  REQUIRE(sort.getEntry(6) == 9);
  REQUIRE(sort.getPosition(9) == 6);

  sort.remove(0);
  REQUIRE(sort.getEntry(1) == 1);
  REQUIRE(sort.getLength() == 5);

  sort.remove(1);
  REQUIRE(sort.getEntry(1) == 2);
  REQUIRE(sort.getLength() == 4);

  sort.remove(9);
  REQUIRE(sort.getEntry(1) == 2);
  REQUIRE(sort.getLength() == 3);

  sort.removeAt(2);
  REQUIRE(sort.getEntry(1) == 2);
  REQUIRE(sort.getLength() == 2);

  sort.removeAt(1);
  REQUIRE(sort.getEntry(1) == 8);
  REQUIRE(sort.getLength() == 1);

  sort.removeAt(1);
  REQUIRE(sort.getLength() == 0);
  REQUIRE(sort.isEmpty());
}

TEST_CASE("Priority: Testing Priority Queue Add/isEmpty/peek/remove", "[priority queue]")
{
  PriorityQueue<int> pq;

  REQUIRE(pq.isEmpty());

  pq.add(3);
  REQUIRE_FALSE(pq.isEmpty());

  pq.add(1);
  pq.add(5);
  pq.add(2);

  REQUIRE(pq.peek() == 5);

  pq.remove();
  REQUIRE(pq.peek() == 3);

  pq.remove();
  REQUIRE(pq.peek() == 2);
}

/** Write your own test cases here */

//test ascending order of sorted list
TEST_CASE("SortedList: Test ascending order", "[sorted list]"){
  SortedList<int> sl;

  sl.insert(6);
  sl.insert(99);
  sl.insert(43);
  sl.insert(-5);
  sl.insert(300);

  for(int i = 1; i < sl.getLength(); i++){
    REQUIRE(sl.getEntry(i) <= sl.getEntry(i + 1));
  }
}

TEST_CASE("SortedList: Test throw delegation", "[sorted list]"){
  SortedList<int> sl;

  REQUIRE(sl.isEmpty());

  REQUIRE_THROWS_AS(sl.removeAt(1), std::out_of_range); //Priority queue's remove method delegates to sorted list's removeAt method, which handles exceptions
  REQUIRE_THROWS_AS(sl.getEntry(1), std::out_of_range); //Priority queue's peek method delegates to sorted list's getEntry method, which handles exceptions

}

TEST_CASE("Priority queue: Test isEmpty()", "[priority queue]"){
  PriorityQueue<char> pq;

  REQUIRE(pq.isEmpty());

  pq.add('a');

  REQUIRE_FALSE(pq.isEmpty());
}

TEST_CASE("Priority queue: Test add(), remove(), and peek()", "[priority queue]"){
  PriorityQueue<std::string> pq;

  pq.add("element");
  pq.add("another element!");

  REQUIRE(pq.peek() == "element"); //add should be able to sort any data type in ascending order

  pq.remove();

  REQUIRE(pq.peek() == "another element!");

  pq.remove();

  REQUIRE_THROWS_AS(pq.peek(), std::out_of_range); //peek should throw exception when queue is empty
  REQUIRE_THROWS_AS(pq.remove(), std::out_of_range); //remove should throw exception when queue is empty  

}
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"
#include "linked_list.hpp"

//Provided test cases

TEST_CASE("Lists: Test ArrayList 1-index Edge Cases", "[ArrayList]")
{
  ArrayList<int> list;
  REQUIRE(list.isEmpty());

  REQUIRE_FALSE(list.insert(0, 0)); // invalid
  REQUIRE(list.isEmpty());          // still empty

  REQUIRE(list.insert(1, 1));     // valid
  REQUIRE(list.getLength() == 1); // length is 1

  REQUIRE_FALSE(list.remove(0));  // invalid
  REQUIRE(list.getLength() == 1); // length is still 1

  REQUIRE(list.remove(1)); // valid
  REQUIRE(list.isEmpty()); // now empty

  list.insert(1, 301);
  list.insert(2, 302);

  REQUIRE(list.getEntry(1) == 301);
  REQUIRE(list.getEntry(2) == 302);

  REQUIRE_THROWS_AS(list.getEntry(0), std::out_of_range);
  REQUIRE_THROWS_AS(list.setEntry(0, 300), std::out_of_range);

  // pos = 1 is the first list item, that also indicates pos = n is the last list item
  // your insertion at pos=n is valid (which makes the old last item shift to right),
  // and your insertion at pos=n+1 is also valid (which appends to the end of the list)
  // your removal at pos=1 is valid, but your removal at pos=n+1 is invalid
}

TEST_CASE("Lists: Test LinkedList 1-index Edge Cases", "[LinkedList]")
{
  LinkedList<int> list;
  REQUIRE(list.isEmpty());

  REQUIRE_FALSE(list.insert(0, 0)); // invalid
  REQUIRE(list.isEmpty());          // still empty

  REQUIRE(list.insert(1, 1));     // valid
  REQUIRE(list.getLength() == 1); // length is 1

  REQUIRE_FALSE(list.remove(0));  // invalid
  REQUIRE(list.getLength() == 1); // length is still 1

  REQUIRE(list.remove(1)); // valid
  REQUIRE(list.isEmpty()); // now empty

  list.insert(1, 301);
  list.insert(2, 302);

  REQUIRE(list.getEntry(1) == 301);
  REQUIRE(list.getEntry(2) == 302);

  REQUIRE_THROWS_AS(list.getEntry(0), std::out_of_range);
  REQUIRE_THROWS_AS(list.setEntry(0, 300), std::out_of_range);

  // pos = 1 is the first list item, that also indicates pos = n is the last list item
  // your insertion at pos=n is valid (which makes the old last item shift to right),
  // and your insertion at pos=n+1 is also valid (which appends to the end of the list)
  // your removal at pos=1 is valid, but your removal at pos=n+1 is invalid
}

//Sasha's test cases

//ArrayList Unit Tests
TEST_CASE("Lists: Test ArrayList default constructor", "[ArrayList]"){
  ArrayList<int> a;
  REQUIRE(a.getLength() == 0);
  REQUIRE(a.isEmpty() == 0);
}

TEST_CASE("Lists: Test ArrayList copy constructor", "[ArrayList]"){
  ArrayList<int> a1;

  a1.insert(1, 5);
  a1.insert(2, 10);
  a1.insert(3, 15);

  ArrayList<int> a2(a1);

  REQUIRE(a1.getLength() == a2.getLength());
  REQUIRE(a1.getEntry(1) == a2.getEntry(1));
  REQUIRE(a1.getEntry(2) == a2.getEntry(2));
  REQUIRE(a1.getEntry(3) == a2.getEntry(3));
}

TEST_CASE("Lists: Test ArrayList copy assignment operator & swap method", "[ArrayList]"){
  ArrayList<int> a1;

  a1.insert(1, 20);
  a1.insert(2, 30);
  a1.insert(3, 40);

  ArrayList<int> a2;
  a2 = a1;

  REQUIRE(a1.getLength() == 3);
  REQUIRE(a2.getLength() == 3);
  REQUIRE(a1.getLength() == a2.getLength());
  REQUIRE(a1.getEntry(1) == a2.getEntry(1));
  REQUIRE(a1.getEntry(2) == a2.getEntry(2));
  REQUIRE(a1.getEntry(3) == a2.getEntry(3));
}

TEST_CASE("Lists: Test ArrayList isEmpty method", "[ArrayList]"){
  ArrayList<int> a;

  REQUIRE(a.isEmpty() == true);

  a.insert(1, 12);
  a.insert(2, 24);

  REQUIRE(a.isEmpty() == false);

  a.remove(2);
  a.remove(1);

  REQUIRE(a.isEmpty() == true);
}

TEST_CASE("Lists: Test ArrayList getLength method", "[ArrayList]"){
  ArrayList<int> a;
  REQUIRE(a.getLength() == 0);

  a.insert(1, 1);
  REQUIRE(a.getLength() == 1);

  a.insert(2, 10);
  REQUIRE(a.getLength() == 2);

  a.insert(3, 100);
  REQUIRE(a.getLength() == 3);

  a.remove(3);
  REQUIRE(a.getLength() == 2);
}

TEST_CASE("Lists: Test ArrayList insert method", "[ArrayList]"){ //require false if invalid position
  ArrayList<int> a;
}

TEST_CASE("Lists: Test ArrayList remove method", "[ArrayList]"){ //require false if invalid position
  ArrayList<int> a;
}

TEST_CASE("Lists: Test ArrayList clear method", "[ArrayList]"){
  ArrayList<int> a;
}

TEST_CASE("Lists: Test ArrayList getEntry method", "[ArrayList]"){ //throw exception if invalid position
  ArrayList<int> a;
}

TEST_CASE("Lists: Test ArrayList setEntry method", "[ArrayList]"){ //throw exception if invalid position
  ArrayList<int> a;
}

//LinkedList Unit Tests
TEST_CASE("Lists: Test LinkedList default constructor", "[LinkedList]"){
  LinkedList<int> l;
  REQUIRE(l.getLength() == 0);
  REQUIRE(l.isEmpty() == true);
}

TEST_CASE("Lists: Test LinkedList copy constructor", "[LinkedList]"){
  LinkedList<int> l1;
  l1.insert(1, 5);
  l1.insert(2, 10);
  l1.insert(3, 15);

  LinkedList<int> l2(l1);

  REQUIRE(l1.getLength() == 3);
  REQUIRE(l2.getLength() == 3);
  REQUIRE(l1.getLength() == l2.getLength());
  REQUIRE(l1.getEntry(1) == l2.getEntry(1));
  REQUIRE(l1.getEntry(2) == l2.getEntry(2));
  REQUIRE(l1.getEntry(3) == l2.getEntry(3));
}

TEST_CASE("Lists: Test LinkedList copy assignment operator & swap method", "[LinkedList]"){
  LinkedList<int> l1;

  l1.insert(1, 20);
  l1.insert(2, 30);
  l1.insert(3, 40);

  LinkedList<int> l2;
  l2 = l1;

  REQUIRE(l1.getLength() == 3);
  REQUIRE(l2.getLength() == 3);
  REQUIRE(l1.getLength() == l2.getLength());
  REQUIRE(l1.getEntry(1) == l2.getEntry(1));
  REQUIRE(l1.getEntry(2) == l2.getEntry(2));
  REQUIRE(l1.getEntry(3) == l2.getEntry(3));
}

TEST_CASE("Lists: Test LinkedList isEmpty method", "[LinkedList]"){
  LinkedList<int> l;

  REQUIRE(l.isEmpty() == true);

  l.insert(1, 12);
  l.insert(2, 24);

  REQUIRE(l.isEmpty() == false);

  l.remove(2);
  l.remove(1);

  REQUIRE(l.isEmpty() == true);

}

TEST_CASE("Lists: Test LinkedList getLength method", "[LinkedList]"){
  LinkedList<int> l;
  REQUIRE(l.getLength() == 0);

  l.insert(1, 1);
  REQUIRE(l.getLength() == 1);

  l.insert(2, 10);
  REQUIRE(l.getLength() == 2);

  l.insert(3, 100);
  REQUIRE(l.getLength() == 3);

  l.remove(3);
  REQUIRE(l.getLength() == 2);
}

TEST_CASE("Lists: Test LinkedList insert method", "[LinkedList]"){ //require false if invalid position
  LinkedList<int> l;
}

TEST_CASE("Lists: Test LinkedList remove method", "[LinkedList]"){ //require false if invalid position
  LinkedList<int> l;
}

TEST_CASE("Lists: Test LinkedList clear method", "[LinkedList]"){
  LinkedList<int> l;
}

TEST_CASE("Lists: Test LinkedList getEntry method", "[LinkedList]"){ //throw exception if invalid position
  LinkedList<int> l;
}

TEST_CASE("Lists: Test LinkedList setEntry method", "[LinkedList]"){ //throw exception if invalid position
  LinkedList<int> l;
}

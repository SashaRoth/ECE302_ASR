/** @file test_iterator.cpp
 * @author G. Zhou */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "LinkedListwIterator.hpp"

#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <typeinfo>

TEST_CASE("Using iterator to traverse LinkedList", "[LinkedList]")
{
  LinkedListwIterator<int> list;
  list.insert(1, 10);
  list.insert(2, 20);
  list.insert(3, 30);

  int sum = 0;
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    int value = *it;
    sum += value;
    std::cout << "It now points to " << value << std::endl;
    std::cout << "`it` is of type " << typeid(it).name() << std::endl;
    std::cout << std::endl;
  }
  REQUIRE(sum == 60);
}

TEST_CASE("Using two different methods to traverse vector and measure time", "[vector]")
{
  LinkedListwIterator<int> list;
  for (int i = 0; i < 100; ++i)
  {
    list.insert(i + 1, 1);
  }
  auto start = std::chrono::high_resolution_clock::now();
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    std::cout << "It now points to " << *it << std::endl;
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "100 items list, Time taken: " << elapsed.count() << " seconds to iterate using iterator" << std::endl;

  start = std::chrono::high_resolution_clock::now();
  for (int i = 1; i <= list.getLength(); ++i)
  {
    std::cout << "It now points to " << list.getEntry(i) << std::endl;
  }
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "100 items list, Time taken: " << elapsed.count() << " seconds to iterate using getEntry()" << std::endl;

  for (int i = 100; i < 1000; ++i)
  {
    list.insert(i + 1, 1);
  }
  start = std::chrono::high_resolution_clock::now();
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    std::cout << "It now points to " << *it << std::endl;
  }
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "1000 items list, Time taken: " << elapsed.count() << " seconds to iterate using iterator" << std::endl;

  start = std::chrono::high_resolution_clock::now();
  for (int i = 1; i <= list.getLength(); ++i)
  {
    std::cout << "It now points to " << list.getEntry(i) << std::endl;
  }
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "1000 items list, Time taken: " << elapsed.count() << " seconds to iterate using getEntry()" << std::endl;

  for (int i = 1000; i < 10000; ++i)
  {
    list.insert(i + 1, 1);
  }
  start = std::chrono::high_resolution_clock::now();
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    std::cout << "It now points to " << *it << std::endl;
  }
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "10000 items list, Time taken: " << elapsed.count() << " seconds to iterate using iterator" << std::endl;

  start = std::chrono::high_resolution_clock::now();
  for (int i = 1; i <= list.getLength(); ++i)
  {
    std::cout << "It now points to " << list.getEntry(i) << std::endl;
  }
  end = std::chrono::high_resolution_clock::now();
  elapsed = end - start;
  std::cout << "10000 items list, Time taken: " << elapsed.count() << " seconds to iterate using getEntry()" << std::endl;

  // TODO: Run the test and comment the differences you noticed from running for 100, 1000, and 10000 items list.
  // Does the time complexity of using iterator and getEntry() to traverse the list match the theoretical time complexity we discussed in class?
}

TEST_CASE("Using std::vector's iterator to test all operators", "[vector]")
{
  // std::vector iterators are categorized as random-access iterators.
  // This is the most powerful category of iterators, supporting all operations, including:
  // Dereferencing (*it or it->).
  // Incrementing / Decrementing(++it, --it, it++, it--)
  // Comparison(it == end, it < end).
  // Arithmetic operations(it + n, it - n).

  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::vector<int>::iterator it;
  int product = 1;
  for (it = vec.begin(); it != vec.end(); ++it)
  {
    product = product * (*it);
    std::cout << std::endl;
  }
  REQUIRE(product == 120);

  it = vec.begin();
  REQUIRE(*it == 1);
  ++it;
  REQUIRE(*it == 2);
  it++;
  REQUIRE(*it == 3);
  --it;
  REQUIRE(*it == 2);
  it--;
  REQUIRE(*it == 1);

  it = vec.end();
  REQUIRE(*(it - 2) == 4);
  REQUIRE(*(it - 4) == 2);
  it -= 3;
  REQUIRE(*it == 3);
  it += 2;
  REQUIRE(*it == 5);

  std::vector<int>::iterator it2 = vec.begin();
  REQUIRE(it != it2);
  REQUIRE(it >= it2);
  REQUIRE(*it != *it2);

  ++it2;
  ++it2;
  ++it2;
  ++it2;
  REQUIRE(it == it2);
  REQUIRE(*it == *it2);

  REQUIRE(it[-1] == 4); // it[-1] is equivalent to *(it - 1)
  it = vec.begin();
  REQUIRE(it[2] == 3); // if set to the beginning, it[2] is equivalent to arr[2]
}

TEST_CASE("Using std::vector's iterator to erase and insert", "[vector]")
{
  std::vector<int> vec = {10, 20, 30, 40, 50};
  std::vector<int>::iterator it;
  for (it = vec.begin(); it != vec.end(); ++it)
  {
    std::cout << "It now points to " << *it << std::endl;
    std::cout << "Its address is " << &(*it) << std::endl;
    std::cout << std::endl;
  }

  // Erase the second element (20)
  it = vec.erase(vec.begin() + 1);
  REQUIRE(vec.size() == 4);
  REQUIRE(vec[1] == 30);
  REQUIRE(*it == 30);

  // Insert 25 at the end the vector
  it = vec.insert(vec.begin() + 4, 25);
  REQUIRE(vec.size() == 5);
  REQUIRE(vec[4] == 25);
  REQUIRE(*it == 25); // 10 30 40 50 25
  it--;
  REQUIRE(*it == 50); // 10 30 40 50 25

  // TODO: based on the above lines, what are the designed return type of erase and insert?
  // Test yourself what are the return value (or it would crash) if erase and insert on vector get invalid?
  // like it = vec.insert(vec.begin() + 10, 60)

  // And how about setting `it` to the second to last element of the vector and then call erase twice?
  // Line above suggests that `it` is already set to the second to last element of the vector, which is 50.
  // Let's call erase the last element
  vec.erase(vec.begin() + 4);
  std::cout << "`it` points to " << *it << std::endl;
  std::cout << "And vector is now ";
  for (int i = 0; i < vec.size(); ++i)
  {
    std::cout << vec[i] << " "; // 10 30 40 50
  }
  std::cout << std::endl;

  vec.erase(vec.begin() + 3);
  std::cout << "`it` points to " << *it << std::endl;
  std::cout << "But vector is now ";
  for (int i = 0; i < vec.size(); ++i)
  {
    std::cout << vec[i] << " "; // 10 30 40
  }
  std::cout << std::endl;
  // TODO: what happens to `it` after the above two erase? Does it point to a valid element in the vector?
}

TEST_CASE("Using std::vector's reverse iterator to traverse string", "[string]")
{
  std::string str = "hello";
  std::string::reverse_iterator rit;
  std::string result;
  for (rit = str.rbegin(); rit != str.rend(); ++rit)
  {
    result += *rit;
  }
  REQUIRE(result == "olleh");
}

TEST_CASE("Sandbox to test forward iterator", "[sandbox]")
{
  class LinkedListwithForward
  {
  private:
    /* ---------- Node declaration ---------- */
    struct Node
    {
      int data;
      Node *next;
      Node(const int &value, Node *nextNode = nullptr) : data(value), next(nextNode) {}
    };
    Node *head; // Pointer to the first node in the list

  public:
    /* ---------- IteratorForward declaration ---------- */
    class IteratorForward
    {
    private:
      Node *current;

    public:
      IteratorForward(Node *ptr = nullptr) : current(ptr) {}

      /* Dereference */
      int &operator*() const { return current->data; } // Return reference → readable & writable

      /* Prefix increment */
      IteratorForward &operator++()
      {
        if (current)
          current = current->next;
        return *this;
      }

      /* Postfix increment */
      IteratorForward operator++(int)
      {
        IteratorForward temp = *this;
        ++(*this);
        return temp;
      }

      /* Equality */
      bool operator==(const IteratorForward &rhs) const { return current == rhs.current; }
      bool operator!=(const IteratorForward &rhs) const { return current != rhs.current; }
    };

    /* ---------- LinkedListwithForward Implementation ---------- */
    LinkedListwithForward() : head(nullptr) {}
    ~LinkedListwithForward() { clear(); }
    void push_front(const int &value) { head = new Node(value, head); }

    void clear()
    {
      while (head)
      {
        Node *temp = head;
        head = head->next;
        delete temp;
      }
    }

    IteratorForward begin() { return IteratorForward(head); }
    IteratorForward end() { return IteratorForward(nullptr); }
  };

  LinkedListwithForward list; // from the sandbox class
  list.push_front(50);
  list.push_front(40);
  list.push_front(30);
  list.push_front(20);
  list.push_front(10);

  auto it = list.begin();
  // (1) int num = *it;
  // (2) bool x = (it != list.end());
  // (3) auto y = it;
  // (4) ++it;
  // (5) std::cout << *y << std::endl;
  // (6) *it = 100;

  LinkedListwIterator<int> list2; // from the provided LinkedListwIterator of input iterator
  list2.insert(1, 10);
  list2.insert(2, 20);
  list2.insert(3, 30);
  list2.insert(4, 40);
  list2.insert(5, 50);

  auto it2 = list2.begin();
  // (1) int num2 = *it2;
  // (2) bool x2 = (it2 != list2.end());
  // (3) auto y2 = it2;
  // (4) ++it2;
  // (5) std::cout << *y2 << std::endl;
  // (6) *it2 = 100;

  // TODO: compare the usage of input iterator and forward iterator based on the above lines.
  // Which operations 1~6 are supported by both iterators?
  // Which operations 1~6 are only supported by forward iterator but not input iterator? Why?
}

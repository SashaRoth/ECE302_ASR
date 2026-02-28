#ifndef LINKEDLISTSMART_
#define LINKEDLISTSMART_

#include <memory>
#include <stdexcept>
#include <utility>
#include <iostream>

template <typename ItemType>
class LinkedListSmart
{
public: // intentionally public for testing purposes, should be private
  ////////////////////////////////////////////////////////////
  // Nested Node Class
  ////////////////////////////////////////////////////////////
  class Node
  {
  public:
    ItemType item;
    std::shared_ptr<Node> next;

    Node(const ItemType &anItem) : item(anItem), next(nullptr) {}
    ~Node()
    {
      std::cout << "Node destructor called for item: " << item << std::endl;
    }
  };

  ////////////////////////////////////////////////////////////
  // Data Members
  ////////////////////////////////////////////////////////////
  std::shared_ptr<Node> headPtr;
  int itemCount;

  ////////////////////////////////////////////////////////////
  // Private Helper
  ////////////////////////////////////////////////////////////
  std::shared_ptr<Node> getNodeAt(int position) const
  {
    if (position < 1 || position > itemCount)
      throw std::out_of_range("Invalid position in getNodeAt().");

    auto curPtr = headPtr;
    for (int skip = 1; skip < position; ++skip)
      curPtr = curPtr->next;

    return curPtr;
  }

public:
  ////////////////////////////////////////////////////////////
  // Constructors / Destructor
  ////////////////////////////////////////////////////////////

  LinkedListSmart() : headPtr(nullptr), itemCount(0) {}

  // Deep Copy Constructor
  LinkedListSmart(const LinkedListSmart &aList) : headPtr(nullptr), itemCount(0)
  {
    if (!aList.headPtr)
      return;

    headPtr = std::make_shared<Node>(aList.headPtr->item);

    auto newChainPtr = headPtr;
    auto origChainPtr = aList.headPtr->next;

    while (origChainPtr)
    {
      auto newNode = std::make_shared<Node>(origChainPtr->item);
      newChainPtr->next = newNode;
      newChainPtr = newNode;
      origChainPtr = origChainPtr->next;
    }

    itemCount = aList.itemCount;
  }

  // Copy-Swap Assignment
  LinkedListSmart &operator=(LinkedListSmart other)
  {
    std::swap(headPtr, other.headPtr);
    std::swap(itemCount, other.itemCount);
    return *this;
  }

  // Destructor
  ~LinkedListSmart()
  {
    std::cout << "LinkedListSmart destructor called...\n";

    // TODO: find all the options to deallocate the memory used by the linked list that won't cause a compilation error
    // Of those options, which one(s) will take the longest time to execute?

    // clear();              // option 1
    // headPtr = nullptr;    // option 2
    // itemCount = 0;        // option 3
    // delete headPtr;       // option 4
    // *headPtr = 0;         // option 5
    // // nothing            // option 6
    // while (itemCount > 0) // option 7
    // {
    //   remove(1);
    // }
    // while (itemCount > 0) // option 8
    // {
    //   remove(itemCount);
    // }
  }

  ////////////////////////////////////////////////////////////
  // Public Methods
  ////////////////////////////////////////////////////////////

  bool isEmpty() const
  {
    return itemCount == 0;
  }

  int getLength() const
  {
    return itemCount;
  }

  bool insert(int newPosition, const ItemType &newEntry)
  {
    bool ableToInsert = (newPosition >= 1 && newPosition <= itemCount + 1);
    if (ableToInsert)
    {
      auto newNode = std::make_shared<Node>(newEntry);
      std::cout << "Node counter after creating new node: " << newNode.use_count() << std::endl;

      if (newPosition == 1)
      {
        newNode->next = headPtr;
        headPtr = newNode;
        std::cout << "Node counter after building links: " << newNode.use_count() << std::endl;
      }
      else
      {
        auto prevPtr = getNodeAt(newPosition - 1);
        newNode->next = prevPtr->next;
        prevPtr->next = newNode;
        std::cout << "Node counter after building links: " << newNode.use_count() << std::endl;
      }
      itemCount++;
    }

    if (newPosition == 1)
    {
      std::cout << "Node counter when inserting function is almost finished: " << headPtr.use_count() << std::endl;
    }
    else
    {
      std::weak_ptr<Node> curPtr = getNodeAt(newPosition);
      std::cout << "Node counter when inserting function is almost finished: " << curPtr.use_count() << std::endl;
    }
    std::cout << std::endl;
    return ableToInsert;
  }

  bool remove(int position)
  {
    bool ableToRemove = (position >= 1 && position <= itemCount);
    if (ableToRemove)
    {
      if (position == 1)
      {
        headPtr = headPtr->next;
      }
      else
      {
        auto prevPtr = getNodeAt(position - 1);
        auto curPtr = prevPtr->next;
        prevPtr->next = curPtr->next;
      }

      itemCount--;
    }
    return ableToRemove;
  }

  void clear()
  {
    headPtr = nullptr;
    itemCount = 0;
  }

  ItemType getEntry(int position) const
  {
    if (position < 1 || position > itemCount)
      throw std::out_of_range("Invalid position in getEntry().");

    return getNodeAt(position)->item;
  }

  void replace(int position, const ItemType &newEntry)
  {
    if (position < 1 || position > itemCount)
      throw std::out_of_range("Invalid position in replace().");

    getNodeAt(position)->item = newEntry;
  }
};

#endif
//   Created by Frank M. Carrano and Timothy M. Henry.
//   Copyright (c) 2025 Pearson Education, Hoboken, New Jersey.

/** ADT list: Link-based implementation
 * @file LinkedListwIterator.hpp */

#ifndef LINKED_LIST_WITH_ITERATOR_
#define LINKED_LIST_WITH_ITERATOR_

#include <memory>
#include "LinkedIterator.hpp"
#include "ListInterface.hpp"
#include "Node.hpp"

template <class ItemType>
class LinkedListwIterator : public ListInterface<ItemType>
{
private:
   Node<ItemType> *headPtr; // Pointer to first node in the chain;
                            // (contains the first entry in the list)
   int itemCount;           // Current count of list items

   // Locates a specified node in this linked list.
   // @pre  position is the number of the desired node;
   //       position >= 1 and position <= itemCount.
   // @post  The node is found and a pointer to it is returned.
   // @param position  The number of the node to locate.
   // @return  A pointer to the node at the given position.
   Node<ItemType> *getNodeAt(int position) const;

public:
   LinkedListwIterator();
   LinkedListwIterator(const LinkedListwIterator<ItemType> &aList);
   virtual ~LinkedListwIterator();

   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const ItemType &newEntry);
   bool remove(int position);
   void clear();

   /** @throw if position < 1 or position > getLength(). */
   ItemType getEntry(int position) const;

   /** @throw if position < 1 or position > getLength(). */
   void replace(int position, const ItemType &newEntry);

   LinkedIterator<ItemType> begin();
   LinkedIterator<ItemType> end();
}; // end LinkedList

#include "LinkedListwIterator.tpp"
#endif
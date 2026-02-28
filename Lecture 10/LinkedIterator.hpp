//   Created by Frank M. Carrano and Timothy M. Henry.
//   Copyright (c) 2025 Pearson Education, Hoboken, New Jersey.

/** @file LinkedIterator.hpp */

#ifndef _LINKED_ITERATOR
#define _LINKED_ITERATOR

#include <iterator>
#include "Node.hpp"

// Forward declaration
template <class ItemType>
class LinkedListwIterator;

template <class ItemType>
class LinkedIterator : public std::iterator<std::input_iterator_tag, ItemType>
{
private:
   // ADT associated with iterator
   LinkedListwIterator<ItemType> *containerPtr;

   // Current location in collection
   Node<ItemType> *currentItemPtr;

public:
   LinkedIterator(LinkedListwIterator<ItemType> *someList,
                  Node<ItemType> *nodePtr);

   /** Dereferencing operator overload.
    @return The item at the position referenced by iterator. */
   const ItemType operator*();

   /** Prefix increment operator overload.
    @return The iterator referencing the next position in the list. */
   LinkedIterator<ItemType> operator++();

   /** Equality operator overload.
    @param LinkedList The iterator for comparison.
    @return True if this iterator references the same list and
       the same position as rightHandSide, false otherwise. */
   bool operator==(const LinkedIterator<ItemType> &rightHandSide) const;

   /** Inequality operator overload.
    @param LinkedList The iterator for comparison.
    @return True if this iterator does not reference the same
       list and the same position as rightHandSide, false otherwise. */
   bool operator!=(const LinkedIterator<ItemType> &rightHandSide) const;
}; // end LinkedIterator

#include "LinkedIterator.tpp"
#endif
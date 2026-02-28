//   Created by Frank M. Carrano and Timothy M. Henry.
//   Copyright (c) 2025 Pearson Education, Hoboken, New Jersey.

/** @file LinkedIterator.hpp */

#include <iostream>
#include "LinkedIterator.hpp"

template <class ItemType>
LinkedIterator<ItemType>::LinkedIterator(LinkedListwIterator<ItemType> *someList,
                                         Node<ItemType> *nodePtr) : containerPtr(someList), currentItemPtr(nodePtr)
{
} // end constructor

template <class ItemType>
const ItemType LinkedIterator<ItemType>::operator*()
{
   // std::cout << "operator * is called" << std::endl;
   return currentItemPtr->getItem();
} // end operator*

template <class ItemType>
LinkedIterator<ItemType> LinkedIterator<ItemType>::operator++()
{
   // std::cout << "operator ++ is called" << std::endl;
   currentItemPtr = currentItemPtr->getNext();
   return *this;
} // end prefix operator++

template <class ItemType>
bool LinkedIterator<ItemType>::operator==(const LinkedIterator<ItemType> &rightHandSide) const
{
   // std::cout << "operator == is called" << std::endl;
   return ((containerPtr == rightHandSide.containerPtr) &&
           (currentItemPtr == rightHandSide.currentItemPtr));
} // end operator==

template <class ItemType>
bool LinkedIterator<ItemType>::operator!=(const LinkedIterator<ItemType> &rightHandSide) const
{
   // std::cout << "operator != is called" << std::endl;
   return (!operator==(rightHandSide));
} // end operator!=
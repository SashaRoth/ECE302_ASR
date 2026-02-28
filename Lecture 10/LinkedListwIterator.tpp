//   Created by Frank M. Carrano and Timothy M. Henry.
//   Copyright (c) 2025 Pearson Education, Hoboken, New Jersey.

/** Implementation file for the class LinkedListwIterator.
 @file LinkedListwIterator.cpp */

#include "LinkedListwIterator.hpp" // Header file
#include <stdexcept>

template <class ItemType>
LinkedListwIterator<ItemType>::LinkedListwIterator() : headPtr(nullptr), itemCount(0)
{
} // end default constructor

template <class ItemType>
LinkedListwIterator<ItemType>::LinkedListwIterator(const LinkedListwIterator<ItemType> &aList) : itemCount(aList.itemCount)
{
   auto origChainPtr = aList.headPtr; // Points to nodes in original chain

   if (origChainPtr == nullptr)
      headPtr = nullptr; // Original list is empty
   else
   {
      // Copy first node
      headPtr = new Node<ItemType>();
      headPtr->setItem(origChainPtr->getItem());

      // Copy remaining nodes
      auto newChainPtr = headPtr;             // Points to last node in new chain
      origChainPtr = origChainPtr->getNext(); // Advance original-chain pointer
      while (origChainPtr != nullptr)
      {
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();

         // Create a new node containing the next item
         auto newNodePtr = new Node<ItemType>(nextItem);

         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr);

         // Advance pointer to new last node
         newChainPtr = newChainPtr->getNext();

         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      } // end while

      newChainPtr->setNext(nullptr); // Flag end of chain
   } // end if
} // end copy constructor

template <class ItemType>
LinkedListwIterator<ItemType>::~LinkedListwIterator()
{
   clear();
} // end destructor

template <class ItemType>
bool LinkedListwIterator<ItemType>::isEmpty() const
{
   return itemCount == 0;
} // end isEmpty

template <class ItemType>
int LinkedListwIterator<ItemType>::getLength() const
{
   return itemCount;
} // end getLength

template <class ItemType>
bool LinkedListwIterator<ItemType>::insert(int newPosition, const ItemType &newEntry)
{
   bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
   if (ableToInsert)
   {
      // Create a new node containing the new entry
      auto newNodePtr = new Node<ItemType>(newEntry);

      // Attach new node to chain
      if (newPosition == 1)
      {
         // Insert new node at beginning of chain
         newNodePtr->setNext(headPtr);
         headPtr = newNodePtr;
      }
      else
      {
         // Find node that will be before new node
         auto prevPtr = getNodeAt(newPosition - 1);

         // Insert new node after node to which prevPtr points
         newNodePtr->setNext(prevPtr->getNext());
         prevPtr->setNext(newNodePtr);
      } // end if

      itemCount++; // Increase count of entries
   } // end if

   return ableToInsert;
} // end insert

template <class ItemType>
bool LinkedListwIterator<ItemType>::remove(int position)
{
   bool ableToRemove = (position >= 1) && (position <= itemCount);
   if (ableToRemove)
   {
      if (position == 1)
      {
         // Remove the first node in the chain
         auto nodeToDelete = headPtr;
         headPtr = headPtr->getNext();
         delete nodeToDelete;
      }
      else
      {
         // Find node that is before the one to delete
         auto prevPtr = getNodeAt(position - 1);

         // Point to node to delete
         auto curPtr = prevPtr->getNext();

         // Disconnect indicated node from chain by connecting the
         // prior node with the one after
         prevPtr->setNext(curPtr->getNext());
         delete curPtr; // Delete the removed node
      } // end if

      itemCount--; // Decrease count of entries

   } // end if

   return ableToRemove;
} // end remove

template <class ItemType>
void LinkedListwIterator<ItemType>::clear()
{
   while (!isEmpty())
   {
      remove(1);
   }
} // end clear

template <class ItemType>
ItemType LinkedListwIterator<ItemType>::getEntry(int position) const
{
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
   {
      auto nodePtr = getNodeAt(position);
      return nodePtr->getItem();
   }
   else
   {
      throw std::out_of_range("getEntry() called with an invalid position.");
   } // end if
} // end getEntry

template <class ItemType>
void LinkedListwIterator<ItemType>::replace(int position, const ItemType &newEntry)
{
   // Enforce precondition
   bool ableToSet = (position >= 1) && (position <= itemCount);
   if (ableToSet)
   {
      auto nodePtr = getNodeAt(position);
      nodePtr->setItem(newEntry);
   }
   else
   {
      // auto gives const string literal
      throw std::out_of_range("replace() called with an invalid position.");
   } // end if
} // end replace

template <class ItemType>
Node<ItemType> *LinkedListwIterator<ItemType>::getNodeAt(int position) const
{
   // Debugging check of precondition
   assert((position >= 1) && (position <= itemCount));

   // Count from the beginning of the chain
   auto curPtr = headPtr;
   for (int skip = 1; skip < position; skip++)
   {
      curPtr = curPtr->getNext();
   }

   return curPtr;
} // end getNodeAt

template <class ItemType>
LinkedIterator<ItemType> LinkedListwIterator<ItemType>::begin()
{
   return LinkedIterator<ItemType>(this, headPtr);
} // end begin()

template <class ItemType>
LinkedIterator<ItemType> LinkedListwIterator<ItemType>::end()
{
   return LinkedIterator<ItemType>(this, nullptr);
} // end end()
//  End of implementation file.
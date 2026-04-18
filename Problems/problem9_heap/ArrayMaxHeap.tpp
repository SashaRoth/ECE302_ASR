#include <cmath>
#include <stdexcept>
#include "ArrayMaxHeap.hpp"

// -----------------------------------------------------------------------
// Private helpers
// -----------------------------------------------------------------------

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 1;
}

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 2;
}

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(const int nodeIndex) const
{
   return (nodeIndex - 1) / 2;
}

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(const int nodeIndex) const
{
   return (getLeftChildIndex(nodeIndex) >= itemCount);
}

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
   // Start at the last parent and rebuild up to the root
   for (int index = itemCount / 2 - 1; index >= 0; index--)
      heapRebuild(index);
}

template <typename ItemType>
void ArrayMaxHeap<ItemType>::swapNodes(int node1, int node2)
{
   ItemType temp = items[node1];
   items[node1] = items[node2];
   items[node2] = temp;
}

// -----------------------------------------------------------------------
// Public methods
// -----------------------------------------------------------------------

template <typename ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap() : itemCount(0)
{
}

template <typename ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap(const ItemType someArray[], const int arraySize)
    : itemCount(arraySize)
{
   for(int i = 0; i < arraySize; i++){
      for(int j = i + 1; j < arraySize; j++){
         if(someArray[i] == someArray[j]){
            itemCount = 0; // leave heap empty if throwing error
            throw std::invalid_argument("Array cannot contain duplicate values");
         }
      }
   }
   for (int i = 0; i < itemCount; i++)
      items[i] = someArray[i];
   heapCreate();
}

template <typename ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{
   clear();
}

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const noexcept
{
   return itemCount == 0;
}

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const noexcept
{
   return ceil(log2(itemCount + 1));
}

template <typename ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const noexcept
{
   return itemCount;
}

template <typename ItemType>
void ArrayMaxHeap<ItemType>::clear() noexcept
{
   itemCount = 0;
}

// -----------------------------------------------------------------------
// TODO (private and public methods)
// -----------------------------------------------------------------------

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(const int subTreeNodeIndex)
{
   if (!isLeaf(subTreeNodeIndex))
   {
      int largerChildIndex;
      int indexR = getRightChildIndex(subTreeNodeIndex);
      int indexL = getLeftChildIndex(subTreeNodeIndex);
      if(indexR >= itemCount){
         largerChildIndex = indexL;
      }
      else if(items[indexL] >= items[indexR]){
         largerChildIndex = indexL;
      }
      else{
         largerChildIndex = indexR;
      }

      if(items[subTreeNodeIndex] < items[largerChildIndex]){
         swapNodes(subTreeNodeIndex, largerChildIndex);
         heapRebuild(largerChildIndex);
      }
   }
}

template <typename ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const
{
   if(isEmpty()){
      throw std::out_of_range("Cannot peek empty heap");
   }
   return items[0];
}

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType &newData)
{
   if(getNumberOfNodes() >= DEFAULT_CAPACITY){
      return false;
   }
   for(int i = 0; i < itemCount; i++){
      if(newData == items[i]){
         return false;
      }
   }
   int currIndex = itemCount; //start from first empty slot in array
   int parentIndex = getParentIndex(currIndex);
   itemCount++;
   items[currIndex] = newData;
   
   //bubble up until heap property has been restored, or until newData cannot bubble up further
   while(items[currIndex] > items[parentIndex] && currIndex > 0){ 
      swapNodes(currIndex, parentIndex);
      parentIndex = getParentIndex(parentIndex);
      currIndex = getParentIndex(currIndex);
   }
   return true;
}

template <typename ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
   if(isEmpty()){
      return false;
   }

   items[0] = items[itemCount - 1]; //replace root with last item
   itemCount--;
   
   heapRebuild(0); //restore heap property

   return true;
}

template <typename ItemType>
void ArrayMaxHeap<ItemType>::heapSort(ItemType anArray[], int n)
{
   if(n > DEFAULT_CAPACITY){
      throw std::invalid_argument("Array exceeds heap capacity");
   }
   for(int i = 0; i < n; i++){
      for(int j = i + 1; j < n; j++){
         if(anArray[i] == anArray[j]){
         throw std::invalid_argument("Array cannot contain duplicate values");
      }
    }
   }

   itemCount = n;
   for (int i = 0; i < itemCount; i++) //move array into heap
      items[i] = anArray[i];
   heapCreate(); //maintain heap property

   for(int i = 0; i < n; i++){ //move sorted values back into array
      anArray[i] = peekTop();
      remove();
      heapRebuild(0);
   }
}
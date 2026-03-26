#include "sorted_list.hpp"
#include <stdexcept>
#include <iostream>

template <typename T>
SortedList<T>::SortedList() : List<T>()
{
} // Constructor, completed

template <typename T>
SortedList<T>::SortedList(List<T> unsorted_list)
{
  for(int i = 1; i <= unsorted_list.getLength(); i++) {
    insert(unsorted_list.getEntry(i)); // insert each item from the unsorted list, will be sorted by insert function
  }
}

template <typename T>
SortedList<T>::SortedList(const SortedList<T> &x) : List<T>(x)
{
} // Copy constructor, completed

template <typename T>
SortedList<T> &SortedList<T>::operator=(SortedList<T> x)
{
  List<T>::operator=(x);
  return *this;
} // Copy assignment operator, completed

template <typename T>
SortedList<T>::~SortedList()
{
} // Destructor, completed

template <typename T>
bool SortedList<T>::isEmpty() const noexcept
{
  return List<T>::isEmpty();
} // Base Class function called, completed

template <typename T>
int SortedList<T>::getLength() const noexcept
{
  return List<T>::getLength();
} // Base Class function called, completed

template <typename T>
void SortedList<T>::insert(const T &item)
{
  if((List<T>::getLength() == 0) || (item <= List<T>::getEntry(1))){
      List<T>::insert(1, item); // if list empty or item <= first element, insert at position 1
      return;
    }
  for(int i = 1; i <= List<T>::getLength(); i++){
    if(item <= List<T>::getEntry(i)) {
      List<T>::insert(i, item); // insert item at the correct position to maintain sorted order
      return;
    }
  }
  // If we get here, item is larger than all elements, so append at the end
  //std::cout << "Inserting " << item << " at the end of the list" << std::endl;
  List<T>::insert(List<T>::getLength() + 1, item);
}

template <typename T>
void SortedList<T>::remove(const T &item)
{
  for(int i = 1; i <= List<T>::getLength(); i++) {
    if(List<T>::getEntry(i) == item) {
      List<T>::remove(i); // remove the first occurrence of item
      return;
    }
  }
  throw std::invalid_argument("Item not found: remove"); // item not found
}

template <typename T>
void SortedList<T>::removeAt(int position)
{
  if(isEmpty()){
        throw std::out_of_range("Cannot remove from empty queue");
    }
  List<T>::remove(position); // remove item at position
}

template <typename T>
void SortedList<T>::clear()
{
  List<T>::clear();
} // Base Class function called, completed

template <typename T>
T SortedList<T>::getEntry(int position) const
{
  if(isEmpty()){
    throw std::out_of_range("Cannot peek empty queue");
  }
  return List<T>::getEntry(position);
} // Base Class function called, completed

template <typename T>
int SortedList<T>::getPosition(const T &item)
{
  for(int i = 1; i <= List<T>::getLength(); i++) {
    if(List<T>::getEntry(i) == item) {
      return i; // return the position of the first occurrence of item
    }
  }
  throw std::invalid_argument("Item not found: getPosition"); // item not found
}
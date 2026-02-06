#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList()
{
  size = 0;
  data = new T[0]; // initial capacity of 0
}

template <typename T>
ArrayList<T>::~ArrayList()
{
  delete[] data;
  data = nullptr;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList &rhs)
{
  size = rhs.getLength(); // copy size
  data = new T[size];        // allocate new list with other list's size
  for (int i = 0; i < rhs.size; i++)
  {
    data[i] = rhs.data[i]; // copy data from other list element-by-element
  }
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(ArrayList rhs)
{
  swap(rhs);      // swap current object with copy
  return *this; // return current object by reference, copy is destroyed
}

template <typename T>
void ArrayList<T>::swap(ArrayList &rhs)
{
  T *tmp_data = new T[size];
  tmp_data = data; // swap data pointers
  data = rhs.data;
  rhs.data = tmp_data;

  int tmp_size = size; // swap sizes
  size = rhs.size;
  rhs.size = tmp_size;
}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept
{
  if (size == 0)
    return true;
  return false;
}

template <typename T>
int ArrayList<T>::getLength() const noexcept
{
  return size;
}

template <typename T>
bool ArrayList<T>::insert(int position, const T &item)
{
  if(position < 1 || position > size + 1) {
    return false; // invalid position
  }

  T *temp = new T[size + 1]; // create new array with increased size
  for(int i = 0; i < size + 1; i++) {
    if(i == position - 1) {
      temp[i] = item; // insert new item at position
    } else if(i > position - 1) {
      temp[i] = data[i - 1]; // shift elements right after position
    } else{
    temp[i] = data[i]; // copy elements before position
    }
  }

  delete[] data; // free old array
  data = temp; // point to new array
  size++; // increase size
  return true;
}

template <typename T>
bool ArrayList<T>::remove(int position)
{
  if(position < 1 || position > size) {
    return false; // invalid position
  }

  T *temp = new T[size - 1];
  for(int i = position - 1; i < size - 1; i++) {
    temp[i] = data[i + 1]; // shift elements left to fill gap
  }
  
  delete[] data; // free old array
  data = temp; // point to new array
  size--; // decrease size
  return true;
}

template <typename T>
void ArrayList<T>::clear()
{
  delete[] data; // free old array
  data = new T[0]; // allocate new empty array
  size = 0; // reset size to zero
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
T ArrayList<T>::getEntry(int position) const
{
  if(position < 1 || position > size){
    throw std::out_of_range("Invalid index");
  }
  return data[position - 1]; // return the item at the specified position
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
void ArrayList<T>::setEntry(int position, const T &newValue)
{
  if(position < 1 || position > size){
    throw std::out_of_range("Invalid index");
  }
  data[position - 1] = newValue; // set the value at the specified position
}

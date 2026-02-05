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
  current_size = rhs.getLength(); // copy size
  data = new T[current_size];        // allocate new list with other list's size
  for (uint32_t i = 0; i < rhs.size; i++)
  {
    data[i] = rhs.data[i]; // copy data from other list element-by-element
  }
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(ArrayList rhs)
{
  swap(x);      // swap current object with copy
  return *this; // return current object by reference, copy is destroyed
}

template <typename T>
void ArrayList<T>::swap(ArrayList &rhs)
{
   T *tmp_data = data; // swap data pointers
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
  // TODO
  return false;
}

template <typename T>
bool ArrayList<T>::remove(int position)
{
  for(int i = position - 1; i < size - 1; i++) {
    data[i] = data[i + 1]; // shift elements left to fill gap
  })
  return false;
}

template <typename T>
void ArrayList<T>::clear()
{
  for(int i = 0; i < size; i++) {
    data[i] = T(); // reset each element to default value
  }
  size = 0; // reset size to zero
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
T ArrayList<T>::getEntry(int position) const
{
  return data[position - 1]; // return the item at the specified position
}

// throw std::out_of_range if position < 1 or position > getLength()
template <typename T>
void ArrayList<T>::setEntry(int position, const T &newValue)
{
  data[position - 1] = newValue; // set the value at the specified position
}
